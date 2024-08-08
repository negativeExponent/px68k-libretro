px68k-libretro

forked from https://github.com/hissorii/px68k
backported c68k core from https://github.com/kenyahiro/px68k/ 
(fork of https://github.com/hissorii/px68k using recent c68k yabause core to support X64 build)

All credit goes to hissorii ( and kenyahiro for updating c68k core) .

Changes (in no particular order):
- main audio sample type changed to int16 from uint8
- translated most japanese comments to english with google translate
- change most files to utf-8
- audio fixes and related
- new x68k cpu interfaces for all m68k cores
- get rid of DWORD writes
- revamp cpu memory read/write routines
- Implement savestate support (wip)
- Fix bug that causes raft in Akumaju Dracula to disappear in stage 2 (c68k).
- Fix crash bug on Etoile Princess (probably others as well) (buffer-overflow).
- Fix crash bug on Star Mobile (buffer-overflow).
- Fix disk image corruption on unknown disk types.
- Fix resizing of disk images when using .DIM image format.
- Fix crash bug when using .D88 image format.
- Prevent unneeded saves when no new data is writting to disk for FDD images.
- Replace IO routines with libretro VFS.
- Support for MIDI through libretro api midi interface (winmm, fluidsynth, timidity, munt, etc).
- Prevent crash due to missing path-ending "slash" to StartDir in config file.
- Fix compatibility when booting using iplrom30.bin (c68k).
- Add SRAM Clean option to px68k in-game menu. Clearing sram is a convinient way to fix issues like unable to boot. (F12)
- Fix shutdown/quit command in px68k menu.
- Fix SASI-HD unable to boot after sram clear in some iplromxx files.
- Update core options.
- Support for relative path for m3u and cmd.
- Misc code cleanups and other fixes i may have forgot.
- CPU Bus handling support (minimal, mostly enough for MIDI to be disabled and some other cases)

How to use :

First create a 'keropi' folder in retroarch system directory.
put the x68000 bios files in.

Then launch emulator with some content (dim|zip|img|d88|88d|hdm|dup|2hd|xdf|hdf)
F12 or joypad L2 to enter menu.
Touroku key via ScrollLock key or Joypad R2 to enable MIDI music when preseed in Wolfteam games.


You can launch content with:

- retroarch -L px68k_libretro.so ./content.hdf

- retroarch -L px68k_libretro.so ./content.xdf

- retroarch -L px68k_libretro.so ./content.cmd
 (cmdfile is a text file contening cmd like "px68k /somewhere/software/x68000/content1.dim /somewhere/software/x68000/content2.dim")

- retroarch -L sdlpx68k_libretro.so "px68k /somewhere/software/x68000/content1.dim /somewhere/software/x68000/content2.dim"

- load retroarch , then load core and content from RA menu.

[original README.MD](README-JP.MD)
