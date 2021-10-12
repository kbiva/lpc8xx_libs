lib_lpc_chip_8xx
================

LPCOpen 3.02 library for LPC8xx

My changes:
=

* mrt_8xx.h: added MRT_MODE_ONESHOT_BUS_STALL
* gpio.h: changed outMask to uint32_t in Chip_GPIO_SetPortDIRMask
* stopwatch.h: removed unnecessary #include "cmsis.h"
* cmsis.h: commented 3 unnecessary pragmas
* removed packing.h
* removed error.h
* removed core_cmInstr.h
* removed core_cmFunc.h
* removed core_cm0plus.h
