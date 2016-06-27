	.data
var1:	 .word	23
var2:	 .word	0
var3:	 .word	0

	.text

main:
	addi $sp, $sp, -12
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $ra, 8($sp)


	li $s0, 100
	li $t5, 5
	sw $t5, var2
	lw $t5, var2
	addi $t6, $t5, 2

	sw $t6, var1
	lw $t5, var1
	lw $t6, var2
	add $t7, $t5, $t6

	sw $t7, var3
	# IF 
	move $t4, $s1
	move $t5, $s1
      slt $t6, $t4, $t5

	beq $t6, $zero, else


	# print
	lw $t4, var1
	move $a0, $t4
	li $v0, 1
	syscall

	j endif
 else: 


	# print
	lw $t4, var2
	move $a0, $t4
	li $v0, 1
	syscall

 endif:

	# WHILE 
 while: 
	lw $t4, var2
	lw $t5, var1
      slt $t6, $t4, $t5

	beq $t6, $zero, endwhile


	# print
	lw $t4, var1
	move $a0, $t4
	li $v0, 1
	syscall
	lw $t5, var2
	addi $t7, $t5, 1

	sw $t7, var2

	j while
 endwhile: 

	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $ra, 8($sp)
	addi $sp, $sp, 12


	# FIN 
 li $v0, 10
 syscall

