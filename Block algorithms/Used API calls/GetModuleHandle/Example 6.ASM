  push 0
  call [GetModuleHandle]
  mov ebx, [eax]
  mov [m_hInstance], ebx