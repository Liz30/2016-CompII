factorial:
	li $v0, 1
	li $t0, 2
	li $t1, 1
	for:
		bgt $t0, $a0, end_for
		mult $v0, $t0
		mflo $v0
		addi $t0, $t1, 0
		j for
	end_for:
		jr $ra 