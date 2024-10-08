
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <libretro.h>
#include <retro_dirent.h>
#include <file/file_path.h>
#include <string/stdstring.h>
#include <streams/file_stream.h>
#include <streams/memory_stream.h>

#include "libretro_core_options.h"

#include "../x11/common.h"

#include "../x11/dswin.h"
#include "../x11/keyboard.h"
#include "../x11/mouse.h"
#include "../x11/prop.h"
#include "../x11/state.h"
#include "../x11/winx68k.h"
#include "../x68k/adpcm.h"
#include "../x68k/fdd.h"
#include "../x68k/opm.h"
#include "../x68k/sram.h"
#include "../x68k/x68kmemory.h"

#include "../x11/joystick.h"

#ifdef HAVE_MERCURY
#include "../x68k/mercury.h"
#endif

#ifdef _WIN32
char slash = '\\';
#else
char slash = '/';
#endif

#define SAMPLERATE (float)Config.SampleRate

#define MODE_HIGH_ACTUAL 55.46 /* floor((10*100*1000^2 / VSYNC_HIGH)) / 100 */
#define MODE_NORM_ACTUAL 61.46 /* floor((10*100*1000^2 / VSYNC_NORM)) / 100 */
#define MODE_HIGH_COMPAT 55.5  /* 31.50 kHz - commonly used  */
#define MODE_NORM_COMPAT 59.94 /* 15.98 kHz - actual value should be ~61.46 fps. this is lowered to
                     * reduced the chances of audio stutters due to mismatch
                     * fps when vsync is used since most monitors are only capable
                     * of upto 60Hz refresh rate. */
enum { MODES_ACTUAL, MODES_COMPAT, MODE_NORM = 0, MODE_HIGH, MODES };
const float fps_table[][MODES] = {
   { MODE_NORM_ACTUAL, MODE_HIGH_ACTUAL },
   { MODE_NORM_COMPAT, MODE_HIGH_COMPAT }
};

static char RPATH[MAX_PATH * 2]; /* stores the full pathname of content file */
char retro_system_conf[1024]; /* dir location for 'keropi' config file */
char base_dir[1024]; /* dir where rom was loaded */

uint8_t Core_Key_State[512];
uint8_t Core_old_Key_State[512];

static bool joypad1, joypad2;

static bool opt_analog;

uint32_t retrow   = FULLSCREEN_WIDTH;
uint32_t retroh   = FULLSCREEN_HEIGHT;
int CHANGEAV = 0; /* 1: update geometry only, 2: reinit */
int VID_MODE = MODE_HIGH; /* what framerate we start in */
static float FRAMERATE;

uint32_t libretro_supports_input_bitmasks      = 0;
static bool libretro_supports_option_categories = 0;

int64_t total_usec                        = -1;

static int16_t soundbuf[1024 * 2];

uint16_t *videoBuffer;

static retro_video_refresh_t video_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_set_rumble_state_t rumble_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_log_printf_t log_cb;
retro_input_state_t input_state_cb;
struct retro_vfs_interface *vfs_interface;

static unsigned no_content;
static int opt_rumble_enabled = 1;
static size_t serialize_size = 0;

int FDD_IsReading = 0;

#define MAX_DISKS 10

typedef enum
{
   FDD0 = 0,
   FDD1 = 1
} disk_drive;

/* .dsk swap support */
struct disk_control_interface_t
{
   unsigned dci_version;               /* disk control interface version, 0 = use old interface */
   unsigned total_images;              /* total number if disk images */
   unsigned index;                     /* currect disk index */
   disk_drive cur_drive;               /* current active drive */
   bool inserted[2];                   /* tray state for FDD0/FDD1, 0 = disk ejected, 1 = disk inserted */
   char path[MAX_DISKS][3072];         /* disk image paths */
   char label[MAX_DISKS][MAX_PATH];    /* disk image base name w/o extension */
   unsigned g_initial_disc;            /* initial disk index */
   char g_initial_disc_path[MAX_PATH]; /* initial disk path */
};

static struct disk_control_interface_t disk;
static struct retro_disk_control_callback dskcb;
static struct retro_disk_control_ext_callback dskcb_ext;

void Error(const char *s)
{
   if (log_cb)
      log_cb(RETRO_LOG_ERROR, "%s", s);
}

static bool file_exists(const char *path)
{
   RFILE *dummy;

   if (!path || !*path)
      return false;
   dummy = filestream_open(path,
      RETRO_VFS_FILE_ACCESS_READ,
      RETRO_VFS_FILE_ACCESS_HINT_NONE);
   if (!dummy)
      return false;
   filestream_close(dummy);
   return true;
}

static bool file_has_valid_extension(const char *path)
{
   char *file_ext = strrchr(path, '.');

   if ((strcasecmp(file_ext, ".d88") == 0) || (strcasecmp(file_ext, ".88d") == 0) ||
       (strcasecmp(file_ext, ".hdm") == 0) || (strcasecmp(file_ext, ".dup") == 0) ||
       (strcasecmp(file_ext, ".2hd") == 0) || (strcasecmp(file_ext, ".dim") == 0) ||
       (strcasecmp(file_ext, ".xdf") == 0) || (strcasecmp(file_ext, ".img") == 0))
      return true;
   return false;
}

