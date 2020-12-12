static void *i286op[] = {
	&&_add_ea_r8,		// 00:	add	EA, REG8
	&&_add_ea_r16,		// 01:	add	EA, REG16
	&&_add_r8_ea,		// 02:	add	REG8, EA
	&&_add_r16_ea,		// 03:	add	REG16, EA
	&&_add_al_data8,	// 04:	add	al, DATA8
	&&_add_ax_data16,	// 05:	add	ax, DATA16
	&&_push_es,		// 06:	push	es
	&&_pop_es,		// 07:	pop	es
	&&_or_ea_r8,		// 08:	or	EA, REGF8
	&&_or_ea_r16,		// 09:	or	EA, REG16
	&&_or_r8_ea,		// 0A:	or	REG8, EA
	&&_or_r16_ea,		// 0B:	or	REG16, EA
	&&_or_al_data8,		// 0C:	or	al, DATA8
	&&_or_ax_data16,	// 0D:	or	ax, DATA16
	&&_push_cs,		// 0E:	push	cs
	&&i286c_cts,		// 0F:	i286 upper opcode
	&&_adc_ea_r8,		// 10:	adc	EA, REG8
	&&_adc_ea_r16,		// 11:	adc	EA, REG16
	&&_adc_r8_ea,		// 12:	adc	REG8, EA
	&&_adc_r16_ea,		// 13:	adc	REG16, EA
	&&_adc_al_data8,	// 14:	adc	al, DATA8
	&&_adc_ax_data16,	// 15:	adc	ax, DATA16
	&&_push_ss,		// 16:	push	ss
	&&_pop_ss,		// 17:	pop	ss
	&&_sbb_ea_r8,		// 18:	sbb	EA, REG8
	&&_sbb_ea_r16,		// 19:	sbb	EA, REG16
	&&_sbb_r8_ea,		// 1A:	sbb	REG8, EA
	&&_sbb_r16_ea,		// 1B:	sbb	REG16, EA
	&&_sbb_al_data8,	// 1C:	sbb	al, DATA8
	&&_sbb_ax_data16,	// 1D:	sbb	ax, DATA16
	&&_push_ds,		// 1E:	push	ds
	&&_pop_ds,		// 1F:	pop	ds
	&&_and_ea_r8,		// 20:	and	EA, REG8
	&&_and_ea_r16,		// 21:	and	EA, REG16
	&&_and_r8_ea,		// 22:	and	REG8, EA
	&&_and_r16_ea,		// 23:	and	REG16, EA
	&&_and_al_data8,	// 24:	and	al, DATA8
	&&_and_ax_data16,	// 25:	and	ax, DATA16
	&&_segprefix_es,	// 26:	es:
	&&_daa,			// 27:	daa
	&&_sub_ea_r8,		// 28:	sub	EA, REG8
	&&_sub_ea_r16,		// 29:	sub	EA, REG16
	&&_sub_r8_ea,		// 2A:	sub	REG8, EA
	&&_sub_r16_ea,		// 2B:	sub	REG16, EA
	&&_sub_al_data8,	// 2C:	sub	al, DATA8
	&&_sub_ax_data16,	// 2D:	sub	ax, DATA16
	&&_segprefix_cs,	// 2E:	cs:
	&&_das,			// 2F:	das
	&&_xor_ea_r8,		// 30:	xor	EA, REG8
	&&_xor_ea_r16,		// 31:	xor	EA, REG16
	&&_xor_r8_ea,		// 32:	xor	REG8, EA
	&&_xor_r16_ea,		// 33:	xor	REG16, EA
	&&_xor_al_data8,	// 34:	xor	al, DATA8
	&&_xor_ax_data16,	// 35:	xor	ax, DATA16
	&&_segprefix_ss,	// 36:	ss:
	&&_aaa,			// 37:	aaa
	&&_cmp_ea_r8,		// 38:	cmp	EA, REG8
	&&_cmp_ea_r16,		// 39:	cmp	EA, REG16
	&&_cmp_r8_ea,		// 3A:	cmp	REG8, EA
	&&_cmp_r16_ea,		// 3B:	cmp	REG16, EA
	&&_cmp_al_data8,	// 3C:	cmp	al, DATA8
	&&_cmp_ax_data16,	// 3D:	cmp	ax, DATA16
	&&_segprefix_ds,	// 3E:	ds:
	&&_aas,			// 3F:	aas
	&&_inc_ax,		// 40:	inc	ax
	&&_inc_cx,		// 41:	inc	cx
	&&_inc_dx,		// 42:	inc	dx
	&&_inc_bx,		// 43:	inc	bx
	&&_inc_sp,		// 44:	inc	sp
	&&_inc_bp,		// 45:	inc	bp
	&&_inc_si,		// 46:	inc	si
	&&_inc_di,		// 47:	inc	di
	&&_dec_ax,		// 48:	dec	ax
	&&_dec_cx,		// 49:	dec	cx
	&&_dec_dx,		// 4A:	dec	dx
	&&_dec_bx,		// 4B:	dec	bx
	&&_dec_sp,		// 4C:	dec	sp
	&&_dec_bp,		// 4D:	dec	bp
	&&_dec_si,		// 4E:	dec	si
	&&_dec_di,		// 4F:	dec	di
	&&_push_ax,		// 50:	push	ax
	&&_push_cx,		// 51:	push	cx
	&&_push_dx,		// 52:	push	dx
	&&_push_bx,		// 53:	push	bx
	&&_push_sp,		// 54:	push	sp
	&&_push_bp,		// 55:	push	bp
	&&_push_si,		// 56:	push	si
	&&_push_di,		// 57:	push	di
	&&_pop_ax,		// 58:	pop	ax
	&&_pop_cx,		// 59:	pop	cx
	&&_pop_dx,		// 5A:	pop	dx
	&&_pop_bx,		// 5B:	pop	bx
	&&_pop_sp,		// 5C:	pop	sp
	&&_pop_bp,		// 5D:	pop	bp
	&&_pop_si,		// 5E:	pop	si
	&&_pop_di,		// 5F:	pop	di
	&&_pusha,		// 60:	pusha
	&&_popa,		// 61:	popa
	&&_bound,		// 62:	bound
	&&_arpl,		// 63:	arpl
	&&_reserved,		// 64:	reserved
	&&_reserved,		// 65:	reserved
	&&_reserved,		// 66:	reserved
	&&_reserved,		// 67:	reserved
	&&_push_data16,		// 68:	push	DATA16
	&&_imul_reg_ea_data16,	// 69:	imul	REG, EA, DATA16
	&&_push_data8,		// 6A:	push	DATA8
	&&_imul_reg_ea_data8,	// 6B:	imul	REG, EA, DATA8
	&&_insb,		// 6C:	insb
	&&_insw,		// 6D:	insw
	&&_outsb,		// 6E:	outsb
	&&_outsw,		// 6F:	outsw
	&&_jo_short,		// 70:	jo	short
	&&_jno_short,		// 71:	jno	short
	&&_jc_short,		// 72:	jnae/jb/jc	short
	&&_jnc_short,		// 73:	jae/jnb/jnc	short
	&&_jz_short,		// 74:	je/jz	short
	&&_jnz_short,		// 75:	jne/jnz	short
	&&_jna_short,		// 76:	jna/jbe	short
	&&_ja_short,		// 77:	ja/jnbe	short
	&&_js_short,		// 78:	js	short
	&&_jns_short,		// 79:	jns	short
	&&_jp_short,		// 7A:	jp/jpe	short
	&&_jnp_short,		// 7B:	jnp/jpo	short
	&&_jl_short,		// 7C:	jl/jnge	short
	&&_jnl_short,		// 7D:	jnl/jge	short
	&&_jle_short,		// 7E:	jle/jng	short
	&&_jnle_short,		// 7F:	jg/jnle	short
	&&_calc_ea8_i8,		// 80:	op	EA8, DATA8
	&&_calc_ea16_i16,	// 81:	op	EA16, DATA16
	&&_calc_ea8_i8,		// 82:	op	EA8, DATA8
	&&_calc_ea16_i8,	// 83:	op	EA16, DATA8
	&&_test_ea_r8,		// 84:	test	EA, REG8
	&&_test_ea_r16,		// 85:	test	EA, REG16
	&&_xchg_ea_r8,		// 86:	xchg	EA, REG8
	&&_xchg_ea_r16,		// 87:	xchg	EA, REG16
	&&_mov_ea_r8,		// 88:	mov	EA, REG8
	&&_mov_ea_r16,		// 89:	mov	EA, REG16
	&&_mov_r8_ea,		// 8A:	mov	REG8, EA
	&&_mov_r16_ea,		// 8B:	mov	REG16, EA
	&&_mov_ea_seg,		// 8C:	mov	EA, segreg
	&&_lea_r16_ea,		// 8D:	lea	REG16, EA
	&&_mov_seg_ea,		// 8E:	mov	segrem, EA
	&&_pop_ea,		// 8F:	pop	EA
	&&_nop,			// 90:	xchg	ax, ax
	&&_xchg_ax_cx,		// 91:	xchg	ax, cx
	&&_xchg_ax_dx,		// 92:	xchg	ax, dx
	&&_xchg_ax_bx,		// 93:	xchg	ax, bx
	&&_xchg_ax_sp,		// 94:	xchg	ax, sp
	&&_xchg_ax_bp,		// 95:	xchg	ax, bp
	&&_xchg_ax_si,		// 96:	xchg	ax, si
	&&_xchg_ax_di,		// 97:	xchg	ax, di
	&&_cbw,			// 98:	cbw
	&&_cwd,			// 99:	cwd
	&&_call_far,		// 9A:	call far
	&&_wait,		// 9B:	wait
	&&_pushf,		// 9C:	pushf
	&&_popf,		// 9D:	popf
	&&_sahf,		// 9E:	sahf
	&&_lahf,		// 9F:	lahf
	&&_mov_al_m8,		// A0:	mov	al, m8
	&&_mov_ax_m16,		// A1:	mov	ax, m16
	&&_mov_m8_al,		// A2:	mov	m8, al
	&&_mov_m16_ax,		// A3:	mov	m16, ax
	&&_movsb,		// A4:	movsb
	&&_movsw,		// A5:	movsw
	&&_cmpsb,		// A6:	cmpsb
	&&_cmpsw,		// A7:	cmpsw
	&&_test_al_data8,	// A8:	test	al, DATA8
	&&_test_ax_data16,	// A9:	test	ax, DATA16
	&&_stosb,		// AA:	stosw
	&&_stosw,		// AB:	stosw
	&&_lodsb,		// AC:	lodsb
	&&_lodsw,		// AD:	lodsw
	&&_scasb,		// AE:	scasb
	&&_scasw,		// AF:	scasw
	&&_mov_al_imm,		// B0:	mov	al, imm8
	&&_mov_cl_imm,		// B1:	mov	cl, imm8
	&&_mov_dl_imm,		// B2:	mov	dl, imm8
	&&_mov_bl_imm,		// B3:	mov	bl, imm8
	&&_mov_ah_imm,		// B4:	mov	ah, imm8
	&&_mov_ch_imm,		// B5:	mov	ch, imm8
	&&_mov_dh_imm,		// B6:	mov	dh, imm8
	&&_mov_bh_imm,		// B7:	mov	bh, imm8
	&&_mov_ax_imm,		// B8:	mov	ax, imm16
	&&_mov_cx_imm,		// B9:	mov	cx, imm16
	&&_mov_dx_imm,		// BA:	mov	dx, imm16
	&&_mov_bx_imm,		// BB:	mov	bx, imm16
	&&_mov_sp_imm,		// BC:	mov	sp, imm16
	&&_mov_bp_imm,		// BD:	mov	bp, imm16
	&&_mov_si_imm,		// BE:	mov	si, imm16
	&&_mov_di_imm,		// BF:	mov	di, imm16
	&&_shift_ea8_data8,	// C0:	shift	EA8, DATA8
	&&_shift_ea16_data8,	// C1:	shift	EA16, DATA8
	&&_ret_near_data16,	// C2:	ret	near DATA16
	&&_ret_near,		// C3:	ret	near
	&&_les_r16_ea,		// C4:	les	REG16, EA
	&&_lds_r16_ea,		// C5:	lds	REG16, EA
	&&_mov_ea8_data8,	// C6:	mov	EA8, DATA8
	&&_mov_ea16_data16,	// C7:	mov	EA16, DATA16
	&&_enter,		// C8:	enter	DATA16, DATA8
	&&fleave,		// C9:	leave
	&&_ret_far_data16,	// CA:	ret	far	DATA16
	&&_ret_far,		// CB:	ret	far
	&&_int_03,		// CC:	int	3
	&&_int_data8,		// CD:	int	DATA8
	&&_into,		// CE:	into
	&&_iret,		// CF:	iret
	&&_shift_ea8_1,		// D0:	shift	EA8, 1
	&&_shift_ea16_1,	// D1:	shift	EA16, 1
	&&_shift_ea8_cl,	// D2:	shift	EA8, cl
	&&_shift_ea16_cl,	// D3:	shift	EA16, cl
	&&_aam,			// D4:	AAM
	&&_aad,			// D5:	AAD
	&&_setalc,		// D6:	setalc (80286)
	&&_xlat,		// D7:	xlat
	&&_esc,			// D8:	esc
	&&_esc,			// D9:	esc
	&&_esc,			// DA:	esc
	&&_esc,			// DB:	esc
	&&_esc,			// DC:	esc
	&&_esc,			// DD:	esc
	&&_esc,			// DE:	esc
	&&_esc,			// DF:	esc
	&&_loopnz,		// E0:	loopnz
	&&_loopz,		// E1:	loopz
	&&_loop,		// E2:	loop
	&&_jcxz,		// E3:	jcxz
	&&_in_al_data8,		// E4:	in	al, DATA8
	&&_in_ax_data8,		// E5:	in	ax, DATA8
	&&_out_data8_al,	// E6:	out	DATA8, al
	&&_out_data8_ax,	// E7:	out	DATA8, ax
	&&_call_near,		// E8:	call	near
	&&_jmp_near,		// E9:	jmp	near
	&&_jmp_far,		// EA:	jmp	far
	&&_jmp_short,		// EB:	jmp	short
	&&_in_al_dx,		// EC:	in	al, dx
	&&_in_ax_dx,		// ED:	in	ax, dx
	&&_out_dx_al,		// EE:	out	dx, al
	&&_out_dx_ax,		// EF:	out	dx, ax
	&&_lock,		// F0:	lock
	&&_lock,		// F1:	lock
	&&_repne,		// F2:	repne
	&&_repe,		// F3:	repe
	&&_hlt,			// F4:	hlt
	&&_cmc,			// F5:	cmc
	&&_ope0xf6,		// F6:	
	&&_ope0xf7,		// F7:	
	&&_clc,			// F8:	clc
	&&_stc,			// F9:	stc
	&&_cli,			// FA:	cli
	&&_sti,			// FB:	sti
	&&_cld,			// FC:	cld
	&&_std,			// FD:	std
	&&_ope0xfe,		// FE:	
	&&_ope0xff,		// FF:	
};

