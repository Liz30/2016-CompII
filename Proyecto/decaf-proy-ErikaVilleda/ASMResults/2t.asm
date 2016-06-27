	.data
x:	 .word	10
y:	 .word	20
z:	 .word	0

	.text

main:

	li $t1, 5
	sw $t1, z

	# print
	lw $t1, x
	addi $t2, $t1, 2

	lw $t1, z
 mult $t2, $t1
 mflo $t3

  addi $t1, $t3, -1

	move $a0, $t1
	li $v0, 1
	syscall

	# print
	lw $t1, x
 li $t4, 2
	lw $t2, z
 mult $t4, $t2
 mflo $t3

	add $t2, $t1, $t3

  addi $t1, $t2, -1

	move $a0, $t1
	li $v0, 1
	syscall

	# print
	lw $t1, x
	addi $t2, $t1, 2

  li $t3, 2
  div $t2, $t3
  mflo $t1

	lw $t2, z
 mult $t1, $t2
 mflo $t3

  addi $t1, $t3, -1

	move $a0, $t1
	li $v0, 1
	syscall

	# print
	li $t1, 8
	move $a0, $t1
	li $v0, 1
	syscall

	# print
	li $t1, 2
	move $a0, $t1
	li $v0, 1
	syscall

	# print
	li $t1, 16
	move $a0, $t1
	li $v0, 1
	syscall

	# print
	lw $t1, x
 li $t3, 8
 mult $t1, $t3
 mflo $t2

	move $a0, $t2
	li $v0, 1
	syscall

