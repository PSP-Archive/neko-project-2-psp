// primitive graphics for Hello World sce

#include <pspdisplay.h>
#include <pspthreadman.h>
#include <pspaudio.h>
#include <pspuser.h>
#include <pspgu.h>
#include "pg.h"

#include "font.c"

#define pg_vramtop ((char *)0x04000000)
long pg_screenmode;
long pg_showframe;
static unsigned int pg_draw_buffer;
long pg_drawframe;

void pgSetDrawBuffer(void *frame_buf)
{
    pg_draw_buffer = (unsigned int)frame_buf;
}

char *pgGetVramAddr(unsigned long x, unsigned long y)
{
    return pg_vramtop + (pg_drawframe?FRAMESIZE:0) + x * PIXELSIZE * 2
        + y * LINESIZE * 2 + 0x40000000;
}

void pgScreenFrame(long mode, long frame)
{
    pg_screenmode = mode;
    frame = (frame?1:0);
    pg_showframe = frame;
    if (mode == 0) {
        //screen off
        pg_drawframe = frame;
        sceDisplaySetFrameBuf(0, 0, 0, 1);
    } else if (mode == 1) {
        //show/draw same
        pg_drawframe = frame;
        sceDisplaySetFrameBuf(pg_vramtop + (pg_showframe?FRAMESIZE:0),
                              LINESIZE, PIXELSIZE, 1);
    } else if (mode == 2) {
        //show/draw different
        pg_drawframe = (frame?0:1);
        sceDisplaySetFrameBuf(pg_vramtop + (pg_showframe?FRAMESIZE:0),
                              LINESIZE, PIXELSIZE, 1);
    }
}

void pgScreenFlip()
{
    pg_showframe = (pg_showframe?0:1);
    pg_drawframe = (pg_drawframe?0:1);
    sceDisplaySetFrameBuf(pg_vramtop+(pg_showframe?FRAMESIZE:0), LINESIZE, PIXELSIZE, 0);
}

/*****************************************************************************/
int pga_ready = 0;
int pga_pause = 1;
int pga_handle;

void *(*pga_callback)(void);
int pga_threadhandle;
volatile int pga_terminate = 0;


static int pgaOutBlocking(unsigned long vol1, unsigned long vol2, void *buf)
{
    if (!pga_ready) return -1;
    if (vol1 > MAXVOLUME) vol1 = MAXVOLUME;
    if (vol2 > MAXVOLUME) vol2 = MAXVOLUME;

    return sceAudioOutputPannedBlocking(pga_handle, vol1, vol2, buf);
//    return sceAudio_2(pga_handle, vol1, vol2, buf);
}

static int pga_channel_thread(int args, void *argp)
{
    void *buf;
    unsigned long vol;

    if (pga_callback) {
        while (pga_terminate == 0) {
            buf = pga_callback();
            vol = pga_pause? 0 : MAXVOLUME;
            pgaOutBlocking(vol, vol, buf);
        }
    }

    sceKernelExitThread(0);
    return 0;
}

void pgaSetChannelCallback(void *callback)
{
    pga_callback = callback;
}

int pgaInit(int samples)
{
    pga_terminate = 0;
    pga_ready = 0;
    pga_threadhandle = -1;

#if 0
    if ((pga_handle = sceAudio_3(-1, samples, OUT_FMT_STEREO)) < 0) {
        return -1;
    }
#else
    if ((pga_handle = sceAudioChReserve(-1, samples, OUT_FMT_STEREO)) < 0) {
        return -1;
    }
#endif

    pga_ready = 1; //なぜかここに必要

    pga_threadhandle = sceKernelCreateThread("pgasnd0", (SceKernelThreadEntry)&pga_channel_thread, 0x12, 0x10000, 0, NULL);

    if (pga_threadhandle >= 0) {
        if (sceKernelStartThread(pga_threadhandle, 0, NULL) == 0) {
            return 0;
        }
        sceKernelDeleteThread(pga_threadhandle);
    }
    pga_threadhandle = -1;
    pga_ready = 0;
    return -1;
}

