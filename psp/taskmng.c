#include <psppower.h>
#include	"compiler.h"
#include "np2.h"
#include	"inputmng.h"
#include	"taskmng.h"
#include	"vramhdl.h"
#include	"menubase.h"
#include	"sysmenu.h"
#include "pg.h"
#include "psplib.h"
#include "scrnmng.h"
#include "keyconf.h"
#include "pspctrl.h"
#include "mousemng.h"
#include "keystat.h"
#include "soundmng.h"

BOOL task_avail;

volatile static int onscrn_cnt = 0;
volatile static int kc_scrn_cnt = 0;
static char onscrn_buf[5][25];
static char kc_scrn_buf[96][27];
static int selected_keyset = 1;
static int keyset = 1;
static int mbutton_l, mbutton_r;

static void update_kc_scrn()
{
    char s[256];

    /* �܂��ݒ�t�@�C����ǂ�ł��Ȃ��A�ݒ�t�@�C�����Ȃ� */
    if (kc_is_ready() == 0) {
        plPrint(0, 0, 0xffff, "no""psp_key.txt");
        return;
    }

    /* witdh:0-95 height:0-26 */
    sprintf(s, "setting-%d", keyset);
    plPrint(17, 6, 0xffff, s);
    sprintf(s, "(%s)", kc_get_comment(keyset));
    plPrint(17, 7, 0xffff, s);

    plPrint(12, 9, 0xffff, " (config key mode)");
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_up));
    plPrint(12, 10, 0xffff, s);
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_right));
    plPrint(12, 11, 0xffff, s);
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_left));
    plPrint(12, 12, 0xffff, s); 
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_down));
    plPrint(12, 13, 0xffff, s);
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_circle));
    plPrint(12, 14, 0xffff, s);
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_triangle));
    plPrint(12, 15, 0xffff, s);
    sprintf(s, "�~ : %s", kc_get_keystrs(keyset, kc_cross));
    plPrint(12, 16, 0xffff, s);
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_square));
    plPrint(12, 17, 0xffff, s);

    plPrint(12, 19, 0xffff, " (pc98 mouse mode)");
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_mm_triangle));
    plPrint(12, 20, 0xffff, s);
    sprintf(s, "�� : %s", kc_get_keystrs(keyset, kc_mm_square));
    plPrint(12, 21, 0xffff, s);

    plPrint(12, 26, 0xffff, "���� : �L�[�R���t�B�O�ύX   �� : �L�[�R���t�B�O����");
}

void taskmng_initialize(void)
{
    int i;

    task_avail = TRUE;

    onscrn_cnt = kc_scrn_cnt = 0;

    for (i = 0; i < 5; i++) {
        onscrn_buf[i][0] = '\0';
    }

    for (i = 0; i < 20; i++) {
        kc_scrn_buf[i][0] = '\0';
    }

    kc_loadfile();

    taskmng_set_psp_clock(np2oscfg.pspturbo);
    taskmng_set_psp_mbutton(np2oscfg.pspmbutton);
}

void taskmng_exit(void)
{
    task_avail = FALSE;
}

void taskmng_prt_onscrn(void)
{
    int i;

    if (kc_scrn_cnt > 0) {
        for (i = 0; i < 27; i++) {
            plClrChars(0, i, 96);
        }
        update_kc_scrn();
        return;
    }

    if (onscrn_cnt > 0) {
        for (i = 0; i < 5; i++) {
            plClrChars(40, i + 10, 25);
            plPrint(40, i + 10, 0xffff, onscrn_buf[i]);
        }
    }
}

void static set_onscrn(int i, char *s)
{
    onscrn_cnt = 120;
    strcpy(&onscrn_buf[i][0], s);
}

void taskmng_set_psp_clock(BOOL turbo)
{
    if (turbo) {
        scePowerSetClockFrequency(333, 333, 166);
        set_onscrn(0, "Clock: 333MHz");
    } else {
        scePowerSetClockFrequency(222, 222, 111);
        set_onscrn(0, "Clock: 222MHz");

    }
}

