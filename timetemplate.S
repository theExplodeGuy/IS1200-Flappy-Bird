# timetemplate.S
# Written 2015 by F Lundevall
# Ported 2024/06 by W Szczerek (from MIPS to RISC-V)
# Copyright abandonded - this file is in the public domain.

#############################################################
# Choose the macro syntax for RARS or DTEK-V board.         #
# The syntax for RARS is probably due to its MIPS heritage. #
#############################################################
###################
# Macros for RARS #
###################
#.macro	PUSH (%reg)
#	addi	sp,sp,-4
#	sw	%reg,0(sp) 
#.end_macro

#.macro	POP (%reg)
#	lw	%reg,0(sp)
#	addi	sp,sp,4
#.end_macro
###################
# Macros for DTEK #
###################
.macro	PUSH reg
	addi sp,sp,-4
	sw \reg,0(sp) 
.endm

.macro	POP reg
	lw	\reg,0(sp)
	addi	sp,sp,4
.endm
#############################################################
.global display_string
.global time2string
.global delay
.global time2seg

	.data
	.align 2
mytime:	.word 	0x1653
timstr:	.asciz 	"12345\0"
	.text
	.globl timetemplate, tick, time2string

# Function for displaying a string with a newline at the end	
display_string:	
	li a7,4
	ecall
	li a0, 10
	li a7,11
	ecall
	jr ra
	
timetemplate:
	la	a0, timstr
	jal     display_string
	
	
	# wait a little
	li	a0, 1000		# ms
	jal	delay
	
	# call tick
	la 	a0, mytime
	jal	tick
	
	# call your function time2string
	la	a0, timstr
	la	t0, mytime
	lw	a1, 0(t0)
	jal	time2string

	la	t0, mytime
	lw	a1, 0(t0)
	jal	time2seg
	
	# go back and do it all again
	j	timetemplate

	
# tick: update time pointed to by $a0
tick:	lw	t0, 0(a0)	# get time
	addi	t0, t0, 1	# increase
	andi	t1, t0, 0xf	# check lowest digit
	sltiu	t2, t1, 0xa	# if digit < a, okay
	bnez	t2, tiend
	addi	t0, t0, 0x6	# adjust lowest digit
	
	andi	t1, t0, 0xf0	# check next digit
	sltiu	t2, t1, 0x60	# if digit < 6, okay
	bnez	t2, tiend
	addi	t0, t0, 0xa0	# adjust digit
	
	li	t3, 0xF
	slli	t3, t3, 0x8
	and	t1, t0, t3	# check minute digit
	addi	t3, x0, 0xA
	slli	t3, t3, 0x8
	slt	t2, t1, t3	# if digit < a, okay
	bnez	t2, tiend
	addi	t0, t0, 0x600	# adjust digit - this one's okay, it's lower than 0x7FF 
	
	li	t3, 0xF
	slli	t3, t3, 0xC
	and	t1, t0, t3	# check last digit
	addi	t3, x0, 0x6
	slli	t3, t3, 0xC
	slt	t2, t1, t3	# if digit < 6, okay
	bnez	t2, tiend
	
	li	t3, 0xA
	slli	t3, t3, 0xC
	add	t0, t0, t3	# adjust last digit
tiend:	sw	t0,0(a0)	# save updated result
	jr	ra		# return

#########################################################
# Place for your functions: time2string, hex2asc, delay.#
#########################################################

hexasc:
	PUSH ra
	
	
	andi t0, a0, 15
	addi t1, zero, 10
	bge t0, t1, letters
	
	addi a0, t0, 0x30
	
	#return
	POP ra
	jr ra
	
	letters:
	addi a0, t0, 55
	
	POP ra
	jr ra

delay:
    # a0 = number of ms to delay
    li t1, 10000         # inner loop count for ~1 ms (approx)
outer:
    ble a0, zero, done
    addi a0, a0, -1
    li t2, 0
inner:
    bge t2, t1, inner_done
    addi t2, t2, 1
    j inner
inner_done:
    j outer
done:
    jr ra


time2string:
	PUSH ra
	PUSH s0 # a0 = address to write
	PUSH s1 # a1 = time to convert to string
	PUSH s2 # counter for loop
	
	add s0, zero, a0
	add s1, zero, a1 
	
	addi s0, s0, 4	# to store them in reverse
	
	addi s2, zero, 2
	for1:
		andi a0, s1, 0xf
		jal hexasc
		sb a0, 0(s0)
		addi s0, s0, -1
		srli s1, s1, 4
		addi s2, s2, -1
	bnez s2, for1
	
	addi t0, zero, 0x3A
	sb t0, 0(s0)
	addi s0, s0, -1
	
	addi s2, zero, 2
	for2:
		andi a0, s1, 0xf
		jal hexasc
		sb a0, 0(s0)
		addi s0, s0, -1
		srli s1, s1, 4
		addi s2, s2, -1
	bnez s2, for2
	
	addi t0, zero, 0x00
	sb t0, 0(s0)

	POP s2
	POP s1
	POP s0
	POP ra
	jr ra
	

time2seg:
	
	PUSH ra
	PUSH s0 # a0 = address to write
	PUSH s1 # a1 = time to convert to string
	PUSH s2 # counter for loop
	PUSH s3 #to turn off extra displays
	
	li s0, 0x04000050
	add s1, zero, a1 
	addi s2, zero, 4
	
	li s3, 0x04000090
	li t5, 0xffff
	sw t5, 0(s3)
	sw t5, 16(s3)
	

	loop:
		andi t1, s1, 0xf

		beq t1, zero, s_zero

		addi t0, zero, 1
		beq t1, t0, s_one

		addi t0, zero, 2
		beq t1, t0, s_two

		addi t0, zero, 3
		beq t1, t0, s_three

		addi t0, zero, 4
		beq t1, t0, s_four

		addi t0, zero, 5
		beq t1, t0, s_five

		addi t0, zero, 6
		beq t1, t0, s_six

		addi t0, zero, 7
		beq t1, t0, s_seven

		addi t0, zero, 8
		beq t1, t0, s_eight

		addi t0, zero, 9
		beq t1, t0, s_nine

		s_zero:
		addi t2, zero, 0xc0
		j next		

		s_one:
		addi t2, zero, 0xf9
		j next	

		s_two:
		addi t2, zero, 0x124
		j next	

		s_three:
		addi t2, zero, 0xb0
		j next

		s_four:
		addi t2, zero, 0x99
		j next		

		s_five:
		addi t2, zero, 0x92
		j next	

		s_six:
		addi t2, zero, 0x82
		j next	

		s_seven:
		addi t2, zero, 0xf8
		j next	

		s_eight:
		addi t2, zero, 0x80
		j next	

		s_nine:
		addi t2, zero, 0x90
		j next	
		
		next:
			addi t3, zero, 2
			addi t4, zero, 0x7f
			beq s2, t3, dotadder
			j nextcontinue
			
			dotadder:
			and t2, t2, t4
			
			nextcontinue:
			sb t2, 0(s0)
			addi s0, s0, 16
			srli s1, s1, 4
			addi s2, s2, -1
			
			
	bnez s2, loop
	
	POP s3
	POP s2
	POP s1
	POP s0
	POP ra
	jr ra
