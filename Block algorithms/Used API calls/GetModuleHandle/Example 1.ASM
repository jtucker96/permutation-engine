  push ebp
  mov ebp, esp
  sub esp, 4

  mov dword [ebp-4], 0
  stdcall [GetModuleHandle]
  ; return value is placed in eax
  lea ebx, [eax]
  mov [m_hInstance], ebx

  ; function epilogue
  mov esp, ebp
  pop ebp