void taskmng_set_psp_mbutton(BOOL mbutton)
{
    if (mbutton) {
        mbutton_l = PSP_CTRL_CROSS;
        mbutton_r = PSP_CTRL_CIRCLE;
        set_onscrn(2, "98mouse button: swap");
    } else {
        mbutton_l = PSP_CTRL_CIRCLE;
        mbutton_r = PSP_CTRL_CROSS;
        set_onscrn(2, "98mouse button: normal");
    }
}

static void mouse_98mode(SceCtrlData *pad)
{
    static int x = 0, y = 0;
    int ax, ay;

    if (pad->Buttons & PSP_CTRL_LEFT) {
        x--;
    }
    if (pad->Buttons & PSP_CTRL_RIGHT) {
        x++;
    }
    if (pad->Buttons & PSP_CTRL_UP) {
        y--;
    }
    if (pad->Buttons & PSP_CTRL_DOWN) {
        y++;
    }

    // x, y�������ꂼ��j���[�g�����Ȃ�0�ɖ߂�
    if (!(pad->Buttons & (PSP_CTRL_LEFT | PSP_CTRL_RIGHT))) {
        x = 0;
    }
    if (!(pad->Buttons & (PSP_CTRL_UP | PSP_CTRL_DOWN))) {
        y = 0;
    }

    // �A�i���O��-5�`5�Ƃ���
    ax = (pad->Lx - 128) / 25;
    ay = (pad->Ly - 128) / 25;

    x += ax;
    y += ay;

    // ������x�������������葬�x�ɂ���
    if (x > 5) {
        x = 5;
    }
    if (x < -5) {
        x = -5;
    }
    if (y > 5) {
        y = 5;
    }
    if (y < -5) {
        y = -5;
    }

    mousemng_update(x, y, pad->Buttons & mbutton_l, pad->Buttons & mbutton_r);
}

typedef struct _psp_key {
    UINT32 button;
    int flag; // 1:repeat (���ݖ��g�p)
    int idx;
    UINT8 keycode[2];
} psp_key_t;

static psp_key_t psp_key[] = {
    {PSP_CTRL_UP, 0, 0, {kc_up, kc_up}},
    {PSP_CTRL_LEFT, 0, 0, {kc_left, kc_left}},
    {PSP_CTRL_RIGHT, 0, 0, {kc_right, kc_right}},
    {PSP_CTRL_DOWN, 0, 0, {kc_down, kc_down}},
    {PSP_CTRL_CIRCLE, 0, 0, {kc_circle, kc_circle}},
    {PSP_CTRL_CROSS, 0, 0, {kc_cross, kc_cross}},
    {PSP_CTRL_TRIANGLE, 0, 0, {kc_triangle, kc_mm_triangle}},
    {PSP_CTRL_SQUARE, 0, 0, {kc_square, kc_mm_square}},
    {0, 0, 0, {0, 0}}
};

static BOOL mouse_98key_mode(SceCtrlData *pad,
                             UINT32 beingdown, UINT32 beingup)
{
    int i, l;
    UINT32 type;
    BOOL moving = FALSE;
    char *p;

    i = 0;
    while ((type = psp_key[i].button) != 0) { // type��NULL�łȂ���
        p = kc_get_keycodes(selected_keyset, psp_key[i].keycode[0]);
        if (p == NULL || *p == 0xff) {
            i++;
            continue;
        }

        for (l = 0; p[l] != (char)0xff; l++)
            ;

        if (l == 1) {
            /* flag��1�Ȃ�{�^����������Ă���Ԃ�senddata()����(repeat mode)�B
               flag��0�Ȃ�{�^���������ꂽ�ŏ��̈��̂�senddata()����B*/
            if ((psp_key[i].flag == 1)?
                pad->Buttons & type : beingdown & type) {
                keystat_senddata(*p);
            }
            if (beingup & type) {
                keystat_senddata(*p | 0x80);
            }
        } else { // ���������uSHIFT A�v�Łua�v�Ƃ�
            while (*p != (char)0xff) {
                if (beingdown & type) {
                    keystat_senddata(*p);
                }
                if (beingup & type) {
                    keystat_senddata(*p | 0x80);
                }
                p++;
            }
        }
        i++;
    }

    // PSP��ʂɂ����܂�Ȃ�PC98��ʂ̃X�N���[������
    moving |= scrnmng_set_scrn_pos(pad->Lx, pad->Ly);

    return moving;
}

