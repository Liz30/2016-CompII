li $t1, 10
addi $t2, $t1, 2
li $t1, 5
mult $t2, $t1
mflo $t3
addi $t1, $t3, -1
move $a0, $t1
li   $v0, 1
syscall

li $t2, 10
li $t4, 2
li $t3, 5
mult $t4, $t3
mflo $t5
add $t3, $t2, $t5
addi $t2, $t3, -1
move $a0, $t2
li   $v0, 1
syscall

li $t3, 10
addi $t4, $t3, 2
li $t5, 2
div $t4, $t5
mflo $t3
li $t4, 5
mult $t3, $t4
mflo $t5
addi $t3, $t5, -1
move $a0, $t3
li   $v0, 1
syscall

li $t3, 8
move $a0, $t3
li   $v0, 1
syscall

li $t3, 2
move $a0, $t3
li   $v0, 1
syscall

li $t3, 16
move $a0, $t3
li   $v0, 1
syscall

li $t3, 10
li $t4, 8
mult $t3, $t4
mflo $t6
move $a0, $t6
li   $v0, 1
syscall

