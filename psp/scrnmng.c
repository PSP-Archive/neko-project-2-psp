#include        "compiler.h"
// #include     <sys/time.h>
// #include     <signal.h>
// #include     <unistd.h>
#include        "scrnmng.h"
#include        "scrndraw.h"
#include        "vramhdl.h"
#include        "menubase.h"
#include        "softkbd.h"
#include "np2.h"
#include "pg.h"
#include "taskmng.h"
#include <pspge.h>

typedef struct {
    BOOL enable;
    int width;
    int height;
    int bpp;
    VRAMHDL vram;
} SCRNMNG;

typedef struct {
    int width;
    int height;
} SCRNSTAT;

static const char app_name[] = "Neko Project II";

static SCRNMNG scrnmng;
static SCRNSTAT scrnstat;
static SCRNSURF scrnsurf;

static CMNVRAM kbdvram;

typedef struct {
    int xalign;
    int yalign;
    int width;
    int height;
    int srcpos;
    int dstpos;
} DRAWRECT;

typedef struct {
    short tsx;      // texture buffer開始座標: (tsx, tsy)
    short tsy;
    short isx;      // image buffer開始座標: (isx, isy)
    short isy;
    short unknown1;
    short tex;      // texture buffer終了座標: (tex, tey)
    short tey;
    short iex;      // image buffer終了座標: (iex, iey)
    short iey;
    short unknown2;
} scr_vtx_t;

/*
  640*400をtextureに描画するが、texture bufferを1024*512にすると
  うまくいかないので512*512を2枚使う)

                           <--------- 512dot---------->
      vramtop   0x04000000 +--------------------------+
                           |                          |
                           |         実画面           |
                           |512*272*2*3               |
                           | 16bps*3画面 24pbs*2画面? |
      texture1  0x040cc000 +--------------------------+ A
                           |                          | |
                           |     512*400              |512dot
                           |- - - - - - - - - - - - - | |
                           |                          | V
      texture2  0x0414c000 +--------------------------+ A
                           |       :  308+4*90+4  :   | |
                           |128*400:- - - - - - - -   |512dot
                           | - - - -                  | |
                           |                          | V
                0x041cc000 +--------------------------+
*/

UINT8 *full_screenl = (UINT8 *)0x040cc000; // 左半分
UINT8 *full_screenr = (UINT8 *)0x0414c000; // 右半分
static unsigned int *GEcmd = (unsigned int *)0x441cc000; // 1024*512*2足す
static short *ScreenVertex = (short *)0x441cc100;
static short *ScreenVertex2 = (short *)0x441cc200;
static short *SoftkbdVertex = (short *)0x441cc300;

int gecbid = -1;
static unsigned int *last_gc;
short skbdx = 512, skbdy = 0; //初期状態は画面外に置いておく
static int psp_scrn_mode = 0;
static short tx = 0, ty = 0;

// 左半分
scr_vtx_t scr_vtx[] = {
    {0, 0, 24, 1, 0, 512, 400, 370, 271, 0}, // scrn0 432x270
    {0, 0, 0, 0, 0, 512, 400, 384, 272, 0}, // scrn1 480x272
    {0, 0, 0, 0, 0, 512, 362, 384, 272, 0}, // scrn2 480x300
    {0, 0, 0, 0, 0, 480, 272, 480, 272, 0}  // scrn3 640x400
};
// 右半分
scr_vtx_t scr_vtx2[] = {
    {0, 0, 370, 1, 0, 128, 400, 456, 271, 0}, // scrn0
    {0, 0, 384, 0, 0, 128, 400, 480, 272, 0}, // scrn1
    {0, 0, 384, 0, 0, 128, 362, 480, 272, 0}, // scrn2
    {0, 0, 480, 0, 0, 128, 272, 608, 272, 0}  // scrn3
};

static unsigned short mouse_cursor[] = {
    0xffff, 0xffff, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0xffff, 0xffff, 0xffff, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0001, 0x0001, 0x0000,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0001, 0x0000,
    0xffff, 0xffff, 0xffff, 0xffff, 0x0001, 0x0001, 0x0001, 0x0000,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0001, 0x0000, 0x0000,
    0xffff, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001, 0x0000, 0x0000,
    0x0001, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001, 0x0000, 0x0000,
    0x0000, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001, 0x0001, 0x0000,
    0x0000, 0x0001, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001, 0x0000,
    0x0000, 0x0000, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001, 0x0000,
    0x0000, 0x0000, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001, 0x0001,
    0x0000, 0x0000, 0x0001, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001,
    0x0000, 0x0000, 0x0000, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001,
    0x0000, 0x0000, 0x0000, 0x0001, 0xffff, 0xffff, 0xffff, 0x0001,
    0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001
};

