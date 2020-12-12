// ------------------------------------------------------------ opecode 0xfe,f
#define I286_F6

I286_F6 _inc_ea8: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			d8 = i286_memoryread(madr);
			INCBYTE(d8)
			i286_memorywrite(madr, d8);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	d8 = *p8;
	INCBYTE(d8)
	*p8 = (UINT8)d8;
	goto *retlb;
}

I286_F6 _dec_ea8: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p8 = REG8_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (madr >= I286_MEMWRITEMAX) {
			d8 = i286_memoryread(madr);
			DECBYTE(d8)
			i286_memorywrite(madr, d8);
			goto *retlb;
		}
		p8 = mem + madr;
	}
	d8 = *p8;
	DECBYTE(d8)
	*p8 = (UINT8)d8;
	goto *retlb;
}

I286_F6 _inc_ea16: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			d16 = i286_memoryread_w(madr);
			INCWORD(d16)
			i286_memorywrite_w(madr, d16);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	d16 = *p16;
	INCWORD(d16)
	*p16 = (UINT16)d16;
	goto *retlb;
}

I286_F6 _dec_ea16: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(2);
		p16 = REG16_B20(op);
	} else {
		I286_WORKCLOCK(7);
		madr = CALC_EA(op);
		if (INHIBIT_WORDP(madr)) {
			d16 = i286_memoryread_w(madr);
			DECWORD(d16)
			i286_memorywrite_w(madr, d16);
			goto *retlb;
		}
		p16 = (UINT16 *)(mem + madr);
	}
	d16 = *p16;
	DECWORD(d16)
	*p16 = (UINT16)d16;
	goto *retlb;
}

I286_F6 _call_ea16: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(7);
		d16 = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(11);
		d16 = i286_memoryread_w(CALC_EA(op));
	}
	REGPUSH0(I286_IP);
	I286_IP = d16;
	goto *retlb;
}

I286_F6 _call_far_ea16: {
	I286_WORKCLOCK(16);
	if (op < 0xc0) {
		tmp = GET_EA(op, &madr);
		REGPUSH0(I286_CS) // ToDo
		REGPUSH0(I286_IP)
		I286_IP = i286_memoryread_w(madr + tmp);
		I286_CS = i286_memoryread_w(madr + LOW16(tmp + 2));
		CS_BASE = SEGSELECT(I286_CS);
	} else {
		INT_NUM(6, I286_IP - 2);
	}
	goto *retlb;
}

I286_F6 _jmp_ea16: {

	if (op >= 0xc0) {
		I286_WORKCLOCK(7);
		I286_IP = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(11);
		I286_IP = i286_memoryread_w(CALC_EA(op));
	}
	goto *retlb;
}

I286_F6 _jmp_far_ea16: {
	I286_WORKCLOCK(11);
	if (op < 0xc0) {
		tmp = GET_EA(op, &madr);
		I286_IP = i286_memoryread_w(madr + tmp);
		I286_CS = i286_memoryread_w(madr + LOW16(tmp + 2));
		CS_BASE = SEGSELECT(I286_CS);
	} else {
		INT_NUM(6, I286_IP - 2);
	}
	goto *retlb;
}

I286_F6 _push_ea16: {
	if (op >= 0xc0) {
		I286_WORKCLOCK(3);
		d16 = *(REG16_B20(op));
	} else {
		I286_WORKCLOCK(5);
		d16 = i286_memoryread_w(CALC_EA(op));
	}
	REGPUSH0(d16);
	goto *retlb;
}

I286_F6 _pop_ea16: {
	REGPOP0(d16);
	I286_WORKCLOCK(5);
	if (op >= 0xc0) {
		*(REG16_B20(op)) = d16;
	} else {
		i286_memorywrite_w(CALC_EA(op), d16);
	}
	goto *retlb;
}
