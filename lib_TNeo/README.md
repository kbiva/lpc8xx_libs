lib_TNeo
================

TNeo: a well-formed and carefully tested preemptive real-time kernel for 16- and 32-bits MCUs

https://github.com/dimonomid/tneo

Version 1.08

My changes:
=
* tn_arch_detect.h: Added "&& (__ARMCC_VERSION < 6000000)", because armclang also defines __ARMCC_VERSION
* removed --cpreproc from project asm options
* preprocessed tn_arch_cortex_m.S: 
```
armclang.exe --target=arm-arm-none-eabi -mcpu=cortex-m0plus -E -undef tn_arch_cortex_m.S -D __GNUC__ -D __ARM_ARCH -D __ARM_ARCH_6M__ -I ../.. -I ../../core > tn_arch_cortex_m0plus_gcc.s
```
