// ���O��libc�֌W��
#include "compiler.h"
#include "pg.h"
#include <stdarg.h>
#include <psprtc.h>

typedef struct _knj10_blank_id {
    int start;
    int end;
} knj10_bid_t;

typedef struct _ank10 {
    unsigned char bmp[10];
} ank10_t;

typedef struct _knj10 {
    unsigned short bmp[10];
} knj10_t;

#include "naga10font/n10font.c"

// for localtime()
struct tm {
  int   tm_sec;
  int   tm_min;
  int   tm_hour;
  int   tm_mday;
  int   tm_mon;
  int   tm_year;
  int   tm_wday;
  int   tm_yday;
  int   tm_isdst;
};

u64 GETTICK() {
  u64 ticks;
  sceRtcGetCurrentTick(&ticks);
  return ticks / 1000;
}

long time(long *timer)
{
    long t;

    sceKernelLibcTime(&t);

    if (timer != NULL) {
        *timer = t;
    }
    return t;
}

static int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// ���K��localtime()
struct tm *localtime(const long *timer)
{
    struct tm *tobj;
    int i;
    int day, year, tmp_year, leapy_cnt, tmp_day;
    long t;

    //1970�ȑO�̏ꍇ�̓G���[
    if (*timer < 0) {
        return NULL;
    }

    tobj = malloc(sizeof(struct tm));
    if (tobj == NULL) {
        return NULL;
    }

    t = *timer + 9 * 60 * 60; // GMT->JST�ϊ�

    day = (int)(t / (60 * 60 * 24));
    tmp_year = day / 365;
    leapy_cnt = (tmp_year + 2) / 4;
    year = (day + leapy_cnt) / 365;

    // 1970 1971 1972 1973 1974 1975 1976
    //  365  365  366  365  365  365  366

    //  1  2  3  4  5  6  7  8  9 10 11 12
    // 31 28 31 30 31 30 31 31 30 31 30 31

    tobj->tm_sec = t % 60;
    tobj->tm_min = (t / 60) % 60;
    tobj->tm_hour = (t / (60 * 60)) % 24;
    tobj->tm_year = year + 70;
    tobj->tm_wday = (day + 4) % 7; // �j��(��:0, ��:1, ...) 1970/1/1�͖�
    tobj->tm_yday = day - (365 * year) - leapy_cnt;
    tmp_day = tobj->tm_yday + 1;
    for (i = 0; i < 12; i++) {
        tmp_day -= days[i];
        if (tmp_day <= 0) {
            break;
        }
    }
    tobj->tm_mon = i;
    tobj->tm_mday = tmp_day + days[i];
    tobj->tm_isdst = 0;

    return tobj;
}        

static char dbgBuf[80];

void dbgPrint(char *s)
{
    strcpy(dbgBuf, s);
}
char *pgGetDbgBuf(void)
{
    return dbgBuf;
}

/***** �i�K10�t�H���g�\���n *****/

#define N10F_SWIDTH 5  //���p������
#define N10F_WWIDTH 10 //�S�p������
#define N10F_HEIGHT 10 //�����̍���

#define PL_SCHAR 1
#define PL_WCHAR 2

/* sjis��jis�R�[�h�ϊ� */
static unsigned int sjis2jis(unsigned int w)
{
    unsigned char wh, wl;

    wh = w / 256, wl = w % 256;

    wh <<= 1;
    if (wl < 0x9f) {
        wh += (wh < 0x3f)? 0x1f : -0x61;
        wl -= (wl > 0x7e)? 0x20 : 0x1f;
    } else {
        wh += (wh < 0x3f)? 0x20 : -0x60;
        wl -= 0x7e;
    }

    return (wh * 256 + wl);
}

/* JIS�R�[�h����0 origin��index�ɕϊ����� */
static unsigned int jis2idx(unsigned int jc) {
    jc -= 0x2121;
    jc = jc % 256 + (jc / 256) * 0x5e;

    return jc;
}

/* ������bit�f�[�^��ԋp���A�Ăь��̕�����̃|�C���^�����炷�B
   �߂�l: PL_SCHAR(���p����), PL_WCHAR(�S�p����) */
static int get_bmp(unsigned char **s, unsigned short *b)
{
    int i;
    unsigned int idx, blank;
    unsigned short bmp;

    // ank����
    if ((**s & 0x80) == 0) {
        for (i = 0; i < N10F_HEIGHT; i++) {
            bmp = ank10[**s - 0x20].bmp[i];
            b[i] = bmp << 8;
        }
        (*s)++;

        return PL_SCHAR;
    }

    // �S�p����
    idx = jis2idx(sjis2jis(**s * 256 + *(*s + 1)));

    /* �󂫃R�[�h���΂� */
    blank = 0;
    for (i = 0; knj10_bid[i].start != -1; i++) {
        if (knj10_bid[i].end > idx) {
            break;
        }
        blank += knj10_bid[i].end - knj10_bid[i].start - 1;
    }
    idx -= blank;

    for (i = 0; i < N10F_HEIGHT; i++) {
        b[i] = knj10[idx].bmp[i];
    }
    *s += 2; //�S�p�Ȃ̂Ŏ��̕�����2byte��ɂȂ�

    return PL_WCHAR;
}

/* �����ʒup�ɕ�w, �����f�[�^bmp, �Fcolor�̈ꕶ����\�� */
static void plPutChar(unsigned short *p, int w, unsigned short *bmp, int color)
{
    unsigned short l;
    int i, j;

    for (j = 0; j < N10F_HEIGHT; j++) {
        l = bmp[j];
        for (i = 0; i < w; i++) {
            if (l & 0x8000) {
                *p = color;
            }
            p++;
            l <<= 1;
        }
        p += 512 - w; //���̃��C���ɂ��炷
    }
}

/* �i�K10�t�H���g(���p5*10, �S�p10*10)��\������ */
void plPrint(int x, int y, int color, char *s)
{
    unsigned short bmp[10], *p;
    unsigned char *us;
    int w;

    us = (unsigned char *)s;
    p = (unsigned short *)pgGetVramAddr(x * N10F_SWIDTH, y * N10F_HEIGHT);

    while (*us != '\0') {
        w = (get_bmp(&us, bmp) == PL_WCHAR)? N10F_WWIDTH : N10F_SWIDTH;
        plPutChar(p, w, bmp, color);
        p += w; // ���̕����ʒu�ɂ��炷
    }
}

/* �i�K10�t�H���g���W(x, y)����w���������N���A���� */
void plClrChars(int x, int y, int w)
{
    unsigned short bmp[10], *p;
    int i;

    memset(bmp, 0xff, sizeof(bmp));
    p = (unsigned short *)pgGetVramAddr(x * N10F_SWIDTH, y * N10F_HEIGHT);

    for (i = 0; i < w; i++) {
        plPutChar(p, N10F_SWIDTH, bmp, 0); // color=0�œh��Ԃ�
        p += N10F_SWIDTH;
    }
}

void plPrintErr(char *s)
{
    plClrChars(40, 15, 20);
    plPrint(40, 15, 0xffff, s);
}

/***** �i�K10�t�H���g�\���n�I��� *****/