static bool file_is_valid(const char *path)
{
   if (string_is_empty(path))
      return false;

   if (!file_exists(path))
   {
      log_cb(RETRO_LOG_ERROR, "File not found '%s'.\n", path);
      return false;
   }

   if (!file_has_valid_extension(path))
   {
      log_cb(RETRO_LOG_ERROR, "File has unsupported file extension '%s'\n", path);
      return false;
   }

   return true;
}


void p6logd(const char *fmt, ...)
{
   va_list args;
   char p6l_buf[256];

   va_start(args, fmt);
   vsprintf(p6l_buf, fmt, args);
   va_end(args);

   if (log_cb)
      log_cb(RETRO_LOG_INFO, "%s", p6l_buf);
}

static bool is_path_absolute(const char *path)
{
   if (string_is_empty(path))
      return false;

   if (path[0] == slash)
      return true;

#ifdef _WIN32
   if ((path[0] >= 'a' && path[0] <= 'z') || (path[0] >= 'A' && path[0] <= 'Z'))
   {
      if (path[1] == ':')
         return true;
   }
#endif
   return false;
}

static void extract_basename(char *buf, const char *path, size_t size)
{
   char *ext;
   const char *base = strrchr(path, '/');

   if (!base)
      base = strrchr(path, '\\');
   if (!base)
      base = path;

   if (*base == '\\' || *base == '/')
      base++;

   strncpy(buf, base, size - 1);
   buf[size - 1] = '\0';

   ext = strrchr(buf, '.');
   if (ext)
      *ext = '\0';
}

static void extract_directory(char *buf, const char *path, size_t size)
{
   char *base = NULL;

   strncpy(buf, path, size - 1);
   buf[size - 1] = '\0';

   base = strrchr(buf, '/');
   if (!base)
      base = strrchr(buf, '\\');

   if (base)
      *base = '\0';
   else
      buf[0] = '\0';
}

/* BEGIN MIDI INTERFACE */
#include "mmsystem.h"
#include "../x68k/midi.h"

static int libretro_supports_midi_output   = 0;
static struct retro_midi_interface midi_cb = { 0 };
static uint64_t midi_write_time = 0;
static midi_interface_t dummy;

midi_interface_t *midi_interface = &dummy;

/* might not be correct but whatever */
static void midi_write(uint8_t msg)
{
   uint64_t current_time = timeGetTime() * 1000;
   uint64_t delta_time;

   if (midi_write_time == 0)
      midi_write_time = current_time;
   delta_time = current_time - midi_write_time;
   midi_write_time = current_time;
   if (delta_time > 0xFFFFFFFF)
      delta_time = 0;

   midi_cb.write(msg, (uint32_t)delta_time);
}

static void libretro_midi_short(uint32_t dwMsg)
{
   if (libretro_supports_midi_output && midi_cb.output_enabled())
   {
      midi_write(dwMsg & 0xff);
      midi_write((dwMsg >> 8) & 0xff);
      midi_write((dwMsg >> 16) & 0xff);
   }
}

static void libretro_midi_long(uint8_t *lpMsg, size_t length)
{
   if (libretro_supports_midi_output && midi_cb.output_enabled())
   {
      unsigned i;

      if (!length) return;
      for (i = 0; i < length; i++)
         midi_write(lpMsg[i]);
   }
}

static int libretro_midi_open(void)
{
   if (libretro_supports_midi_output && midi_cb.output_enabled())
   {
      return 1;
   }

   return 0;
}

static void libretro_midi_close(void)
{
}

static void update_variable_midi_interface(void)
{
   struct retro_variable var;

   var.key   = "px68k_next_midi_output";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "disabled"))
         Config.MIDI_SW = 0;
      else if (!strcmp(var.value, "enabled"))
         Config.MIDI_SW = 1;
   }

   var.key   = "px68k_next_midi_output_type";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "LA"))
         Config.MIDI_Type = 0;
      else if (!strcmp(var.value, "GM"))
         Config.MIDI_Type = 1;
      else if (!strcmp(var.value, "GS"))
         Config.MIDI_Type = 2;
      else if (!strcmp(var.value, "XG"))
         Config.MIDI_Type = 3;
   }
}

static void midi_interface_init(void)
{
   static midi_interface_t midi;

   libretro_supports_midi_output = 0;
   if (environ_cb(RETRO_ENVIRONMENT_GET_MIDI_INTERFACE, &midi_cb))
   {
      libretro_supports_midi_output = 1;

      midi.Open = libretro_midi_open;
      midi.Close = libretro_midi_close;
      midi.SendShort = libretro_midi_short;
      midi.SendLong = libretro_midi_long;

      midi_interface = &midi;
   }
}

/* END OF MIDI INTERFACE */

static void update_variable_disk_drive_swap(void)
{
   struct retro_variable var = { "px68k_next_disk_drive", NULL };

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (strcmp(var.value, "FDD0") == 0)
         disk.cur_drive = FDD0;
      else
         disk.cur_drive = FDD1;
   }
}

