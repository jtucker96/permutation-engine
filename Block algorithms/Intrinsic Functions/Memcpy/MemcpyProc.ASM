 proc memcpy, m_pDest, m_pcSource, m_uiLength
     mov esi, [m_pcSource]
     mov edi, [m_pDest]
     mov ecx, [m_uiLength]
     push ecx
     cmp ecx, 32
     jl remaindermemcpy
     greaterthanmemcpy:
     and ecx, 31
     push ecx
     pop edx
     pop ecx
     shr ecx, 5
	greaterthanloopmemcpy:
	movd mm1, [ESI + 0]
	movd mm2, [ESI + 4]
	movd mm3, [ESI + 8]
	movd mm4, [ESI + 12]
	movd mm5, [ESI + 16]
	movd mm6, [ESI + 20]
	movd mm7, [ESI + 24]
	movd mm0, [ESI + 28]
	movd [EDI + 0], mm1
	movd [EDI + 4], mm2
	movd [EDI + 8], mm3
	movd [EDI + 12], mm4
	movd [EDI + 16], mm5
	movd [EDI + 20], mm6
	movd [EDI + 24], mm7
	movd [EDI + 28], mm0
	add esi, 32
	add edi, 32
	dec ecx
	cmp ecx, 1
	jne remainderfromloopmemcpy
	cmp ecx, 0
	jne greaterthanloopmemcpy
     jmp completed
     remainderfromloopmemcpy:
     mov ecx, edx
     jmp remaindermemcpy
     remaindermemcpy:
	movsb
	dec ecx
	cmp ecx, 0
	jne remaindermemcpy
	jmp completed