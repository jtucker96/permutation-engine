In declarations as such:

import KERNEL32,\
ExitProcess, 'ExitProcess',\
GetModuleHandle, 'GetModuleHandleA'
                                           

Symbols can be changed to:

import KERNEL32,\
ExitProcess, 'ExitProcess',\
Blahblah, 'GetModuleHandleA'
                                      
Called in the program as so:

call [Blahblah]     