//menu��psp�̎����(480x272)�ɕ`�悷��
static BOOL mouse_digipad(short *x, short *y, SceCtrlData *pad)
{
    BOOL moving = FALSE;

    if (pad->Buttons & PSP_CTRL_LEFT) {
        if (*x > 0) {
            (*x)--;
            moving = TRUE;
        }
    }
    if (pad->Buttons & PSP_CTRL_RIGHT) {
        if (*x < 479) {
            (*x)++;
            moving = TRUE;
        }
    }
    if (pad->Buttons & PSP_CTRL_UP) {
        if (*y > 0) {
            (*y)--;
            moving = TRUE;
        }
    }
    if (pad->Buttons & PSP_CTRL_DOWN) {
        if (*y < 271) {
            (*y)++;
            moving = TRUE;
        }
    }

    return moving;
}

BOOL taskmng_mouse_anapad(short *x, short *y, UINT8 ax, UINT8 ay,
                          short maxx, short maxy)
{
    short oldx, oldy;

    oldx = *x, oldy = *y;

    if (ax > 255 / 2 + 32) {
        (*x)++;
        if (ax > 255 - 5) {
            (*x)++;
            if (ax == 255) {
                *x += 2;
            }
        }
        if (*x > maxx) {
            *x = maxx;
        }
    }
    if (ax < 255 / 2 - 32) {
        (*x)--;
        if (ax < 5) {
            (*x)--;
            if (ax == 0) {
                *x -= 2;
            }
        }
        if (*x < 0) {
            *x = 0;
        }
    }
    if (ay > 255 / 2 + 32) {
        (*y)++;
        if (ay > 255 - 5) {
            (*y)++;
            if (ay == 255) {
                *y += 2;
            }
        }
        if (*y > maxy) {
            *y = maxy;
        }
    }
    if (ay < 255 / 2 - 32) {
        (*y)--;
        if (ay < 5) {
            (*y)--;
            if (ay == 0) {
                *y -= 2;
            }
        }
        if (*y < 0) {
            *y = 0;
        }
    }

    return (oldx != *x || oldy != *y);
}

#define SKBD_TBL_ROW 6
#define SKBD_TBL_COL 22

UINT8 skbd_tbl[SKBD_TBL_ROW][SKBD_TBL_COL] = {
     //          COPY   f.1         f.2   f.3   f.4   f.5                     f.8         f.9  f.10
    {0x60, 0x60, 0x61, 0x62, 0x62, 0x63, 0x64, 0x65, 0x66, 0x66, 0x67, 0x68, 0x69, 0x69, 0x6a, 0x6b, 0x52, 0x53, 0x54, 0x54, 0x55, 0x56},
     //             1                                                           -           \  BS
    {0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x38, 0x39, 0x3e, 0x3f, 0x40, 0x41},
     //             q                                                                 [   RET   RET
    {0x0f, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1c, 0x36, 0x37, 0x42, 0x43, 0x44, 0x45},
     //             a     s     d     f                                               ]   RET   RET    ��
    {0x74, 0x71, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x1c, 0x3a, 0x3a, 0x3a, 0x46, 0x47, 0x48, 0x49},
     //            29                                                              RSFT  RSFT  RSFT   ��    ��    [1]
    {0x70, 0x70, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x7d, 0x7d, 0x7d, 0x3b, 0x3c, 0x4a, 0x4b, 0x4c, 0x4d},
     //          KANA                                                                                  ��         [0]
    {0xff, 0xff, 0x72, 0x73, 0x51, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x35, 0x35, 0xff, 0xff, 0xff, 0x3d, 0x3d, 0x4e, 0x4f, 0x50, 0x1c}
};

