format PE CONSOLE 4.0
include 'win32ax.inc'
entry start

section '.data' readable writeable

section '.code' executable readable writeable
start:

  push 0
  invoke ExitProcess



section '.idata' import data readable writeable
library KERNEL32,'KERNEL32.DLL',\
USER32, 'USER32.DLL',\
MSVCRT, 'MSVCRT.DLL'

import KERNEL32,\
ExitProcess, 'ExitProcess'

import USER32,\
MessageBox, 'MessageBoxA'

import MSVCRT,\
printf, 'printf',\
scanf, 'scanf'