static void *i286op_repe[] = {
	&&_add_ea_r8,		// 00:	add	EA, REG8
	&&_add_ea_r16,		// 01:	add	EA, REG16
	&&_add_r8_ea,		// 02:	add	REG8, EA
	&&_add_r16_ea,		// 03:	add	REG16, EA
	&&_add_al_data8,	// 04:	add	al, DATA8
	&&_add_ax_data16,	// 05:	add	ax, DATA16
	&&_push_es,		// 06:	push	es
	&&_pop_es,		// 07:	pop	es
	&&_or_ea_r8,		// 08:	or	EA, REGF8
	&&_or_ea_r16,		// 09:	or	EA, REG16
	&&_or_r8_ea,		// 0A:	or	REG8, EA
	&&_or_r16_ea,		// 0B:	or	REG16, EA
	&&_or_al_data8,		// 0C:	or	al, DATA8
	&&_or_ax_data16,	// 0D:	or	ax, DATA16
	&&_push_cs,		// 0E:	push	cs
	&&i286c_cts,		// 0F:	i286 upper opcode
	&&_adc_ea_r8,		// 10:	adc	EA, REG8
	&&_adc_ea_r16,		// 11:	adc	EA, REG16
	&&_adc_r8_ea,		// 12:	adc	REG8, EA
	&&_adc_r16_ea,		// 13:	adc	REG16, EA
	&&_adc_al_data8,	// 14:	adc	al, DATA8
	&&_adc_ax_data16,	// 15:	adc	ax, DATA16
	&&_push_ss,		// 16:	push	ss
	&&_pop_ss,		// 17:	pop	ss
	&&_sbb_ea_r8,		// 18:	sbb	EA, REG8
	&&_sbb_ea_r16,		// 19:	sbb	EA, REG16
	&&_sbb_r8_ea,		// 1A:	sbb	REG8, EA
	&&_sbb_r16_ea,		// 1B:	sbb	REG16, EA
	&&_sbb_al_data8,	// 1C:	sbb	al, DATA8
	&&_sbb_ax_data16,	// 1D:	sbb	ax, DATA16
	&&_push_ds,		// 1E:	push	ds
	&&_pop_ds,		// 1F:	pop	ds
	&&_and_ea_r8,		// 20:	and	EA, REG8
	&&_and_ea_r16,		// 21:	and	EA, REG16
	&&_and_r8_ea,		// 22:	and	REG8, EA
	&&_and_r16_ea,		// 23:	and	REG16, EA
	&&_and_al_data8,	// 24:	and	al, DATA8
	&&_and_ax_data16,	// 25:	and	ax, DATA16
	&&_repe_segprefix_es,	// 26:	repe es:
	&&_daa,			// 27:	daa
	&&_sub_ea_r8,		// 28:	sub	EA, REG8
	&&_sub_ea_r16,		// 29:	sub	EA, REG16
	&&_sub_r8_ea,		// 2A:	sub	REG8, EA
	&&_sub_r16_ea,		// 2B:	sub	REG16, EA
	&&_sub_al_data8,	// 2C:	sub	al, DATA8
	&&_sub_ax_data16,	// 2D:	sub	ax, DATA16
	&&_repe_segprefix_cs,	// 2E:	repe cs:
	&&_das,			// 2F:	das
	&&_xor_ea_r8,		// 30:	xor	EA, REG8
	&&_xor_ea_r16,		// 31:	xor	EA, REG16
	&&_xor_r8_ea,		// 32:	xor	REG8, EA
	&&_xor_r16_ea,		// 33:	xor	REG16, EA
	&&_xor_al_data8,	// 34:	xor	al, DATA8
	&&_xor_ax_data16,	// 35:	xor	ax, DATA16
	&&_repe_segprefix_ss,	// 36:	repe ss:
	&&_aaa,			// 37:	aaa
	&&_cmp_ea_r8,		// 38:	cmp	EA, REG8
	&&_cmp_ea_r16,		// 39:	cmp	EA, REG16
	&&_cmp_r8_ea,		// 3A:	cmp	REG8, EA
	&&_cmp_r16_ea,		// 3B:	cmp	REG16, EA
	&&_cmp_al_data8,	// 3C:	cmp	al, DATA8
	&&_cmp_ax_data16,	// 3D:	cmp	ax, DATA16
	&&_repe_segprefix_ds,	// 3E:	repe ds:
	&&_aas,			// 3F:	aas
	&&_inc_ax,		// 40:	inc	ax
	&&_inc_cx,		// 41:	inc	cx
	&&_inc_dx,		// 42:	inc	dx
	&&_inc_bx,		// 43:	inc	bx
	&&_inc_sp,		// 44:	inc	sp
	&&_inc_bp,		// 45:	inc	bp
	&&_inc_si,		// 46:	inc	si
	&&_inc_di,		// 47:	inc	di
	&&_dec_ax,		// 48:	dec	ax
	&&_dec_cx,		// 49:	dec	cx
	&&_dec_dx,		// 4A:	dec	dx
	&&_dec_bx,		// 4B:	dec	bx
	&&_dec_sp,		// 4C:	dec	sp
	&&_dec_bp,		// 4D:	dec	bp
	&&_dec_si,		// 4E:	dec	si
	&&_dec_di,		// 4F:	dec	di
	&&_push_ax,		// 50:	push	ax
	&&_push_cx,		// 51:	push	cx
	&&_push_dx,		// 52:	push	dx
	&&_push_bx,		// 53:	push	bx
	&&_push_sp,		// 54:	push	sp
	&&_push_bp,		// 55:	push	bp
	&&_push_si,		// 56:	push	si
	&&_push_di,		// 57:	push	di
	&&_pop_ax,		// 58:	pop	ax
	&&_pop_cx,		// 59:	pop	cx
	&&_pop_dx,		// 5A:	pop	dx
	&&_pop_bx,		// 5B:	pop	bx
	&&_pop_sp,		// 5C:	pop	sp
	&&_pop_bp,		// 5D:	pop	bp
	&&_pop_si,		// 5E:	pop	si
	&&_pop_di,		// 5F:	pop	di
	&&_pusha,		// 60:	pusha
	&&_popa,		// 61:	popa
	&&_bound,		// 62:	bound
	&&_arpl,		// 63:	arpl
	&&_reserved,		// 64:	reserved
	&&_reserved,		// 65:	reserved
	&&_reserved,		// 66:	reserved
	&&_reserved,		// 67:	reserved
	&&_push_data16,		// 68:	push	DATA16
	&&_imul_reg_ea_data16,	// 69:	imul	REG, EA, DATA16
	&&_push_data8,		// 6A:	push	DATA8
	&&_imul_reg_ea_data8,	// 6B:	imul	REG, EA, DATA8
	&&i286c_rep_insb,	// 6C:	rep	insb
	&&i286c_rep_insw,	// 6D:	rep	insw
	&&i286c_rep_outsb,	// 6E:	rep	outsb
	&&i286c_rep_outsw,	// 6F:	rep	outsw
	&&_jo_short,		// 70:	jo	short
	&&_jno_short,		// 71:	jno	short
	&&_jc_short,		// 72:	jnae/jb/jc	short
	&&_jnc_short,		// 73:	jae/jnb/jnc	short
	&&_jz_short,		// 74:	je/jz	short
	&&_jnz_short,		// 75:	jne/jnz	short
	&&_jna_short,		// 76:	jna/jbe	short
	&&_ja_short,		// 77:	ja/jnbe	short
	&&_js_short,		// 78:	js	short
	&&_jns_short,		// 79:	jns	short
	&&_jp_short,		// 7A:	jp/jpe	short
	&&_jnp_short,		// 7B:	jnp/jpo	short
	&&_jl_short,		// 7C:	jl/jnge	short
	&&_jnl_short,		// 7D:	jnl/jge	short
	&&_jle_short,		// 7E:	jle/jng	short
	&&_jnle_short,		// 7F:	jg/jnle	short
	&&_calc_ea8_i8,		// 80:	op	EA8, DATA8
	&&_calc_ea16_i16,	// 81:	op	EA16, DATA16
	&&_calc_ea8_i8,		// 82:	op	EA8, DATA8
	&&_calc_ea16_i8,	// 83:	op	EA16, DATA8
	&&_test_ea_r8,		// 84:	test	EA, REG8
	&&_test_ea_r16,		// 85:	test	EA, REG16
	&&_xchg_ea_r8,		// 86:	xchg	EA, REG8
	&&_xchg_ea_r16,		// 87:	xchg	EA, REG16
	&&_mov_ea_r8,		// 88:	mov	EA, REG8
	&&_mov_ea_r16,		// 89:	mov	EA, REG16
	&&_mov_r8_ea,		// 8A:	mov	REG8, EA
	&&_mov_r16_ea,		// 8B:	add	REG16, EA
	&&_mov_ea_seg,		// 8C:	mov	EA, segreg
	&&_lea_r16_ea,		// 8D:	lea	REG16, EA
	&&_mov_seg_ea,		// 8E:	mov	segrem, EA
	&&_pop_ea,		// 8F:	pop	EA
	&&_nop,			// 90:	xchg	ax, ax
	&&_xchg_ax_cx,		// 91:	xchg	ax, cx
	&&_xchg_ax_dx,		// 92:	xchg	ax, dx
	&&_xchg_ax_bx,		// 93:	xchg	ax, bx
	&&_xchg_ax_sp,		// 94:	xchg	ax, sp
	&&_xchg_ax_bp,		// 95:	xchg	ax, bp
	&&_xchg_ax_si,		// 96:	xchg	ax, si
	&&_xchg_ax_di,		// 97:	xchg	ax, di
	&&_cbw,			// 98:	cbw
	&&_cwd,			// 99:	cwd
	&&_call_far,		// 9A:	call far
	&&_wait,		// 9B:	wait
	&&_pushf,		// 9C:	pushf
	&&_popf,		// 9D:	popf
	&&_sahf,		// 9E:	sahf
	&&_lahf,		// 9F:	lahf
	&&_mov_al_m8,		// A0:	mov	al, m8
	&&_mov_ax_m16,		// A1:	mov	ax, m16
	&&_mov_m8_al,		// A2:	mov	m8, al
	&&_mov_m16_ax,		// A3:	mov	m16, ax
	&&i286c_rep_movsb,	// A4:	rep movsb
	&&i286c_rep_movsw,	// A5:	rep movsw
	&&i286c_repe_cmpsb,	// A6:	repe cmpsb
	&&i286c_repe_cmpsw,	// A7:	repe cmpsw
	&&_test_al_data8,	// A8:	test	al, DATA8
	&&_test_ax_data16,	// A9:	test	ax, DATA16
	&&i286c_rep_stosb,	// AA:	rep stosb
	&&i286c_rep_stosw,	// AB:	rep stosw
	&&i286c_rep_lodsb,	// AC:	rep lodsb
	&&i286c_rep_lodsw,	// AD:	rep lodsw
	&&i286c_repe_scasb,	// AE:	repe scasb
	&&i286c_repe_scasw,	// AF:	repe scasw
	&&_mov_al_imm,		// B0:	mov	al, imm8
	&&_mov_cl_imm,		// B1:	mov	cl, imm8
	&&_mov_dl_imm,		// B2:	mov	dl, imm8
	&&_mov_bl_imm,		// B3:	mov	bl, imm8
	&&_mov_ah_imm,		// B4:	mov	ah, imm8
	&&_mov_ch_imm,		// B5:	mov	ch, imm8
	&&_mov_dh_imm,		// B6:	mov	dh, imm8
	&&_mov_bh_imm,		// B7:	mov	bh, imm8
	&&_mov_ax_imm,		// B8:	mov	ax, imm16
	&&_mov_cx_imm,		// B9:	mov	cx, imm16
	&&_mov_dx_imm,		// BA:	mov	dx, imm16
	&&_mov_bx_imm,		// BB:	mov	bx, imm16
	&&_mov_sp_imm,		// BC:	mov	sp, imm16
	&&_mov_bp_imm,		// BD:	mov	bp, imm16
	&&_mov_si_imm,		// BE:	mov	si, imm16
	&&_mov_di_imm,		// BF:	mov	di, imm16
	&&_shift_ea8_data8,	// C0:	shift	EA8, DATA8
	&&_shift_ea16_data8,	// C1:	shift	EA16, DATA8
	&&_ret_near_data16,	// C2:	ret near DATA16
	&&_ret_near,		// C3:	ret near
	&&_les_r16_ea,		// C4:	les	REG16, EA
	&&_lds_r16_ea,		// C5:	lds	REG16, EA
	&&_mov_ea8_data8,	// C6:	mov	EA8, DATA8
	&&_mov_ea16_data16,	// C7:	mov	EA16, DATA16
	&&_enter,		// C8:	enter	DATA16, DATA8
	&&fleave,		// C9:	leave
	&&_ret_far_data16,	// CA:	ret far	DATA16
	&&_ret_far,		// CB:	ret far
	&&_int_03,		// CC:	int	3
	&&_int_data8,		// CD:	int	DATA8
	&&_into,		// CE:	into
	&&_iret,		// CF:	iret
	&&_shift_ea8_1,		// D0:	shift	EA8, 1
	&&_shift_ea16_1,	// D1:	shift	EA16, 1
	&&_shift_ea8_cl,	// D2:	shift	EA8, cl
	&&_shift_ea16_cl,	// D3:	shift	EA16, cl
	&&_aam,			// D4:	AAM
	&&_aad,			// D5:	AAD
	&&_setalc,		// D6:	setalc (80286)
	&&_xlat,		// D7:	xlat
	&&_esc,			// D8:	esc
	&&_esc,			// D9:	esc
	&&_esc,			// DA:	esc
	&&_esc,			// DB:	esc
	&&_esc,			// DC:	esc
	&&_esc,			// DD:	esc
	&&_esc,			// DE:	esc
	&&_esc,			// DF:	esc
	&&_loopnz,		// E0:	loopnz
	&&_loopz,		// E1:	loopz
	&&_loop,		// E2:	loop
	&&_jcxz,		// E3:	jcxz
	&&_in_al_data8,		// E4:	in	al, DATA8
	&&_in_ax_data8,		// E5:	in	ax, DATA8
	&&_out_data8_al,	// E6:	out	DATA8, al
	&&_out_data8_ax,	// E7:	out	DATA8, ax
	&&_call_near,		// E8:	call near
	&&_jmp_near,		// E9:	jmp near
	&&_jmp_far,		// EA:	jmp far
	&&_jmp_short,		// EB:	jmp short
	&&_in_al_dx,		// EC:	in	al, dx
	&&_in_ax_dx,		// ED:	in	ax, dx
	&&_out_dx_al,		// EE:	out	dx, al
	&&_out_dx_ax,		// EF:	out	dx, ax
	&&_lock,		// F0:	lock
	&&_lock,		// F1:	lock
	&&_repne,		// F2:	repne
	&&_repe,		// F3:	repe
	&&_hlt,			// F4:	hlt
	&&_cmc,			// F5:	cmc
	&&_ope0xf6,		// F6:	
	&&_ope0xf7,		// F7:	
	&&_clc,			// F8:	clc
	&&_stc,			// F9:	stc
	&&_cli,			// FA:	cli
	&&_sti,			// FB:	sti
	&&_cld,			// FC:	cld
	&&_std,			// FD:	std
	&&_ope0xfe,		// FE:	
	&&_ope0xff,		// FF:	
};