static void get_skbd_key_pos(int row, int col, int *x, int *y, int *w, int *h)
{
    UINT8 tmp_tbl[21];
    int i, j;

    // �L�[�R�[�h�łȂ�0xff���΂��Ȃ���Acol�����̃_�u����Ȃ���
    for (i = 0, j = 0; i < 22; i++) {
        if (skbd_tbl[row][i] != 0xff) {
            if (j == 0) {
                tmp_tbl[j++] = skbd_tbl[row][i];
            } else if (tmp_tbl[j - 1] != skbd_tbl[row][i]) {
                tmp_tbl[j++] = skbd_tbl[row][i];
            }
        }
    }

    // �����牽�Ԗڂ̃L�[�����Z�o(0 origin)
    for (i = 0; tmp_tbl[i] != skbd_tbl[row][col]; i++)
        ;

    switch (row) {
    case 0:
        *y = 2, *h = 14;
        if (i == 0) {
            *x = 2, *w = 14;
        } else if (i == 1) {
            *x = 19, *w = 14;
        } else if (i >= 2 && i <= 6) {
            *x = 40 + (17 * (i - 2)), *w = 17;
        } else if (i >= 7 && i <= 11) {
            *x = 130 + (17 * (i - 7)), *w = 17; 
        } else if (i >= 12) {
            *x = 220 + (17 * (i - 12)), *w = 17;
        }
        break;
    case 1:
        *y = 18, *h = 14;
        if (i == 0) {
            *x = 2, *w = 17;
        } else if (i >= 1 && i <= 13) {
            *x = 19 + (14 * (i - 1)), *w = 14;
        } else if (i == 14) { // BS
            *x = 201, *w = 17;
        } else if (i == 15 || i == 16) { // INS, DEL
            *x = 218 + (14 * (i - 15)), *w = 14;
        } else if (i >= 17) {
            *x = 250 + (14 * (i - 17)), *w = 14;
        }
        break;
    case 2:
        *y = 32, *h = 14;
        if (i == 0) { // TAB
            *x = 2, *w = 24;
        } else if (i >= 1 && i <= 12) {
            *x = 26 + (14 * (i - 1)), *w = 14;
        } else if (i == 13) { // RET
            *x = 199, *w = 19, *h = 28;
        } else if (i == 14 || i == 15) {
            *x = 218 + (14 * (i - 14)), *w = 14;
        } else if (i >= 16) {
            *x = 250 + (14 * (i - 16)), *w = 14;
        }
        break;
    case 3:
        *y = 46, *h = 14;
        if (i >= 0 && i <= 13) {
            *x = 2 + (14 * i), *w = 14;
        } else if (i == 14) { // RET
            *x = 199, *y = 32, *w = 19, *h = 28;
        } else if (i == 15) { // ��
            *x = 218, *w = 29;
        } else if (i >= 16) {
            *x = 250 + (14 * (i - 16)), *w = 14;
        }
        break;
    case 4:
        *y = 60, *h = 14;
        if (i == 0) {
            *x = 2, *w = 34;
        } else if (i >= 1 && i <= 11) {
            *x = 36 + (14 * (i - 1)), *w = 14;
        } else if (i == 12) {
            *x = 190, *w = 28;
        } else if (i == 13 || i == 14) {
            *x = 218 + (14 * (i - 13)), *w = 14;
        } else if (i >= 15) {
            *x = 250 + (14 * (i - 15)), *w = 14;
        }
        break;
    case 5:
        *y = 74, *h = 14;
        if (i == 0 || i == 1) {
            *x = 29 + (14 * i), *w = 14;
        } else if (i == 2) {
            *x = 57, *w = 21;
        } else if (i == 3) {
            *x = 78, *w = 90;
        } else if (i == 4) {
            *x = 169, *w = 22;
        } else if (i == 5) {
            *x = 218, *w = 29;
        } else if (i >= 6) {
            *x = 250 + (14 * (i - 6)), *w = 14;            
        }
        break;
    }
}

