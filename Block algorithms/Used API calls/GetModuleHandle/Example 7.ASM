  invoke GetModuleHandle, 0
  lea ecx, [eax]
  mov [m_hInstance], ecx