static  void *i286op_repne[] = {
	&&_add_ea_r8,		// 00:	add	EA, REG8
	&&_add_ea_r16,		// 01:	add	EA, REG16
	&&_add_r8_ea,		// 02:	add	REG8, EA
	&&_add_r16_ea,		// 03:	add	REG16, EA
	&&_add_al_data8,	// 04:	add	al, DATA8
	&&_add_ax_data16,	// 05:	add	ax, DATA16
	&&_push_es,		// 06:	push	es
	&&_pop_es,		// 07:	pop	es
	&&_or_ea_r8,		// 08:	or	EA, REGF8
	&&_or_ea_r16,		// 09:	or	EA, REG16
	&&_or_r8_ea,		// 0A:	or	REG8, EA
	&&_or_r16_ea,		// 0B:	or	REG16, EA
	&&_or_al_data8,		// 0C:	or	al, DATA8
	&&_or_ax_data16,	// 0D:	or	ax, DATA16
	&&_push_cs,		// 0E:	push	cs
	&&i286c_cts,		// 0F:	i286 upper opcode
	&&_adc_ea_r8,		// 10:	adc	EA, REG8
	&&_adc_ea_r16,		// 11:	adc	EA, REG16
	&&_adc_r8_ea,		// 12:	adc	REG8, EA
	&&_adc_r16_ea,		// 13:	adc	REG16, EA
	&&_adc_al_data8,	// 14:	adc	al, DATA8
	&&_adc_ax_data16,	// 15:	adc	ax, DATA16
	&&_push_ss,		// 16:	push	ss
	&&_pop_ss,		// 17:	pop	ss
	&&_sbb_ea_r8,		// 18:	sbb	EA, REG8
	&&_sbb_ea_r16,		// 19:	sbb	EA, REG16
	&&_sbb_r8_ea,		// 1A:	sbb	REG8, EA
	&&_sbb_r16_ea,		// 1B:	sbb	REG16, EA
	&&_sbb_al_data8,	// 1C:	sbb	al, DATA8
	&&_sbb_ax_data16,	// 1D:	sbb	ax, DATA16
	&&_push_ds,		// 1E:	push	ds
	&&_pop_ds,		// 1F:	pop	ds
	&&_and_ea_r8,		// 20:	and	EA, REG8
	&&_and_ea_r16,		// 21:	and	EA, REG16
	&&_and_r8_ea,		// 22:	and	REG8, EA
	&&_and_r16_ea,		// 23:	and	REG16, EA
	&&_and_al_data8,	// 24:	and	al, DATA8
	&&_and_ax_data16,	// 25:	and	ax, DATA16
	&&_repne_segprefix_es,	// 26:	repne es:
	&&_daa,			// 27:	daa
	&&_sub_ea_r8,		// 28:	sub	EA, REG8
	&&_sub_ea_r16,		// 29:	sub	EA, REG16
	&&_sub_r8_ea,		// 2A:	sub	REG8, EA
	&&_sub_r16_ea,		// 2B:	sub	REG16, EA
	&&_sub_al_data8,	// 2C:	sub	al, DATA8
	&&_sub_ax_data16,	// 2D:	sub	ax, DATA16
	&&_repne_segprefix_cs,	// 2E:	repne cs:
	&&_das,			// 2F:	das
	&&_xor_ea_r8,		// 30:	xor	EA, REG8
	&&_xor_ea_r16,		// 31:	xor	EA, REG16
	&&_xor_r8_ea,		// 32:	xor	REG8, EA
	&&_xor_r16_ea,		// 33:	xor	REG16, EA
	&&_xor_al_data8,	// 34:	xor	al, DATA8
	&&_xor_ax_data16,	// 35:	xor	ax, DATA16
	&&_repne_segprefix_ss,	// 36:	repne ss:
	&&_aaa,			// 37:	aaa
	&&_cmp_ea_r8,		// 38:	cmp	EA, REG8
	&&_cmp_ea_r16,		// 39:	cmp	EA, REG16
	&&_cmp_r8_ea,		// 3A:	cmp	REG8, EA
	&&_cmp_r16_ea,		// 3B:	cmp	REG16, EA
	&&_cmp_al_data8,	// 3C:	cmp	al, DATA8
	&&_cmp_ax_data16,	// 3D:	cmp	ax, DATA16
	&&_repne_segprefix_ds,	// 3E:	repne ds:
	&&_aas,			// 3F:	aas
	&&_inc_ax,		// 40:	inc	ax
	&&_inc_cx,		// 41:	inc	cx
	&&_inc_dx,		// 42:	inc	dx
	&&_inc_bx,		// 43:	inc	bx
	&&_inc_sp,		// 44:	inc	sp
	&&_inc_bp,		// 45:	inc	bp
	&&_inc_si,		// 46:	inc	si
	&&_inc_di,		// 47:	inc	di
	&&_dec_ax,		// 48:	dec	ax
	&&_dec_cx,		// 49:	dec	cx
	&&_dec_dx,		// 4A:	dec	dx
	&&_dec_bx,		// 4B:	dec	bx
	&&_dec_sp,		// 4C:	dec	sp
	&&_dec_bp,		// 4D:	dec	bp
	&&_dec_si,		// 4E:	dec	si
	&&_dec_di,		// 4F:	dec	di
	&&_push_ax,		// 50:	push	ax
	&&_push_cx,		// 51:	push	cx
	&&_push_dx,		// 52:	push	dx
	&&_push_bx,		// 53:	push	bx
	&&_push_sp,		// 54:	push	sp
	&&_push_bp,		// 55:	push	bp
	&&_push_si,		// 56:	push	si
	&&_push_di,		// 57:	push	di
	&&_pop_ax,		// 58:	pop	ax
	&&_pop_cx,		// 59:	pop	cx
	&&_pop_dx,		// 5A:	pop	dx
	&&_pop_bx,		// 5B:	pop	bx
	&&_pop_sp,		// 5C:	pop	sp
	&&_pop_bp,		// 5D:	pop	bp
	&&_pop_si,		// 5E:	pop	si
	&&_pop_di,		// 5F:	pop	di
	&&_pusha,		// 60:	pusha
	&&_popa,		// 61:	popa
	&&_bound,		// 62:	bound
	&&_arpl,		// 63:	arpl
	&&_reserved,		// 64:	reserved
	&&_reserved,		// 65:	reserved
	&&_reserved,		// 66:	reserved
	&&_reserved,		// 67:	reserved
	&&_push_data16,		// 68:	push	DATA16
	&&_imul_reg_ea_data16,	// 69:	imul	REG, EA, DATA16
	&&_push_data8,		// 6A:	push	DATA8
	&&_imul_reg_ea_data8,	// 6B:	imul	REG, EA, DATA8
	&&i286c_rep_insb,	// 6C:	rep insb
	&&i286c_rep_insw,	// 6D:	rep insw
	&&i286c_rep_outsb,	// 6E:	rep outsb
	&&i286c_rep_outsw,	// 6F:	rep outsw
	&&_jo_short,		// 70:	jo short
	&&_jno_short,		// 71:	jno short
	&&_jc_short,		// 72:	jnae/jb/jc short
	&&_jnc_short,		// 73:	jae/jnb/jnc short
	&&_jz_short,		// 74:	je/jz short
	&&_jnz_short,		// 75:	jne/jnz short
	&&_jna_short,		// 76:	jna/jbe short
	&&_ja_short,		// 77:	ja/jnbe short
	&&_js_short,		// 78:	js short
	&&_jns_short,		// 79:	jns short
	&&_jp_short,		// 7A:	jp/jpe short
	&&_jnp_short,		// 7B:	jnp/jpo short
	&&_jl_short,		// 7C:	jl/jnge short
	&&_jnl_short,		// 7D:	jnl/jge short
	&&_jle_short,		// 7E:	jle/jng short
	&&_jnle_short,		// 7F:	jg/jnle short
	&&_calc_ea8_i8,		// 80:	op	EA8, DATA8
	&&_calc_ea16_i16,	// 81:	op	EA16, DATA16
	&&_calc_ea8_i8,		// 82:	op	EA8, DATA8
	&&_calc_ea16_i8,	// 83:	op	EA16, DATA8
	&&_test_ea_r8,		// 84:	test	EA, REG8
	&&_test_ea_r16,		// 85:	test	EA, REG16
	&&_xchg_ea_r8,		// 86:	xchg	EA, REG8
	&&_xchg_ea_r16,		// 87:	xchg	EA, REG16
	&&_mov_ea_r8,		// 88:	mov	EA, REG8
	&&_mov_ea_r16,		// 89:	mov	EA, REG16
	&&_mov_r8_ea,		// 8A:	mov	REG8, EA
	&&_mov_r16_ea,		// 8B:	add	REG16, EA
	&&_mov_ea_seg,		// 8C:	mov	EA, segreg
	&&_lea_r16_ea,		// 8D:	lea	REG16, EA
	&&_mov_seg_ea,		// 8E:	mov	segrem, EA
	&&_pop_ea,		// 8F:	pop	EA
	&&_nop,			// 90:	xchg	ax, ax
	&&_xchg_ax_cx,		// 91:	xchg	ax, cx
	&&_xchg_ax_dx,		// 92:	xchg	ax, dx
	&&_xchg_ax_bx,		// 93:	xchg	ax, bx
	&&_xchg_ax_sp,		// 94:	xchg	ax, sp
	&&_xchg_ax_bp,		// 95:	xchg	ax, bp
	&&_xchg_ax_si,		// 96:	xchg	ax, si
	&&_xchg_ax_di,		// 97:	xchg	ax, di
	&&_cbw,			// 98:	cbw
	&&_cwd,			// 99:	cwd
	&&_call_far,		// 9A:	call far
	&&_wait,		// 9B:	wait
	&&_pushf,		// 9C:	pushf
	&&_popf,		// 9D:	popf
	&&_sahf,		// 9E:	sahf
	&&_lahf,		// 9F:	lahf
	&&_mov_al_m8,		// A0:	mov	al, m8
	&&_mov_ax_m16,		// A1:	mov	ax, m16
	&&_mov_m8_al,		// A2:	mov	m8, al
	&&_mov_m16_ax,		// A3:	mov	m16, ax
	&&i286c_rep_movsb,	// A4:	rep movsb
	&&i286c_rep_movsw,	// A5:	rep movsw
	&&i286c_repne_cmpsb,	// A6:	repne cmpsb
	&&i286c_repne_cmpsw,	// A7:	repne cmpsw
	&&_test_al_data8,	// A8:	test	al, DATA8
	&&_test_ax_data16,	// A9:	test	ax, DATA16
	&&i286c_rep_stosb,	// AA:	rep stosb
	&&i286c_rep_stosw,	// AB:	rep stosw
	&&i286c_rep_lodsb,	// AC:	rep lodsb
	&&i286c_rep_lodsw,	// AD:	rep lodsw
	&&i286c_repne_scasb,	// AE:	repne scasb
	&&i286c_repne_scasw,	// AF:	repne scasw
	&&_mov_al_imm,		// B0:	mov	al, imm8
	&&_mov_cl_imm,		// B1:	mov	cl, imm8
	&&_mov_dl_imm,		// B2:	mov	dl, imm8
	&&_mov_bl_imm,		// B3:	mov	bl, imm8
	&&_mov_ah_imm,		// B4:	mov	ah, imm8
	&&_mov_ch_imm,		// B5:	mov	ch, imm8
	&&_mov_dh_imm,		// B6:	mov	dh, imm8
	&&_mov_bh_imm,		// B7:	mov	bh, imm8
	&&_mov_ax_imm,		// B8:	mov	ax, imm16
	&&_mov_cx_imm,		// B9:	mov	cx, imm16
	&&_mov_dx_imm,		// BA:	mov	dx, imm16
	&&_mov_bx_imm,		// BB:	mov	bx, imm16
	&&_mov_sp_imm,		// BC:	mov	sp, imm16
	&&_mov_bp_imm,		// BD:	mov	bp, imm16
	&&_mov_si_imm,		// BE:	mov	si, imm16
	&&_mov_di_imm,		// BF:	mov	di, imm16
	&&_shift_ea8_data8,	// C0:	shift	EA8, DATA8
	&&_shift_ea16_data8,	// C1:	shift	EA16, DATA8
	&&_ret_near_data16,	// C2:	ret near DATA16
	&&_ret_near,		// C3:	ret near
	&&_les_r16_ea,		// C4:	les	REG16, EA
	&&_lds_r16_ea,		// C5:	lds	REG16, EA
	&&_mov_ea8_data8,	// C6:	mov	EA8, DATA8
	&&_mov_ea16_data16,	// C7:	mov	EA16, DATA16
	&&_enter,		// C8:	enter	DATA16, DATA8
	&&fleave,		// C9:	leave
	&&_ret_far_data16,	// CA:ret far	DATA16
	&&_ret_far,		// CB:	ret far
	&&_int_03,		// CC:	int	3
	&&_int_data8,		// CD:	int	DATA8
	&&_into,		// CE:	into
	&&_iret,		// CF:	iret
	&&_shift_ea8_1,		// D0:	shift EA8, 1
	&&_shift_ea16_1,	// D1:	shift EA16, 1
	&&_shift_ea8_cl,	// D2:	shift EA8, cl
	&&_shift_ea16_cl,	// D3:	shift EA16, cl
	&&_aam,			// D4:	AAM
	&&_aad,			// D5:	AAD
	&&_setalc,		// D6:	setalc (80286)
	&&_xlat,		// D7:	xlat
	&&_esc,			// D8:	esc
	&&_esc,			// D9:	esc
	&&_esc,			// DA:	esc
	&&_esc,			// DB:	esc
	&&_esc,			// DC:	esc
	&&_esc,			// DD:	esc
	&&_esc,			// DE:	esc
	&&_esc,			// DF:	esc
	&&_loopnz,		// E0:	loopnz
	&&_loopz,		// E1:	loopz
	&&_loop,		// E2:	loop
	&&_jcxz,		// E3:	jcxz
	&&_in_al_data8,		// E4:	in	al, DATA8
	&&_in_ax_data8,		// E5:	in	ax, DATA8
	&&_out_data8_al,	// E6:	out	DATA8, al
	&&_out_data8_ax,	// E7:	out	DATA8, ax
	&&_call_near,		// E8:	call near
	&&_jmp_near,		// E9:	jmp near
	&&_jmp_far,		// EA:	jmp far
	&&_jmp_short,		// EB:	jmp short
	&&_in_al_dx,		// EC:	in	al, dx
	&&_in_ax_dx,		// ED:	in	ax, dx
	&&_out_dx_al,		// EE:	out	dx, al
	&&_out_dx_ax,		// EF:	out	dx, ax
	&&_lock,		// F0:	lock
	&&_lock,		// F1:	lock
	&&_repne,		// F2:	repne
	&&_repe,		// F3:	repe
	&&_hlt,			// F4:	hlt
	&&_cmc,			// F5:	cmc
	&&_ope0xf6,		// F6:	
	&&_ope0xf7,		// F7:	
	&&_clc,			// F8:	clc
	&&_stc,			// F9:	stc
	&&_cli,			// FA:	cli
	&&_sti,			// FB:	sti
	&&_cld,			// FC:	cld
	&&_std,			// FD:	std
	&&_ope0xfe,		// FE:	
	&&_ope0xff,		// FF:	
};

