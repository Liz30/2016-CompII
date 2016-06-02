li $t4, 10
addi $t3, $t4, 2
li $t2, 5
mult $t3, $t2
mflo $t1
addi $t0, $t1, -1
move $a0, $t0
li   $v0, 1
syscall

li $t4, 10
li $t5, 2
li $t4, 5
mult $t5, $t4
mflo $t3
add $t2, $t4, $t3
addi $t1, $t2, -1
move $a0, $t1
li   $v0, 1
syscall

li $t8, 10
addi $t7, $t8, 2
li $t6, 2
div $t7, $t6
mflo $t5
li $t4, 5
mult $t5, $t4
mflo $t3
addi $t2, $t3, -1
move $a0, $t2
li   $v0, 1
syscall

# Exit
li $v0, 10
syscall
