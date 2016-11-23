  invoke GetModuleHandle, 0
  lea edx, [eax]
  mov [m_hInstance], edx