/* deltar, deltac��-1, 0, +1�̂����ꂩ�B�ǂ��炩�Е���0 */
static BOOL skbd_key_move(int *row, int *col, int deltar, int deltac)
{
    int r, c;
    int x, y, w, h;

    /* ����0�Ȃ�L�[�̈ړ��Ȃ� */
    if (deltar == 0 && deltac == 0) {
        return FALSE;
    }

    r = *row, c = *col;

    while (r < SKBD_TBL_ROW && c < SKBD_TBL_COL && r >= 0 && c >= 0
           && skbd_tbl[r][c] != 0xff) {

        if (skbd_tbl[*row][*col] != skbd_tbl[r][c]) {
            /* ���܂ł̔��]�����ɖ߂� */
            get_skbd_key_pos(*row, *col, &x, &y, &w, &h);
            scrnmng_skbd_key_reverse(x, y, w, h);

            /* �V�����L�[�𔽓]���� */
            *row = r, *col = c;
            get_skbd_key_pos(*row, *col, &x, &y, &w, &h);
            scrnmng_skbd_key_reverse(x, y, w, h);

            return TRUE;
        }
        r += deltar, c += deltac;
    }

    return FALSE;
}

#define SKBD_ROW_INIT 3
#define SKBD_COL_INIT 5
static int skbd_mode(UINT32 beingdown, UINT32 beingup, UINT32 button_down,
                     SceCtrlData *pad)
{
    static int key_repeat;
    static int skbdrow = SKBD_ROW_INIT, skbdcol = SKBD_COL_INIT;
    int deltar, deltac;
    int redraw = 0;

    // �\�t�g�L�[�{�[�h�͉�ʂ̊O�Ɋ��S�ɏo�Ȃ��悤�ɂ���
    if (taskmng_mouse_anapad(&skbdx, &skbdy, pad->Lx, pad->Ly,
                             479 - 4, 271 - 4)) {
        redraw = TRUE;
    }

    if (beingdown & PSP_CTRL_CIRCLE) {
        keystat_senddata(skbd_tbl[skbdrow][skbdcol]);
    }
    if (beingup & PSP_CTRL_CIRCLE) {
        keystat_senddata(skbd_tbl[skbdrow][skbdcol] | 0x80);
    }

    deltar = deltac = 0;
    if (beingdown &
        (PSP_CTRL_LEFT | PSP_CTRL_RIGHT | PSP_CTRL_UP | PSP_CTRL_DOWN)) {
        key_repeat = 30;
    }
    deltac = (beingdown & PSP_CTRL_LEFT)? -1 : deltac;
    deltac = (beingdown & PSP_CTRL_RIGHT)? +1 : deltac;
    deltar = (beingdown & PSP_CTRL_UP)? -1 : deltar;
    deltar = (beingdown & PSP_CTRL_DOWN)? +1 : deltar;

    if (button_down &
        (PSP_CTRL_LEFT | PSP_CTRL_RIGHT | PSP_CTRL_UP | PSP_CTRL_DOWN)) {
        key_repeat--;
        if (key_repeat < 0) {
            deltac = (button_down & PSP_CTRL_LEFT)? -1 : deltac;
            deltac = (button_down & PSP_CTRL_RIGHT)? +1 : deltac;
            deltar = (button_down & PSP_CTRL_UP)? -1 : deltar;
            deltar = (button_down & PSP_CTRL_DOWN)? +1 : deltar;
            key_repeat = 3;
        }
    }

    redraw |= skbd_key_move(&skbdrow, &skbdcol, deltar, deltac);

    return redraw;
}

