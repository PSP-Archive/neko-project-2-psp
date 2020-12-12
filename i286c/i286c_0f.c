#define I286EXT
#define I286_0F

I286_0F _sldt: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		*(REG16_B20(op)) = I286_LDTR;
	} else {
		I286_WORKCLOCK(3);
		i286_memorywrite_w(CALC_EA(op), I286_LDTR);
	}
	goto *retlb;
}

I286_0F _str: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(3);
		*(REG16_B20(op)) = I286_TR;
	} else {
		I286_WORKCLOCK(6);
		i286_memorywrite_w(CALC_EA(op), I286_TR);
	}
	goto *retlb;
}

I286_0F _lldt: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(17);
		d16 = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(19);
		d16 = i286_memoryread_w(CALC_EA(op));
	}
	madr = i286c_selector(d16);
	I286_LDTR = d16;
	I286_LDTRC.limit = i286_memoryread_w(madr);
	I286_LDTRC.base = i286_memoryread_w(madr + 2);
	I286_LDTRC.base24 = i286_memoryread(madr + 4);
	goto *retlb;
}

I286_0F _ltr: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(17);
		d16 = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(19);
		d16 = i286_memoryread_w(CALC_EA(op));
	}
	madr = i286c_selector(d16);
	I286_TR = d16;
	I286_TRC.limit = i286_memoryread_w(madr);
	I286_TRC.base = i286_memoryread_w(madr + 2);
	I286_TRC.base24 = i286_memoryread(madr + 4);
	goto *retlb;
}

I286_0F _verr: {
  // xxxxx ‚±‚ÌŠÖ”‚ÌˆÓ–¡‚ÍH
	if (op >= 0xc0) {
		I286_WORKCLOCK(14);
		d16 = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(16);
		d16 = i286_memoryread_w(CALC_EA(op));
	}
	goto *retlb;
}

I286_0F _verw: {
  // xxxxx ‚±‚ÌŠÖ”‚ÌˆÓ–¡‚ÍH
	if (op >= 0xc0) {
		I286_WORKCLOCK(14);
		d16 = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(16);
		d16 = i286_memoryread_w(CALC_EA(op));
	}
	goto *retlb;
}

I286_0F _sgdt: {
	I286_WORKCLOCK(11);
	if (op < 0xc0) {
		madr = CALC_EA(op);
		i286_memorywrite_w(madr, I286_GDTR.limit);
		i286_memorywrite_w(madr + 2, I286_GDTR.base);
		i286_memorywrite_w(madr + 4, (REG16)(0xff00 + I286_GDTR.base24));
	} else {
		INT_NUM(6, I286_IP - 2);
	}
	goto *retlb;
}

I286_0F _sidt: {
	I286_WORKCLOCK(12);
	if (op < 0xc0) {
		madr = CALC_EA(op);
		i286_memorywrite_w(madr, I286_IDTR.limit);
		i286_memorywrite_w(madr + 2, I286_IDTR.base);
		i286_memorywrite_w(madr + 4, (REG16)(0xff00 + I286_IDTR.base24));
	} else {
		INT_NUM(6, I286_IP - 2);
	}
	goto *retlb;
}

I286_0F _lgdt: {
	I286_WORKCLOCK(11);
	if (op < 0xc0) {
		madr = CALC_EA(op);
		I286_GDTR.limit = i286_memoryread_w(madr);
		I286_GDTR.base = i286_memoryread_w(madr + 2);
		I286_GDTR.base24 = i286_memoryread(madr + 4);
	} else {
		INT_NUM(6, I286_IP - 2);
	}
	goto *retlb;
}

I286_0F _lidt: {
	I286_WORKCLOCK(12);
	if (op < 0xc0) {
		madr = CALC_EA(op);
		I286_IDTR.limit = i286_memoryread_w(madr);
		I286_IDTR.base = i286_memoryread_w(madr + 2);
		I286_IDTR.base24 = i286_memoryread(madr + 4);
	} else {
		INT_NUM(6, I286_IP - 2);
	}
	goto *retlb;
}

I286_0F _smsw: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		*(REG16_B20(op)) = I286_MSW;
	} else {
		I286_WORKCLOCK(3);
		i286_memorywrite_w(CALC_EA(op), I286_MSW);
	}
	goto *retlb;
}