short pspmx = 0, pspmy = 0;
static int scr0o_f = 0;

// カーソル描画
static void draw_cursor(short x, short y)
{
    int i, j, idx;
    unsigned short *vp;

    vp = (unsigned short *)(pgGetVramAddr(x, y));

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 8; j++) {
            idx = i * 8 + j;
            /* 0なら描かない(透過させる) */
            if (mouse_cursor[idx] != 0x0) {
                *vp = mouse_cursor[idx];
            }
            vp++;
        }
        vp += 512; //次の行
        vp -= 8; // カーソル幅分戻す
    }
}
void scrnmng_draw_cursor()
{
    draw_cursor(pspmx, pspmy);
}

// 432x270の画面モードで、外枠の黒領域をクリアする
static void fill_scrn0out()
{
    unsigned short *vp;
    int i, j;

    if (psp_scrn_mode != 0) {
        return;
    }

    vp = (unsigned short *)pgGetVramAddr(0, 0);
    for (i = 0; i < 480; i++) {
        *vp++ = 0;
    }
    vp = (unsigned short *)pgGetVramAddr(0, 271);
    for (i = 0; i < 480; i++) {
        *vp++ = 0;
    }
    vp = (unsigned short *)pgGetVramAddr(0, 0);
    for (i = 0; i < 272; i++) {
        for (j = 0; j < 24; j++) {
            *vp++ = 0;
        }
        vp += 512;
        vp -= 24;
    }
    vp = (unsigned short *)pgGetVramAddr(480 - 24, 0);
    for (i = 0; i < 272; i++) {
        for (j = 0; j < 24; j++) {
            *vp++ = 0;
        }
        vp += 512;
        vp -= 24;
    }
}

void scrnmng_change_scrn(UINT8 scrn_mode)
{
    psp_scrn_mode = (int)scrn_mode;

    if (psp_scrn_mode == 0) {
        // 外枠を表・裏面ともにクリアする
        scr0o_f = 2;
    }

    if (psp_scrn_mode == 2) {
        // (400 - 2y) * 0.75 = 272 ⇒ y = 18
        tx = 0, ty = 18; // 上下を18ドットずつはみ出るようにする
    } else {
        tx = 0, ty = 0;
    }
}

BOOL scrnmng_set_scrn_pos(short ax, short ay)
{
    short tx0, ty0, tmpx;

    tx0 = tx, ty0 = ty;

    // 画面からはみ出ない画面モードなら終了
    if (psp_scrn_mode == 0 || psp_scrn_mode == 1) {
        return FALSE;
    }

    if (psp_scrn_mode == 2) {
        // (400 - y) * 0.75 = 272 ⇒ y=38
        (void)taskmng_mouse_anapad(&tmpx, &ty, ax, ay, 0, 38);
    } else if (psp_scrn_mode == 3) {
        (void)taskmng_mouse_anapad(&tx, &ty, ax, ay, 160, 128);
    }

    return (tx != tx0 || ty != ty0);
}

void scrnmng_gu_update()
{
    static int qid = -1;

    // ソフトキーボード
    scr_vtx_t skbd_vtx = {128, 0, skbdx, skbdy, 0,
                          128 + 308 + 4, 0 + 90 + 4,
                          skbdx + 308 + 4, skbdy + 90 + 4, 0};

    if (qid >= 0) {
        sceGeListSync(qid, 0);
    }

    *(scr_vtx_t *)ScreenVertex = scr_vtx[psp_scrn_mode];
    ((scr_vtx_t *)ScreenVertex)->tsx = tx;
    ((scr_vtx_t *)ScreenVertex)->tsy = ty;
    ((scr_vtx_t *)ScreenVertex)->tex += tx;
    ((scr_vtx_t *)ScreenVertex)->tey += ty;
    *(scr_vtx_t *)ScreenVertex2 = scr_vtx2[psp_scrn_mode];
    ((scr_vtx_t *)ScreenVertex2)->tsy = ty;
    ((scr_vtx_t *)ScreenVertex2)->tey += ty;
    if (tx > 32) {
        ((scr_vtx_t *)ScreenVertex2)->isx -= tx - 32;
        ((scr_vtx_t *)ScreenVertex2)->iex -= tx - 32;
    }
    *(scr_vtx_t *)SoftkbdVertex = skbd_vtx;

    /* 実画面の表<->裏切替。31-24bitは変わらないのでGEcmd[1]は触らない */
    GEcmd[0] = 0x9C000000UL |
        ((UINT32)(UINT8 *)pgGetVramAddr(0, 0) & 0x00FFFFFF);

    if (menuvram || skbdx < 512) {
        fill_scrn0out();
        scr0o_f = 2;
    } else if (scr0o_f) {
        fill_scrn0out();
        scr0o_f--;
    }

    sceKernelDcacheWritebackAll();
    qid = sceGeListEnQueue(&GEcmd[0], last_gc, gecbid, NULL);
}

