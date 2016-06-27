	.data
a:	 .word	0
b:	 .word	0
i:	 .word	10
m:	 .word	0
str:	 .asciiz " Max: "
str1:	 .asciiz " i es menor a 10"
str2:	 .asciiz " i es mayor a 10"

	.text

whileTest:
	addi $sp, $sp, -16
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $ra, 12($sp)


	li $s0, 0

	li $s2, 30

	li $s1, 0
	# WHILE 
 while: 
	move $t5, $s0
      slti $t6, $t5, 10

	beq $t6, $zero, endwhile

	# IF 
	move $t5, $s2
	move $t7, $s1
      slt $t8, $t7, $t5

	beq $t8, $zero, else

	move $t7, $s2
	move $s1, $t7

	j endif
 else: 
 endif:

	move $t7, $s0
	addi $t8, $t7, 1

	move $s0, $t8

	j while
 endwhile: 

	# print
	la $t5, str
	move $a0, $t5
	li $v0, 4
	syscall
	move $t5, $s1
	move $a0, $t5
	li $v0, 1
	syscall

	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $ra, 12($sp)
	addi $sp, $sp, 16

main:

	li $t6, 1875578177
	sw $t6, m

Aritmetica:
	addi $sp, $sp, -8
	sw $s0, 0($sp)
	sw $ra, 4($sp)


	li $a0, 10

	li $a1, 3
	move $t6, $a0
	move $t7, $a1
	add $t8, $t6, $t7

	move $s0, $t8
	move $t6, $a0
	move $t7, $a1
 sub $t8, $t6, $t7
	move $s0, $t8

	# print
	move $t5, $a1
	move $a0, $t5
	li $v0, 1
	syscall

	lw $s0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8

ifTest:

	# IF 
      li $t7, 10
	lw $t5, i
	addi $t6, $t5, 20

      slt $t5, $t7, $t6

	beq $t5, $zero, else1


	# print
	la $t6, str1
	move $a0, $t6
	li $v0, 4
	syscall

	j endif1
 else1: 


	# print
	la $t6, str2
	move $a0, $t6
	li $v0, 4
	syscall

 endif1:


forTest:
	addi $sp, $sp, -8
	sw $s0, 0($sp)
	sw $ra, 4($sp)


	lw $s0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8

q:


	# FIN 
 li $v0, 10
 syscall

