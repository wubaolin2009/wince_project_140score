
#define CON 0x444
.text

.global _start
.global printCPSR
.global Wait

_start:
    b   RESET 			@reset handle
    b   UDEF	    
    b	SWI 
    b   PABT
    b   DABT
    b   RESERVED 
    ldr pc,=UCOS_IRQHandler
    b   FIQ


RESET:
	 @ init stack 
	@ ldr sp,=0x10000
 
	@ disable all interrupts
	mov r1, #0x4A000000
	mov r2, #0xffffffff
	str r2, [r1, #0x08]
	ldr r2, =0x7ff
	str r2, [r1, #0x1c]
	@bl disable_watch_dog      @关闭看门狗
	@bl clock_init
	@bl InitMem 

	@bl copy_2th_to_sdram               @ 将第二部分代码复制到SDRAM
	@bl create_page_table               @ 设置页表
	@bl mmu_init                        @ 启动MMU

	msr cpsr_c, #0xd2         @进入IRQ模式，IRQ和FIQ都处于禁止状态
	ldr sp, =0x31800000
	msr cpsr_c, #0xd3         @进入SVC模式，IRQ和FIQ都处于禁止状态
	ldr sp, =0x31500000	@ 把堆栈指针设置为4K处！！！
		

	
	@INTMSK
	ldr r0, =0x0
	ldr r1, =0X4A000008
	str r0,[r1]
	@INTSUBMSK
	ldr r0, =0x1ff
	ldr r1, =0X4A00001C
	str r0,[r1]

	msr cpsr_c, #0x53

	mov	fp, #0			@ 前面没有函数调用，所以把fp清零
	mov r0, #0			@ 把main函数的argc设置为0
	
	mov r1, #0			@ 把main函数的argv设置为0
	
	
	bl main				@ 跳转到C语言的main函数
halt_loop:
	mov r0,#0xf
	@b print
	
	b halt_loop
    
SWI:
	
PABT:
	
DABT:
	
RESERVED :
FIQ:
	b FIQ;
	mov r0,#0xf
	bl print
	b halt_loop
	
UDEF:
	@mov r0,lr
	@bl print
	b UDEF
label:
	b print1
	
	b halt_loop

print1:
	ldr r0,=0x50004020
	ldr r1,=0x41
	str r1,[r0]
	
	mov pc,lr
	b halt_loop
	
Wait:
	nop
	nop
	nop
	nop
	nop
	nop	
	nop
	nop
	mov pc,lr
print111:
	@mov	ip, sp
	@stmfd	sp!, {fp, ip, lr, pc}
	@sub	fp, ip, #4
	@ldmfd	sp, {fp, sp, pc}
	b label
	


