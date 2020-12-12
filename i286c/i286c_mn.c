#include "bios.h"

#define	NEXT_OPCODE \
	if (I286_REMCLOCK < 1) { \
		I286_BASECLOCK += (1 - I286_REMCLOCK); \
		I286_REMCLOCK = 1; \
	}

#define	REMAIN_ADJUST(c) \
	if (I286_REMCLOCK != (c)) { \
		I286_BASECLOCK += ((c) - I286_REMCLOCK); \
		I286_REMCLOCK = (c); \
	}

/********** i286 functions **********/

_reserved: {
	INT_NUM(6, I286_IP - 1);
	goto *retlb;
}

_add_ea_r8: // 00: add EA, REG8
{
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			dst = i286_memoryread(madr);
			ADDBYTE(res, dst, src);
			i286_memorywrite(madr, (REG8)res);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	dst = *p8;
	ADDBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

_add_ea_r16: // 01: add EA, REG16
{
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			dst = i286_memoryread_w(madr);
			ADDWORD(res, dst, src);
			i286_memorywrite_w(madr, (REG16)res);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	dst = *p16;
	ADDWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

_add_r8_ea: { // 02: add REG8, EA
	PREPART_REG8_EA(op, src, p8, 2, 7);
	dst = *p8;
	ADDBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

_add_r16_ea: { // 03: add REG16, EA
	PREPART_REG16_EA(op, src, p16, 2, 7);
	dst = *p16;
	ADDWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

_add_al_data8: { // 04: add al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src);
	ADDBYTE(res, I286_AL, src);
	I286_AL = (UINT8)res;
	goto *retlb;
}

_add_ax_data16: { // 05: add ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src);
	ADDWORD(res, I286_AX, src);
	I286_AX = (UINT16)res;
	goto *retlb;
}

_push_es: { // 06: push es
	REGPUSH(I286_ES, 3);
	goto *retlb;
}

_pop_es: { // 07: pop es
	REGPOP(tmp, 5)
	I286_ES = tmp;
	ES_BASE = SEGSELECT(tmp);
	goto *retlb;
}

_or_ea_r8: { // 08: or EA, REG8
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			dst = i286_memoryread(madr);
			ORBYTE(dst, src);
			i286_memorywrite(madr, (REG8)dst);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	dst = *p8;
	ORBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

_or_ea_r16: { // 09: or EA, REG16
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			dst = i286_memoryread_w(madr);
			ORWORD(dst, src);
			i286_memorywrite_w(madr, (REG16)dst);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	dst = *p16;
	ORWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

_or_r8_ea: { // 0a: or REG8, EA
	PREPART_REG8_EA(op, src, p8, 2, 7);
	dst = *p8;
	ORBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

_or_r16_ea: { // 0b: or REG16, EA
	PREPART_REG16_EA(op, src, p16, 2, 7);
	dst = *p16;
	ORWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

_or_al_data8: { // 0c: or al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src);
	dst = I286_AL;
	ORBYTE(dst, src);
	I286_AL = (UINT8)dst;
	goto *retlb;
}

_or_ax_data16: { // 0d: or ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src);
	dst = I286_AX;
	ORWORD(dst, src);
	I286_AX = (UINT16)dst;
	goto *retlb;
}

_push_cs: { // 0e: push cs
	REGPUSH(I286_CS, 3);
	goto *retlb;
}

/*xxxxx missing 0f xxxxx*/
// i286c_cts

_adc_ea_r8: { // 10: adc EA, REG8
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			dst = i286_memoryread(madr);
			ADCBYTE(res, dst, src);
			i286_memorywrite(madr, (REG8)res);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	dst = *p8;
	ADCBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

_adc_ea_r16: { // 11: adc EA, REG16
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			dst = i286_memoryread_w(madr);
			ADCWORD(res, dst, src);
			i286_memorywrite_w(madr, (REG16)res);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	dst = *p16;
	ADCWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

_adc_r8_ea: { // 12: adc REG8, EA
	PREPART_REG8_EA(op, src, p8, 2, 7);
	dst = *p8;
	ADCBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

_adc_r16_ea: { // 13: adc REG16, EA
	PREPART_REG16_EA(op, src, p16, 2, 7);
	dst = *p16;
	ADCWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

_adc_al_data8: { // 14: adc al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src);
	ADCBYTE(res, I286_AL, src);
	I286_AL = (UINT8)res;
	goto *retlb;
}

_adc_ax_data16: { // 15: adc ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src);
	ADCWORD(res, I286_AX, src);
	I286_AX = (UINT16)res;
	goto *retlb;
}

_push_ss: { // 16: push ss
	REGPUSH(I286_SS, 3);
	goto *retlb;
}

_pop_ss: { // 17: pop ss
	REGPOP(tmp, 5)
	I286_SS = tmp;
	SS_BASE = SEGSELECT(tmp);
	SS_FIX = SS_BASE;
	NEXT_OPCODE
	goto *retlb;
}

_sbb_ea_r8: { // 18: sbb EA, REG8
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			dst = i286_memoryread(madr);
			SBBBYTE(res, dst, src);
			i286_memorywrite(madr, (REG8)res);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	dst = *p8;
	SBBBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

_sbb_ea_r16: { // 19: sbb EA, REG16
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			dst = i286_memoryread_w(madr);
			SBBWORD(res, dst, src);
			i286_memorywrite_w(madr, (REG16)res);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	dst = *p16;
	SBBWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

_sbb_r8_ea: { // 1a: sbb REG8, EA
	PREPART_REG8_EA(op, src, p8, 2, 7);
	dst = *p8;
	SBBBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

_sbb_r16_ea: { // 1b: sbb REG16, EA
	PREPART_REG16_EA(op, src, p16, 2, 7);
	dst = *p16;
	SBBWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

_sbb_al_data8: { // 1c: adc al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src);
	SBBBYTE(res, I286_AL, src);
	I286_AL = (UINT8)res;
	goto *retlb;
}

_sbb_ax_data16: { // 1d: adc ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src);
	SBBWORD(res, I286_AX, src);
	I286_AX = (UINT16)res;
	goto *retlb;
}

_push_ds: { // 1e: push ds
	REGPUSH(I286_DS, 3);
	goto *retlb;
}

_pop_ds: { // 1f: pop ds
	REGPOP(tmp, 5)
	I286_DS = tmp;
	DS_BASE = SEGSELECT(tmp);
	DS_FIX = DS_BASE;
	goto *retlb;
}

_and_ea_r8: { // 20: and EA, REG8
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			dst = i286_memoryread(madr);
			ANDBYTE(dst, src);
			i286_memorywrite(madr, (REG8)dst);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	dst = *p8;
	ANDBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

_and_ea_r16: { // 21: and EA, REG16
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			dst = i286_memoryread_w(madr);
			ANDWORD(dst, src);
			i286_memorywrite_w(madr, (REG16)dst);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	dst = *p16;
	ANDWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

_and_r8_ea: { // 22: and REG8, EA
	PREPART_REG8_EA(op, src, p8, 2, 7);
	dst = *p8;
	ANDBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

_and_r16_ea: { // 23: and REG16, EA
	PREPART_REG16_EA(op, src, p16, 2, 7);
	dst = *p16;
	ANDWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

_and_al_data8: { // 24: and al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src);
	dst = I286_AL;
	ANDBYTE(dst, src);
	I286_AL = (UINT8)dst;
	goto *retlb;
}

_and_ax_data16: { // 25: and ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src);
	dst = I286_AX;
	ANDWORD(dst, src);
	I286_AX = (UINT16)dst;
	goto *retlb;
}

_segprefix_es: { // 26: es:
	SS_FIX = ES_BASE;
	DS_FIX = ES_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(opcode);
		retstk[retstk_idx++] = retlb;
		retlb = &&_segpfx_es_lb;
		goto *i286op[opcode];
	_segpfx_es_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_daa: { // 27: daa
	I286_WORKCLOCK(3);
	I286_OV = ((I286_AL < 0x80) && 
				((I286_AL >= 0x7a) ||
				((I286_AL >= 0x1a) && (I286_FLAGL & C_FLAG))));
	if ((I286_FLAGL & A_FLAG) || ((I286_AL & 0x0f) > 9)) {
		I286_FLAGL |= A_FLAG;
		I286_FLAGL |= (UINT8)((I286_AL + 6) >> 8);
		I286_AL += 6;
	}
	if ((I286_FLAGL & C_FLAG) || (I286_AL > 0x9f)) {
		I286_FLAGL |= C_FLAG;
		I286_AL += 0x60;
	}
	I286_FLAGL &= A_FLAG | C_FLAG;
	I286_FLAGL |= BYTESZPF(I286_AL);
	goto *retlb;
}

_sub_ea_r8: { // 28: sub EA, REG8
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			dst = i286_memoryread(madr);
			SUBBYTE(res, dst, src);
			i286_memorywrite(madr, (REG8)res);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	dst = *p8;
	SUBBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

_sub_ea_r16: { // 29: sub EA, REG16
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			dst = i286_memoryread_w(madr);
			SUBWORD(res, dst, src);
			i286_memorywrite_w(madr, (REG16)res);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	dst = *p16;
	SUBWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

_sub_r8_ea: { // 2a: sub REG8, EA
	PREPART_REG8_EA(op, src, p8, 2, 7);
	dst = *p8;
	SUBBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

_sub_r16_ea: { // 2b: sub REG16, EA
	PREPART_REG16_EA(op, src, p16, 2, 7);
	dst = *p16;
	SUBWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

_sub_al_data8: { // 2c: sub al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src);
	SUBBYTE(res, I286_AL, src);
	I286_AL = (UINT8)res;
	goto *retlb;
}

_sub_ax_data16: { // 2d: sub ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src);
	SUBWORD(res, I286_AX, src);
	I286_AX = (UINT16)res;
	goto *retlb;
}

_segprefix_cs: { // 2e: cs:
	SS_FIX = CS_BASE;
	DS_FIX = CS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(opcode);
		retstk[retstk_idx++] = retlb;
		retlb = &&_segpfx_cs_lb;
		goto *i286op[opcode];
	_segpfx_cs_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_das: { // 2f: das
	I286_WORKCLOCK(3);
	if ((I286_FLAGL & C_FLAG) || (I286_AL > 0x99)) {
		I286_FLAGL |= C_FLAG;
		I286_AL -= 0x60;
	}
	if ((I286_FLAGL & A_FLAG) || ((I286_AL & 0x0f) > 9)) {
		I286_FLAGL |= A_FLAG;
		I286_FLAGL |= ((I286_AL - 6) >> 8) & 1;
		I286_AL -= 6;
	}
	I286_FLAGL &= A_FLAG | C_FLAG;
	I286_FLAGL |= BYTESZPF(I286_AL);
	goto *retlb;
}

_xor_ea_r8: { // 30: xor EA, REG8
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			dst = i286_memoryread(madr);
			XORBYTE(dst, src);
			i286_memorywrite(madr, (REG8)dst);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	dst = *p8;
	XORBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

_xor_ea_r16: { // 31: xor EA, REG16
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			dst = i286_memoryread_w(madr);
			XORWORD(dst, src);
			i286_memorywrite_w(madr, (REG16)dst);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	dst = *p16;
	XORWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

_xor_r8_ea: { // 32: xor REG8, EA
	PREPART_REG8_EA(op, src, p8, 2, 7);
	dst = *p8;
	XORBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

_xor_r16_ea: { // 33: or REG16, EA
	PREPART_REG16_EA(op, src, p16, 2, 7);
	dst = *p16;
	XORWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

_xor_al_data8: { // 34: or al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src);
	dst = I286_AL;
	XORBYTE(dst, src);
	I286_AL = (UINT8)dst;
	goto *retlb;
}

_xor_ax_data16: { // 35: or ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src);
	dst = I286_AX;
	XORWORD(dst, src);
	I286_AX = (UINT16)dst;
	goto *retlb;
}

_segprefix_ss: { // 36: ss:
	SS_FIX = SS_BASE;
	DS_FIX = SS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(opcode);
		retstk[retstk_idx++] = retlb;
		retlb = &&_segpfx_ss_lb;
		goto *i286op[opcode];
	_segpfx_ss_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_aaa: { // 37: aaa
	I286_WORKCLOCK(3);
	if ((I286_FLAGL & A_FLAG) || ((I286_AL & 0xf) > 9)) {
		I286_FLAGL |= A_FLAG | C_FLAG;
		I286_AX += 6;
		I286_AH++;
	} else {
		I286_FLAGL &= ~(A_FLAG | C_FLAG);
	}
	I286_AL &= 0x0f;
	goto *retlb;
}

_cmp_ea_r8: { // 38: cmp EA, REG8
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		dst = *(REG8_B20(op));
		SUBBYTE(res, dst, src);
	} else {
		I286_WORKCLOCK(6);
		dst = i286_memoryread(CALC_EA(op));
		SUBBYTE(res, dst, src);
	}
	goto *retlb;
}

_cmp_ea_r16: { // 39: cmp EA, REG16
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		dst = *(REG16_B20(op));
		SUBWORD(res, dst, src);
	} else {
		I286_WORKCLOCK(6);
		dst = i286_memoryread_w(CALC_EA(op));
		SUBWORD(res, dst, src);
	}
	goto *retlb;
}

_cmp_r8_ea: { // 3a: cmp REG8, EA
	PREPART_REG8_EA(op, src, p8, 2, 6);
	dst = *p8;
	SUBBYTE(res, dst, src);
	goto *retlb;
}

_cmp_r16_ea: { // 3b: cmp REG16, EA
	PREPART_REG16_EA(op, src, p16, 2, 6);
	dst = *p16;
	SUBWORD(res, dst, src);
	goto *retlb;
}

_cmp_al_data8: { // 3c: cmp al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src);
	SUBBYTE(res, I286_AL, src);
	goto *retlb;
}

_cmp_ax_data16: { // 3d: cmp ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src);
	SUBWORD(res, I286_AX, src);
	goto *retlb;
}

_segprefix_ds: { // 3e: ds:
	SS_FIX = DS_BASE;
	DS_FIX = DS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(opcode);
		retstk[retstk_idx++] = retlb;
		retlb = &&_segpfx_ds_lb;
		goto *i286op[opcode];
	_segpfx_ds_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_aas: { // 3f: aas
	I286_WORKCLOCK(3);
	if ((I286_FLAGL & A_FLAG) || ((I286_AL & 0xf) > 9)) {
		I286_FLAGL |= A_FLAG | C_FLAG;
		I286_AX -= 6;
		I286_AH--;
	} else {
		I286_FLAGL &= ~(A_FLAG | C_FLAG);
	}
	goto *retlb;
}

_inc_ax: { INCWORD2(I286_AX, 2); goto *retlb; }	// 40:	inc		ax
_inc_cx: { INCWORD2(I286_CX, 2); goto *retlb; }	// 41:	inc		cx
_inc_dx: { INCWORD2(I286_DX, 2); goto *retlb; }	// 42:	inc		dx
_inc_bx: { INCWORD2(I286_BX, 2); goto *retlb; }	// 43:	inc		bx
_inc_sp: { INCWORD2(I286_SP, 2); goto *retlb; }	// 44:	inc		sp
_inc_bp: { INCWORD2(I286_BP, 2); goto *retlb; }	// 45:	inc		bp
_inc_si: { INCWORD2(I286_SI, 2); goto *retlb; }	// 46:	inc		si
_inc_di: { INCWORD2(I286_DI, 2); goto *retlb; }	// 47:	inc		di
_dec_ax: { DECWORD2(I286_AX, 2); goto *retlb; }	// 48:	dec		ax
_dec_cx: { DECWORD2(I286_CX, 2); goto *retlb; }	// 49:	dec		cx
_dec_dx: { DECWORD2(I286_DX, 2); goto *retlb; }	// 4a:	dec		dx
_dec_bx: { DECWORD2(I286_BX, 2); goto *retlb; }	// 4b:	dec		bx
_dec_sp: { DECWORD2(I286_SP, 2); goto *retlb; }	// 4c:	dec		sp
_dec_bp: { DECWORD2(I286_BP, 2); goto *retlb; }	// 4d:	dec		bp
_dec_si: { DECWORD2(I286_SI, 2); goto *retlb; }	// 4e:	dec		si
_dec_di: { DECWORD2(I286_DI, 2); goto *retlb; }	// 4f:	dec		di

_push_ax: { REGPUSH(I286_AX, 3); goto *retlb; }	// 50:	push	ax
_push_cx: { REGPUSH(I286_CX, 3); goto *retlb; }	// 51:	push	cx
_push_dx: { REGPUSH(I286_DX, 3); goto *retlb; }	// 52:	push	dx
_push_bx: { REGPUSH(I286_BX, 3); goto *retlb; }	// 53:	push	bx
_push_sp: { SP_PUSH(I286_SP, 3); goto *retlb; }	// 54:	push	sp
_push_bp: { REGPUSH(I286_BP, 3); goto *retlb; }	// 55:	push	bp
_push_si: { REGPUSH(I286_SI, 3); goto *retlb; }	// 56:	push	si
_push_di: { REGPUSH(I286_DI, 3); goto *retlb; }	// 57:	push	di
_pop_ax: { REGPOP(I286_AX, 5); goto *retlb; }	// 58:	pop		ax
_pop_cx: { REGPOP(I286_CX, 5); goto *retlb; }	// 59:	pop		cx
_pop_dx: { REGPOP(I286_DX, 5); goto *retlb; }	// 5A:	pop		dx
_pop_bx: { REGPOP(I286_BX, 5); goto *retlb; }	// 5B:	pop		bx
_pop_sp: { SP_POP(I286_SP, 5); goto *retlb; }	// 5C:	pop		sp
_pop_bp: { REGPOP(I286_BP, 5); goto *retlb; }	// 5D:	pop		bp
_pop_si: { REGPOP(I286_SI, 5); goto *retlb; }	// 5E:	pop		si
_pop_di: { REGPOP(I286_DI, 5); goto *retlb; }	// 5F:	pop		di

#if (defined(ARM) || defined(X11)) && defined(BYTESEX_LITTLE)

_pusha: { // 60:	pusha
	I286_WORKCLOCK(17);
	tmp = I286_SP;
	madr = tmp + SS_BASE;
	if ((tmp < 16) || (INHIBIT_WORDP(madr))) {
		REGPUSH0(I286_AX)
		REGPUSH0(I286_CX)
		REGPUSH0(I286_DX)
		REGPUSH0(I286_BX)
	    REGPUSH0((REG16)tmp)
		REGPUSH0(I286_BP)
		REGPUSH0(I286_SI)
		REGPUSH0(I286_DI)
	} else {
		*(UINT16 *)(mem + madr - 2) = I286_AX;
		*(UINT16 *)(mem + madr - 4) = I286_CX;
		*(UINT16 *)(mem + madr - 6) = I286_DX;
		*(UINT16 *)(mem + madr - 8) = I286_BX;
		*(UINT16 *)(mem + madr - 10) = (UINT16)tmp;
		*(UINT16 *)(mem + madr - 12) = I286_BP;
		*(UINT16 *)(mem + madr - 14) = I286_SI;
		*(UINT16 *)(mem + madr - 16) = I286_DI;
		I286_SP -= 16;
	}
	goto *retlb;
}

_popa: { // 61:	popa
	I286_WORKCLOCK(19);
	tmp = I286_SP + 16;
	madr = tmp + SS_BASE;
	if ((tmp >= 0x10000) || (INHIBIT_WORDP(madr))) {
		REGPOP0(I286_DI);
		REGPOP0(I286_SI);
		REGPOP0(I286_BP);
		I286_SP += 2;
		REGPOP0(I286_BX);
		REGPOP0(I286_DX);
		REGPOP0(I286_CX);
		REGPOP0(I286_AX);
	} else {
		I286_DI = *(UINT16 *)(mem + madr - 16);
		I286_SI = *(UINT16 *)(mem + madr - 14);
		I286_BP = *(UINT16 *)(mem + madr - 12);
		I286_BX = *(UINT16 *)(mem + madr - 8);
		I286_DX = *(UINT16 *)(mem + madr - 6);
		I286_CX = *(UINT16 *)(mem + madr - 4);
		I286_AX = *(UINT16 *)(mem + madr - 2);
		I286_SP = (UINT16)tmp;
	}
	goto *retlb;
}

#else

_pusha: { // 60:	pusha
	tmp = I286_SP;
	REGPUSH0(I286_AX)
	REGPUSH0(I286_CX)
	REGPUSH0(I286_DX)
	REGPUSH0(I286_BX)
	REGPUSH0((REG16)tmp)
	REGPUSH0(I286_BP)
	REGPUSH0(I286_SI)
	REGPUSH0(I286_DI)
	I286_WORKCLOCK(17);
	goto *retlb;
}

_popa: { // 61:	popa
	REGPOP0(I286_DI);
	REGPOP0(I286_SI);
	REGPOP0(I286_BP);
	I286_SP += 2;
	REGPOP0(I286_BX);
	REGPOP0(I286_DX);
	REGPOP0(I286_CX);
	REGPOP0(I286_AX);
	I286_WORKCLOCK(19);
	goto *retlb;
}

#endif

_bound: { // 62:	bound
	tmp = 0;

	I286_WORKCLOCK(13); // ToDo
	GET_PCBYTE(op);
	if (op < 0xc0) {
		d16 = *(REG16_B53(op));
		madr = CALC_EA(op);
		if (d16 >= i286_memoryread_w(madr)) {
			madr += 2; // ToDo
			if (d16 <= i286_memoryread_w(madr)) {
				goto *retlb;
			}
		}
		tmp = 5;
	} else {
		tmp = 6;
	}
	INT_NUM(tmp, I286_IP);
	goto *retlb;
}

_arpl: { // 63:	arpl
	GET_PCBYTE(op)
	tmp = ((op < 0xc0)?1:0);
	I286_IP += (UINT8)tmp;
	I286_WORKCLOCK(tmp + 10);
	INT_NUM(6, I286_IP);
	goto *retlb;
}

_push_data16: { // 68:	push	DATA16
	GET_PCWORD(tmp)
	REGPUSH((UINT16)tmp, 3)
	goto *retlb;
}

_imul_reg_ea_data16: { // 69:	imul	REG, EA, DATA16
	SINT16	src;
	SINT16	dst;
	SINT32	res;

	PREPART_REG16_EA(op, src, p16, 21, 24)
	GET_PCWORD(dst)
	WORD_IMUL(res, dst, src)
	*p16 = (UINT16)res;
	goto *retlb;
}

_push_data8: { // 6A:	push	DATA8
	GET_PCBYTES(tmp)
	REGPUSH((UINT16)tmp, 3)
	goto *retlb;
}

_imul_reg_ea_data8: { // 6B:	imul	REG, EA, DATA8
	SINT16	src;
	SINT16	dst;
	SINT32	res;

	PREPART_REG16_EA(op, src, p16, 21, 24)
	GET_PCBYTES(dst)
	WORD_IMUL(res, dst, src)
	*p16 = (UINT16)res;
	goto *retlb;
}

_insb: { // 6C:	insb
	I286_WORKCLOCK(5);
	d16 = iocore_inp8(I286_DX);
	i286_memorywrite(I286_DI + ES_BASE, (REG8)d16);
	I286_DI += STRING_DIR;
	goto *retlb;
}

_insw: { // 6D:	insw
	I286_WORKCLOCK(5);
	d16 = iocore_inp16(I286_DX);
	i286_memorywrite_w(I286_DI + ES_BASE, d16);
	I286_DI += STRING_DIRx2;
	goto *retlb;
}

_outsb: { // 6E:	outsb
	I286_WORKCLOCK(3);
	d16 = i286_memoryread(I286_SI + DS_FIX);
	I286_SI += STRING_DIR;
	iocore_out8(I286_DX, (UINT8)d16);
	goto *retlb;
}

_outsw: { // 6F:	outsw
	I286_WORKCLOCK(3);
	d16 = i286_memoryread_w(I286_SI + DS_FIX);
	I286_SI += STRING_DIRx2;
	iocore_out16(I286_DX, (UINT16)d16);
	goto *retlb;
}

_jo_short: { // 70:	jo short

	if (!I286_OV) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jno_short: { // 71:	jno short

	if (I286_OV) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;

}

_jc_short: { // 72:	jnae/jb/jc short

	if (!(I286_FLAGL & C_FLAG)) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jnc_short: { // 73:	jae/jnb/jnc short

	if (I286_FLAGL & C_FLAG) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jz_short: { // 74:	je/jz short

	if (!(I286_FLAGL & Z_FLAG)) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jnz_short: { // 75:	jne/jnz short

	if (I286_FLAGL & Z_FLAG) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jna_short: { // 76:	jna/jbe short

	if (!(I286_FLAGL & (Z_FLAG | C_FLAG))) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_ja_short: { // 77:	ja/jnbe short
	if (I286_FLAGL & (Z_FLAG | C_FLAG)) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_js_short: { // 78:	js short

	if (!(I286_FLAGL & S_FLAG)) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jns_short: { // 79:	jns short

	if (I286_FLAGL & S_FLAG) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jp_short: { // 7A:	jp/jpe short

	if (!(I286_FLAGL & P_FLAG)) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jnp_short: { // 7B:	jnp/jpo short

	if (I286_FLAGL & P_FLAG) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jl_short: { // 7C:	jl/jnge short

	if (((I286_FLAGL & S_FLAG) == 0) == (I286_OV == 0)) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jnl_short: { // 7D:	jnl/jge short

	if (((I286_FLAGL & S_FLAG) == 0) != (I286_OV == 0)) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jle_short: { // 7E:	jle/jng short

	if ((!(I286_FLAGL & Z_FLAG)) &&
		(((I286_FLAGL & S_FLAG) == 0) == (I286_OV == 0))) JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_jnle_short: { // 7F:	jg/jnle short

	if ((I286_FLAGL & Z_FLAG) ||
		(((I286_FLAGL & S_FLAG) == 0) != (I286_OV == 0)))
			JMPNOP(3) else JMPSHORT(7)

	goto *retlb;
}

_calc_ea8_i8: { // 80:	op		EA8, DATA8
	// 82:	op		EA8, DATA8

	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(3);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			goto *c_op8xext8_tbl[(op >> 3) & 7]; // (maddr)
			// ŒÄ‚Ñæ‚©‚ç’¼Ú–ß‚é
		}
		p8 = mem + madr;
	}
	goto *c_op8xreg8_tbl[(op >> 3) & 7]; // (p8)
	// ŒÄ‚Ñæ‚©‚ç’¼Ú–ß‚é
}

_calc_ea16_i16: { // 81:	op		EA16, DATA16
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(3);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			GET_PCWORD(src);
			goto *c_op8xext16_tbl[(op >> 3) & 7]; //(madr, src)
			// ŒÄ‚Ñæ‚©‚ç’¼Ú–ß‚é
		}
		p16 = (UINT16 *)(mem + madr);
	}
	GET_PCWORD(src);
	goto *c_op8xreg16_tbl[(op >> 3) & 7]; // (p16, src)
	// ŒÄ‚Ñæ‚©‚ç’¼Ú–ß‚é
}

_calc_ea16_i8: { // 83:	op		EA16, DATA8
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(3);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			GET_PCBYTES(src);
			goto *c_op8xext16_tbl[(op >> 3) & 7]; //(madr, src)
			// ŒÄ‚Ñæ‚©‚ç’¼Ú–ß‚é
		}
		p16 = (UINT16 *)(mem + madr);
	}
	GET_PCBYTES(src);
	goto *c_op8xreg16_tbl[(op >> 3) & 7]; // (p16, src)
	// ŒÄ‚Ñæ‚©‚ç’¼Ú–ß‚é
}

_test_ea_r8: { // 84:	test	EA, REG8
	PREPART_EA_REG8(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(6);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			tmp = i286_memoryread(madr);
			ANDBYTE(tmp, src);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	tmp = *p8;
	ANDBYTE(tmp, src);
	goto *retlb;
}

_test_ea_r16: { // 85:	test	EA, REG16
	PREPART_EA_REG16(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(6);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			tmp = i286_memoryread_w(madr);
			ANDWORD(tmp, src);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	tmp = *p16;
	ANDWORD(tmp, src);
	goto *retlb;
}

_xchg_ea_r8: { // 86:	xchg	EA, REG8

	UINT8	*src;

	PREPART_EA_REG8P(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(3);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(5);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			UINT8 tmp = i286_memoryread(madr);
			i286_memorywrite(madr, *src);
			*src = tmp;
			goto *retlb;
		}
		p8 = mem + madr;
	}
	SWAPBYTE(*p8, *src);
	goto *retlb;
}

_xchg_ea_r16: { // 87:	xchg	EA, REG16
	UINT16	*src;

	PREPART_EA_REG16P(op, src);
	if (op >= 0xc0) {
		I286_WORKCLOCK(3);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(5);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			UINT16 tmp = i286_memoryread_w(madr);
			i286_memorywrite_w(madr, *src);
			*src = tmp;
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	SWAPWORD(*p16, *src);
	goto *retlb;
}

_mov_ea_r8: { // 88:	mov		EA, REG8
	PREPART_EA_REG8(op, d8)
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		*(REG8_B20(op)) = d8;
	} else {
		I286_WORKCLOCK(3);
		madr = CALC_EA(op);
		i286_memorywrite(madr, d8);
	}
	goto *retlb;
}

_mov_ea_r16: { // 89:	mov		EA, REG16
	PREPART_EA_REG16(op, d16);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		*(REG16_B20(op)) = d16;
	} else {
		I286_WORKCLOCK(3);
		i286_memorywrite_w(CALC_EA(op), d16);
	}
	goto *retlb;
}

_mov_r8_ea: { // 8A:	mov		REG8, EA
	PREPART_REG8_EA(op, d8, p8, 2, 5);
	*p8 = d8;
	goto *retlb;
}

_mov_r16_ea: { // 8B:	mov		REG16, EA
	PREPART_REG16_EA(op, d16, p16, 2, 5);
	*p16 = d16;
	goto *retlb;
}

_mov_ea_seg: { // 8C:	mov		EA, segreg
	GET_PCBYTE(op);
	d16 = *SEGMENTPTR((op >> 3) & 3);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		*(REG16_B20(op)) = d16;
	} else {
		I286_WORKCLOCK(3);
		i286_memorywrite_w(CALC_EA(op), d16);
	}
	goto *retlb;
}

_lea_r16_ea: { // 8D:	lea		REG16, EA
	I286_WORKCLOCK(3);
	GET_PCBYTE(op)
	if (op < 0xc0) {
		*(REG16_B53(op)) = CALC_LEA(op);
	} else {
		INT_NUM(6, I286_SP - 2);
	}
	goto *retlb;
}

_mov_seg_ea: { // 8E:	mov		segrem, EA
	d16 = I286_IP;
	GET_PCBYTE(op);
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		tmp = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(5);
		tmp = i286_memoryread_w(CALC_EA(op));
	}
	madr = SEGSELECT(tmp);
	switch(op & 0x18) {
		case 0x00:// es
			I286_ES = (UINT16)tmp;
			ES_BASE = madr;
			break;

		case 0x10:// ss
			I286_SS = (UINT16)tmp;
			SS_BASE = madr;
			SS_FIX = madr;
			NEXT_OPCODE
			break;

		case 0x18:// ds
			I286_DS = (UINT16)tmp;
			DS_BASE = madr;
			DS_FIX = madr;
			break;

		default:// cs
			INT_NUM(6, d16 - 1);
			break;
	}
	goto *retlb;
}

_pop_ea: { // 8F:	pop		EA
	I286_WORKCLOCK(5);
	REGPOP0(d16)

	GET_PCBYTE(op)
	if (op < 0xc0) {
		i286_memorywrite_w(CALC_EA(op), d16);
	} else {
		*(REG16_B20(op)) = d16;
	}
	goto *retlb;
}

_nop: { // 90: nop / bios func

#if 1 // call BIOS
	madr = LOW16(I286_IP - 1) + CS_BASE;
	if ((madr >= 0xf8000) && (madr < 0x100000)) {
		biosfunc(madr);
		ES_BASE = I286_ES << 4;
		CS_BASE = I286_CS << 4;
		SS_BASE = I286_SS << 4;
		SS_FIX = SS_BASE;
		DS_BASE = I286_DS << 4;
		DS_FIX = DS_BASE;
	}
#endif
	I286_WORKCLOCK(3);
	goto *retlb;
}

_xchg_ax_cx: { // 91:	xchg	ax, cx

	I286_WORKCLOCK(3);
	SWAPWORD(I286_AX, I286_CX);
	goto *retlb;
}

_xchg_ax_dx: { // 92:	xchg	ax, dx

	I286_WORKCLOCK(3);
	SWAPWORD(I286_AX, I286_DX);
	goto *retlb;
}

_xchg_ax_bx: { // 93:	xchg	ax, bx

	I286_WORKCLOCK(3);
	SWAPWORD(I286_AX, I286_BX);
	goto *retlb;
}

_xchg_ax_sp: { // 94:	xchg	ax, sp

	I286_WORKCLOCK(3);
	SWAPWORD(I286_AX, I286_SP);
	goto *retlb;
}

_xchg_ax_bp: { // 95:	xchg	ax, bp

	I286_WORKCLOCK(3);
	SWAPWORD(I286_AX, I286_BP);
	goto *retlb;
}

_xchg_ax_si: { // 96:	xchg	ax, si

	I286_WORKCLOCK(3);
	SWAPWORD(I286_AX, I286_SI);
	goto *retlb;
}

_xchg_ax_di: { // 97:	xchg	ax, di

	I286_WORKCLOCK(3);
	SWAPWORD(I286_AX, I286_DI);
	goto *retlb;
}

_cbw: { // 98:	cbw

	I286_WORKCLOCK(2);
	I286_AX = __CBW(I286_AL);
	goto *retlb;
}

_cwd: { // 99:	cwd

	I286_WORKCLOCK(2);
	I286_DX = ((I286_AH & 0x80)?0xffff:0x0000);
	goto *retlb;
}

_call_far: { // 9A:	call far
	I286_WORKCLOCK(13);
	REGPUSH0(I286_CS)
	GET_PCWORD(d16)
	GET_PCWORD(I286_CS)
	CS_BASE = SEGSELECT(I286_CS);
	REGPUSH0(I286_IP)
	I286_IP = d16;
	goto *retlb;
}

_wait: { // 9B:	wait
	I286_WORKCLOCK(2);
	goto *retlb;
}

_pushf: { // 9C:	pushf
	REGPUSH(REAL_FLAGREG, 3)
	goto *retlb;
}

_popf: { // 9D:	popf
	REGPOP0(tmp)
	I286_OV = tmp & O_FLAG;
	I286_FLAG = tmp & (0xfff ^ O_FLAG);
	I286_TRAP = ((tmp & 0x300) == 0x300);
	I286_WORKCLOCK(5);
#if defined(INTR_FAST)
	if ((I286_TRAP) || ((tmp & I_FLAG) && (PICEXISTINTR))) {
		I286IRQCHECKTERM
	}
#else
	I286IRQCHECKTERM
#endif
	goto *retlb;
}

_sahf: { // 9E:	sahf
	I286_WORKCLOCK(2);
	I286_FLAGL = I286_AH;
	goto *retlb;
}

_lahf: { // 9F:	lahf
	I286_WORKCLOCK(2);
	I286_AH = I286_FLAGL;
	goto *retlb;
}

_mov_al_m8: { // A0:	mov		al, m8
	I286_WORKCLOCK(5);
	GET_PCWORD(op)
	I286_AL = i286_memoryread(DS_FIX + op);
	goto *retlb;
}

_mov_ax_m16: { // A1:	mov		ax, m16
	I286_WORKCLOCK(5);
	GET_PCWORD(op)
	I286_AX = i286_memoryread_w(DS_FIX + op);
	goto *retlb;
}

_mov_m8_al: { // A2:	mov		m8, al
	I286_WORKCLOCK(3);
	GET_PCWORD(op)
	i286_memorywrite(DS_FIX + op, I286_AL);
	goto *retlb;
}

_mov_m16_ax: { // A3:	mov		m16, ax
	I286_WORKCLOCK(3);
	GET_PCWORD(op);
	i286_memorywrite_w(DS_FIX + op, I286_AX);
	goto *retlb;
}

_movsb: { // A4:	movsb
	I286_WORKCLOCK(5);
	d8 = i286_memoryread(I286_SI + DS_FIX);
	i286_memorywrite(I286_DI + ES_BASE, d8);
	I286_SI += STRING_DIR;
	I286_DI += STRING_DIR;
	goto *retlb;
}

_movsw: { // A5:	movsw
	I286_WORKCLOCK(5);
	d16 = i286_memoryread_w(I286_SI + DS_FIX);
	i286_memorywrite_w(I286_DI + ES_BASE, d16);
	I286_SI += STRING_DIRx2;
	I286_DI += STRING_DIRx2;
	goto *retlb;
}

_cmpsb: { // A6:	cmpsb
	I286_WORKCLOCK(8);
	dst = i286_memoryread(I286_SI + DS_FIX);
	src = i286_memoryread(I286_DI + ES_BASE);
	SUBBYTE(res, dst, src)
	I286_SI += STRING_DIR;
	I286_DI += STRING_DIR;
	goto *retlb;
}

_cmpsw: { // A7:	cmpsw
	I286_WORKCLOCK(8);
	dst = i286_memoryread_w(I286_SI + DS_FIX);
	src = i286_memoryread_w(I286_DI + ES_BASE);
	SUBWORD(res, dst, src)
	I286_SI += STRING_DIRx2;
	I286_DI += STRING_DIRx2;
	goto *retlb;
}

_test_al_data8: { // A8:	test	al, DATA8
	I286_WORKCLOCK(3);
	GET_PCBYTE(src)
	dst = I286_AL;
	ANDBYTE(dst, src)
	goto *retlb;
}

_test_ax_data16: { // A9:	test	ax, DATA16
	I286_WORKCLOCK(3);
	GET_PCWORD(src)
	dst = I286_AX;
	ANDWORD(dst, src)
	goto *retlb;
}

_stosb: { // AA:	stosw
	I286_WORKCLOCK(3);
	i286_memorywrite(I286_DI + ES_BASE, I286_AL);
	I286_DI += STRING_DIR;
	goto *retlb;
}

_stosw: { // AB:	stosw
	I286_WORKCLOCK(3);
	i286_memorywrite_w(I286_DI + ES_BASE, I286_AX);
	I286_DI += STRING_DIRx2;
	goto *retlb;
}

_lodsb: { // AC:	lodsb
	I286_WORKCLOCK(5);
	I286_AL = i286_memoryread(I286_SI + DS_FIX);
	I286_SI += STRING_DIR;
	goto *retlb;
}

_lodsw: { // AD:	lodsw
	I286_WORKCLOCK(5);
	I286_AX = i286_memoryread_w(I286_SI + DS_FIX);
	I286_SI += STRING_DIRx2;
	goto *retlb;
}

_scasb: { // AE:	scasb
	I286_WORKCLOCK(7);
	src = i286_memoryread(I286_DI + ES_BASE);
	dst = I286_AL;
	SUBBYTE(res, dst, src)
	I286_DI += STRING_DIR;
	goto *retlb;
}

_scasw: { // AF:	scasw
	I286_WORKCLOCK(7);
	src = i286_memoryread_w(I286_DI + ES_BASE);
	dst = I286_AX;
	SUBWORD(res, dst, src)
	I286_DI += STRING_DIRx2;
	goto *retlb;
}

_mov_al_imm: { MOVIMM8(I286_AL);goto *retlb; }// B0:	mov	al, imm8
_mov_cl_imm: { MOVIMM8(I286_CL);goto *retlb; }// B1:	mov	cl, imm8
_mov_dl_imm: { MOVIMM8(I286_DL);goto *retlb; }// B2:	mov	dl, imm8
_mov_bl_imm: { MOVIMM8(I286_BL);goto *retlb; }// B3:	mov	bl, imm8
_mov_ah_imm: { MOVIMM8(I286_AH);goto *retlb; }// B4:	mov	ah, imm8
_mov_ch_imm: { MOVIMM8(I286_CH);goto *retlb; }// B5:	mov	ch, imm8
_mov_dh_imm: { MOVIMM8(I286_DH);goto *retlb; }// B6:	mov	dh, imm8
_mov_bh_imm: { MOVIMM8(I286_BH);goto *retlb; }// B7:	mov	bh, imm8
_mov_ax_imm: { MOVIMM16(I286_AX);goto *retlb; }	// B8:	mov	ax, imm16
_mov_cx_imm: { MOVIMM16(I286_CX);goto *retlb; }	// B9:	mov	cx, imm16
_mov_dx_imm: { MOVIMM16(I286_DX);goto *retlb; }	// BA:	mov	dx, imm16
_mov_bx_imm: { MOVIMM16(I286_BX);goto *retlb; }	// BB:	mov	bx, imm16
_mov_sp_imm: { MOVIMM16(I286_SP);goto *retlb; }	// BC:	mov	sp, imm16
_mov_bp_imm: { MOVIMM16(I286_BP);goto *retlb; }	// BD:	mov	bp, imm16
_mov_si_imm: { MOVIMM16(I286_SI);goto *retlb; }	// BE:	mov	si, imm16
_mov_di_imm: { MOVIMM16(I286_DI);goto *retlb; }	// BF:	mov	di, imm16

_shift_ea8_data8: { // C0:	shift	EA8, DATA8
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(5);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(8);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			GET_PCBYTE(d8)
			I286_WORKCLOCK(d8);
			goto *sft_e8cl_table[(op >> 3) & 7]; //(madr, d8);
		}
		p8 = mem + madr;
	}
	GET_PCBYTE(d8)
	I286_WORKCLOCK(d8);
	goto *sft_r8cl_table[(op >> 3) & 7];
}

_shift_ea16_data8: { // C1:	shift	EA16, DATA8
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(5);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(8);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			GET_PCBYTE(d8);
			I286_WORKCLOCK(d8);
			goto *sft_e16cl_table[(op >> 3) & 7]; //(madr, d8);
		}
		p16 = (UINT16 *)(mem + madr);
	}
	GET_PCBYTE(d8);
	I286_WORKCLOCK(d8);
	goto *sft_r16cl_table[(op >> 3) & 7]; //(p16, d8);
}

_ret_near_data16: { // C2:	ret near DATA16
	I286_WORKCLOCK(11);
	GET_PCWORD(d16)
	REGPOP0(I286_IP)
	I286_SP += d16;
	goto *retlb;
}

_ret_near: { // C3:	ret near
	I286_WORKCLOCK(11);
	REGPOP0(I286_IP)
	goto *retlb;
}

_les_r16_ea: { // C4:	les		REG16, EA
	I286_WORKCLOCK(3);
	GET_PCBYTE(op)
	if (op < 0xc0) {
		tmp = GET_EA(op, &madr);
		*(REG16_B53(op)) = i286_memoryread_w(madr + tmp);
		I286_ES = i286_memoryread_w(madr + LOW16(tmp + 2));
		ES_BASE = SEGSELECT(I286_ES);
	} else {
		INT_NUM(6, I286_IP - 2);
	}
	goto *retlb;
}

_lds_r16_ea: { // C5:	lds		REG16, EA
	I286_WORKCLOCK(3);
	GET_PCBYTE(op)
	if (op < 0xc0) {
		tmp = GET_EA(op, &madr);
		*(REG16_B53(op)) = i286_memoryread_w(madr + tmp);
		I286_DS = i286_memoryread_w(madr + LOW16(tmp + 2));
		DS_BASE = SEGSELECT(I286_DS);
		DS_FIX = DS_BASE;
	} else {
		INT_NUM(6, I286_IP - 2);
	}
	goto *retlb;
}

_mov_ea8_data8: { // C6:	mov		EA8, DATA8
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		GET_PCBYTE(*(REG8_B53(op)))
	} else { // 03/11/23
		UINT32 ad;
		UINT8 val;
		I286_WORKCLOCK(3);
		ad = CALC_EA(op);
		GET_PCBYTE(val)
		i286_memorywrite(ad, val);
	}
	goto *retlb;
}

_mov_ea16_data16: { // C7:	mov		EA16, DATA16
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		GET_PCWORD(*(REG16_B53(op)))
	} else { // 03/11/23
		UINT32	ad;
		UINT16	val;
		I286_WORKCLOCK(3);
		ad = CALC_EA(op);
		GET_PCWORD(val)
		i286_memorywrite_w(ad, val);
	}
	goto *retlb;
}

_enter: { // C8:	enter	DATA16, DATA8

	UINT16	dimsize;
	UINT8	level;

	GET_PCWORD(dimsize)
	GET_PCBYTE(level)
	REGPUSH0(I286_BP)
	level &= 0x1f;
	if (!level) { // enter level=0
		I286_WORKCLOCK(11);
		I286_BP = I286_SP;
		I286_SP -= dimsize;
	} else {
		level--;
		if (!level) { // enter level=1
			UINT16 tmp;
			I286_WORKCLOCK(15);
			tmp = I286_SP;
			REGPUSH0(tmp)
			I286_BP = tmp;
			I286_SP -= dimsize;
		} else { // enter level=2-31
			UINT16 bp;
			I286_WORKCLOCK(12 + 4 + level*4);
			bp = I286_BP;
			I286_BP = I286_SP;
			while(level--) {
#if 1 // ‚È‚É‚â‚Á‚Ä‚ñ‚¾ƒ’ƒŒ
				REG16 val;
				bp -= 2;
				I286_SP -= 2;
				val = i286_memoryread_w(bp + SS_BASE);
				i286_memorywrite_w(I286_SP + SS_BASE, val);
#else
				UINT16 val = i286_memoryread_w(bp + SS_BASE);
				i286_memorywrite_w(I286_SP + SS_BASE, val);
				bp -= 2;
				I286_SP -= 2;
#endif
			}
			REGPUSH0(I286_BP)
			I286_SP -= dimsize;
		}
	}
	goto *retlb;
}

fleave: { // C9:	leave

	I286_WORKCLOCK(5);
	I286_SP = I286_BP;
	REGPOP0(I286_BP)
	goto *retlb;
}

_ret_far_data16: { // CA:	ret far	DATA16

	UINT16	ad;

	I286_WORKCLOCK(15);
	GET_PCWORD(ad)
	REGPOP0(I286_IP)
	REGPOP0(I286_CS)
	I286_SP += ad;
	CS_BASE = SEGSELECT(I286_CS);
	goto *retlb;
}

_ret_far: { // CB:	ret far

	I286_WORKCLOCK(15);
	REGPOP0(I286_IP)
	REGPOP0(I286_CS)
	CS_BASE = SEGSELECT(I286_CS);
	goto *retlb;
}

_int_03: { // CC:	int		3
	I286_WORKCLOCK(3);
	INT_NUM(3, I286_IP);
	goto *retlb;
}

_int_data8: { // CD:	int		DATA8

	UINT	vect;

	I286_WORKCLOCK(3);
	GET_PCBYTE(vect)
#if defined(ENABLE_TRAP)
	softinttrap(CPU_CS, CPU_IP - 2, vect);
#endif
	INT_NUM(vect, I286_IP);
	goto *retlb;
}

_into: { // CE:	into

	I286_WORKCLOCK(4);
	if (I286_OV) {
		INT_NUM(4, I286_IP);
	}
	goto *retlb;
}

_iret: { // CF:	iret

	UINT	flag;

	REGPOP0(I286_IP)
	REGPOP0(I286_CS)
	REGPOP0(flag)
	I286_OV = flag & O_FLAG;
	I286_FLAG = flag & (0xfff ^ O_FLAG);
	I286_TRAP = ((flag & 0x300) == 0x300);
	CS_BASE = I286_CS << 4;
//	CS_BASE = SEGSELECT(I286_CS);
	I286_WORKCLOCK(31);
#if defined(INTR_FAST)
	if ((I286_TRAP) || ((flag & I_FLAG) && (PICEXISTINTR))) {
		I286IRQCHECKTERM
	}
#else
	I286IRQCHECKTERM
#endif
	goto *retlb;
}

_shift_ea8_1: { // D0:	shift EA8, 1
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			goto *sft_e8_table[(op >> 3) & 7];
			// ŒÄ‚Ñæ‚©‚ç’¼Ú–ß‚é
		}
		p8 = mem + madr;
	}
	goto *sft_r8_table[(op >> 3) & 7]; //(p8);
}

_shift_ea16_1: { // D1:	shift EA16, 1
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			goto *sft_e16_table[(op >> 3) & 7];
		}
		p16 = (UINT16 *)(mem + madr);
	}
	goto *sft_r16_table[(op >> 3) & 7]; //(p16);
}

_shift_ea8_cl: { // D2:	shift EA8, cl
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(5);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(8);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			d8 = I286_CL;
			I286_WORKCLOCK(d8);
			goto *sft_e8cl_table[(op >> 3) & 7]; //(madr, d8);
		}
		p8 = mem + madr;
	}
	d8 = I286_CL;
	I286_WORKCLOCK(d8);
	goto *sft_r8cl_table[(op >> 3) & 7]; //(p8, d8);
}

_shift_ea16_cl: { // D3:	shift EA16, cl
	GET_PCBYTE(op)
	if (op >= 0xc0) {
		I286_WORKCLOCK(5);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(8);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			d8 = I286_CL;
			I286_WORKCLOCK(d8);
			goto *sft_e16cl_table[(op >> 3) & 7]; //(madr, d8);
		}
		p16 = (UINT16 *)(mem + madr);
	}
	d8 = I286_CL;
	I286_WORKCLOCK(d8);
	goto *sft_r16cl_table[(op >> 3) & 7]; //(p16, d8);
}

_aam: { // D4:	AAM

	UINT8	al;
	UINT8	div;

	I286_WORKCLOCK(16);
	GET_PCBYTE(div);
	if (div) {
		al = I286_AL;
		I286_AH = al / div;
		I286_AL = al % div;
		I286_FLAGL &= ~(S_FLAG | Z_FLAG | P_FLAG);
		I286_FLAGL |= WORDSZPF(I286_AX);
	} else {
		INT_NUM(0, I286_IP - 2);// 80286
//		INT_NUM(0, I286_IP);// V30
	}
	goto *retlb;
}

_aad: { // D5:	AAD

	UINT8	mul;

	I286_WORKCLOCK(14);
	GET_PCBYTE(mul);
	I286_AL += (UINT8)(I286_AH * mul);
	I286_AH = 0;
	I286_FLAGL &= ~(S_FLAG | Z_FLAG | P_FLAG);
	I286_FLAGL |= BYTESZPF(I286_AL);
	goto *retlb;
}

_setalc: { // D6:	setalc (80286)

	I286_AL = ((I286_FLAGL & C_FLAG)?0xff:0);
	goto *retlb;
}

_xlat: { // D7:	xlat

	I286_WORKCLOCK(5);
	I286_AL = i286_memoryread(LOW16(I286_AL + I286_BX) + DS_FIX);
	goto *retlb;
}

_esc: { // D8:	esc
	I286_WORKCLOCK(2);
	GET_PCBYTE(op)
	if (op < 0xc0) {
		CALC_LEA(op);
	}
	goto *retlb;
}

_loopnz: { // E0:	loopnz

	I286_CX--;
	if ((!I286_CX) || (I286_FLAGL & Z_FLAG)) JMPNOP(4) else JMPSHORT(8)

	goto *retlb;
}

_loopz: { // E1:	loopz

	I286_CX--;
	if ((!I286_CX) || (!(I286_FLAGL & Z_FLAG))) JMPNOP(4) else JMPSHORT(8)

	goto *retlb;
}

_loop: { // E2:	loop

	I286_CX--;
	if (!I286_CX) JMPNOP(4) else JMPSHORT(8)

	goto *retlb;
}

_jcxz: { // E3:	jcxz

	if (I286_CX) JMPNOP(4) else JMPSHORT(8)

	goto *retlb;
}

_in_al_data8: { // E4:	in		al, DATA8

	UINT	port;

	I286_WORKCLOCK(5);
	GET_PCBYTE(port)
	I286_INPADRS = CS_BASE + I286_IP;
	I286_AL = iocore_inp8(port);
	I286_INPADRS = 0;
	goto *retlb;
}

_in_ax_data8: { // E5:	in		ax, DATA8

	UINT	port;

	I286_WORKCLOCK(5);
	GET_PCBYTE(port)
	I286_AX = iocore_inp16(port);
	goto *retlb;
}

_out_data8_al: { // E6:	out		DATA8, al

	UINT	port;

	I286_WORKCLOCK(3);
	GET_PCBYTE(port);
	iocore_out8(port, I286_AL);
	goto *retlb;
}

_out_data8_ax: { // E7:	out		DATA8, ax

	UINT	port;

	I286_WORKCLOCK(3);
	GET_PCBYTE(port);
	iocore_out16(port, I286_AX);
	goto *retlb;
}

_call_near: { // E8:	call near

	UINT16	ad;

	I286_WORKCLOCK(7);
	GET_PCWORD(ad)
	REGPUSH0(I286_IP)
	I286_IP += ad;
	goto *retlb;
}

_jmp_near: { // E9:	jmp near

	UINT16	ad;

	I286_WORKCLOCK(7);
	GET_PCWORD(ad)
	I286_IP += ad;
	goto *retlb;
}

_jmp_far: { // EA:	jmp far

	UINT16	ad;

	I286_WORKCLOCK(11);
	GET_PCWORD(ad);
	GET_PCWORD(I286_CS);
	I286_IP = ad;
	CS_BASE = SEGSELECT(I286_CS);
	goto *retlb;
}

_jmp_short: { // EB:	jmp short

	UINT16	ad;

	I286_WORKCLOCK(7);
	GET_PCBYTES(ad)
	I286_IP += ad;
	goto *retlb;
}

_in_al_dx: { // EC:	in		al, dx

	I286_WORKCLOCK(5);
	I286_AL = iocore_inp8(I286_DX);
	goto *retlb;
}

_in_ax_dx: { // ED:	in		ax, dx

	I286_WORKCLOCK(5);
	I286_AX = iocore_inp16(I286_DX);
	goto *retlb;
}

_out_dx_al: { // EE:	out		dx, al

	I286_WORKCLOCK(3);
	iocore_out8(I286_DX, I286_AL);
	goto *retlb;
}

_out_dx_ax: { // EF:	out		dx, ax

	I286_WORKCLOCK(3);
	iocore_out16(I286_DX, I286_AX);
	goto *retlb;
}

_lock: { // F0:	lock
	// F1:	lock
	I286_WORKCLOCK(2);
	goto *retlb;
}

_repne: { // F2:	repne

	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repne_lb;
		goto *i286op_repne[op];
        _repne_lb:
		retlb = retstk[--retstk_idx];
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_repe: { // F3:	repe

	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repe_lb;
		goto *i286op_repe[op]; 
        _repe_lb:
		retlb = retstk[--retstk_idx];
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_hlt: { // F4:	hlt

	I286_REMCLOCK = -1;
	I286_IP--;
	goto *retlb;
}

_cmc: { // F5:	cmc

	I286_WORKCLOCK(2);
	I286_FLAGL ^= C_FLAG;
	goto *retlb;
}

_ope0xf6: { // F6:	
	GET_PCBYTE(op);
	goto *c_ope0xf6_table[(op >> 3) & 7];
	// ŒÄ‚Ñæ‚©‚ç’¼Ú–ß‚é
}

_ope0xf7: { // F7:	
	GET_PCBYTE(op);
	goto *c_ope0xf7_table[(op >> 3) & 7]; // (op);
}

_clc: { // F8:	clc

	I286_WORKCLOCK(2);
	I286_FLAGL &= ~C_FLAG;
	goto *retlb;
}

_stc: { // F9:	stc

	I286_WORKCLOCK(2);
	I286_FLAGL |= C_FLAG;
	goto *retlb;
}

_cli: { // FA:	cli

	I286_WORKCLOCK(2);
	I286_FLAG &= ~I_FLAG;
	I286_TRAP = 0;
	goto *retlb;
}

_sti: { // FB:	sti

	I286_WORKCLOCK(2);
#if defined(INTR_FAST)
	if (I286_FLAG & I_FLAG) {
		NEXT_OPCODE;
		goto *retlb; // XV‚ÌˆÓ–¡‚È‚µ
	}
#endif
	I286_FLAG |= I_FLAG;
	I286_TRAP = (I286_FLAG & T_FLAG) >> 8;
#if defined(INTR_FAST)
	if ((I286_TRAP) || (PICEXISTINTR)) {
		REMAIN_ADJUST(1)
	} else {
		NEXT_OPCODE;
	}
#else
	REMAIN_ADJUST(1)
#endif
	goto *retlb;
}

_cld: { // FC:	cld

	I286_WORKCLOCK(2);
	I286_FLAG &= ~D_FLAG;
	goto *retlb;
}

_std: { // FD:	std

	I286_WORKCLOCK(2);
	I286_FLAG |= D_FLAG;
	goto *retlb;
}

_ope0xfe: { // FE:	
	GET_PCBYTE(op);
	goto *c_ope0xfe_table[(op >> 3) & 1];
}

_ope0xff: { // FF:	
	GET_PCBYTE(op);
	goto *c_ope0xff_table[(op >> 3) & 7];
}

// ----------------------------------------------------------------- repe

_repe_segprefix_es: {
	DS_FIX = ES_BASE;
	SS_FIX = ES_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repe_segprefix_es_lb;
		goto *i286op_repe[op];
        _repe_segprefix_es_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_repe_segprefix_cs: {

	DS_FIX = CS_BASE;
	SS_FIX = CS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repe_segprefix_cs_lb;
		goto *i286op_repe[op];
        _repe_segprefix_cs_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_repe_segprefix_ss: {

	DS_FIX = SS_BASE;
	SS_FIX = SS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repe_segprefix_ss_lb;
		goto *i286op_repe[op];
        _repe_segprefix_ss_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_repe_segprefix_ds: {

	DS_FIX = DS_BASE;
	SS_FIX = DS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repe_segprefix_ds_lb;
		goto *i286op_repe[op];
        _repe_segprefix_ds_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

// ----------------------------------------------------------------- repne

_repne_segprefix_es: {

	DS_FIX = ES_BASE;
	SS_FIX = ES_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repne_segprefix_es_lb;
		goto *i286op_repne[op];
        _repne_segprefix_es_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_repne_segprefix_cs: {

	DS_FIX = CS_BASE;
	SS_FIX = CS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repne_segprefix_cs_lb;
		goto *i286op_repne[op];
        _repne_segprefix_cs_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_repne_segprefix_ss: {

	DS_FIX = SS_BASE;
	SS_FIX = SS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repne_segprefix_ss_lb;
		goto *i286op_repne[op];
        _repne_segprefix_ss_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

_repne_segprefix_ds: {

	DS_FIX = DS_BASE;
	SS_FIX = DS_BASE;
	I286_PREFIX++;
	if (I286_PREFIX < MAX_PREFIX) {
		GET_PCBYTE(op);
		retstk[retstk_idx++] = retlb;
		retlb = &&_repne_segprefix_ds_lb;
		goto *i286op_repne[op];
        _repne_segprefix_ds_lb:
		retlb = retstk[--retstk_idx];
		REMOVE_PREFIX
		I286_PREFIX = 0;
	} else {
		INT_NUM(6, I286_IP);
	}
	goto *retlb;
}

/********** 0F **********/

