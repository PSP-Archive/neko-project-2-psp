
#define INTR_FAST

#define	I286_STAT		i286core.s.r

#define	I286_REG		i286core.s.r
#define	I286_SEGREG		i286core.s.r.w.es

#define	I286_AX			i286core.s.r.w.ax
#define	I286_BX			i286core.s.r.w.bx
#define	I286_CX			i286core.s.r.w.cx
#define	I286_DX			i286core.s.r.w.dx
#define	I286_SI			i286core.s.r.w.si
#define	I286_DI			i286core.s.r.w.di
#define	I286_BP			i286core.s.r.w.bp
#define	I286_SP			i286core.s.r.w.sp
#define	I286_CS			i286core.s.r.w.cs
#define	I286_DS			i286core.s.r.w.ds
#define	I286_ES			i286core.s.r.w.es
#define	I286_SS			i286core.s.r.w.ss
#define	I286_IP			i286core.s.r.w.ip

#define	SEG_BASE		i286core.s.es_base
#define	ES_BASE			i286core.s.es_base
#define	CS_BASE			i286core.s.cs_base
#define	SS_BASE			i286core.s.ss_base
#define	DS_BASE			i286core.s.ds_base
#define	SS_FIX			i286core.s.ss_fix
#define	DS_FIX			i286core.s.ds_fix

#define	I286_AL			i286core.s.r.b.al
#define	I286_BL			i286core.s.r.b.bl
#define	I286_CL			i286core.s.r.b.cl
#define	I286_DL			i286core.s.r.b.dl
#define	I286_AH			i286core.s.r.b.ah
#define	I286_BH			i286core.s.r.b.bh
#define	I286_CH			i286core.s.r.b.ch
#define	I286_DH			i286core.s.r.b.dh

#define	I286_FLAG		i286core.s.r.w.flag
#define	I286_FLAGL		i286core.s.r.b.flag_l
#define	I286_FLAGH		i286core.s.r.b.flag_h
#define	I286_TRAP		i286core.s.trap
#define	I286_OV			i286core.s.ovflag

#define	I286_GDTR		i286core.s.GDTR
#define	I286_IDTR		i286core.s.IDTR
#define	I286_LDTR		i286core.s.LDTR
#define	I286_LDTRC		i286core.s.LDTRC
#define	I286_TR			i286core.s.TR
#define	I286_TRC		i286core.s.TRC
#define	I286_MSW		i286core.s.MSW

#define	I286_REMCLOCK	i286core.s.remainclock
#define	I286_BASECLOCK	i286core.s.baseclock
#define	I286_CLOCK		i286core.s.clock
#define	I286_ADRSMASK	i286core.s.adrsmask

#define	I286_PREFIX		i286core.s.prefix

#define	I286_INPADRS	i286core.e.inport


#define I286FN	static void

typedef void (*I286OP)(void);

extern void CPUCALL i286c_intnum(UINT vect, REG16 IP);
extern UINT32 i286c_selector(UINT sel);

#if !defined(MEMOPTIMIZE) || (MEMOPTIMIZE < 2)
extern void i286cea_initialize(void);
#endif

#define i286_memoryread(a)			memp_read8(a)
#define i286_memoryread_w(a)		memp_read16(a)
#define i286_memoryread_d(a)		memp_read32(a)
#define i286_memorywrite(a, v)		memp_write8(a, v)
#define i286_memorywrite_w(a, v)	memp_write16(a, v)
#define i286_memorywrite_d(a, v)	memp_write32(a, v)

