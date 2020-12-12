// ------------------------------------------------------------------------
#include "i286c_sf.mcr"

#define I286_SFT


I286_SFT _rol_r8_1: {
	src = *p8;
	BYTE_ROL1(dst, src)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _ror_r8_1: {
	src = *p8;
	BYTE_ROR1(dst, src)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _rcl_r8_1: {
	src = *p8;
	BYTE_RCL1(dst, src)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _rcr_r8_1: {
	src = *p8;
	BYTE_RCR1(dst, src)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _shl_r8_1: {
	src = *p8;
	BYTE_SHL1(dst, src)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _shr_r8_1: {
	src = *p8;
	BYTE_SHR1(dst, src)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _sar_r8_1: {
	src = *p8;
	BYTE_SAR1(dst, src)
	*p8 = (UINT8)dst;
	goto *retlb;
}


I286_SFT _rol_e8_1: {
	src = i286_memoryread(madr);
	BYTE_ROL1(dst, src)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _ror_e8_1: {
	src = i286_memoryread(madr);
	BYTE_ROR1(dst, src)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _rcl_e8_1: {
	src = i286_memoryread(madr);
	BYTE_RCL1(dst, src)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _rcr_e8_1: {
	src = i286_memoryread(madr);
	BYTE_RCR1(dst, src)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _shl_e8_1: {
	src = i286_memoryread(madr);
	BYTE_SHL1(dst, src)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _shr_e8_1: {
	src = i286_memoryread(madr);
	BYTE_SHR1(dst, src)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _sar_e8_1: {
	src = i286_memoryread(madr);
	BYTE_SAR1(dst, src)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}


// ------------------------------------------------------------------------

I286_SFT _rol_r16_1: {
	src = *p16;
	WORD_ROL1(dst, src)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _ror_r16_1: {
	src = *p16;
	WORD_ROR1(dst, src)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _rcl_r16_1: {
	src = *p16;
	WORD_RCL1(dst, src)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _rcr_r16_1: {
	src = *p16;
	WORD_RCR1(dst, src)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _shl_r16_1: {
	src = *p16;
	WORD_SHL1(dst, src)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _shr_r16_1: {
	src = *p16;
	WORD_SHR1(dst, src)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _sar_r16_1: {
	src = *p16;
	WORD_SAR1(dst, src)
	*p16 = (UINT16)dst;
	goto *retlb;
}


I286_SFT _rol_e16_1: {
	src = i286_memoryread_w(madr);
	WORD_ROL1(dst, src)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _ror_e16_1: {
	src = i286_memoryread_w(madr);
	WORD_ROR1(dst, src)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _rcl_e16_1: {
	src = i286_memoryread_w(madr);
	WORD_RCL1(dst, src)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _rcr_e16_1: {
	src = i286_memoryread_w(madr);
	WORD_RCR1(dst, src)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _shl_e16_1: {
	src = i286_memoryread_w(madr);
	WORD_SHL1(dst, src)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _shr_e16_1: {
	src = i286_memoryread_w(madr);
	WORD_SHR1(dst, src)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _sar_e16_1: {
	src = i286_memoryread_w(madr);
	WORD_SAR1(dst, src)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}


// ------------------------------------------------------------------------

I286_SFT _rol_r8_cl: {
	src = *p8;
	BYTE_ROLCL(dst, src, d8)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _ror_r8_cl: {
	src = *p8;
	BYTE_RORCL(dst, src, d8)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _rcl_r8_cl: {
	src = *p8;
	BYTE_RCLCL(dst, src, d8)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _rcr_r8_cl: {
	src = *p8;
	BYTE_RCRCL(dst, src, d8)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _shl_r8_cl: {
	src = *p8;
	BYTE_SHLCL(dst, src, d8)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _shr_r8_cl: {
	src = *p8;
	BYTE_SHRCL(dst, src, d8)
	*p8 = (UINT8)dst;
	goto *retlb;
}

I286_SFT _sar_r8_cl: {
	src = *p8;
	BYTE_SARCL(dst, src, d8)
	*p8 = (UINT8)dst;
	goto *retlb;
}


I286_SFT _rol_e8_cl: {
	src = i286_memoryread(madr);
	BYTE_ROLCL(dst, src, d8)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _ror_e8_cl: {
	src = i286_memoryread(madr);
	BYTE_RORCL(dst, src, d8)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _rcl_e8_cl: {
	src = i286_memoryread(madr);
	BYTE_RCLCL(dst, src, d8)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _rcr_e8_cl: {
	src = i286_memoryread(madr);
	BYTE_RCRCL(dst, src, d8)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _shl_e8_cl: {
	src = i286_memoryread(madr);
	BYTE_SHLCL(dst, src, d8)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _shr_e8_cl: {
	src = i286_memoryread(madr);
	BYTE_SHRCL(dst, src, d8)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}

I286_SFT _sar_e8_cl: {
	src = i286_memoryread(madr);
	BYTE_SARCL(dst, src, d8)
	i286_memorywrite(madr, (REG8)dst);
	goto *retlb;
}


// ------------------------------------------------------------------------

I286_SFT _rol_r16_cl: {
	src = *p16;
	WORD_ROLCL(dst, src, d8)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _ror_r16_cl: {
	src = *p16;
	WORD_RORCL(dst, src, d8)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _rcl_r16_cl: {
	src = *p16;
	WORD_RCLCL(dst, src, d8)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _rcr_r16_cl: {
	src = *p16;
	WORD_RCRCL(dst, src, d8)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _shl_r16_cl: {
	src = *p16;
	WORD_SHLCL(dst, src, d8)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _shr_r16_cl: {
	src = *p16;
	WORD_SHRCL(dst, src, d8)
	*p16 = (UINT16)dst;
	goto *retlb;
}

I286_SFT _sar_r16_cl: {
	src = *p16;
	WORD_SARCL(dst, src, d8)
	*p16 = (UINT16)dst;
	goto *retlb;
}


I286_SFT _rol_e16_cl: {
	src = i286_memoryread_w(madr);
	WORD_ROLCL(dst, src, d8)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _ror_e16_cl: {
	src = i286_memoryread_w(madr);
	WORD_RORCL(dst, src, d8)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _rcl_e16_cl: {
	src = i286_memoryread_w(madr);
	WORD_RCLCL(dst, src, d8)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _rcr_e16_cl: {
	src = i286_memoryread_w(madr);
	WORD_RCRCL(dst, src, d8)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _shl_e16_cl: {
	src = i286_memoryread_w(madr);
	WORD_SHLCL(dst, src, d8)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _shr_e16_cl: {
	src = i286_memoryread_w(madr);
	WORD_SHRCL(dst, src, d8)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

I286_SFT _sar_e16_cl: {
	src = i286_memoryread_w(madr);
	WORD_SARCL(dst, src, d8)
	i286_memorywrite_w(madr, (REG16)dst);
	goto *retlb;
}

