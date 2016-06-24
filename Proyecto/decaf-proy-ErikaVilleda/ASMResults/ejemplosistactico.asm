	.data
i:	 .word
j:	 .word
k:	 .word
b1:	 .byte
a1:	 .word
var1:	 .word	23
var2:	 .word
var3:	 .word
variable:	 .byte

	.text

main:
	addi $sp, $sp, -20
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $s3, 12($sp)
	sw $ra, 16($sp)

	li $s0, 30
	li $t2, 100
	la $t3, i
	sw $t2, 0($t3)

	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $s3, 12($sp)
	lw $ra, 16($sp)
	addi $sp, $sp, 20

max:

	li $t4, 5
	la $t5, var2
	sw $t4, 0($t5)
	lw $t6, var2
	addi $t7, $t6, 2

	la $t6, var1
	sw $t7, 0($t6)
	lw $t7, var1
	lw $t8, var2
	add $t9, $t7, $t8

	la $t7, var3
	sw $t9, 0($t7)

	# print
	lw $t7, var1
	move $a0, $t7
	li $v0, 1
	syscall
	lw $t7, var2
	move $a0, $t7
	li $v0, 1
	syscall
	lw $t7, var3
	move $a0, $t7
	li $v0, 1
	syscall

max1:
	addi $sp, $sp, -12
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $ra, 8($sp)

	li $s0, 0
	li $a1, 0
	li $a0, 30
	move $s1, $a0

	# print
	move $a0 , $s1
	#move $a0, 
	li $v0, 1
	syscall

	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $ra, 8($sp)
	addi $sp, $sp, 12

