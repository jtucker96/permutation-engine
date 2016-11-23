format PE CONSOLE 4.0
include 'win32ax.inc'
entry start

section '.data' readable writeable
     m_eszSource db 'String to be copied to dest!ascxzdcvfg12242rasdkjasfvkajvakscnasjcsdkfjhdfcdcsjkchaasf'
     m_eszDestination db ?
section '.code' executable readable writeable
start:

     stdcall memcpy, m_eszDestination, m_eszSource, 86 ; 4 remainder

     invoke ExitProcess, 0

     proc memcpy, m_pDest, m_pcSource, m_uiLength
     mov esi, [m_pcSource]
     mov edi, [m_pDest]
     mov ecx, [m_uiLength]
     push ecx
     cmp ecx, 32 ; compare this number with 32
     jl remainder

     greaterthan: ; greater than 32 loop
     and ecx, 31
     push ecx
     pop edx ; remainder in edx
     pop ecx ;restore original ecx
     shr ecx, 5   ; 32 blocks
	greaterthanloop:

	movd mm1, [ESI + 0] ; Read in source data
	movd mm2, [ESI + 4]
	movd mm3, [ESI + 8]
	movd mm4, [ESI + 12]
	movd mm5, [ESI + 16]
	movd mm6, [ESI + 20]
	movd mm7, [ESI + 24]
	movd mm0, [ESI + 28]

	movd [EDI + 0], mm1 ; Write to destination
	movd [EDI + 4], mm2
	movd [EDI + 8], mm3
	movd [EDI + 12], mm4
	movd [EDI + 16], mm5
	movd [EDI + 20], mm6
	movd [EDI + 24], mm7
	movd [EDI + 28], mm0
	; loop epilogue
	add esi, 32
	add edi, 32

	dec ecx
	cmp ecx, 1
	jne remainderfromloop
	cmp ecx, 0
	jne greaterthanloop ; when ecx is not zero

     jmp completed


     remainderfromloop:

     mov ecx, edx   ; move the remainder value to ecx
     jmp remainder  ; ecx is rounds to complete

     remainder:
	movsb
	dec ecx
	cmp ecx, 0
	jne remainder

	completed:
	ret

	endp


section '.idata' import data readable writeable
library KERNEL32,'KERNEL32.DLL'

import KERNEL32,\
ExitProcess, 'ExitProcess'
