li $t0, 20
addi $t2, $t0, -3
move $a0, $t2
li   $v0, 1
syscall

li $t2, 10
move $a0, $t2
li   $v0, 1
syscall

li $t2, 20
li $t3, 5
sub $t5, $t2, $t3
move $a0, $t5
li   $v0, 1
syscall

li $t6, 15
li $t2, 20
sub $t5, $t6, $t2
move $a0, $t5
li   $v0, 1
syscall

li $t2, 8
move $a0, $t2
li   $v0, 1
syscall

li $t2, -8
move $a0, $t2
li   $v0, 1
syscall

