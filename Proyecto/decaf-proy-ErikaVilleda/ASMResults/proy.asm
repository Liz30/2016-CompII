	.datavar1:	 .word	23
var2:	 .word
var3:	 .word

	.text
main:

	li $t1, 5
	sw $t1, var2
	lw $t2, var2
	addi $t3, $t2, 2
	sw $t3, var1
	lw $t5, var1

	lw $t6, var2

	add $t7, $t5, $t6
	sw $t7, var3