static int set_gecmd(int id, unsigned int *gc)
{
    while (*gc != 0) {
        GEcmd[id++] = *gc++;
    }

    return id;
}

void scrnmng_gu_init()
{
    unsigned int log2w = 9, log2h = 9; // 512*512
    int last_id;

    // ソフトキーボード
    scr_vtx_t skbd_vtx = {128, 0, skbdx, skbdy, 0,
                          128 + 308 + 4, 0 + 90 + 4,
                          skbdx + 308 + 4, skbdy + 90 + 4, 0};

    // ソフトキーボードの外枠だけ黒塗りすればよいが、面倒なので全部クリア。
    memset(full_screenr, 0, 512 * 2 * 512);

    unsigned int gc[] = {
        // Set Draw Buffer
        0x9C000000UL | ((UINT32)(UINT8 *)pgGetVramAddr(0, 0) & 0x00FFFFFF),
        0x9D000000UL |
        (((UINT32)(UINT8 *)pgGetVramAddr(0, 0) & 0xFF000000) >> 8) | 512,
        // --- 640*400の左側 512*400
        // Set Tex Buffer
        0xA0000000UL | ((UINT32)(UINT8 *)full_screenl & 0x00FFFFFF),
        0xA8000000UL | (((UINT32)(UINT8 *)full_screenl & 0xFF000000) >> 8) |
        512,
        0xB8000000UL | (log2h << 8) | log2w,
        // Tex Flush
        0xCB000000UL,
        // Set Vertex
        0x12000000UL |
        (1 << 23) | (0 << 11) | (0 << 9) | (2 << 7) | (0 << 5) | (0 << 2) | 2,
        0x10000000UL | (((UINT32)(void *)ScreenVertex & 0xFF000000) >> 8),
        0x01000000UL | ((UINT32)(void *)ScreenVertex & 0x00FFFFFF),
        // Draw Vertex
        0x04000000UL | (6 << 16) | 2,
        // --- 640*400の右側 128*400
        // Set Tex Buffer
        0xA0000000UL | ((UINT32)(UINT8 *)full_screenr & 0x00FFFFFF),
        0xA8000000UL | (((UINT32)(UINT8 *)full_screenr & 0xFF000000) >> 8) |
        512,
        0xB8000000UL | (log2h << 8) | log2w,
        // Tex Flush
        0xCB000000UL,
        // Set Vertex
        0x12000000UL |
        (1 << 23) | (0 << 11) | (0 << 9) | (2 << 7) | (0 << 5) | (0 << 2) | 2,
        0x10000000UL |
        (((UINT32)(void *)ScreenVertex2 & 0xFF000000) >> 8),
        0x01000000UL | ((UINT32)(void *)ScreenVertex2 & 0x00FFFFFF),
        // Draw Vertex
        0x04000000UL | (6 << 16) | 2,
        // --- ソフトキーボード用 308*90
        // Set Vertex
        0x12000000UL |
        (1 << 23) | (0 << 11) | (0 << 9) | (2 << 7) | (0 << 5) | (0 << 2) | 2,
        0x10000000UL |
        (((UINT32)(void *)SoftkbdVertex & 0xFF000000) >> 8),
        0x01000000UL | ((UINT32)(void *)SoftkbdVertex & 0x00FFFFFF),
        // Draw Vertex
        0x04000000UL | (6 << 16) | 2,
        // List End
        0x0F000000UL,
        0x0C000000UL,
        // End flag for set_gecmd()
        0
    };

    /* 構造体のコピー */
    *(scr_vtx_t *)ScreenVertex = scr_vtx[psp_scrn_mode];
    ((scr_vtx_t *)ScreenVertex)->tsx = tx;
    ((scr_vtx_t *)ScreenVertex)->tsy = ty;
    ((scr_vtx_t *)ScreenVertex)->tex += tx;
    ((scr_vtx_t *)ScreenVertex)->tey += ty;
    *(scr_vtx_t *)ScreenVertex2 = scr_vtx2[psp_scrn_mode];
    *(scr_vtx_t *)SoftkbdVertex = skbd_vtx;

    last_id = set_gecmd(0, gc);
    last_gc = &GEcmd[last_id];
    *last_gc = 0x00000000UL; // NOP
}

