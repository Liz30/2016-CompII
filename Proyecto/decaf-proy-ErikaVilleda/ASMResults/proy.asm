
	.data
var1:	 .word	23
var2:	 .word
var3:	 .word

	.text
main:
	addi $sp, $sp, -8
	sw $s0, 0($sp)
	sw $ra, 4($sp)

	li $s0, 100
	li $t2, 5
	sw $t2, var2
	lw $t3, var2
	addi $t4, $t3, 2
	sw $t4, var1
	lw $t5, var1
	lw $t6, var2
	add $t7, $t5, $t6
	sw $t7, var3

	# print
	lw $t5, var1
	move $a0, $t5
	li $v0, 1
	syscall

	# print
	lw $t5, var2
	move $a0, $t5
	li $v0, 1
	syscall

	# print
	lw $t5, var3
	move $a0, $t5
	li $v0, 1
	syscall

	# print
	move $t5, $s0
	move $a0, $t5
	li $v0, 1
	syscall

	lw $s0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8

