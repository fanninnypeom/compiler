.data
_a:.word 1
b:.word -1
ch1:.word 45
ch2:.word 110
enter:.word 0
.text
addi $fp,$sp,0
j main
testchildexpression:
sw $ra,4($sp)
addi $sp,$sp,-72
li $t0,0
li $t1,10
addi $t2,$fp,-20
sub $t0,$t0,$t1
sw $t0,0($t2)
li $t0,10
addi $t1,$fp,-24
sw $t0,0($t1)
li $t0,0
li $t1,10
addi $t2,$fp,-28
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-28
lw $t0,0($t0)
addi $t1,$fp,-8
sw $t0,0($t1)
li $t0,0
li $t1,10
addi $t2,$fp,-32
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-32
lw $t0,0($t0)
addi $t1,$fp,-0
sw $t0,0($t1)
addi $t0,$fp,-32
lw $t0,0($t0)
addi $t1,$fp,-28
lw $t1,0($t1)
addi $t2,$fp,-36
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-36
lw $t0,0($t0)
addi $t1,$fp,-4
sw $t0,0($t1)
addi $t0,$fp,-36
lw $t0,0($t0)
addi $t1,$fp,-8
sw $t0,0($t1)
addi $t0,$fp,-32
lw $t0,0($t0)
addi $t1,$fp,-36
lw $t1,0($t1)
addi $t2,$fp,-40
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-40
lw $t0,0($t0)
addi $t1,$fp,-36
lw $t1,0($t1)
addi $t2,$fp,-44
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-44
lw $t0,0($t0)
addi $t1,$fp,-12
sw $t0,0($t1)
addi $t0,$fp,-44
lw $t0,0($t0)
addi $t1,$fp,-16
sw $t0,0($t1)
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
addi $t0,$fp,-12
lw $t0,0($t0)
addi $t1,$fp,-16
lw $t1,0($t1)
addi $t2,$fp,-48
add $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-48
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,1
syscall
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
manyparameter:
sw $ra,4($sp)
addi $sp,$sp,-92
addi $t0,$fp,-0
lw $t0,0($t0)
addi $t1,$fp,-4
lw $t1,0($t1)
addi $t2,$fp,-32
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
li $t0,0
li $t1,3
addi $t2,$fp,-36
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-36
lw $t0,0($t0)
addi $t1,$fp,-32
lw $t1,0($t1)
addi $t2,$fp,-40
add $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-40
lw $t0,0($t0)
addi $t1,$fp,-28
sw $t0,0($t1)
li $t0,7
addi $t1,$fp,-40
lw $t1,0($t1)
addi $t2,$fp,-44
add $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-44
lw $t0,0($t0)
addi $t1,$fp,-28
sw $t0,0($t1)
li $t0,0
li $t1,0
addi $t2,$fp,-48
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $a0,$zero,77
li $v0,11
syscall
addi $a0,$zero,80
li $v0,11
syscall
addi $a0,$zero,86
li $v0,11
syscall
addi $a0,$zero,97
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,58
li $v0,11
syscall
addi $a0,$zero,32
li $v0,11
syscall
addi $t0,$fp,-28
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,1
syscall
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
addi $t0,$fp,-20
lw $t0,0($t0)
addi $t1,$fp,-24
lw $t1,0($t1)
addi $t2,$fp,-52
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-0
lw $t0,0($t0)
addi $t1,$fp,-4
lw $t1,0($t1)
addi $t2,$fp,-56
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-56
lw $t0,0($t0)
addi $t1,$fp,-8
lw $t1,0($t1)
addi $t2,$fp,-60
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-60
lw $t0,0($t0)
addi $t1,$fp,-12
lw $t1,0($t1)
addi $t2,$fp,-64
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-64
lw $t0,0($t0)
addi $t1,$fp,-16
lw $t1,0($t1)
addi $t2,$fp,-68
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-68
lw $t0,0($t0)
addi $t1,$fp,-52
lw $t1,0($t1)
addi $t2,$fp,-72
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-28
lw $t0,0($t0)
addi $t1,$fp,-72
lw $t1,0($t1)
addi $t2,$fp,-76
add $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-76
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,1
syscall
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
testcompare:
sw $ra,4($sp)
addi $sp,$sp,-56
li $t0,1
addi $t1,$fp,-4
sw $t0,0($t1)
li $t0,1
addi $s0,$t0,0
addi $t1,$fp,-4
lw $t1,0($t1)
sub $t2,$s0,$t1
bltz $t2,label0
li $t1,2
addi $t2,$fp,-8
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-8
lw $t0,0($t0)
addi $s0,$t0,0
j label1
label0:
label1:
li $t0,3
addi $t1,$fp,-12
sw $t0,0($t1)
addi $t1,$fp,-12
lw $t1,0($t1)
sub $t2,$s0,$t1
bgez $t2,label2
li $t1,3
addi $t2,$fp,-16
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-16
lw $t0,0($t0)
addi $s0,$t0,0
j label3
label2:
label3:
li $t0,3
addi $t1,$fp,-20
sw $t0,0($t1)
addi $t1,$fp,-20
lw $t1,0($t1)
sub $t2,$s0,$t1
bltz $t2,label4
li $t1,4
addi $t2,$fp,-24
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-24
lw $t0,0($t0)
addi $s0,$t0,0
j label5
label4:
label5:
li $t0,7
addi $t1,$fp,-28
sw $t0,0($t1)
addi $t1,$fp,-28
lw $t1,0($t1)
sub $t2,$s0,$t1
bgez $t2,label6
li $t1,4
addi $t2,$fp,-32
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-32
lw $t0,0($t0)
addi $s0,$t0,0
j label7
label6:
label7:
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,67
li $v0,11
syscall
addi $a0,$zero,111
li $v0,11
syscall
addi $a0,$zero,109
li $v0,11
syscall
addi $a0,$zero,112
li $v0,11
syscall
addi $a0,$zero,97
li $v0,11
syscall
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,58
li $v0,11
syscall
addi $a0,$zero,32
li $v0,11
syscall
add $a0,$zero,$s0
li $v0,1
syscall
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
testswitch:
sw $ra,4($sp)
addi $sp,$sp,-96
li $t0,48
addi $s0,$t0,0
addi $t1,$zero,48
bne $s0,$t1,label9
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,49
li $v0,11
syscall
j label8
label9:
addi $t1,$zero,0
bne $s0,$t1,label10
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,50
li $v0,11
syscall
j label8
label10:
addi $a0,$zero,100
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,102
li $v0,11
syscall
addi $a0,$zero,97
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,49
li $v0,11
syscall
label8:
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
li $t0,0
li $t1,48
addi $t2,$fp,-4
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-4
lw $t0,0($t0)
addi $s0,$t0,0
addi $t1,$zero,-48
bne $s0,$t1,label12
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,51
li $v0,11
syscall
j label11
label12:
addi $t1,$zero,48
bne $s0,$t1,label13
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,52
li $v0,11
syscall
j label11
label13:
addi $a0,$zero,100
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,102
li $v0,11
syscall
addi $a0,$zero,97
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,50
li $v0,11
syscall
label11:
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
li $t0,4
addi $t1,$fp,-8
sw $t0,0($t1)
li $t0,19
addi $t1,$fp,-12
sw $t0,0($t1)
li $t1,96
addi $t2,$fp,-16
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-16
lw $t0,0($t0)
li $t1,4
addi $t2,$fp,-20
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-20
lw $t0,0($t0)
li $t1,4
addi $t2,$fp,-24
div $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-24
lw $t0,0($t0)
li $t1,19
addi $t2,$fp,-28
add $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-28
lw $t0,0($t0)
li $t1,19
addi $t2,$fp,-32
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-32
lw $t0,0($t0)
addi $t1,$zero,48
bne $t0,$t1,label15
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,53
li $v0,11
syscall
j label14
label15:
addi $t0,$fp,-32
lw $t0,0($t0)
addi $t1,$zero,48
bne $t0,$t1,label16
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,54
li $v0,11
syscall
j label14
label16:
addi $a0,$zero,100
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,102
li $v0,11
syscall
addi $a0,$zero,97
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,51
li $v0,11
syscall
label14:
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
li $t0,4
addi $t1,$fp,-36
sw $t0,0($t1)
li $t0,19
addi $t1,$fp,-40
sw $t0,0($t1)
li $t1,96
addi $t2,$fp,-44
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-44
lw $t0,0($t0)
li $t1,4
addi $t2,$fp,-48
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-48
lw $t0,0($t0)
li $t1,4
addi $t2,$fp,-52
div $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-52
lw $t0,0($t0)
li $t1,19
addi $t2,$fp,-56
add $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-56
lw $t0,0($t0)
li $t1,19
addi $t2,$fp,-60
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-60
lw $t0,0($t0)
addi $t1,$zero,1
bne $t0,$t1,label18
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,55
li $v0,11
syscall
j label17
label18:
addi $t0,$fp,-60
lw $t0,0($t0)
addi $t1,$zero,-1
bne $t0,$t1,label19
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,56
li $v0,11
syscall
j label17
label19:
addi $a0,$zero,100
li $v0,11
syscall
addi $a0,$zero,101
li $v0,11
syscall
addi $a0,$zero,102
li $v0,11
syscall
addi $a0,$zero,97
li $v0,11
syscall
addi $a0,$zero,117
li $v0,11
syscall
addi $a0,$zero,108
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,52
li $v0,11
syscall
label17:
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
pr:
sw $ra,4($sp)
addi $sp,$sp,-56
addi $t0,$fp,-0
lw $t0,0($t0)
addi $s0,$t0,0
addi $t0,$fp,-4
lw $t0,0($t0)
addi $s1,$t0,0
li $t0,0
li $t1,1
addi $t2,$fp,-8
sub $t0,$t0,$t1
sw $t0,0($t2)
addi $t1,$fp,-8
lw $t1,0($t1)
bne $s0,$t1,label20
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
j label21
label20:
label21:
addi $t1,$zero,0
bne $s1,$t1,label23
j label22
label23:
li $t0,0
addi $t1,$fp,-12
sw $t0,0($t1)
li $t0,50
addi $t1,$fp,-16
sw $t0,0($t1)
li $t1,50
addi $t2,$fp,-20
div $s1,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-20
lw $t0,0($t0)
li $t1,50
addi $t2,$fp,-24
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t1,$fp,-24
lw $t1,0($t1)
addi $t2,$fp,-28
sub $t0,$s1,$t1
sw $t0,0($t2)
addi $t0,$fp,-28
lw $t0,0($t0)
addi $t1,$fp,-12
lw $t1,0($t1)
bne $t0,$t1,label24
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
j label25
label24:
label25:
label22:
li $t1,1
addi $t2,$fp,-32
sub $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-32
lw $t0,0($t0)
addi $s0,$t0,0
li $t1,1
addi $t2,$fp,-36
add $t0,$s1,$t1
sw $t0,0($t2)
addi $t0,$fp,-36
lw $t0,0($t0)
addi $s1,$t0,0
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
sw $s0,0($sp)
sw $s1,-4($sp)
addi $fp,$sp,0
jal pr
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
getnum:
sw $ra,4($sp)
addi $sp,$sp,-36
li $t0,1
addi $t1,$fp,-0
sw $t0,0($t1)
li $t0,0
addi $s0,$t0,0
label27:
li $t0,1000
addi $t1,$fp,-8
sw $t0,0($t1)
addi $t1,$fp,-8
lw $t1,0($t1)
sub $t2,$s0,$t1
bgez $t2,label26
li $t0,100
addi $t1,$fp,-12
sw $t0,0($t1)
addi $t1,$fp,-12
lw $t1,0($t1)
sub $t2,$s0,$t1
bgez $t2,label28
li $t1,1
addi $t2,$fp,-16
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-16
lw $t0,0($t0)
addi $s0,$t0,0
j label29
label28:
li $t1,2
addi $t2,$fp,-20
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-20
lw $t0,0($t0)
addi $s0,$t0,0
label29:
j label27
label26:
addi $v0,$s0,0
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
getzero:
sw $ra,4($sp)
addi $sp,$sp,-40
li $t0,0
addi $s1,$t0,0
li $t0,1
addi $s0,$t0,0
label31:
li $t0,10
addi $t1,$fp,-8
sw $t0,0($t1)
addi $t1,$fp,-8
lw $t1,0($t1)
sub $t2,$s0,$t1
bgtz $t2,label30
addi $t2,$fp,-12
add $t0,$s1,$s0
sw $t0,0($t2)
addi $t0,$fp,-12
lw $t0,0($t0)
addi $s1,$t0,0
li $t1,1
addi $t2,$fp,-16
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-16
lw $t0,0($t0)
addi $s0,$t0,0
j label31
label30:
li $t1,55
addi $t2,$fp,-20
sub $t0,$s1,$t1
sw $t0,0($t2)
addi $t0,$fp,-20
lw $t0,0($t0)
addi $v0,$t0,0
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
getchar:
sw $ra,4($sp)
addi $sp,$sp,-16
li $t0,109
addi $t1,$fp,-4
sw $t0,0($t1)
li $t0,109
addi $t1,$fp,-0
sw $t0,0($t1)
li $t0,109
li $t1,1
addi $t2,$fp,-8
add $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-8
lw $t0,0($t0)
addi $v0,$t0,0
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
addi $sp,$fp,40
lw $fp,-32($sp)
addi $t0,$sp,-36
lw $ra,0($t0)
lw $s0,0($sp)
lw $s1,-4($sp)
lw $s2,-8($sp)
lw $s3,-12($sp)
lw $s4,-16($sp)
lw $s5,-20($sp)
lw $s6,-24($sp)
lw $s7,-28($sp)
jr $ra
main:
addi $sp,$sp,-12264
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal getchar
addi $t2,$fp,-12068
sw $v0,0($t2)
li $t0,0
addi $t1,$fp,-12072
sw $t0,0($t1)
addi $t0,$fp,-12068
lw $t0,0($t0)
addi $s3,$t0,0
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal getchar
addi $t2,$fp,-12076
sw $v0,0($t2)
addi $t0,$fp,-12072
lw $t0,0($t0)
li $t1,4
mult $t0,$t1
mflo $t0
addi $t1,$fp,-0
sub $t0,$t1,$t0
addi $t1,$fp,-12076
lw $t1,0($t1)
sw $t1,0($t0)
li $t0,2
addi $t1,$fp,-12080
sw $t0,0($t1)
li $t0,0
addi $t1,$fp,-12084
sw $t0,0($t1)
addi $t0,$fp,-12084
lw $t0,0($t0)
li $t1,4
mult $t0,$t1
mflo $t0
addi $t1,$fp,-64
sub $t0,$t1,$t0
addi $t1,$fp,-12080
lw $t1,0($t1)
sw $t1,0($t0)
li $t0,10
la $t1,enter
sw $t0,0($t1)
li $v0,5
syscall
addi $s4,$v0,0
li $t0,3
addi $s2,$t0,0
label33:
sub $t2,$s2,$s4
bgtz $t2,label32
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal getzero
addi $t2,$fp,-12088
sw $v0,0($t2)
addi $t0,$fp,-12088
lw $t0,0($t0)
addi $s0,$t0,0
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal getzero
addi $t2,$fp,-12092
sw $v0,0($t2)
addi $t0,$fp,-12092
lw $t0,0($t0)
addi $s1,$t0,0
add $a0,$zero,$s0
li $v0,1
syscall
label35:
li $t0,1000
addi $t1,$fp,-12096
sw $t0,0($t1)
addi $t1,$fp,-12096
lw $t1,0($t1)
sub $t2,$s1,$t1
bgtz $t2,label34
li $t0,10
addi $t1,$fp,-12100
sw $t0,0($t1)
li $t1,4
mult $s1,$t1
mflo $t0
addi $t1,$fp,-64
sub $t0,$t1,$t0
lw $t0,0($t0)
addi $t1,$fp,-12104
sw $t0,0($t1)
addi $t0,$fp,-12104
lw $t0,0($t0)
addi $t2,$fp,-12108
mult $t0,$s2
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-12108
lw $t0,0($t0)
addi $t1,$fp,-60
sw $t0,0($t1)
addi $t0,$fp,-12108
lw $t0,0($t0)
addi $t2,$fp,-12112
add $t0,$t0,$s0
sw $t0,0($t2)
addi $t0,$fp,-12112
lw $t0,0($t0)
li $t1,10
addi $t2,$fp,-12116
div $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-12116
lw $t0,0($t0)
li $t1,10
addi $t2,$fp,-12120
mult $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-12112
lw $t0,0($t0)
addi $t1,$fp,-12120
lw $t1,0($t1)
addi $t2,$fp,-12124
sub $t0,$t0,$t1
sw $t0,0($t2)
li $t1,4
mult $s1,$t1
mflo $t0
addi $t1,$fp,-64
sub $t0,$t1,$t0
addi $t1,$fp,-12124
lw $t1,0($t1)
sw $t1,0($t0)
addi $t0,$fp,-60
lw $t0,0($t0)
addi $t2,$fp,-12128
add $t0,$t0,$s0
sw $t0,0($t2)
li $t0,10
addi $t1,$fp,-12132
sw $t0,0($t1)
addi $t0,$fp,-12128
lw $t0,0($t0)
addi $t1,$fp,-12132
lw $t1,0($t1)
addi $t2,$fp,-12136
div $t0,$t1
mflo $t0
sw $t0,0($t2)
addi $t0,$fp,-12136
lw $t0,0($t0)
addi $s0,$t0,0
la $t1,_a
lw $t1,0($t1)
addi $t2,$fp,-12140
add $t0,$s1,$t1
sw $t0,0($t2)
addi $t0,$fp,-12140
lw $t0,0($t0)
addi $s1,$t0,0
j label35
label34:
la $t1,_a
lw $t1,0($t1)
addi $t2,$fp,-12144
add $t0,$s2,$t1
sw $t0,0($t2)
addi $t0,$fp,-12144
lw $t0,0($t0)
addi $s2,$t0,0
j label33
label32:
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal getnum
addi $t2,$fp,-12148
sw $v0,0($t2)
addi $t0,$fp,-12148
lw $t0,0($t0)
addi $s0,$t0,0
label37:
li $t0,0
addi $t1,$fp,-12152
sw $t0,0($t1)
li $t1,4
mult $s0,$t1
mflo $t0
addi $t1,$fp,-64
sub $t0,$t1,$t0
lw $t0,0($t0)
addi $t1,$fp,-12156
sw $t0,0($t1)
addi $t0,$fp,-12156
lw $t0,0($t0)
addi $t1,$fp,-12152
lw $t1,0($t1)
bne $t0,$t1,label36
la $t1,b
lw $t1,0($t1)
addi $t2,$fp,-12160
add $t0,$s0,$t1
sw $t0,0($t2)
addi $t0,$fp,-12160
lw $t0,0($t0)
addi $s0,$t0,0
j label37
label36:
addi $s2,$s0,0
add $a0,$zero,$s0
li $v0,1
syscall
addi $a0,$zero,115
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
addi $a0,$zero,97
li $v0,11
syscall
addi $a0,$zero,114
li $v0,11
syscall
addi $a0,$zero,116
li $v0,11
syscall
la $t0,ch1
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
la $t0,ch2
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
label39:
li $t0,0
addi $t1,$fp,-12164
sw $t0,0($t1)
addi $t1,$fp,-12164
lw $t1,0($t1)
sub $t2,$s2,$t1
bltz $t2,label38
li $t1,4
mult $s2,$t1
mflo $t0
addi $t1,$fp,-64
sub $t0,$t1,$t0
lw $t0,0($t0)
addi $t1,$fp,-12168
sw $t0,0($t1)
addi $t0,$fp,-12168
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,1
syscall
li $t1,1
addi $t2,$fp,-12172
sub $t0,$s2,$t1
sw $t0,0($t2)
addi $t0,$fp,-12172
lw $t0,0($t0)
addi $s2,$t0,0
j label39
label38:
addi $a0,$zero,92
li $v0,11
syscall
add $a0,$zero,$s3
li $v0,11
syscall
la $t0,enter
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal testcompare
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal testswitch
li $t0,7
addi $t1,$fp,-12176
sw $t0,0($t1)
li $t0,6
addi $t1,$fp,-12180
sw $t0,0($t1)
li $t0,5
addi $t1,$fp,-12184
sw $t0,0($t1)
li $t0,4
addi $t1,$fp,-12188
sw $t0,0($t1)
li $t0,3
addi $t1,$fp,-12192
sw $t0,0($t1)
li $t0,2
addi $t1,$fp,-12196
sw $t0,0($t1)
li $t0,1
addi $t1,$fp,-12200
sw $t0,0($t1)
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $t0,$fp,-12200
lw $t0,0($t0)
sw $t0,0($sp)
addi $t0,$fp,-12196
lw $t0,0($t0)
sw $t0,-4($sp)
addi $t0,$fp,-12192
lw $t0,0($t0)
sw $t0,-8($sp)
addi $t0,$fp,-12188
lw $t0,0($t0)
sw $t0,-12($sp)
addi $t0,$fp,-12184
lw $t0,0($t0)
sw $t0,-16($sp)
addi $t0,$fp,-12180
lw $t0,0($t0)
sw $t0,-20($sp)
addi $t0,$fp,-12176
lw $t0,0($t0)
sw $t0,-24($sp)
addi $fp,$sp,0
jal manyparameter
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal testchildexpression
li $t0,0
li $t1,4
mult $t0,$t1
mflo $t0
addi $t1,$fp,-0
sub $t0,$t1,$t0
lw $t0,0($t0)
addi $t1,$fp,-12204
sw $t0,0($t1)
addi $t0,$fp,-12204
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
sw $s0,0($sp)
sw $s1,-4($sp)
sw $s2,-8($sp)
sw $s3,-12($sp)
sw $s4,-16($sp)
sw $s5,-20($sp)
sw $s6,-24($sp)
sw $s7,-28($sp)
sw $fp,-32($sp)
addi $sp,$sp,-40
addi $fp,$sp,0
jal getchar
addi $t2,$fp,-12208
sw $v0,0($t2)
addi $t0,$fp,-12208
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,11
syscall
li $t0,109
addi $t1,$fp,-12212
sw $t0,0($t1)
li $t0,109
li $t1,1
addi $t2,$fp,-12216
add $t0,$t0,$t1
sw $t0,0($t2)
addi $t0,$fp,-12216
lw $t0,0($t0)
add $a0,$zero,$t0
li $v0,1
syscall
EXIT:
