#ifndef LIBRETRO_CORE_OPTIONS_INTL_H__
#define LIBRETRO_CORE_OPTIONS_INTL_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* https://support.microsoft.com/en-us/kb/980263 */
#pragma execution_character_set("utf-8")
#pragma warning(disable:4566)
#endif

#include <libretro.h>

/*
 ********************************
 * VERSION: 2.0
 ********************************
 *
 * - 2.0: Add support for core options v2 interface
 * - 1.3: Move translations to libretro_core_options_intl.h
 *        - libretro_core_options_intl.h includes BOM and utf-8
 *          fix for MSVC 2010-2013
 *        - Added HAVE_NO_LANGEXTRA flag to disable translations
 *          on platforms/compilers without BOM support
 * - 1.2: Use core options v1 interface when
 *        RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION is >= 1
 *        (previously required RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION == 1)
 * - 1.1: Support generation of core options v0 retro_core_option_value
 *        arrays containing options with a single value
 * - 1.0: First commit
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 ********************************
 * Core Option Definitions
 ********************************
*/

/* RETRO_LANGUAGE_JAPANESE */

/* RETRO_LANGUAGE_FRENCH */

/* needs to be translated */
struct retro_core_option_v2_category option_cats_fr[] = {
   {
      "system",
      "System",
      "Change emulated hardware settings."
   },
   {
      "audio",
      "Audio",
      "Change sound volumes and midi output type."
   },
   {
      "input",
      "Input",
      "Change controller types and button mapping."
   },
   {
      "media",
      "Media",
      "Change floppy disk media swapping options."
   },
   {
      "advanced",
      "Advanced",
      "Change system-related advanced options for performance or aesthetics."
   },

   { NULL, NULL, NULL },
};

