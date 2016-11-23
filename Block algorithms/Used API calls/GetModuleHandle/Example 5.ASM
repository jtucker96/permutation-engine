  invoke GetModuleHandle, 0
  lea ebx, [eax]
  mov [m_hInstance], ebx