static bool set_eject_state(bool ejected)
{
   if (disk.index == disk.total_images)
      return true;

   if (ejected)
   {
      FDD_EjectFD(disk.cur_drive);
      Config.FDDImage[disk.cur_drive][0] = '\0';
   }
   else
   {
      strcpy(Config.FDDImage[disk.cur_drive], disk.path[disk.index]);
      FDD_SetFD(disk.cur_drive, Config.FDDImage[disk.cur_drive], 0);
   }
   disk.inserted[disk.cur_drive] = !ejected;
   return true;
}

static bool get_eject_state(void)
{
   update_variable_disk_drive_swap();
   return !disk.inserted[disk.cur_drive];
}

static unsigned get_image_index(void) { return disk.index; }
static unsigned get_num_images(void) { return disk.total_images; }

static bool set_image_index(unsigned index)
{
   disk.index = index;
   return true;
}

static bool add_image_index(void)
{
   if (disk.total_images >= MAX_DISKS)
      return false;

   disk.total_images++;
   return true;
}

static bool replace_image_index(unsigned index, const struct retro_game_info *info)
{
   char image[MAX_PATH];
   extract_basename(image, info->path, sizeof(image));
   strcpy(disk.path[index], info->path);
   strcpy(disk.label[index], image);
   return true;
}

static bool disk_get_image_path(unsigned index, char *path, size_t len)
{
   if (len < 1)
      return false;

   if (index < disk.total_images)
   {
      if (!string_is_empty(disk.path[index]))
      {
         strncpy(path, disk.path[index], len);
         return true;
      }
   }

   return false;
}

static bool disk_get_image_label(unsigned index, char *label, size_t len)
{
   if (len < 1)
      return false;

   if (index < disk.total_images)
   {
      if (!string_is_empty(disk.label[index]))
      {
         strncpy(label, disk.label[index], len);
         return true;
      }
   }

   return false;
}

static void attach_disk_swap_interface(void)
{
   dskcb.set_eject_state     = set_eject_state;
   dskcb.get_eject_state     = get_eject_state;
   dskcb.set_image_index     = set_image_index;
   dskcb.get_image_index     = get_image_index;
   dskcb.get_num_images      = get_num_images;
   dskcb.add_image_index     = add_image_index;
   dskcb.replace_image_index = replace_image_index;

   environ_cb(RETRO_ENVIRONMENT_SET_DISK_CONTROL_INTERFACE, &dskcb);
}

static void attach_disk_swap_interface_ext(void)
{
   dskcb_ext.set_eject_state     = set_eject_state;
   dskcb_ext.get_eject_state     = get_eject_state;
   dskcb_ext.set_image_index     = set_image_index;
   dskcb_ext.get_image_index     = get_image_index;
   dskcb_ext.get_num_images      = get_num_images;
   dskcb_ext.add_image_index     = add_image_index;
   dskcb_ext.replace_image_index = replace_image_index;
   dskcb_ext.set_initial_image   = NULL;
   dskcb_ext.get_image_path      = disk_get_image_path;
   dskcb_ext.get_image_label     = disk_get_image_label;

   environ_cb(RETRO_ENVIRONMENT_SET_DISK_CONTROL_EXT_INTERFACE, &dskcb_ext);
}

static void disk_swap_interface_init(void)
{
   unsigned i;

   disk.dci_version  = 0;
   disk.total_images = 0;
   disk.index        = 0;
   disk.cur_drive    = FDD1;
   disk.inserted[0]  = false;
   disk.inserted[1]  = false;

   disk.g_initial_disc         = 0;
   disk.g_initial_disc_path[0] = '\0';

   for (i = 0; i < MAX_DISKS; i++)
   {
      disk.path[i][0]  = '\0';
      disk.label[i][0] = '\0';
   }

   if (environ_cb(RETRO_ENVIRONMENT_GET_DISK_CONTROL_INTERFACE_VERSION, &disk.dci_version) && (disk.dci_version >= 1))
      attach_disk_swap_interface_ext();
   else
      attach_disk_swap_interface();
}
/* end .dsk swap support */

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb = cb; }
void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }
void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

/* Args for experimental_cmdline */
static char ARGUV[64][2048];
static unsigned char ARGUC = 0;

/* Args for Core */
static char XARGV[64][2048];
static const char *xargv_cmd[64];
static int PARAMCOUNT = 0;

static char CMDFILE[512];

#ifdef DEBUG
static int isM3U = 0;
#endif

static int loadcmdfile(char *argv)
{
   int res = 0;

   RFILE *fp;

   fp = filestream_open(argv,
      RETRO_VFS_FILE_ACCESS_READ,
      RETRO_VFS_FILE_ACCESS_HINT_NONE);
   if (fp != NULL)
   {
      if (filestream_gets(fp, CMDFILE, 512) != NULL)
         res = 1;
      filestream_close(fp);
   }

   return res;
}


