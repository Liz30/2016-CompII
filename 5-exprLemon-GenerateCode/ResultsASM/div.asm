li $t0, 20
li $t1, 10
div $t0, $t1
mflo $t3
move $a0, $t3
li   $v0, 1
syscall

li $t0, 10
li $t4, 5
div $t0, $t4
mflo $t3
move $a0, $t3
li   $v0, 1
syscall

li $t5, 4
li $t0, 20
div $t5, $t0
mflo $t4
move $a0, $t4
li   $v0, 1
syscall

li $t0, 6
move $a0, $t0
li   $v0, 1
syscall

