format PE CONSOLE 4.0
entry start
include 'win32ax.inc'
section '.data' readable writeable
message db 'Hello world'
section '.code' executable readable writeable
start:
invoke MessageBox, NULL, message, NULL,NULL
invoke ExitProcess, NULL, NULL
section '.idata' import data readable writeable
library KERNEL32,'KERNEL32.DLL',\
USER32, 'USER32.DLL'
import KERNEL32,\
ExitProcess, 'ExitProcess'
import USER32,\
MessageBox, 'MessageBoxA'