static bool read_m3u(const char *file)
{
   unsigned index = 0;
   char name[2048];
   char line[1024];
   unsigned i;
   RFILE *f;

   f = filestream_open(file,
      RETRO_VFS_FILE_ACCESS_READ,
      RETRO_VFS_FILE_ACCESS_HINT_NONE);
   if (!f)
      return false;

   while (filestream_gets(f, line, sizeof(line)) && index < sizeof(disk.path) / sizeof(disk.path[0]))
   {
      char *carriage_return;
      char *newline;

      if (line[0] == '#')
         continue;

      carriage_return = strchr(line, '\r');
      if (carriage_return)
         *carriage_return = '\0';

      newline = strchr(line, '\n');
      if (newline)
         *newline = '\0';

      /* Remove any beginning and ending quotes as these can cause issues when feeding the paths into command line
       * later */
      if (line[0] == '"')
         memmove(line, line + 1, strlen(line));

      if (line[strlen(line) - 1] == '"')
         line[strlen(line) - 1] = '\0';

      if (line[0] != '\0')
      {
         char image_label[3072];
         char *custom_label;
         size_t len = 0;

         if (is_path_absolute(line))
            strncpy(name, line, sizeof(name) - 1);
         else
            sprintf(name, "%s%c%s", base_dir, slash, line);

         custom_label = strchr(name, '|');
         if (custom_label)
         {
            /* get disk path */
            len = custom_label + 1 - name;
            strncpy(disk.path[index], name, len - 1);

            /* get custom label */
            custom_label++;
            strncpy(disk.label[index], custom_label, sizeof(disk.label[index]));
         }
         else
         {
            /* copy path */
            strncpy(disk.path[index], name, sizeof(disk.path[index]) - 1);

            /* extract base name from path for labels */
            extract_basename(image_label, name, sizeof(image_label));
            strncpy(disk.label[index], image_label, sizeof(disk.label[index]));
         }

         index++;
      }
   }

   disk.total_images = index;
   filestream_close(f);

   for (i = 0; i < index; i++)
   {
      /* verify that file exists */
      if (!file_is_valid(disk.path[i]))
         return false;
   }

   return (disk.total_images != 0);
}

static void Add_Option(const char *option)
{
   static int first = 0;

   if (first == 0)
   {
      PARAMCOUNT = 0;
      first++;
   }

   sprintf(XARGV[PARAMCOUNT++], "%s", option);
}


static void parse_cmdline(const char *argv)
{
   char *p, *p2, *start_of_word = 0;
   int c, c2;
   static char buffer[512 * 4];
   enum states { DULL, IN_WORD, IN_STRING } state = DULL;

   strcpy(buffer, argv);
   strcat(buffer, " \0");

   for (p = buffer; *p != '\0'; p++)
   {
      c = (unsigned char)*p; /* convert to unsigned char for is* functions */
      switch (state)
      {
      case DULL:          /* not in a word, not in a double quoted string */
         if (isspace(c)) /* still not in a word, so ignore this char */
            continue;
         /* not a space -- if it's a double quote we go to IN_STRING, else to IN_WORD */
         if (c == '"')
         {
            state         = IN_STRING;
            start_of_word = p + 1; /* word starts at *next* char, not this one */
            continue;
         }
         state         = IN_WORD;
         start_of_word = p; /* word starts here */
         continue;
      case IN_STRING:
         /* we're in a double quoted string, so keep going until we hit a close " */
         if (c == '"')
         {
            /* word goes from start_of_word to p-1 */
            /* ... do something with the word ... */
            for (c2 = 0, p2 = start_of_word; p2 < p; p2++, c2++)
               ARGUV[ARGUC][c2] = (unsigned char)*p2;

            ARGUC++;

            state = DULL; /* back to "not in word, not in string" state */
         }
         continue; /* either still IN_STRING or we handled the end above */
      case IN_WORD:
         /* we're in a word, so keep going until we get to a space */
         if (isspace(c))
         {
            /* word goes from start_of_word to p-1 */
            /* ... do something with the word ... */
            for (c2 = 0, p2 = start_of_word; p2 < p; p2++, c2++)
               ARGUV[ARGUC][c2] = (unsigned char)*p2;

            ARGUC++;

            state = DULL; /* back to "not in word, not in string" state */
         }
         continue; /* either still IN_WORD or we handled the end above */
      }
   }
}

static int load_file_cmd(const char *argv)
{
   int i;
   int res = loadcmdfile((char *)argv);

   if (!res)
   {
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "%s\n", "[libretro]: failed to read cmd file ...");
      return 0;
   }

   parse_cmdline(CMDFILE);

   /* handle relative paths, append content dir if needed */
   for (i = 1; i < ARGUC; i++)
   {
      if (!is_path_absolute(ARGUV[i]))
      {
         char tmp[2048] = { 0 };
         strcpy(tmp, ARGUV[i]);
         ARGUV[i][0] = '\0';
         sprintf(ARGUV[i], "%s%c%s", base_dir, slash, tmp);
      }

      /* verify that file exists */
      if (!file_is_valid(ARGUV[i]))
         return 0;
   }

   return 1;
}

static int load_file_m3u(const char *argv)
{
   if (!read_m3u((char *)argv))
   {
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "%s\n", "[libretro]: failed to read m3u file ...");
      return 0;
   }

   if (disk.total_images > 1)
   {
      sprintf((char *)RPATH, "%s \"%s\" \"%s\"", "px68k", disk.path[0], disk.path[1]);
      disk.inserted[1] = true;
   }
   else
      sprintf((char *)RPATH, "%s \"%s\"", "px68k", disk.path[0]);

   disk.inserted[0] = true;

