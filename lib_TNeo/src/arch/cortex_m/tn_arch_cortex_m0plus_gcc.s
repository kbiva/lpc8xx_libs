# 1 "tn_arch_cortex_m.S"
# 1 "<built-in>" 1
# 1 "tn_arch_cortex_m.S" 2
# 84 "tn_arch_cortex_m.S"
# 1 "./../tn_arch_detect.h" 1
# 85 "tn_arch_cortex_m.S" 2
# 1 "../../core\\tn_cfg_dispatch.h" 1
# 70 "../../core\\tn_cfg_dispatch.h"
# 1 "../..\\tn_cfg.h" 1
# 71 "../../core\\tn_cfg_dispatch.h" 2
# 82 "../../core\\tn_cfg_dispatch.h"
# 1 "../..\\tn_cfg_default.h" 1
# 83 "../../core\\tn_cfg_dispatch.h" 2
# 86 "tn_arch_cortex_m.S" 2
# 195 "tn_arch_cortex_m.S"
   .text
   .syntax unified
   .thumb
# 216 "tn_arch_cortex_m.S"
   .extern _tn_curr_run_task
   .extern _tn_next_task_to_run

   .extern _tn_sys_on_context_switch
# 232 "tn_arch_cortex_m.S"
   .global PendSV_Handler
   .global SVC_Handler
   .global _tn_arch_sys_start
   .global _tn_arch_context_switch_now_nosave
   .global tn_arch_int_dis
   .global tn_arch_int_en

   .global tn_arch_sr_save_int_dis
   .global tn_arch_sr_restore
   .global _tn_arch_is_int_disabled
   .global _tn_arch_inside_isr
   .global _tn_arch_context_switch_pend
   .global tn_arch_sched_dis_save
   .global tn_arch_sched_restore
# 254 "tn_arch_cortex_m.S"
.equ ICSR_ADDR, 0xE000ED04


.equ PENDSVSET, 0x10000000


.equ PR_08_11_ADDR, 0xE000ED1C


.equ PR_12_15_ADDR, 0xE000ED20



.equ PENDS_VPRIORITY, 0x00FF0000



.equ SVC_VPRIORITY, 0xFF000000



.equ FPU_FPCCR_ADDR, 0xE000EF34
.equ FPU_FPCCR_LSPEN, 0xBFFFFFFF
# 299 "tn_arch_cortex_m.S"
.thumb_func
PendSV_Handler:



      push {lr}


      cpsid i



      mrs r2, PSP
# 328 "tn_arch_cortex_m.S"
      subs r2, #32
      stmia r2!, {r4-r7}
      mov r4, r8
      mov r5, r9
      mov r6, r10
      mov r7, r11
      stmia r2!, {r4-r7}
      subs r2, #32





      ldr r5, =_tn_curr_run_task
      ldr r6, =_tn_next_task_to_run
      ldr r0, [r5]
      ldr r1, [r6]
      str r2, [r0]
# 354 "tn_arch_cortex_m.S"
      bl _tn_sys_on_context_switch



      ldr r4, [r6]
      str r4, [r5]



L__context_restore:


      ldr r0, [r4]





      adds r0, #16
      ldmia r0!, {r4-r7}
      mov r8, r4
      mov r9, r5
      mov r10, r6
      mov r11, r7
      subs r0, #32
      ldmia r0!, {r4-r7}
      adds r0, #16
# 395 "tn_arch_cortex_m.S"
      msr PSP, r0

      cpsie i



      pop {r0}
      mov lr, r0


      bx lr


.thumb_func
_tn_arch_sys_start:
# 419 "tn_arch_cortex_m.S"
      mrs r2, MSP
      msr PSP, r2



      mrs r2, CONTROL
      movs r3, #0x02

      orrs r2, r2, r3
      msr CONTROL, r2


      isb




      movs r2, #4
      muls r1, r2, r1
      adds r0, r0, r1
      msr MSP, r0


      ldr r1, =PR_12_15_ADDR
      ldr r0, [r1]
      ldr r2, =PENDS_VPRIORITY
      orrs r0, r0, r2
      str r0, [r1]


      ldr r1, =PR_08_11_ADDR
      ldr r0, [r1]
      ldr r2, =SVC_VPRIORITY
      orrs r0, r0, r2
      str r0, [r1]
# 469 "tn_arch_cortex_m.S"
.thumb_func
_tn_arch_context_switch_now_nosave:




      cpsie i


      svc #0x00



.thumb_func
SVC_Handler:






      push {lr}


      cpsid i

      ldr r5, =_tn_curr_run_task
      ldr r6, =_tn_next_task_to_run
      ldr r0, [r5]
      ldr r1, [r6]







      bl _tn_sys_on_context_switch


      ldr r4, [r6]
      str r4, [r5]




      b L__context_restore



.thumb_func
tn_arch_int_dis:

      cpsid i
      bx lr



.thumb_func
tn_arch_int_en:

      cpsie i
      bx lr


.thumb_func
tn_arch_sr_save_int_dis:

      mrs r0, PRIMASK
      cpsid i
      bx lr


.thumb_func
tn_arch_sr_restore:

      msr PRIMASK, r0
      bx lr


.thumb_func
_tn_arch_is_int_disabled:

      mrs r0, PRIMASK
      bx lr


.thumb_func
_tn_arch_inside_isr:

      mrs r0, CONTROL
# 570 "tn_arch_cortex_m.S"
      movs r1, #0x02
      tst r0, r1
      bne L__ne
      movs r0, #1
      bx lr
L__ne:
      movs r0, #0
      bx lr



.thumb_func
_tn_arch_context_switch_pend:

      ldr r1, =ICSR_ADDR
      ldr r0, =PENDSVSET
      str r0, [r1]

      bx lr
# 602 "tn_arch_cortex_m.S"
.thumb_func
tn_arch_sched_dis_save:
# 633 "tn_arch_cortex_m.S"
      b tn_arch_sr_save_int_dis


.thumb_func
tn_arch_sched_restore:
# 647 "tn_arch_cortex_m.S"
      b tn_arch_sr_restore
