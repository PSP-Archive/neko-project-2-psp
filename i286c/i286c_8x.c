// -------------------------------------------------------- opecode 0x80,1,2,3
#define I286_8X

// ----- reg8

I286_8X _add_r8_i: {
	GET_PCBYTE(src)
	dst = *p8;
	ADDBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

I286_8X _or_r8_i: {
	GET_PCBYTE(src)
	dst = *p8;
	ORBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_8X _adc_r8_i: {
	GET_PCBYTE(src)
	dst = *p8;
	ADCBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

I286_8X _sbb_r8_i: {
	GET_PCBYTE(src)
	dst = *p8;
	SBBBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

I286_8X _and_r8_i: {
	GET_PCBYTE(src)
	dst = *p8;
	ANDBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_8X _sub_r8_i: {
	GET_PCBYTE(src)
	dst = *p8;
	SUBBYTE(res, dst, src);
	*p8 = (UINT8)res;
	goto *retlb;
}

I286_8X _xor_r8_i: {
	GET_PCBYTE(src)
	dst = *p8;
	XORBYTE(dst, src);
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_8X _cmp_r8_i: {
	GET_PCBYTE(src)
	dst = *p8;
	SUBBYTE(res, dst, src);
	goto *retlb;
}


// ----- ext8

I286_8X _add_ext8_i: {
	GET_PCBYTE(src)
	dst = i286_memoryread(madr);
	ADDBYTE(res, dst, src);
	i286_memorywrite(madr, (REG8)res);
	goto *retlb;
}

I286_8X _or_ext8_i: {
	GET_PCBYTE(src)
	dst = i286_memoryread(madr);
	ORBYTE(dst, src);
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_8X _adc_ext8_i: {
	GET_PCBYTE(src)
	dst = i286_memoryread(madr);
	ADCBYTE(res, dst, src);
	i286_memorywrite(madr, (REG8)res);
	goto *retlb;
}

I286_8X _sbb_ext8_i: {
	GET_PCBYTE(src)
	dst = i286_memoryread(madr);
	SBBBYTE(res, dst, src);
	i286_memorywrite(madr, (REG8)res);
	goto *retlb;
}

I286_8X _and_ext8_i: {
	GET_PCBYTE(src)
	dst = i286_memoryread(madr);
	ANDBYTE(dst, src);
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_8X _sub_ext8_i: {
	GET_PCBYTE(src)
	dst = i286_memoryread(madr);
	SUBBYTE(res, dst, src);
	i286_memorywrite(madr, (REG8)res);
	goto *retlb;
}

I286_8X _xor_ext8_i: {
	GET_PCBYTE(src)
	dst = i286_memoryread(madr);
	XORBYTE(dst, src);
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_8X _cmp_ext8_i: {
	GET_PCBYTE(src)
	dst = i286_memoryread(madr);
	SUBBYTE(res, dst, src);
	goto *retlb;
}


// -------------------------------------------------------------------------

// ----- reg16

I286_8X _add_r16_i: {
	dst = *p16;
	ADDWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

I286_8X _or_r16_i: {
	dst = *p16;
	ORWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_8X _adc_r16_i: {
	dst = *p16;
	ADCWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

I286_8X _sbb_r16_i: {
	dst = *p16;
	SBBWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

I286_8X _and_r16_i: {
	dst = *p16;
	ANDWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_8X _sub_r16_i: {
	dst = *p16;
	SUBWORD(res, dst, src);
	*p16 = (UINT16)res;
	goto *retlb;
}

I286_8X _xor_r16_i: {
	dst = *p16;
	XORWORD(dst, src);
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_8X _cmp_r16_i: {
	dst = *p16;
	SUBWORD(res, dst, src);
	goto *retlb;
}


// ----- ext16

I286_8X _add_ext16_i: {
	dst = i286_memoryread_w(madr);
	ADDWORD(res, dst, src);
	i286_memorywrite_w(madr, (REG16)res);
	goto *retlb;
}

I286_8X _or_ext16_i: {
	dst = i286_memoryread_w(madr);
	ORWORD(dst, src);
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_8X _adc_ext16_i: {
	dst = i286_memoryread_w(madr);
	ADCWORD(res, dst, src);
	i286_memorywrite_w(madr, (REG16)res);
	goto *retlb;
}

I286_8X _sbb_ext16_i: {
	dst = i286_memoryread_w(madr);
	SBBWORD(res, dst, src);
	i286_memorywrite_w(madr, (REG16)res);
	goto *retlb;
}

I286_8X _and_ext16_i: {
	dst = i286_memoryread_w(madr);
	ANDWORD(dst, src);
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_8X _sub_ext16_i: {
	dst = i286_memoryread_w(madr);
	SUBWORD(res, dst, src);
	i286_memorywrite_w(madr, (REG16)res);
	goto *retlb;
}

I286_8X _xor_ext16_i: {
	dst = i286_memoryread_w(madr);
	XORWORD(dst, src);
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_8X _cmp_ext16_i: {
	dst = i286_memoryread_w(madr);
	SUBWORD(res, dst, src);
	goto *retlb;
}
