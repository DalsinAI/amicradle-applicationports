/* Included before every C++ file of OpenCPN on AmigaOS 3 (-include).
 * Some OpenCPN headers include <sys/socket.h> before wx's, and libnix's
 * pulls in exec/lists.h, whose IsListEmpty() macro then breaks wx's
 * wxComboBox::IsListEmpty(). Taking exec/lists.h first and dropping the
 * macro keeps the two apart; OpenCPN never uses the exec macro.
 * Copyright (c) 2026 AmiCradle Team */
#if defined(__AMIGAOS3__) && defined(__cplusplus)
#include <exec/lists.h>
#undef IsListEmpty
#endif
