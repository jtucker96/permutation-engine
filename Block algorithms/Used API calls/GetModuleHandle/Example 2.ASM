  push ebp
  mov ebp, esp
  sub esp, 4

  mov dword [ebp-4], 0
  call [GetModuleHandle]
  ; return value is placed in eax
  mov [m_hInstance], eax
  ; function epilogue
  mov esp, ebp
  pop ebp