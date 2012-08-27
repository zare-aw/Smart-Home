;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Modified version of IARs cstartup.asm
;;
;; $Revision: 14946 $
;;

        MODULE  ?cstartup

        ;; Forward declaration of sections used here.
        SECTION IRQ_STACK:DATA:NOROOT(3)
        SECTION FIQ_STACK:DATA:NOROOT(3)
        SECTION UND_STACK:DATA:NOROOT(3)
        SECTION ABT_STACK:DATA:NOROOT(3)
        SECTION CSTACK:DATA:NOROOT(3)

;
; The module in this file are included in the libraries, and may be
; replaced by any user-defined modules that define the PUBLIC symbol
; __iar_program_start or a user defined start symbol.
;
; To override the cstartup defined in the library, simply add your
; modified version to the workbench project.

        SECTION .intvec:CODE:NOROOT(2)

        PUBLIC  __vector
        PUBLIC  __vector_0x14
        PUBLIC  __iar_program_start
        PUBLIC  __undefined_instructions
        PUBLIC  __software_interrupt
        PUBLIC  __prefetch_abort
        PUBLIC  __data_abort
        EXTERN IRQ_ISR_Handler
        EXTERN Undefined_Instructions_Handler
        EXTERN Software_Interrupt_Handler
        EXTERN Prefetch_Abort_Handler
        EXTERN Data_Abort_Handler

        ARM
__vector:
        ldr   pc,=__iar_program_start         ;; Reset
        ldr   pc,=__undefined_instructions    ;; Undefined instructions
        ldr   pc,=__software_interrupt        ;; Software interrupt (SWI/SVC)
        ldr   pc,=__prefetch_abort            ;; Prefetch abort
        ldr   pc,=__data_abort                ;; Data abort
__vector_0x14:
        DC32  0                         ;; RESERVED
        ldr     pc, [pc, #-0xFF0]       ;; IRQ Handler (reads vector address from VicVecAddr)
        B   .                           ;; FIQ
        ltorg                           ;; Instruct Assembler to generate literal pool here for values used in instructions at the beginning

        SECTION .text:CODE:NOROOT(2)

        EXTERN  ?main
        REQUIRE __vector
        ARM
        
__undefined_instructions:
        sub     r0, lr, #8              ;; Address of latest instruntion
        ldr     r1, [r0]                ;; Instruction
        ldr     r2,=Undefined_Instructions_Handler
        bx      r2
__software_interrupt:
        sub     r0, lr, #8              ;; Address of latest instruntion
        ldr     r1, [r0]                ;; Instruction
        ldr     r2,=Software_Interrupt_Handler
        bx      r2
__prefetch_abort:
        sub     r0, lr, #8              ;; Address of latest instruntion
        ldr     r2,=Prefetch_Abort_Handler
        bx      r2
__data_abort:
        sub     r0, lr, #8              ;; Address of latest instruntion
        ldr     r1, [r0]                ;; Instruction
        ldr     r2,=Data_Abort_Handler
        bx      r2

__iar_program_start:

;
; Add initialization needed before setup of stackpointers here.
;
; LPC2148 Errata
; Date: August 5, 2005
; Document Release: Version 1.0
; Device Affected: LPC2148
; Incorrect read of data from SRAM after Reset and MAM is not enabled or partially enabled MAM.1
; Init MAM before acsses to SRAM
MAMCR    DEFINE 0xE01FC000      ; MAM Control Register
MAMTIM   DEFINE 0xE01FC004      ; MAM Timing register

                ldr   r0,=MAMCR
                ldr   r1,=MAMTIM
                ldr   r2,=0
                str   r2,[r0]
                ldr   r2,=7
                str   r2,[r1]
                ldr   r2,=2
                str   r2,[r0]

; Enable USB peripherial to be able to use USB SRAM
; Default value in PCONP is 0x001817BE, we are enabling MSB (add 0x80000000) for USB peripherial
; We need to enable USB SRAM before initialize it after executing startup file (this file)
PCONP       DEFINE  0xE01FC0C4      ; PCONP - Power control register
PCONP_VAL   DEFINE  0x801817BE      ; Initial value for PCONP

                ldr r0, =PCONP
                ldr r1, =PCONP_VAL
                str r1, [r0]

;
; Initialize the stack pointers.
; The pattern below can be used for any of the exception stacks:
; FIQ, IRQ, SVC, ABT, UND, SYS.
; The USR mode uses the same stack as SYS.
; The stack segments must be defined in the linker command file,
; and be declared above.
;
; --------------------
; Mode, correspords to bits 0-5 in CPSR

MODE_MSK DEFINE 0x1F            ; Bit mask for mode bits in CPSR

USR_MODE DEFINE 0x10            ; User mode
FIQ_MODE DEFINE 0x11            ; Fast Interrupt Request mode
IRQ_MODE DEFINE 0x12            ; Interrupt Request mode
SVC_MODE DEFINE 0x13            ; Supervisor mode
ABT_MODE DEFINE 0x17            ; Abort mode
UND_MODE DEFINE 0x1B            ; Undefined Instruction mode
SYS_MODE DEFINE 0x1F            ; System mode

; Initialize the stack pointers.
; Stack pointers are initialized only for modes that are used in this program.

                mrs     r0,cpsr                             ; Original PSR value
                bic     r0,r0,#MODE_MSK                     ; Clear the mode bits
                orr     r0,r0,#IRQ_MODE                     ; Set IRQ mode bits
                msr     cpsr_c,r0                           ; Change the mode
                ldr     sp,=SFE(IRQ_STACK)                  ; End of IRQ_STACK
                
                mrs     r0,cpsr                             ; Original PSR value
                bic     r0,r0,#MODE_MSK                     ; Clear the mode bits
                orr     r0,r0,#UND_MODE                     ; Set ABT mode bits
                msr     cpsr_c,r0                           ; Change the mode
                ldr     sp,=SFE(ABT_STACK)                  ; End of ABT_STACK
                
                mrs     r0,cpsr                             ; Original PSR value
                bic     r0,r0,#MODE_MSK                     ; Clear the mode bits
                orr     r0,r0,#ABT_MODE                     ; Set ABT mode bits
                msr     cpsr_c,r0                           ; Change the mode
                ldr     sp,=SFE(UND_STACK)                  ; End of UND_STACK

                bic     r0,r0,#MODE_MSK                     ; Clear the mode bits
                orr     r0,r0,#SYS_MODE                     ; Set System mode bits
                msr     cpsr_c,r0                           ; Change the mode
                ldr     sp,=SFE(CSTACK)                     ; End of CSTACK

; Continue to ?main for more IAR specific system startup

                ldr     r0,=?main                           ; Call IAR library that initializes
                                                            ; C directives
                bx      r0                                  ; After directieves are initialized
                                                            ; library function will call
                                                            ; user main() function.

        END