#ifdef DEBUG
   isM3U = 1;
#endif

   parse_cmdline(RPATH);

   return 1;
}

static struct retro_input_descriptor inputDescriptors[64];
static struct retro_input_descriptor inputDescriptorsP1[] = {
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Right" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "R2" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "L2 - Menu" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "R3" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L3, "L3" },
};
static struct retro_input_descriptor inputDescriptorsP2[] = {
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Right" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "R2" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "L2" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "R3" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L3, "L3" },

};

static struct retro_input_descriptor inputDescriptorsNull[] = {
   { 0, 0, 0, 0, NULL }
};

static void retro_set_controller_descriptors()
{
   unsigned i;
   unsigned size = 16;

   for (i = 0; i < (2 * size); i++)
      inputDescriptors[i] = inputDescriptorsNull[0];

   if (joypad1 && joypad2)
   {
      for (i = 0; i < (2 * size); i++)
      {
         if (i < size)
            inputDescriptors[i] = inputDescriptorsP1[i];
         else
            inputDescriptors[i] = inputDescriptorsP2[i - size];
      }
   }
   else if (joypad1 || joypad2)
   {
      for (i = 0; i < size; i++)
      {
         if (joypad1)
            inputDescriptors[i] = inputDescriptorsP1[i];
         else
            inputDescriptors[i] = inputDescriptorsP2[i];
      }
   }
   else
      inputDescriptors[0] = inputDescriptorsNull[0];
   environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, &inputDescriptors);
}

void retro_set_controller_port_device(unsigned port, unsigned device)
{
   if (port >= 2)
      return;

   switch (device)
   {
   case RETRO_DEVICE_JOYPAD:
      if (port == 0)
         joypad1 = true;
      if (port == 1)
         joypad2 = true;
      break;
   case RETRO_DEVICE_KEYBOARD:
      if (port == 0)
         joypad1 = false;
      if (port == 1)
         joypad2 = false;
      break;
   case RETRO_DEVICE_NONE:
      if (port == 0)
         joypad1 = false;
      if (port == 1)
         joypad2 = false;
      break;
   default:
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "[libretro]: Invalid device, setting type to RETRO_DEVICE_JOYPAD ...\n");
      break;
   }
   log_cb(RETRO_LOG_INFO, "Set Controller Device: %d, Port: %d %d %d\n", device, port, joypad1, joypad2);
   retro_set_controller_descriptors();
}

void retro_set_environment(retro_environment_t cb)
{
   int nocontent = 1;
   struct retro_vfs_interface_info vfs_iface_info;
   static const struct retro_controller_description port[] = {
      { "RetroPad", RETRO_DEVICE_JOYPAD },
      { "RetroKeyboard", RETRO_DEVICE_KEYBOARD },
      { 0 },
   };

   static const struct retro_controller_info ports[] = {
      { port, 2 },
      { port, 2 },
      { NULL, 0 },
   };

   environ_cb = cb;

   vfs_iface_info.required_interface_version = 1;
   vfs_iface_info.iface                      = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VFS_INTERFACE, &vfs_iface_info))
   {
      vfs_interface = vfs_iface_info.iface;
      filestream_vfs_init(&vfs_iface_info);
	   path_vfs_init(&vfs_iface_info);
      dirent_vfs_init(&vfs_iface_info);
   }

   cb(RETRO_ENVIRONMENT_SET_CONTROLLER_INFO, (void *)ports);
   cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &nocontent);

   libretro_supports_option_categories = 0;
   libretro_set_core_options(cb,
         &libretro_supports_option_categories);
}

