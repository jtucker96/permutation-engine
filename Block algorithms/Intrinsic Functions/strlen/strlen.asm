; __stdcall strlen 
; 
      strlen:; (str) 
             push ebp 
             mov  ebp, esp 
                cld 
                mov al,  0    ; Scan for null byte 
                mov eax, -1   ; Make the loop infinite until we hit the null byte 
                mov edi, dword[ebp+8] 
                repne scasb 
                mov eax, -2   ; If first byte is null ECX will be -2 
                sub eax, ecx 
             leave 
      ret 4 