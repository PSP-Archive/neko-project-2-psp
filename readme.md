Machine translation of the Readme file from the author:
__________________________________________________________

NP2 for PSP ver0.38
                                                                     2011/04/01
                                                           Hissorii

Emulate the NEC PC-9801 series
I tried porting Neko Project II (http://www.yui.ne.jp/np2/) to PSP.
It's omission as it is.
The original source version is ver0.81a.

Taken over from the original transplanter, sakahi
It has been quietly developed since Ver0.34.

0) Disclaimer

  The author is not responsible for any damage caused by using this software.
  Please use at your own risk.

1) Preparation

   ·Install Directory

   "PSP \ GAME \ np2" etc. The np2 part can be changed as you like.

   ・ Preparation of Japanese fonts

   Get MAKEFONT32 from the Neko Project II official website. Under the NP2 Tool.
   (http://retropc.net/yui/np2tool/index.html)

   With MAKEFONT32
     FontFace: MS Gothic
     FontType: PC-98 Bitmap
   Select to create font.bmp and place it in the installation directory.
   FontFace: may be MS Mincho.

2) Key operation

   Right trigger: soft keyboard on / off
   Left trigger: Menu on / off

   SELECT: Key config selection mode on / off
   START: Config key mode <-> pc98 mouse mode switching

   Mode config key / pc98 mouse
   -------------------------------------------------- -
   △: Config-dependent / config-dependent
   □: Config-dependent / config-dependent
   ○: Config dependent / Left mouse click (* 1)
   ×: Config dependent / Right mouse click (* 1)
   Digital pad ↑: Config dependent / Mouse movement
   Digital pad →: Config dependent / Mouse movement
   Digital pad ←: Config dependent / Mouse movement
   Digital pad ↓: Config dependent / Mouse movement
   Analog pad: unused / mouse movement
   -------------------------------------------------- -

   (* 1) By checking menu-> psp-> Swap 98mouse buttons,
        In pc98 mouse mode, ○ is right-clicked and × is left-clicked.
        You can change it. The change settings are saved.

   2.1) Key config

   Key config is done in a file called psp_key.txt.
   Place it in the same directory as EBOOT.PBP.
   As standard, the following psp_key.txt is included.

[KeySetting]
up = UP
down = DOWN
left = LEFT
right = RIGHT
circle = RET
cross = ESC
triangle = SHIFT
square = SPC
mm_triangle = SHIFT
mm_square = SPC
comment = "Basic settings (cursor key movement)"

[KeySetting]
up = [8]
down = [2]
left = [4]
right = [6]
circle = RET
cross = ESC
triangle = SHIFT
square = SPC
mm_triangle = SHIFT
mm_square = SPC
comment = "Basic setting (numeric keypad movement)"

   ・ Up / down / left / right are set when the digital pad is pressed.
   ・ Circle / cross / triangle / square are set when ○ / × / △ / □ are pressed respectively.
   ・ Mm_triangle / mm_square are the settings when △ / □ is pressed in pc98 mouse mode.
   -Comment is a comment displayed when the key config setting is selected on the PSP. With half-width ""
     Please wrap it up. If you want to use Kanji, use SJIS.
   -I feel that the line feed code is compatible with DOS (Windows), MAC, and Unix.