static void update_variables(int running)
{
   int i = 0, snd_opt = 0;
   char key[256]             = { 0 };
   struct retro_variable var = { 0 };

   if (!running)
      update_variable_midi_interface();

   strcpy(key, "px68k_next_joytype");
   var.key = key;
   for (i = 0; i < 2; i++)
   {
      key[strlen("px68k_next_joytype")] = '1' + i;
      var.value                    = NULL;
      if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      {
         int type = Config.joyType[i];

         if (!(strcmp(var.value, "Default (2 Buttons)")))
         {
            Config.joyType[i] = PAD_2BUTTON;
         }
         else if (!(strcmp(var.value, "CPSF-MD (8 Buttons)")))
         {
            Config.joyType[i] = PAD_CPSF_MD;
         }
         else if (!(strcmp(var.value, "CPSF-SFC (8 Buttons)")))
         {
            Config.joyType[i] = PAD_CPSF_SFC;
         }
         else if (!(strcmp(var.value, "CyberStick (Analog)")))
         {
            Config.joyType[i] = PAD_CYBERSTICK_ANALOG;
         }
         else if (!(strcmp(var.value, "CyberStick (Digital)")))
         {
            Config.joyType[i] = PAD_CYBERSTICK_DIGITAL;
         }

         if (type != Config.joyType[i])
         {
            Joystick_Init();
         }
      }
   }

   var.key   = "px68k_next_cpuspeed";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (strcmp(var.value, "10Mhz") == 0)
         Config.cpuClock = 10;
      else if (strcmp(var.value, "16Mhz") == 0)
         Config.cpuClock = 16;
      else if (strcmp(var.value, "20Mhz") == 0)
         Config.cpuClock = 20;
      else if (strcmp(var.value, "25Mhz") == 0)
         Config.cpuClock = 25;
      else if (strcmp(var.value, "33Mhz") == 0)
         Config.cpuClock = 33;
      else if (strcmp(var.value, "40Mhz") == 0)
         Config.cpuClock = 40;
      else if (strcmp(var.value, "50Mhz") == 0)
         Config.cpuClock = 50;
      else if (strcmp(var.value, "66Mhz (OC)") == 0)
         Config.cpuClock = 66;
      else if (strcmp(var.value, "100Mhz (OC)") == 0)
         Config.cpuClock = 100;
   }

   var.key   = "px68k_next_ramsize";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (strcmp(var.value, "1MB") == 0)
         Config.ramSize = 1;
      else if (strcmp(var.value, "2MB") == 0)
         Config.ramSize = 2;
      else if (strcmp(var.value, "4MB") == 0)
         Config.ramSize = 4;
      else if (strcmp(var.value, "6MB") == 0)
         Config.ramSize = 6;
      else if (strcmp(var.value, "8MB") == 0)
         Config.ramSize = 8;
      else if (strcmp(var.value, "12MB") == 0)
         Config.ramSize = 12;
   }

   var.key   = "px68k_next_analog";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "disabled"))
         opt_analog = false;
      if (!strcmp(var.value, "enabled"))
         opt_analog = true;
   }

   var.key   = "px68k_next_adpcm_lowpassfilter";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (strcmp(var.value, "enabled") == 0)
         Config.Sound_LPF = 1;
      else
         Config.Sound_LPF = 0;
   }

   var.key   = "px68k_next_adpcm_vol";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      snd_opt = atoi(var.value);
      if (snd_opt != Config.PCM_VOL)
      {
         Config.PCM_VOL = snd_opt;
         ADPCM_SetVolume((uint8_t)Config.PCM_VOL);
      }
   }

   var.key   = "px68k_next_opm_vol";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      snd_opt = atoi(var.value);
      if (snd_opt != Config.OPM_VOL)
      {
         Config.OPM_VOL = snd_opt;
         OPM_SetVolume((uint8_t)Config.OPM_VOL);
      }
   }

#ifdef HAVE_MERCURY
   var.key   = "px68k_next_mercury_vol";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      snd_opt = atoi(var.value);
      if (snd_opt != Config.MCR_VOL)
      {
         Config.MCR_VOL = snd_opt;
         Mcry_SetVolume((uint8_t)Config.MCR_VOL);
      }
   }
#endif

   update_variable_disk_drive_swap();

   var.key   = "px68k_next_menufontsize";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (strcmp(var.value, "normal") == 0)
         Config.menuSize = 0;
      else
         Config.menuSize = 1;
   }

   var.key   = "px68k_next_joy1_select";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "XF1"))
         Config.P1SelectMap = KBD_XF1;
      else if (!strcmp(var.value, "XF2"))
         Config.P1SelectMap = KBD_XF2;
      else if (!strcmp(var.value, "XF3"))
         Config.P1SelectMap = KBD_XF3;
      else if (!strcmp(var.value, "XF4"))
         Config.P1SelectMap = KBD_XF4;
      else if (!strcmp(var.value, "XF5"))
         Config.P1SelectMap = KBD_XF5;
      else if (!strcmp(var.value, "F1"))
         Config.P1SelectMap = KBD_F1;
      else if (!strcmp(var.value, "F2"))
         Config.P1SelectMap = KBD_F2;
      else if (!strcmp(var.value, "OPT1"))
         Config.P1SelectMap = KBD_OPT1;
      else if (!strcmp(var.value, "OPT2"))
         Config.P1SelectMap = KBD_OPT2;
      else
         Config.P1SelectMap = 0;
   }

   var.key   = "px68k_next_save_fdd_path";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "disabled"))
         Config.saveFDDPath = 0;
      if (!strcmp(var.value, "enabled"))
         Config.saveFDDPath = 1;
   }

   var.key   = "px68k_next_save_hdd_path";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "disabled"))
         Config.saveHDDPath = 0;
      if (!strcmp(var.value, "enabled"))
         Config.saveHDDPath = 1;
   }

   var.key   = "px68k_next_rumble_on_disk_read";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "disabled"))
         opt_rumble_enabled = 0;
      if (!strcmp(var.value, "enabled"))
         opt_rumble_enabled = 1;
   }

   /* PX68K Menu */

   var.key   = "px68k_next_joy_mouse";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      int value = 0;
      if (!strcmp(var.value, "Joystick"))
         value = 0;
      else if (!strcmp(var.value, "Mouse"))
         value = 1;

      Config.JoyOrMouse = value;
      Mouse_StartCapture(value == 1);
   }

   var.key   = "px68k_next_vbtn_swap";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "TRIG1 TRIG2"))
         Config.VbtnSwap = 0;
      else if (!strcmp(var.value, "TRIG2 TRIG1"))
         Config.VbtnSwap = 1;
   }

   var.key   = "px68k_next_no_wait_mode";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "disabled"))
         Config.NoWaitMode = 0;
      else if (!strcmp(var.value, "enabled"))
         Config.NoWaitMode = 1;
   }

   var.key   = "px68k_next_frameskip";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "Auto Frame Skip"))
         Config.FrameRate = 7;
      else if (!strcmp(var.value, "1/2 Frame"))
         Config.FrameRate = 2;
      else if (!strcmp(var.value, "1/3 Frame"))
         Config.FrameRate = 3;
      else if (!strcmp(var.value, "1/4 Frame"))
         Config.FrameRate = 4;
      else if (!strcmp(var.value, "1/5 Frame"))
         Config.FrameRate = 5;
      else if (!strcmp(var.value, "1/6 Frame"))
         Config.FrameRate = 6;
      else if (!strcmp(var.value, "1/8 Frame"))
         Config.FrameRate = 8;
      else if (!strcmp(var.value, "1/16 Frame"))
         Config.FrameRate = 16;
      else if (!strcmp(var.value, "1/32 Frame"))
         Config.FrameRate = 32;
      else if (!strcmp(var.value, "1/60 Frame"))
         Config.FrameRate = 60;
      else if (!strcmp(var.value, "Full Frame"))
         Config.FrameRate = 1;
   }

   var.key   = "px68k_next_adjust_frame_rates";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      int temp = Config.AdjustFrameRates;
      if (!strcmp(var.value, "disabled"))
         Config.AdjustFrameRates = 0;
      else if (!strcmp(var.value, "enabled"))
         Config.AdjustFrameRates = 1;

      if (running && Config.AdjustFrameRates != temp)
      {
         CHANGEAV = 2;
      }
   }

   var.key   = "px68k_next_audio_desync_hack";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (!strcmp(var.value, "disabled"))
         Config.AudioDesyncHack = 0;
      else if (!strcmp(var.value, "enabled"))
         Config.AudioDesyncHack = 1;
   }
}