/*---------- op 0x0f ----------*/

static void *cts0_table[] = {
        &&_sldt,
	&&_str,
	&&_lldt,
        &&_ltr,
        &&_verr,
        &&_verw,
        &&_verr,
	&&_verw
};

static void *cts1_table[] = {
        &&_sgdt,
	&&_sidt,
	&&_lgdt,
	&&_lidt,
        &&_smsw,
	&&_smsw,
	&&_lmsw,
	&&_lmsw
};


/*---------- op 0x80, 1, 2, 3 ----------*/

static void *c_op8xreg8_tbl[] = {
	&&_add_r8_i,
	&&_or_r8_i,
	&&_adc_r8_i,
	&&_sbb_r8_i,
	&&_and_r8_i,
	&&_sub_r8_i,
	&&_xor_r8_i,
	&&_cmp_r8_i
};

static void *c_op8xext8_tbl[] = {
	&&_add_ext8_i,
	&&_or_ext8_i,
	&&_adc_ext8_i,
	&&_sbb_ext8_i,
	&&_and_ext8_i,
	&&_sub_ext8_i,
	&&_xor_ext8_i,
	&&_cmp_ext8_i
};

static void *c_op8xreg16_tbl[] = {
	&&_add_r16_i,
	&&_or_r16_i,
	&&_adc_r16_i,
	&&_sbb_r16_i,
	&&_and_r16_i,
	&&_sub_r16_i,
	&&_xor_r16_i,
	&&_cmp_r16_i
};
static void  *c_op8xext16_tbl[] = {
	&&_add_ext16_i,
	&&_or_ext16_i,
	&&_adc_ext16_i,
	&&_sbb_ext16_i,
	&&_and_ext16_i,
	&&_sub_ext16_i,
	&&_xor_ext16_i,
	&&_cmp_ext16_i
};

