NP2 for PSP ver0.38
                                                                     2011/04/01
                                                           �Ђ����股(hissorii)

NEC PC-9801�V���[�Y���G�~�����[�g����
Neko Project II(http://www.yui.ne.jp/np2/)��PSP�ɈڐA���Ă݂܂����B
����Ȃ�Ɏ蔲���ł��B
���ɂ����\�[�X�̃o�[�W������ver0.81a�B

�I���W�i���ڐA�҂�sakahi���񂩂�����p��
Ver0.34���A�Ђ����股���J�����Ă��܂��B

0) �Ɛ�

  �{�\�t�g�E�F�A���g�p�������Ƃɂ��A�����Ȃ鑹�Q����҂͐ӔC�𕉂��܂���B
  �����܂ł����ȐӔC�ł̎g�p�����肢�v���܂��B

1) ����

   �E�C���X�g�[���f�B���N�g��

   �uPSP\GAME\np2�v�ȂǁBnp2�̕����͂��D�݂ŕύX�\�B

   �E���{��t�H���g�̏���

   Neko Project II�����T�C�g�ɂ�MAKEFONT32����肵�Ă��������BNP2 Tool�̉��B
   ( http://retropc.net/yui/np2tool/index.html )

   MAKEFONT32�ŁA
     FontFace: MS �S�V�b�N
     FontType: PC-98 Bitmap
   ��I���font.bmp���쐬���A�C���X�g�[���f�B���N�g���ɒu���B
   FontFace: ��MS�����ł��悢�����B

2) �L�[����

   �E�g���K�[: �\�t�g�L�[�{�[�hon/off
   ���g���K�[: ���j���[on/off

   SELECT: �L�[�R���t�B�O�I�����[�hon/off
   START:  �R���t�B�O�L�[���[�h <-> pc98�}�E�X���[�h �ؑ�

   ���[�h            �R���t�B�O�L�[ / pc98�}�E�X
   ----------------------------------------------------
   ��              : �R���t�B�O�ˑ� / �R���t�B�O�ˑ�
   ��              : �R���t�B�O�ˑ� / �R���t�B�O�ˑ�
   ��              : �R���t�B�O�ˑ� / �}�E�X���N���b�N (*1)
   �~              : �R���t�B�O�ˑ� / �}�E�X�E�N���b�N (*1)
   �f�W�^���p�b�h��: �R���t�B�O�ˑ� / �}�E�X�ړ�
   �f�W�^���p�b�h��: �R���t�B�O�ˑ� / �}�E�X�ړ�
   �f�W�^���p�b�h��: �R���t�B�O�ˑ� / �}�E�X�ړ�
   �f�W�^���p�b�h��: �R���t�B�O�ˑ� / �}�E�X�ړ�
   �A�i���O�p�b�h  : ���g�p         / �}�E�X�ړ�
   ----------------------------------------------------

   (*1) menu->psp->Swap 98mouse buttons���`�F�b�N���邱�ƂŁA
        pc98�}�E�X���[�h���Ɂ����}�E�X�E�N���b�N�A�~���}�E�X���N���b�N��
        �ύX�ł��܂��B�ύX�ݒ�͕ۑ�����܂��B

   2.1) �L�[�R���t�B�O

   �L�[�R���t�B�O�́Apsp_key.txt�Ƃ����t�@�C���ōs���܂��B
   EBOOT.PBP�Ɠ����f�B���N�g���ɒu���Ă��������B
   �W���ŁA�ȉ��̗l��psp_key.txt�𓯍����Ă��܂��B

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
comment = "��{�Z�b�e�B���O(�J�[�\���L�[�ړ�)"

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
comment = "��{�Z�b�e�B���O(�e���L�[�ړ�)"

   �Eup/down/left/right�͂��ꂼ��f�W�^���p�b�h�������ꂽ���̐ݒ�
   �Ecircle/cross/triangle/square�͂��ꂼ�ꁛ/�~/��/���������ꂽ���̐ݒ�
   �Emm_triangle/mm_square�͂��ꂼ��pc98�}�E�X���[�h���Ɂ�/���������ꂽ���̐ݒ�
   �Ecomment��PSP�ł̃L�[�R���t�B�O�ݒ�I�����ɕ\�������R�����g�B���p��""��
     �������Ă��������B�������g���ꍇ��SJIS�ŁB
   �E���s�R�[�h�́ADOS(Windows), MAC, Unix�n�ɑΉ������C�����܂��B

   KeySetting�͂Ƃ肠���������ł��ǉ��ł��܂��B

   �ݒ�ł���L�[�͈ȉ��̂Ƃ���B

   1 2 3 4 5 6 7 8 9 0 (��10�L�[)
   A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
   - ^ \ @ [ ; : ] , . / _
   ESC BS TAB RET SPC XFER RLUP RLDN INS DEL HOME HELP NFER
   STOP COPY SHIFT(���V�t�g) RSHIFT(�E�V�t�g) CAPS KANA GRPH CTRL
   LWIN(��WIN�L�[) RWIN(�EWIN�L�[) APP
   UP LEFT RIGHT DOWN (�J�[�\���L�[)
   [-] [/] [*] [+] [=] [,] [.] (10�L�[)
   [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] (10�L�[)
   VF1 VF2 VF3 VF4 VF5 (�t�@���N�V�����L�[)
   F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 (�t�@���N�V�����L�[)

   2.2)

   �J�[�\���̂����܂��Ȉړ��̓A�i���O�ŁA�ׂ����ړ��̓f�W�^�������₷��

   2.3) �\�t�g�L�[�{�[�h���[�h���̃L�[����

        �f�W�^���p�b�h: �L�[�̑I��
        �A�i���O�p�b�h: �\�t�g�L�[�{�[�h���̂��̂̈ړ�
        ��: �L�[�̓���

3) ��ʃT�C�Y

   menu->psp�̂���ȉ��̉�ʃT�C�Y��I���\�ł��B

   �E432x270 (�k���� 0.675�{, ���E24�h�b�g����, �㉺1�h�b�g������ʗ̈�)   
   �E480x272 (�������C�h��� �k���� W*0.75, H*0.68)
   �E480x300 (�k���� 0.75�{, �㉺��14�h�b�g���؂��)
   �E640x400 (���{, �E160�h�b�g, ��128�h�b�g�؂��)

   �E480x300, 640x400�̏ꍇ��PSP�̉��(480x272)�Ɏ��܂�Ȃ��̂ŁA
     �R���t�B�O�L�[���[�h���̃A�i���O�p�b�h���g���ĉ�ʑS�̂����n���܂��B
   �E�I��������ʐݒ�͕ۑ�����܂��B

4) PSP����N���b�N�ݒ�

   �Emenu->psp->Clock 333MHz���`�F�b�N�����333MHz�A
     �`�F�b�N���͂�����222MHz�œ��삵�܂��B
   �E�I�������ݒ�͕ۑ�����܂��B

5) ����̗\��(�͖���...)

   �E���{��t�@�C���̓ǂݍ��ݑΉ�
   �EUI�̌�����
   �E�������̃o�O�C��
       :
   �E���x���P

6) �A�C�R��

  pochi style (http://pochistyle.pspwire.net/index.html)���A
  pochi����쐬�̃A�C�R�����g�p�����Ă��������܂����B

7) �t�H���g

  �t�H���g�̈ꕔ�Ɂu�i�K10�v�t�H���g���g�p���Ă��܂��B

8) �ύX����

ver0.38
�E�X���[�v���[�h�Ή�
�E�\�t�g�L�[�{�[�h�̃L�[���͂����������̂��C��(Ver0.37�������ŃG���o�O)
�Emenu��[Reset with HELP key]�ŃV�X�e���Z�b�g�A�b�v���j���[��
  ����Ȃ��Ȃ��Ă����̂��C��(Ver0.37�������ŃG���o�O)

ver0.37
�E��ʃT�C�Y640x480�̏ꍇ�ɁA��512�h�b�g�t�߂ɏc��������o�O(ver0.35�ɂ�
  �G���o�O���܂���)�̏C��
�Epc98�}�E�X���[�h���ɁAPSP�́��{�^���Ƀ}�E�X�E�N���b�N�A
  PSP�́~�{�^���Ƀ}�E�X���N���b�N�������ĉ\�ɂ��܂���
�E���傱���ƍ��������܂���

ver0.36
�E��ʃT�C�Y480x300�̏ꍇ�ɁA�A�i���O�p�b�h�ŃX�N���[�������Ă��ŉ�����
  �\������Ȃ����������C��

ver0.35
�E�L�[�R���t�B�O�̒ǉ�

ver0.34
�EBEEP/PSG�������������Đ�����Ă��Ȃ����������C��
�E�N�����́u�҂ۂ��v���Ȃ�悤�ɂȂ�܂����B

ver0.33
�EFM�������������Đ�����Ă��Ȃ����������C��

ver0.32
�E���j���[�����₷���Ȃ�܂���...
�E���j���[���쎞�̂��������Ȃ������߁A���j���[�\�����̓G�~�����[�V������
  ��~����悤�ɕύX
�E640x400�Ȃǂŕ\���̈�����炵�Ă��鎞���A��Ƀ��j���[��PSP��ʏ㕔��
  �Œ�\�������悤�C��
�E�t�@�C���I�����j���[�ŁA�g���q���������̃t�@�C�����\������Ȃ����������C��
�EPC98�}�E�X���[�h�ŁA�J�[�\���̍�/������ړ��̉������~�܂�Ȃ����������C��
�Epochi style (http://pochistyle.pspwire.net/index.html)��pochi����쐬��
  �A�C�R�����g�p����悤�ɂ���
�E�J������PSPSDK�Ɉڍs(�̓r��)
�E���s�t�@�C��EBOOT.PBP�̃T�C�Y�����Ȃ菬�����Ȃ�܂���

ver0.3
�E���ʃT�|�[�g (432x270, 480x272(wide), 480x300, 640x400)
�E�\�t�g�E�F�A�L�[�{�[�h����
�E�}�E�X�J�[�\������(���܂ɉ�ʂɂ��݂��o��)���C��
�E����Clock(222/333MHz)�����j���[�Ɉړ��Bclock�ݒ�̕ۑ����T�|�[�g�B
�E���j���[�̃t�H���g�����ɂ����Ȃ�܂���...

ver0.21
�EFDI�C���[�W��ǂݍ��߂�悤�C��
�E�I�������Ŏ��s���邱�Ƃ��������̂��C��
�Enp2��menu->emulate->Exit�܂��̓��j���[�o�[��x�{�^����
  �z�[���֖߂��悤�ɏC��
�Enp2��menu->emulate->Reset with HELP key�Ń��Z�b�g���
  �V�X�e���Z�b�g�A�b�v���j���[�֓����悤�ɏC��
�E�ȈՃR���t�B�O�L�[���[�h�̒ǉ�

ver0.2
�E�����o��悤�ɂȂ�܂���
�E�I������(�z�[���֖߂��, ini�t�@�C���̕ۑ�)
�E�C���X�g�[���f�B���N�g����np2���߂�������������
�E���ݎ����擾�����Ă��Ȃ������̂��C��(���Otime()/localtime()�쐬)
�E�Ȃ񂿂����malloc()/free()����߂�
  (sceKernel�`��p�������Omalloc()/free()�쐬)
�E�_�C�A���O�̕����������C��(���Osprintf()�̍쐬)
�E�x�[�X�̃\�[�X��ver0.81��ver0.81a�ɕύX
�E�\�[�X���J

ver0.1
�E�Ƃ肠���������[�X

8) PSP�ō��Web�T�C�g

���Ђ����股(hissorii)
News�nblog: �Ђ����股�h�b�g�R�� 
http://hissorii.blog45.fc2.com/

�J���nblog: ���݂�͂� - Emulator Hacking ���L
http://emuhani.seesaa.net/

��sakahi
http://sakahi.hp.infoseek.co.jp/
