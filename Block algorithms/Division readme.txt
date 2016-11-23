dividing - use operand div,

mov ax, 6
mov bl, 2
div bl	

divide ax by value in bl
result is stored in al, remainder is in ah

IDIV A = A = 32-bit operand,divides register-pair EDX:EAX by A and stores quotient to EAX. Remainder is stored to EDX.
IDIV A = A = 16-bit operand,divides register-pair DX:AX by A and stores quotient to AX. Remainder is stored to DX.
IDIV A = A = 8-bit operand,divides register AX by A and stores quotient to AL. Remainder is stored to AH.

Divide -30000 by 5:
MOV EAX,-30000  ;Store -30000 to EAX.
CDQ             ;EDX:EAX holds -30000 now.
MOV ECX,5
IDIV ECX        ;Divide -30000 by 5. Stores answer to EAX.

Scenario A
EDX = 00000000
EAX = 00030000
Therefore, EDX:EAX = 0000000000030000 = 30000

Let's say you wanted to divide 30,000 (hex) by 5 using IDIV. Just do this:
MOV EDX,0        ;The first part of EDX:EAX
MOV EAX,30000    ;Second part. Now EDX:EAX holds 30000.
MOV ECX,5
IDIV ECX         ;Divide 30000 by 5. Stores answer to EAX.


http://www.cavestory.org/guides/csasm/guide/redefine_imul_idiv.html