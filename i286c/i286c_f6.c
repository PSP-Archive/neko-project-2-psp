#define I286_F6

// ------------------------------------------------------------ opecode 0xf6,7

I286_F6 _test_ea8_data8: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		dst = *(REG8_B20(op));
	} else {
		I286_WORKCLOCK(6);
		dst = i286_memoryread(CALC_EA(op));
	}
	GET_PCBYTE(src)
	ANDBYTE(dst, src)
	goto *retlb;
}

I286_F6 _not_ea8: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		*(REG8_B20(op)) ^= 0xff;
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			d8 = i286_memoryread(madr);
			d8 ^= 0xff;
			i286_memorywrite(madr, d8);
			goto *retlb;
		}
		*(mem + madr) ^= 0xff;
	}
	goto *retlb;
}

I286_F6 _neg_ea8: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			src = i286_memoryread(madr);
			NEGBYTE(dst, src)
			i286_memorywrite(madr, (REG8)dst);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	src = *p8;
	NEGBYTE(dst, src)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_F6 _mul_ea8: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(13);
		src = *(REG8_B20(op));
	} else {
		I286_WORKCLOCK(16);
		src = i286_memoryread(CALC_EA(op));
	}
	BYTE_MUL(res, I286_AL, src)
	I286_AX = (UINT16)res;
	goto *retlb;
}

I286_F6 _imul_ea8: {
	SINT32	res;

	if (op >= 0xc0) {
		I286_WORKCLOCK(13);
		src = *(REG8_B20(op));
	} else {
		I286_WORKCLOCK(16);
		src = i286_memoryread(CALC_EA(op));
	}
	BYTE_IMUL(res, I286_AL, src)
	I286_AX = (UINT16)res;
	goto *retlb;
}

I286_F6 _div_ea8: {
	d16 = I286_IP;
	if (op >= 0xc0) {
		I286_WORKCLOCK(14);
		d8 = *(REG8_B20(op));
	} else {
	  I286_WORKCLOCK(17);
		d8 = i286_memoryread(CALC_EA(op));
	}
	tmp = I286_AX;
	if ((d8) && (tmp < ((UINT16)d8 << 8))) {
		I286_AL = tmp / d8;
		I286_AH = tmp % d8;
	} else {
		INT_NUM(0, d16 - 2); // 80x86
	}
	goto *retlb;
}

I286_F6 _idiv_ea8: {

	SINT16	tmp, r;
	SINT8	src;

	d16 = I286_IP;
	if (op >= 0xc0) {
		I286_WORKCLOCK(17);
		src = *(REG8_B20(op));
	} else {
		I286_WORKCLOCK(20);
		src = i286_memoryread(CALC_EA(op));
	}
	tmp = (SINT16)I286_AX;
	if (src) {
		r = tmp / src;
		if (!((r + 0x80) & 0xff00)) {
			I286_AL = (UINT8)r;
			I286_AH = tmp % src;
			goto *retlb;
		}
	}
	INT_NUM(0, d16 - 2); // 80x86
	goto *retlb;
}


I286_F6 _test_ea16_data16: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		dst = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(6);
		dst = i286_memoryread_w(CALC_EA(op));
	}
	GET_PCWORD(src)
	ANDWORD(dst, src)
	goto *retlb;
}

I286_F6 _not_ea16: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		*(REG16_B20(op)) ^= 0xffff;
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (!(INHIBIT_WORDP(madr))) {
			*(mem + madr) ^= 0xffff;
		} else {
			d16 = i286_memoryread_w(madr);
			d16 = ~d16;
			i286_memorywrite_w(madr, d16);
		}
	}
	goto *retlb;
}

I286_F6 _neg_ea16: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			src = i286_memoryread_w(madr);
			NEGWORD(dst, src)
			i286_memorywrite_w(madr, (REG16)dst);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	src = *p16;
	NEGWORD(dst, src)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_F6 _mul_ea16: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(21);
		d16 = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(24);
		d16 = i286_memoryread_w(CALC_EA(op));
	}
	WORD_MUL(res, I286_AX, d16)
	I286_AX = (UINT16)res;
	I286_DX = (UINT16)(res >> 16);
	goto *retlb;
}

I286_F6 _imul_ea16: {
	SINT16	src;
	SINT32	res;

	if (op >= 0xc0) {
		I286_WORKCLOCK(21);
		src = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(24);
		src = i286_memoryread_w(CALC_EA(op));
	}
	WORD_IMUL(res, I286_AX, src)
	I286_AX = (UINT16)res;
	I286_DX = (UINT16)(res >> 16);
	goto *retlb;
}

I286_F6 _div_ea16: {
	d16 = I286_IP;
	if (op >= 0xc0) {
		I286_WORKCLOCK(22);
		src = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(25);
		src = i286_memoryread_w(CALC_EA(op));
	}
	tmp = (I286_DX << 16) + I286_AX;
	if ((src) && (tmp < (src << 16))) {
		I286_AX = tmp / src;
		I286_DX = tmp % src;
	} else {
		INT_NUM(0, d16 - 2); // 80x86
	}
	goto *retlb;
}

I286_F6 _idiv_ea16: {
	SINT32	tmp;
	SINT32	r;
	SINT16	src;

	d16 = I286_IP;
	if (op >= 0xc0) {
		I286_WORKCLOCK(25);
		src = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(28);
		src = i286_memoryread_w(CALC_EA(op));
	}
	tmp = (SINT32)((I286_DX << 16) + I286_AX);
	if (src) {
		r = tmp / src;
		if (!((r + 0x8000) & 0xffff0000)) {
			I286_AX = (SINT16)r;
			I286_DX = tmp % src;
			goto *retlb;
		}
	}
	INT_NUM(0, d16 - 2); // 80x86
	goto *retlb;
}