/************************************
 * libretro implementation
 ************************************/

size_t retro_serialize_size(void) {
	return STATE_SIZE;
}

bool retro_serialize(void *data, size_t size) {
   if (size != STATE_SIZE) return false;
	return PX68K_SaveStateMem(data);
}

bool retro_unserialize(const void *data, size_t size) {
   if (size != STATE_SIZE) return false;
	return PX68K_LoadStateMem(data);
}

void retro_cheat_reset(void) { }
void retro_cheat_set(unsigned index, bool enabled, const char *code) { }
bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) { return false; }
void retro_unload_game(void) { }
unsigned retro_get_region(void) { return RETRO_REGION_NTSC; }
unsigned retro_api_version(void) { return RETRO_API_VERSION; }

static void frame_time_cb(retro_usec_t usec)
{
   total_usec += usec;
   /* -1 is reserved as an error code for unavailable a la stdlib clock() */
   if (total_usec == -1)
      total_usec = 0;
}

static void setup_frame_time_cb(void)
{
   struct retro_frame_time_callback cb;

   cb.callback  = frame_time_cb;
   cb.reference = ceil(1000000.0 / FRAMERATE);
   if (!environ_cb(RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK, &cb))
      total_usec = -1;
   else if (total_usec == -1)
      total_usec = 0;
}

void retro_get_system_info(struct retro_system_info *info)
{
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
#ifndef PX68K_VERSION
#define PX68K_VERSION "0.15+"
#endif
   memset(info, 0, sizeof(*info));
   info->library_name     = "PX68K_Next";
   info->library_version  = PX68K_VERSION GIT_VERSION;
   info->need_fullpath    = true;
   info->valid_extensions = "dim|img|d88|88d|hdm|dup|2hd|xdf|hdf|cmd|m3u";
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
   FRAMERATE = fps_table[Config.AdjustFrameRates][VID_MODE];

   info->geometry.base_width = retrow;
   info->geometry.base_height = retroh;
   info->geometry.max_width = FULLSCREEN_WIDTH;
   info->geometry.max_height = FULLSCREEN_HEIGHT;
   info->geometry.aspect_ratio = 4.0 / 3.0;

   info->timing.fps = FRAMERATE;
   info->timing.sample_rate = SAMPLERATE;

   setup_frame_time_cb();
}