static int pspmenu_mode(UINT32 beingdown, UINT32 beingup, SceCtrlData *pad)
{
    static short x = 0, y = 0;
    BOOL moving = FALSE;
    int redraw = 0;

    // �f�W�^���p�b�h
    moving |= mouse_digipad(&x, &y, pad);

    // �A�i���O�p�b�h
    moving |= taskmng_mouse_anapad(&x, &y,
                                   pad->Lx, pad->Ly,
                                   479, 271);

    // PC98���z���(640x400)����PSP�����(480x272)�֍��W�ϊ�
    scrnmng_set_pspmxy(x, y);

    if (moving) {
        if (menuvram) {
            menubase_moving(x, y, 0);
        }
        redraw = TRUE;
    }

    if (beingdown & PSP_CTRL_CIRCLE) {
        if (menuvram) {
            menubase_moving(x, y, 1);
            redraw = TRUE;
        }
    }
    if (beingup & PSP_CTRL_CIRCLE) {
        if (menuvram) {
            menubase_moving(x, y, 2);
            redraw = TRUE;
        }
    }

    return redraw;
}

static char mouse_mode_str[4][25]
    = {"pspmenu", "PC98Mode: mouse", "PC98Mode: config key", "pc98skbd"};

void taskmng_rol(void)
{
    SceCtrlData psppad;
    int redraw = 0;
    UINT32 beingdown = 0, beingup = 0, button_changing;
    static UINT32 button_down = 0;
    int keyx, keyy, keyw, keyh;
    static BOOL first_call = TRUE;
    static enum {
        pspmenu,
        pc98mouse,
        pc98key,
        pc98skbd,
        keyconf
    } mouse_mode = pc98mouse, old_mouse_mode = pc98mouse;

    if (first_call == TRUE) {
        set_onscrn(1, mouse_mode_str[mouse_mode]);

        get_skbd_key_pos(SKBD_ROW_INIT, SKBD_COL_INIT,
                         &keyx, &keyy, &keyw, &keyh);
        scrnmng_skbd_key_reverse(keyx, keyy, keyw, keyh);
        first_call = FALSE;
    }

    // ���Z�b�g��A���΂炭HELP�L�[������
    if (help_key_sending > 0) {
        keystat_senddata(0x3f);
        sceDisplayWaitVblankStart();
        if (--help_key_sending == 0) {
            keystat_senddata(0x3f | 0x80);
        }
    }

    if (onscrn_cnt > 0) {
        onscrn_cnt--;
        redraw = TRUE;
    }

    // LTRIGGER���g���Ă��Ȃ��ă��j���[������ꂽ�ꍇ�̑Ώ��B
    // ������Ƃ����������B
    if (mouse_mode == pspmenu && menuvram == NULL) {
        soundmng_play();
        mouse_mode = old_mouse_mode;
        set_onscrn(1, mouse_mode_str[mouse_mode]);
    }

//    sceCtrlRead(&psppad, 1);
    sceCtrlPeekBufferPositive(&psppad, 1);

    // �O��ƕω��̂�����bit�𗧂Ă�
    button_changing = psppad.Buttons ^ button_down;
    // ���񏉂߂ĉ����ꂽ = �O��ƕω������� & ���{�^����������Ă���
    beingdown = button_changing & psppad.Buttons;
    // ���񏉂߂Ă͂Ȃ��ꂽ = �O��ƕω������� & �O�񉟂���Ă���
    beingup = button_changing & button_down;
    // �ω��̂�����bit�𔽓]������
    button_down ^= button_changing;

    // �L�[�R���t�B�O���[�h
    if (beingdown & PSP_CTRL_SELECT) {
        if (mouse_mode != keyconf) {
            // pc98���[�h�ɖ߂�(keycon -> pspmenu or pc98skbd�ɂ͖߂��Ȃ�)
            if (mouse_mode == pc98mouse || mouse_mode == pc98key) {
                old_mouse_mode = mouse_mode;
            }
            mouse_mode = keyconf;
            onscrn_cnt = 0;
            kc_scrn_cnt = 1;
            keyset = selected_keyset;

            if (menuvram) {
                menubase_close();
                soundmng_play();
            }
            if (skbdx < 512) {
                skbdx += 512;
            }
        } else {
            mouse_mode = old_mouse_mode;
            kc_scrn_cnt = 0;
            set_onscrn(1, mouse_mode_str[mouse_mode]);
	}
	redraw = TRUE;
    }

    if (beingdown & PSP_CTRL_LTRIGGER) {
        if (mouse_mode != pspmenu) {
            // pc98���[�h�ɖ߂�(pspmenu->pc98skbd�ɂ͖߂��Ȃ�)
            if (mouse_mode == pc98mouse || mouse_mode == pc98key) {
                old_mouse_mode = mouse_mode;
            }
            mouse_mode = pspmenu;

            if (!menuvram) {
                soundmng_stop();
                sysmenu_menuopen(0, 0, 0);
            }
            if (skbdx < 512) {
                skbdx += 512;
            }
            kc_scrn_cnt = 0;
        } else {
            menubase_close();
            soundmng_play();
            mouse_mode = old_mouse_mode;
            set_onscrn(1, mouse_mode_str[mouse_mode]);
        }
        redraw = TRUE;
    }

    if (beingdown & PSP_CTRL_RTRIGGER) {
        if (mouse_mode != pc98skbd) {
            if (mouse_mode == pc98mouse || mouse_mode == pc98key) {
                old_mouse_mode = mouse_mode;
            }
            mouse_mode = pc98skbd;

            if (skbdx >= 512) {
                skbdx -= 512;
            }
            if (menuvram) {
                menubase_close();
                soundmng_play();
            }
            kc_scrn_cnt = 0;
        } else {
            skbdx += 512;
            mouse_mode = old_mouse_mode;
            set_onscrn(1, mouse_mode_str[mouse_mode]);
        }
        redraw = TRUE;
    }

    if (mouse_mode == pc98skbd) {
        sceDisplayWaitVblankStart();      
        redraw |= skbd_mode(beingdown, beingup, button_down, &psppad);
        goto done; //�\�t�g�L�[�{�[�h���[�h�Ȃ炱���ŏI��
    }

    if (mouse_mode == pspmenu) {
        redraw |= pspmenu_mode(beingdown, beingup, &psppad);
        goto done;
    }

    if (mouse_mode == keyconf) {
        if (beingdown & PSP_CTRL_LEFT) {
            if (--keyset == 0) {
                keyset = kc_get_ks_num();
            }
            redraw = TRUE;
        }
        if (beingdown & PSP_CTRL_RIGHT) {
            if (++keyset == kc_get_ks_num() + 1) {
                keyset = 1;
            }
            redraw = TRUE;
        }
        if (beingdown & PSP_CTRL_CIRCLE) {
            selected_keyset = keyset;
            mouse_mode = old_mouse_mode;
            kc_scrn_cnt = 0;
            set_onscrn(1, mouse_mode_str[mouse_mode]);
            redraw = TRUE;
	}
        goto done;
    }

    // �����܂ł���̂�mouse_mode��pc98key�܂���pc98mouse�̂Ƃ��B

    if (beingdown & PSP_CTRL_START) {
        if (mouse_mode == pc98key) {
            mouse_mode = pc98mouse;
        } else {
            mouse_mode = pc98key;
        }
        set_onscrn(1, mouse_mode_str[mouse_mode]);
        redraw = TRUE;
    }

    // PC98�}�E�X���[�h
    if (mouse_mode == pc98mouse) {
        mouse_98mode(&psppad);
        goto done;
    }

    // PC98�R���t�B�O�L�[���[�h
    if (mouse_mode == pc98key) {
        redraw |= mouse_98key_mode(&psppad, beingdown, beingup);
    }

 done:
    if (redraw) {
        scrnmng_gu_update();
    }
}

BOOL taskmng_sleep(UINT32 tick) {

	UINT32	base;

	base = GETTICK();
	while((task_avail) && ((GETTICK() - base) < tick)) {
		taskmng_rol();
#ifndef PSP
#if !defined(TARGET_MONA)
		Sleep(1);
#endif
#endif
	}
	return(task_avail);
}
