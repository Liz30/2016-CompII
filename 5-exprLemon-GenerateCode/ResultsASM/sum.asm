li $t1, 5
move $a0, $t1
li   $v0, 1
syscall

li $t1, 10
addi $t3, $t1, 32
move $a0, $t3
li   $v0, 1
syscall

li $t1, 10
li $t3, 20
add $t5, $t1, $t3
move $a0, $t5
li   $v0, 1
syscall

li $t1, 20
addi $t5, $t1, 4
move $a0, $t5
li   $v0, 1
syscall

li $t1, 190
move $a0, $t1
li   $v0, 1
syscall

