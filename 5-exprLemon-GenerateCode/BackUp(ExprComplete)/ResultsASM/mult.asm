li $t0, 10
li $t1, 20
mult $t0, $t1
mflo $t3
move $a0, $t3
li   $v0, 1
syscall

li $t0, 10
li $t1, 3
mult $t0, $t1
mflo $t4
move $a0, $t4
li   $v0, 1
syscall

li $t1, 4
li $t0, 10
mult $t1, $t0
mflo $t5
move $a0, $t5
li   $v0, 1
syscall

li $t0, 1899
move $a0, $t0
li   $v0, 1
syscall

li $t0, 300
move $a0, $t0
li   $v0, 1
syscall

