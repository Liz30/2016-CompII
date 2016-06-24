	.data
var1:	 .word	23
var2:	 .word	0
var3:	 .word	0

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
	lw $t4, var1
	lw $t5, var2
	add $t6, $t4, $t5

	sw $t6, var3

	# print
	lw $t4, var1
	move $a0, $t4
	li $v0, 1
	syscall

	# print
	lw $t4, var2
	move $a0, $t4
	li $v0, 1
	syscall

	# print
	lw $t4, var3
	move $a0, $t4
	li $v0, 1
	syscall

	# print
	move $t4, $s0
	move $a0, $t4
	li $v0, 1
	syscall

	# print
	move $t4, $s0
  addi $t5, $t4, -10

	move $a0, $t5
	li $v0, 1
	syscall

	# print
	move $t4, $s0
	lw $t5, var1
 sub $t6, $t4, $t5
	move $a0, $t6
	li $v0, 1
	syscall

	lw $s0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8