bool retro_load_game(const struct retro_game_info *info)
{
   const char *full_path = 0;

   no_content = 1;
   RPATH[0]   = '\0';

   /* set sane defaults */
   Config.saveFDDPath = 1;
   Config.cpuClock    = 10;
   Config.joyType[0]  = 0;
   Config.joyType[1]  = 0;

   if (info && string_is_empty(info->path) == 0)
   {
      int i = 0;
      int Only1Arg = 0;
      const char *file_ext;

      no_content = 0;
      full_path  = info->path;
      strcpy(RPATH, full_path);
      extract_directory(base_dir, info->path, sizeof(base_dir));

      if (strlen(RPATH) < 4)
         return false;

      file_ext = strrchr(RPATH, '.');

      if (strcasecmp(file_ext, ".cmd") == 0)
      {
         if (!load_file_cmd(RPATH))
            return false;
      }
      else if (strcasecmp(file_ext, ".m3u") == 0)
      {
         if (!load_file_m3u(RPATH))
            return false;
      }

      for (i = 0; i < 64; i++)
         xargv_cmd[i] = NULL;

      Only1Arg = (strcmp(ARGUV[0], "px68k") == 0) ? 0 : 1;

      if (Only1Arg)
      {
         Add_Option("px68k");

         if (strlen(RPATH) >= strlen("hdf"))
         {
            size_t len = strlen(RPATH);
            if (!strcasecmp(&RPATH[len - strlen("hdf")], "hdf"))
               Add_Option("-h");
         }

         Add_Option(RPATH);
      }
      else
      {
         /* Pass all cmdline args */
         for (i = 0; i < ARGUC; i++)
            Add_Option(ARGUV[i]);
      }

      for (i = 0; i < PARAMCOUNT; i++)
         xargv_cmd[i] = (char *)(XARGV[i]);

#ifdef DEBUG
      /* Log successfully loaded paths when loading from m3u */
      if (isM3U)
      {
         p6logd("%s\n", "Loading from an m3u file ...");
         for (i = 0; i < disk.total_images; i++)
            p6logd("index %d: %s\n", i + 1, disk.path[i]);
      }

      /* List arguments to be passed to core */
      p6logd("%s\n", "Parsing arguments ...");
      for (i = 0; i < PARAMCOUNT; i++)
         p6logd("%d : %s\n", i, xargv_cmd[i]);
#endif
   }

   SetConfigDefaults();
   update_variables(0);

   if (!pmain(PARAMCOUNT, (char **)xargv_cmd))
      return false;

   return true;
}

void *retro_get_memory_data(unsigned id)
{
   if (id == RETRO_MEMORY_SYSTEM_RAM)
      return MEM;
   return NULL;
}

size_t retro_get_memory_size(unsigned id)
{
   if (id == RETRO_MEMORY_SYSTEM_RAM)
      return 0xc00000;
   return 0;
}

void retro_init(void)
{
   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;
   struct retro_log_callback log;
   struct retro_rumble_interface rumble;
   const char *system_dir  = NULL;

   serialize_size = 0;

   if (environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
      log_cb = log.log;
   else
      log_cb = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir)
      sprintf(retro_system_conf, "%s%ckeropi", system_dir, slash);

   if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
   {
      fprintf(stderr, "RGB565 is not supported.\n");
      exit(0);
   }

   if (environ_cb(RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE, &rumble) && rumble.set_rumble_state)
      rumble_cb = rumble.set_rumble_state;

   libretro_supports_input_bitmasks = 0;
   if (environ_cb(RETRO_ENVIRONMENT_GET_INPUT_BITMASKS, NULL))
      libretro_supports_input_bitmasks = 1;

   disk_swap_interface_init();
   midi_interface_init();

   memset(Core_Key_State, 0, 512);
   memset(Core_old_Key_State, 0, sizeof(Core_old_Key_State));
}

void retro_deinit(void)
{
   end_loop_retro();

   libretro_supports_input_bitmasks    = 0;
   libretro_supports_midi_output       = 0;
   libretro_supports_option_categories = 0;
}

void retro_reset(void)
{
   WinX68k_Reset(1);
   if (Config.MIDI_SW && Config.MIDI_Reset)
      MIDI_Reset();
}

static void rumbleFrames(void)
{
   static int last_read_state;

   if (!rumble_cb)
      return;

   if (last_read_state != FDD_IsReading)
   {
      if (opt_rumble_enabled && FDD_IsReading)
      {
         rumble_cb(0, RETRO_RUMBLE_STRONG, 0x8000);
         rumble_cb(0, RETRO_RUMBLE_WEAK, 0x800);
      }
      else
      {
         rumble_cb(0, RETRO_RUMBLE_STRONG, 0);
         rumble_cb(0, RETRO_RUMBLE_WEAK, 0);
      }
   }

   last_read_state = FDD_IsReading;
}

void retro_run(void)
{
   bool updated = false;
   int soundbuf_size;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      update_variables(1);

   input_poll_cb();
   exec_app_retro();
   rumbleFrames();

   if (CHANGEAV)
   {
      struct retro_system_av_info system_av_info = {0};
      unsigned cmd = RETRO_ENVIRONMENT_SET_GEOMETRY;
      retro_get_system_av_info(&system_av_info);
      if (CHANGEAV == 2)
      {
         cmd = RETRO_ENVIRONMENT_SET_SYSTEM_AV_INFO;
      }
      environ_cb(cmd, &system_av_info);
      CHANGEAV = 0;
   }

   soundbuf_size = (int)(SAMPLERATE / FRAMERATE);

   if (Config.AudioDesyncHack)
   {
      int nsamples = audio_samples_avail();
      if (nsamples > soundbuf_size)
         audio_samples_discard(nsamples - soundbuf_size);
   }

   raudio_callback(soundbuf, soundbuf_size * sizeof(int16_t));

   audio_batch_cb((const int16_t *)soundbuf, soundbuf_size);
   video_cb(videoBuffer, retrow, retroh, FULLSCREEN_WIDTH << 1);

   if (libretro_supports_midi_output && midi_cb.output_enabled())
      midi_cb.flush();
}

void shutdown_app_retro(void)
{
   environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0);
}
