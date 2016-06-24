
	.text

swap:
	addi $sp, $sp, -8
	sw $s0, 0($sp)
	sw $ra, 4($sp)

	move $s0, $t1
	move $a0, $t3
	move $a1, $t5

	lw $s0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8

SelectionSort:
	addi $sp, $sp, -16
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $ra, 12($sp)


	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $ra, 12($sp)
	addi $sp, $sp, 16