static void *c_ope0xf6_table[] = {
	&&_test_ea8_data8,
	&&_test_ea8_data8,
	&&_not_ea8,
	&&_neg_ea8,
	&&_mul_ea8,
	&&_imul_ea8,
	&&_div_ea8,
	&&_idiv_ea8
};

static void *c_ope0xf7_table[] = {
	&&_test_ea16_data16,
	&&_test_ea16_data16,
	&&_not_ea16,
	&&_neg_ea16,
	&&_mul_ea16,
	&&_imul_ea16,
	&&_div_ea16,
	&&_idiv_ea16
};

static void *c_ope0xfe_table[] = {
	&&_inc_ea8,
	&&_dec_ea8
};

static void *c_ope0xff_table[] = {
	&&_inc_ea16,
	&&_dec_ea16,
	&&_call_ea16,
	&&_call_far_ea16,
	&&_jmp_ea16,
	&&_jmp_far_ea16,
	&&_push_ea16,
	&&_pop_ea16
};

static void *sft_r8_table[] = {
	&&_rol_r8_1,
	&&_ror_r8_1,
	&&_rcl_r8_1,
	&&_rcr_r8_1,
	&&_shl_r8_1,
	&&_shr_r8_1,
	&&_shl_r8_1,
	&&_sar_r8_1
};


