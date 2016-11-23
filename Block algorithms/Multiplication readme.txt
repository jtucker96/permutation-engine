Multiplying - use operand mul, 

mov ah, 2
mov al, 3
mul ah
answer is : 6 stored at ax - 16 bit register

All 8-bit multiplication output is stored in 16 bit register ax, taking al and source as operands always.
IMUL A = Assuming A is a 16-bit operand, this multiplies AX by A. Stores the result to the register-pair DX:AX.
IMUL A = Assuming A is an 8-bit operand, this multiplies AL by A. Stores the result to AX. 