void scrnmng_set_pspmxy(short x, short y)
{
    pspmx = x, pspmy = y;
}

static BOOL calcdrawrect(DRAWRECT *dr, VRAMHDL s, const RECT_T *rt) {

	int		pos;

	dr->xalign = 2; // depth(16bpp) / 8
	dr->yalign = 512 * 2; //次の行までのサイズ？横は実画面？
	dr->srcpos = 0;
	dr->dstpos = 0;
	dr->width = min(scrnmng.width, s->width);
	dr->height = min(scrnmng.height, s->height);
	if (rt) {
		pos = max(rt->left, 0);
		dr->srcpos += pos;
		dr->dstpos += pos * dr->xalign;
		dr->width = min(rt->right, dr->width) - pos;

		pos = max(rt->top, 0);
		dr->srcpos += pos * s->width;
		dr->dstpos += pos * dr->yalign;
		dr->height = min(rt->bottom, dr->height) - pos;
	}
	if ((dr->width <= 0) || (dr->height <= 0)) {
		return(FAILURE);
	}
	return(SUCCESS);
}


void scrnmng_initialize(void)
{
    scrnstat.width = 640;
    scrnstat.height = 400;
}

void scrnmng_skbd_key_reverse(int x, int y, int w, int h)
{
    short *dst;
    UINT8 *tmp;
    int i, j;

    dst = (short *)((UINT8 *)kbdvram.ptr +
                    x * kbdvram.xalign + y * kbdvram.yalign);

    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            *dst = ~*dst;
            dst++;
        }

#if 0
        (UINT8 *)dst -= (w * kbdvram.xalign);
        (UINT8 *)dst += kbdvram.yalign;
#else
        tmp = (UINT8 *)dst;
        tmp -= w * kbdvram.xalign;
        tmp += kbdvram.yalign;
        dst = (short *)tmp;
#endif
    }
}

static void palcnv(CMNPAL *dst, const RGB32 *src, UINT pals, UINT bpp)
{
    UINT i;

    if (bpp == 16) {
        for (i = 0; i < pals; i++) {
            dst[i].pal16 = ((src[i].p.r & 0xf8) << 8) |
                ((src[i].p.g & 0xfc) << 3) | (src[i].p.b >> 3);
        }
    }
}

BOOL scrnmng_create(int width, int height)
{
    scrnmng.enable = TRUE;
    scrnmng.width = width;
    scrnmng.height = height;
    scrnmng.bpp = 16; // 16bpp for psp

    softkbd_initialize();
    kbdvram.width = 512;
    kbdvram.height = 512;
    kbdvram.xalign = 2;
    kbdvram.yalign = 512 * 2;
    //テクスチャ用full_screenrの左128ドットはメインスクリーン用に
    //使っているので、あまっている部分をソフトキーボード用に使う。
    kbdvram.ptr = (UINT8 *)full_screenr + (128 + 2) * kbdvram.xalign
        + 2 * kbdvram.yalign;
    kbdvram.bpp = 16;
    softkbd_paint(&kbdvram, palcnv, TRUE);

    return(SUCCESS);

}

void scrnmng_destroy(void) {

	scrnmng.enable = FALSE;
}

RGB16 scrnmng_makepal16(RGB32 pal32) {
	RGB16	ret;
#ifdef PSP
	ret = (pal32.p.b & 0xf8) << 7;
	ret += (pal32.p.g & 0xf8) << 2;
	ret += pal32.p.r >> 3;
#else
	ret = (pal32.p.r & 0xf8) << 8;
#if defined(SIZE_QVGA)
	ret += (pal32.p.g & 0xfc) << (3 + 16);
#else
	ret += (pal32.p.g & 0xfc) << 3;
#endif
	ret += pal32.p.b >> 3;

#endif
	return(ret);
}

void scrnmng_setwidth(int posx, int width)
{
    scrnstat.width = width;
}

void scrnmng_setheight(int posy, int height)
{
    scrnstat.height = height;
}

