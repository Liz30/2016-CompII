1:Caracter no reconocido: #13, 
2:Caracter no reconocido: #13, 
3:Caracter no reconocido: #13, 
4:Caracter no reconocido: #13, 
5:Caracter no reconocido: #13, 
6:Caracter no reconocido: #13, 
7:Caracter no reconocido: #13, 
8:Caracter no reconocido: #13, 
9:Caracter no reconocido: #13, 
10:Caracter no reconocido: #13, 
11:Caracter no reconocido: #13, 
	.data
var1:	 .word	23
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

