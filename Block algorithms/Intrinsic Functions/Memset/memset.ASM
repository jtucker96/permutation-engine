format PE CONSOLE 4.0
include 'win32ax.inc'
entry start

section '.data' readable writeable
    m_eszDestination db ?
section '.code' executable readable writeable
start:
	stdcall memset, m_eszDestination, 6 , 32
	call [ExitProcess]

   proc memset, m_pTarget, uiValue, m_uiLength
	mov esi, [uiValue]
	mov edi, [m_pTarget]
	mov ecx, [m_uiLength]

    mloop:
	mov dword [edi], esi
	inc edi
	dec ecx
	cmp ecx, 0
	jne mloop

	completed:
	ret

	endp

section '.idata' import data readable writeable
library KERNEL32,'KERNEL32.DLL',\
MSVCRT, 'MSVCRT.DLL'

import KERNEL32,\
ExitProcess, 'ExitProcess'
import MSVCRT,\
printf, 'printf'