struct retro_core_option_v2_definition option_defs_fr[] = {
   {
      "px68k_menufontsize",
      "Taille de la police du menu",
      NULL,
	  NULL,
	  NULL,
	  "system",
      {
         { "normale", NULL },
         { "grande",  NULL },
         { NULL,     NULL },
      },
      "normale"
   },
   {
      "px68k_cpuspeed",
      "Vitesse du CPU",
	  NULL,
      "Configurez la vitesse du processeur. Peut être utilisé pour ralentir les jeux trop rapides ou pour accélérer les temps de chargement des disquettes.",
	  NULL,
	  "system",
      {
         { "10Mhz",       NULL },
         { "16Mhz",       NULL },
         { "20Mhz",       NULL },
         { "25Mhz",       NULL },
         { "33Mhz",       NULL },
         { "40Mhz",       NULL },
         { "50Mhz",       NULL },
         { "66Mhz (OC)",  NULL },
         { "100Mhz (OC)", NULL },
         { NULL,          NULL },
      },
      "10Mhz"
   },
   {
      "px68k_ramsize",
      "Taille de la RAM (Redémare)",
	  NULL,
      "Définit la quantité de RAM à utiliser par le système.",
	  NULL,
	  "system",
      {
         { "1MB",  NULL },
         { "2MB",  NULL },
         { "3MB",  NULL },
         { "4MB",  NULL },
         { "5MB",  NULL },
         { "6MB",  NULL },
         { "7MB",  NULL },
         { "8MB",  NULL },
         { "9MB",  NULL },
         { "10MB", NULL },
         { "11MB", NULL },
         { "12MB", NULL },
         { NULL,   NULL },
      },
      "2MB"
   },
   {
      "px68k_analog",
      "Utiliser l'Analogique",
      NULL,
	  NULL,
	  NULL,
	  "input",
      {
         { "désactivé", NULL },
         { "activé",  NULL },
         { NULL,       NULL },
      },
      "désactivé"
   },
   {
      "px68k_joytype1",
      "Type de Manette du J1",
	  NULL,
      "Défini le type de manette du joueur 1.",
	  NULL,
	  "input",
      {
         { "Défaut (2 Boutons)",  NULL },
         { "CPSF-MD (8 Boutons)",  NULL },
         { "CPSF-SFC (8 Boutons)", NULL },
         { NULL,                   NULL },
      },
      "Default (2 Buttons)"
   },
   {
      "px68k_joytype2",
      "Type de Joypad du J2",
	  NULL,
      "Défini le type de manette du joueur 2.",
	  NULL,
	  "input",
      {
         { "Défaut (2 Boutons)",  NULL },
         { "CPSF-MD (8 Boutons)",  NULL },
         { "CPSF-SFC (8 Boutons)", NULL },
         { NULL,                   NULL },
      },
      "Défaut (2 Boutons)"
   },
   {
      "px68k_joy1_select",
      "Mappage de la manette du J1",
	  NULL,
      "Attribue une touche du clavier au bouton SELECT de la manette, car certains jeux utilisent ces touches comme boutons Démarrer ou Insérer une pièce.",
	  NULL,
	  "input",
      {
         { "Défaut", NULL },
         { "XF1",     NULL },
         { "XF2",     NULL },
         { "XF3",     NULL },
         { "XF4",     NULL },
         { "XF5",     NULL },
         { "OPT1",    NULL },
         { "OPT2",    NULL },
         { "F1",      NULL },
         { "F2",      NULL },
         { NULL,      NULL },
      },
      "Défaut"
   },
   {
      "px68k_adpcm_vol",
      "Volume ADPCM",
	  NULL,
      "Règlage du volume du canal audio ADPCM.",
	  NULL,
	  "audio",
      {
         { "0",  NULL },
         { "1",  NULL },
         { "2",  NULL },
         { "3",  NULL },
         { "4",  NULL },
         { "5",  NULL },
         { "6",  NULL },
         { "7",  NULL },
         { "8",  NULL },
         { "9",  NULL },
         { "10", NULL },
         { "11", NULL },
         { "12", NULL },
         { "13", NULL },
         { "14", NULL },
         { "15", NULL },
         { NULL, NULL },
      },
      "15"
   },
   {
      "px68k_opm_vol",
      "Volume OPM",
	  NULL,
      "Règlage du volume du canal audio OPM.",
	  NULL,
	  "audio",
      {
         { "0",  NULL },
         { "1",  NULL },
         { "2",  NULL },
         { "3",  NULL },
         { "4",  NULL },
         { "5",  NULL },
         { "6",  NULL },
         { "7",  NULL },
         { "8",  NULL },
         { "9",  NULL },
         { "10", NULL },
         { "11", NULL },
         { "12", NULL },
         { "13", NULL },
         { "14", NULL },
         { "15", NULL },
         { NULL, NULL },
      },
      "12"
   },
#ifndef NO_MERCURY
   {
      "px68k_mercury_vol",
      "Volume Mercury",
	  NULL,
      "Règlage du volume du canal sonore Mercury.",
	  NULL,
	  "audio",
      {
         { "0",  NULL },
         { "1",  NULL },
         { "2",  NULL },
         { "3",  NULL },
         { "4",  NULL },
         { "5",  NULL },
         { "6",  NULL },
         { "7",  NULL },
         { "8",  NULL },
         { "9",  NULL },
         { "10", NULL },
         { "11", NULL },
         { "12", NULL },
         { "13", NULL },
         { "14", NULL },
         { "15", NULL },
         { NULL, NULL },
      },
      "13"
   },
#endif
   {
      "px68k_disk_drive",
      "Échange de disques sur le lecteur",
	  NULL,
      "Par défaut, l'interface native de RetroArch, d'échange de disque dans le menu, échange le disque dans le lecteur FDD1. Modifiez cette option pour échanger des disques dans le lecteur FDD0.",
	  NULL,
	  "media",
      {
         { "FDD1", NULL },
         { "FDD0", NULL },
         { NULL,   NULL },
      },
      "FDD1"
   },
   {
      "px68k_save_fdd_path",
      "Enregistrer les chemins d'accès aux disques",
	  NULL,
      "Lorsqu'elle est activée, les chemins d'accès aux disques précédemment chargés seront enregistrés pour chaque lecteur, puis chargés automatiquement au démarrage. Lorsqu'elle est désactivé, FDD et HDD commencent à vide.",
	  NULL,
	  "media",
      {
         { "activé",  NULL },
         { "désactivé", NULL },
         { NULL,       NULL },
      },
      "activé"
   },