static void  *sft_e8_table[] = {
	&&_rol_e8_1,
	&&_ror_e8_1,
	&&_rcl_e8_1,
	&&_rcr_e8_1,
	&&_shl_e8_1,
	&&_shr_e8_1,
	&&_shl_e8_1,
	&&_sar_e8_1
};


static void *sft_r16_table[] = {
	&&_rol_r16_1,
	&&_ror_r16_1,
	&&_rcl_r16_1,
	&&_rcr_r16_1,
	&&_shl_r16_1,
	&&_shr_r16_1,
	&&_shl_r16_1,
	&&_sar_r16_1
};

static void *sft_e16_table[] = {
	&&_rol_e16_1,
	&&_ror_e16_1,
	&&_rcl_e16_1,
	&&_rcr_e16_1,
	&&_shl_e16_1,
	&&_shr_e16_1,
	&&_shl_e16_1,
	&&_sar_e16_1
};

static void *sft_r8cl_table[] = {
        &&_rol_r8_cl,
        &&_ror_r8_cl,
        &&_rcl_r8_cl,
        &&_rcr_r8_cl,
        &&_shl_r8_cl,
        &&_shr_r8_cl,
        &&_shl_r8_cl,
        &&_sar_r8_cl
};

static void *sft_e8cl_table[] = {
        &&_rol_e8_cl,
        &&_ror_e8_cl,
        &&_rcl_e8_cl,
        &&_rcr_e8_cl,
        &&_shl_e8_cl,
        &&_shr_e8_cl,
        &&_shl_e8_cl,
        &&_sar_e8_cl
};


static void *sft_r16cl_table[] = {
        &&_rol_r16_cl,
        &&_ror_r16_cl,
        &&_rcl_r16_cl,
        &&_rcr_r16_cl,
        &&_shl_r16_cl,
        &&_shr_r16_cl,
        &&_shl_r16_cl,
        &&_sar_r16_cl
};

static void *sft_e16cl_table[] = {
        &&_rol_e16_cl,
        &&_ror_e16_cl,
        &&_rcl_e16_cl,
        &&_rcr_e16_cl,
        &&_shl_e16_cl,
        &&_shr_e16_cl,
        &&_shl_e16_cl,
        &&_sar_e16_cl
};