void pgaTermPre()
{
    pga_ready = 0;
    pga_terminate = 1;
}

void pgaTerm()
{
    pga_ready = 0;
    pga_terminate = 1;

    if (pga_threadhandle != -1) {
        sceKernelWaitThreadEnd(pga_threadhandle, NULL);
        sceKernelDeleteThread(pga_threadhandle);
        pga_threadhandle = -1;
    }

    if (pga_handle != -1) {
        sceAudioChRelease(pga_handle); //sceAudio_4(pga_handle);
    }
}

void pgaPause(int n)
{
    pga_pause = n? 1 : 0;
}

//バッファは64バイト境界じゃなくても大丈夫みたい
//[0]が左、[1]が右
//サンプル速度は44100
//vol1が左

/******************************************************************************/
void pgGeInit()
{
    int qid;
    static unsigned int GEcmd[64];

    sceGuInit();

    // Draw Area
    GEcmd[ 0] = 0x15000000UL | (0 << 10) | 0;
    GEcmd[ 1] = 0x16000000UL | (271 << 10) | 479;
    // Tex Enable
    GEcmd[ 2] = 0x1E000000UL | 1;
    // Viewport
    GEcmd[ 3] = 0x42000000UL | (((int)((float)(480)) >> 8) & 0x00FFFFFF);
    GEcmd[ 4] = 0x43000000UL | (((int)((float)(-272)) >> 8) & 0x00FFFFFF);
    GEcmd[ 5] = 0x44000000UL | (((int)((float)(50000)) >> 8) & 0x00FFFFFF);
    GEcmd[ 6] = 0x45000000UL | (((int)((float)(2048)) >> 8) & 0x00FFFFFF);
    GEcmd[ 7] = 0x46000000UL | (((int)((float)(2048)) >> 8) & 0x00FFFFFF);
    GEcmd[ 8] = 0x47000000UL | (((int)((float)(60000)) >> 8) & 0x00FFFFFF);
    GEcmd[ 9] = 0x4C000000UL | (1024 << 4);
    GEcmd[10] = 0x4D000000UL | (1024 << 4);
    // Model Color
    GEcmd[11] = 0x54000000UL;
    GEcmd[12] = 0x55000000UL | 0xFFFFFF;
    GEcmd[13] = 0x56000000UL | 0xFFFFFF;
    GEcmd[14] = 0x57000000UL | 0xFFFFFF;
    GEcmd[15] = 0x58000000UL | 0xFF;
    // Depth Buffer
    GEcmd[16] = 0x9E000000UL | 0x88000;
    GEcmd[17] = 0x9F000000UL | (0x44 << 16) | 512;
    // Tex
    GEcmd[18] = 0xC2000000UL | (0 << 16) | (0 << 8) | 0;
    GEcmd[19] = 0xC3000000UL | 1;
    GEcmd[20] = 0xC6000000UL | (1 << 8) | 1;
    GEcmd[21] = 0xC7000000UL | (1 << 8) | 1;
    GEcmd[22] = 0xC9000000UL | (0 << 16) | (0 << 8) | 3;
    // Pixel Format
    GEcmd[23] = 0xD2000000UL | 1;
    // Scissor
    GEcmd[24] = 0xD4000000UL | (0 << 10) | 0;
    GEcmd[25] = 0xD5000000UL | (271 << 10) | 479;
    // Depth
    GEcmd[26] = 0xD6000000UL | 10000;
    GEcmd[27] = 0xD7000000UL | 50000;
    // List End
    GEcmd[28] = 0x0F000000UL;
    GEcmd[29] = 0x0C000000UL;
    GEcmd[30] = 0;
    sceKernelDcacheWritebackAll();
    qid = sceGeListEnQueue(&GEcmd[0], &GEcmd[30], -1, 0);
    sceGeListSync(qid, 0);
}