const SCRNSURF *scrnmng_surflock(void)
{
if (scrnmng.vram == NULL) {
        scrnsurf.ptr = (UINT8 *)full_screenl;
        scrnsurf.xalign = 2; // depth(16bpp) / 8
        scrnsurf.yalign = 512 * 2;
        scrnsurf.bpp = 16; // depth(16bpp)
    } else {
        scrnsurf.ptr = scrnmng.vram->ptr;
        scrnsurf.xalign = scrnmng.vram->xalign;
        scrnsurf.yalign = scrnmng.vram->yalign;
        scrnsurf.bpp = scrnmng.vram->bpp;
    }
    scrnsurf.width = min(scrnstat.width, 640);
    scrnsurf.height = min(scrnstat.height, 400);
    scrnsurf.extend = 0;
    return(&scrnsurf);
}

void scrnmng_surfunlock(const SCRNSURF *surf)
{
        scrnmng_gu_update();
}


// ----

BOOL scrnmng_entermenu(SCRNMENU *smenu)
{
    if (smenu == NULL) {
        goto smem_err;
    }
    vram_destroy(scrnmng.vram);
    scrnmng.vram
        = vram_create(scrnmng.width, scrnmng.height, FALSE, scrnmng.bpp);
    if (scrnmng.vram == NULL) {
        goto smem_err;
    }
    scrndraw_redraw();
#if 0
    smenu->width = scrnmng.width;
    smenu->height = scrnmng.height;
#else
    // メニュー画面はPSPサイズにする
    smenu->width = 480;
    smenu->height = 272;
#endif
    smenu->bpp = (scrnmng.bpp == 32)?24:scrnmng.bpp;
    return(SUCCESS);

 smem_err:
    return(FAILURE);
}

void scrnmng_leavemenu(void) {

	VRAM_RELEASE(scrnmng.vram);
}

void scrnmng_menudraw(const RECT_T *rct) {

    DRAWRECT dr;
    const UINT8 *p;
    const UINT8 *q;
//    UINT8 *r;
    UINT8 *a;
    int salign;
    int dalign;
    int x;

    if ((!scrnmng.enable) && (menuvram == NULL)) {
        return;
    }

    if (calcdrawrect(&dr, menuvram, rct) == SUCCESS) {
        p = scrnmng.vram->ptr + (dr.srcpos * 2);
        q = menuvram->ptr + (dr.srcpos * 2);
//        r = pgGetVramAddr(0, 0) + dr.dstpos;
        a = menuvram->alpha + dr.srcpos;
        salign = menuvram->width;
        dalign = dr.yalign - (dr.width * dr.xalign);
        do {
            x = 0;
            do {
                if (a[x]) {
                    if (!(a[x] & 2)) {
                        a[x] = 0;
                    }
#if 0
                    if (a[x] & 2) {
                        // ダイアログ描画
//                        *(UINT16 *)r = *(UINT16 *)(q + (x * 2));
                    } else {
                        // ダイアログ消去・移動時の背景(PC-98画面)描画
                        a[x] = 0;
//                        *(UINT16 *)r = *(UINT16 *)(p + (x * 2));
                    }
#endif
                }
//                r += dr.xalign;
            } while(++x < dr.width);
            p += salign * 2;
            q += salign * 2;
//            r += dalign;
            a += salign;
        } while(--dr.height);
    }
}

void scrnmng_menudraw2(const RECT_T *rct) {

    DRAWRECT dr;
    const UINT8 *p;
    const UINT8 *q;
    UINT8 *r;
    UINT8 *a;
    int salign;
    int dalign;
    int x;

    if ((!scrnmng.enable) && (menuvram == NULL)) {
        return;
    }

    // 全範囲再描画なので、第3引数はNULLを指定
    if (calcdrawrect(&dr, menuvram, NULL) == SUCCESS) {
        p = scrnmng.vram->ptr + (dr.srcpos * 2);
        q = menuvram->ptr + (dr.srcpos * 2);
        r = (UINT8 *)(pgGetVramAddr(0, 0) + dr.dstpos);
        a = menuvram->alpha + dr.srcpos;
        salign = menuvram->width;
        dalign = dr.yalign - (dr.width * dr.xalign);
        do {
            x = 0;
            do {
                if (a[x]) {
                    if (a[x] & 2) {
                        // ダイアログ描画
                        *(UINT16 *)r = *(UINT16 *)(q + (x * 2));
                    } else {
                        // ダイアログ消去・移動時の背景(PC-98画面)描画
                        a[x] = 0;
                        *(UINT16 *)r = *(UINT16 *)(p + (x * 2));
                    }
                }
                r += dr.xalign;
            } while(++x < dr.width);
            p += salign * 2;
            q += salign * 2;
            r += dalign;
            a += salign;
        } while(--dr.height);
    }
}