I286_0F _lmsw: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(3);
		d16 = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(6);
		d16 = i286_memoryread_w(CALC_EA(op));
	}
	I286_MSW = d16 | (I286_MSW & MSW_PE);
	if (d16 & MSW_PE) {
		TRACEOUT(("80286 ProtectMode Enable... / MSW=%.4x [%.4x:%.4x]",
												I286_MSW, I286_CS, I286_IP));
	}
	goto *retlb;
}

I286_0F _loadall286: {
	I286_WORKCLOCK(195);
	I286_MSW = LOADINTELWORD(mem + 0x804);
	I286_TR = LOADINTELWORD(mem + 0x816);			// ver0.73
	d16 = LOADINTELWORD(mem + 0x818);
	I286_OV = d16 & O_FLAG;
	I286_FLAG = d16 & (0xfff ^ O_FLAG);
	I286_TRAP = ((d16 & 0x300) == 0x300);
	I286_IP = LOADINTELWORD(mem + 0x81a);
	I286_LDTR = LOADINTELWORD(mem + 0x81c);			// ver0.73
	I286_DS = LOADINTELWORD(mem + 0x81e);
	I286_SS = LOADINTELWORD(mem + 0x820);
	I286_CS = LOADINTELWORD(mem + 0x822);
	I286_ES = LOADINTELWORD(mem + 0x824);
	I286_DI = LOADINTELWORD(mem + 0x826);
	I286_SI = LOADINTELWORD(mem + 0x828);
	I286_BP = LOADINTELWORD(mem + 0x82a);
	I286_SP = LOADINTELWORD(mem + 0x82c);
	I286_BX = LOADINTELWORD(mem + 0x82e);
	I286_DX = LOADINTELWORD(mem + 0x830);
	I286_CX = LOADINTELWORD(mem + 0x832);
	I286_AX = LOADINTELWORD(mem + 0x834);
	madr = LOADINTELDWORD(mem + 0x836) & 0x00ffffff;
	ES_BASE = madr;
	madr = LOADINTELDWORD(mem + 0x83c) & 0x00ffffff;
	CS_BASE = madr;
	madr = LOADINTELDWORD(mem + 0x842) & 0x00ffffff;
	SS_BASE = madr;
	SS_FIX = madr;
	madr = LOADINTELDWORD(mem + 0x848) & 0x00ffffff;
	DS_BASE = madr;
	DS_FIX = madr;

	I286_GDTR.base = LOADINTELWORD(mem + 0x84e);
	*(UINT16 *)(&I286_GDTR.base24) = LOADINTELWORD(mem + 0x850);
	I286_GDTR.limit = LOADINTELWORD(mem + 0x852);

	I286_LDTRC.base = LOADINTELWORD(mem + 0x854);
	*(UINT16 *)(&I286_LDTRC.base24) = LOADINTELWORD(mem + 0x856);
	I286_LDTRC.limit = LOADINTELWORD(mem + 0x858);

	I286_IDTR.base = LOADINTELWORD(mem + 0x85a);
	*(UINT16 *)(&I286_IDTR.base24) = LOADINTELWORD(mem + 0x85c);
	I286_IDTR.limit = LOADINTELWORD(mem + 0x85e);

	I286_TRC.base = LOADINTELWORD(mem + 0x860);
	*(UINT16 *)(&I286_TRC.base24) = LOADINTELWORD(mem + 0x8620);
	I286_TRC.limit = LOADINTELWORD(mem + 0x864);

	I286IRQCHECKTERM

	goto *retlb;
}

I286EXT i286c_cts: {
	d16 = I286_IP;
	GET_PCBYTE(op);

	if (op == 0) {
		if (!(I286_MSW & MSW_PE)) {
			INT_NUM(6, d16 - 1);
		} else {
			GET_PCBYTE(op);
			goto *cts0_table[(op >> 3) & 7]; //(op2);
		}
	} else if (op == 1) {
		GET_PCBYTE(op);
		goto *cts1_table[(op >> 3) & 7]; //(op2);
	} else if (op == 5) {
		goto _loadall286;
	} else {
		INT_NUM(6, d16 - 1);
	}
	goto *retlb;
}