   /* from PX68K Menu */
   {
      "px68k_joy_mouse",
      "Manette /sourie",
	  NULL,
      "Sélectionner la [sourie] ou la [manette] pour contrôler le pointeur de sourie dans les jeux..",
	  NULL,
	  "input",
      {
         { "Sourie",    NULL},
         { "Manette", NULL}, /* unimplemented yet */
         { NULL,       NULL },
      },
      "Manette"
   },
   {
      "px68k_vbtn_swap",
      "Echange des boutons",
	  NULL,
      "Echange le BOUTON1 et le BOUTON2 quand une manette 2 boutons est sélectionné.",
	  NULL,
	  "input",
      {
         { "BOUTON1 BOUTON2", NULL},
         { "BOUTON2 BOUTON1", NULL},
         { NULL,          NULL },
      },
      "BOUTON1 BOUTON2"
   },
   {
      "px68k_no_wait_mode",
      "Mode sans attente",
	  NULL,
      "Lorsque ce mode est [activé], le cœur s'exécute aussi vite que possible. Cela peut provoquer une désynchronisation audio mais permet une avance rapide. Il est recommandé de définir ce paramètre à [désactivé].",
	  NULL,
	  "advanced",
      {
         { "désactivé", NULL},
         { "activé",  NULL},
         { NULL,       NULL },
      },
      "désactivé"
   },
   {
      "px68k_frameskip",
      "Saut d'images",
	  NULL,
      "Choisissez le nombre d'images à ignorer pour améliorer les performances au détriment de la fluidité visuelle.",
	  NULL,
	  "advanced",
      {
         { "Toutes les images",      NULL },
         { "1/2 image",       NULL },
         { "1/3 image",       NULL },
         { "1/4 image",       NULL },
         { "1/5 image",       NULL },
         { "1/6 image",       NULL },
         { "1/8 image",       NULL },
         { "1/16 image",      NULL },
         { "1/32 image",      NULL },
         { "1/60 image",      NULL },
         { "Auto image Skip", NULL },
         { NULL,   NULL },
      },
      "Toutes les images"
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fr = {
   option_cats_fr,
   option_defs_fr
};

/* RETRO_LANGUAGE_SPANISH */

/* RETRO_LANGUAGE_GERMAN */

/* RETRO_LANGUAGE_ITALIAN */

/* RETRO_LANGUAGE_DUTCH */

/* RETRO_LANGUAGE_PORTUGUESE_BRAZIL */

/* RETRO_LANGUAGE_PORTUGUESE_PORTUGAL */

/* RETRO_LANGUAGE_RUSSIAN */

/* RETRO_LANGUAGE_KOREAN */

/* RETRO_LANGUAGE_CHINESE_TRADITIONAL */

/* RETRO_LANGUAGE_CHINESE_SIMPLIFIED */

/* RETRO_LANGUAGE_ESPERANTO */

/* RETRO_LANGUAGE_POLISH */

/* RETRO_LANGUAGE_VIETNAMESE */

/* RETRO_LANGUAGE_ARABIC */

/* RETRO_LANGUAGE_GREEK */

/* RETRO_LANGUAGE_TURKISH */

/* RETRO_LANGUAGE_SLOVAK */

/* RETRO_LANGUAGE_PERSIAN */

/* RETRO_LANGUAGE_HEBREW */

/* RETRO_LANGUAGE_ASTURIAN */

/* RETRO_LANGUAGE_FINNISH */

#ifdef __cplusplus
}
#endif

#endif
