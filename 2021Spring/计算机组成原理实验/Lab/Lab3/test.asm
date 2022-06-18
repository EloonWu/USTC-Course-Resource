.data
	in: .word 3
	out: .word 0
	str1: .string  "test lw\n"
	str2: .string  "test sw\n"
	str3: .string  "test add\n"
	str4: .string  "test addi\n"
	str5: .string  "test bep\n"
	str6: .string  "test jal\n"
	str7: .string  "The function has been tested!\n"
	newline: .string     "\n"

.text
	la s0, in
#test lw
	la a0, str1 
    li a7, 4   
    ecall

	lw a1, 0(s0)
	addi a0, a1, 0     
    li a7, 1    
    ecall

    jal printNewline  
#test sw
	la a0, str2
    li a7, 4   
    ecall

	sw a1, 0(a2)
	lw s1, 0(a2)
	addi a0, s1, 0
	li a7, 1
	ecall

	jal printNewline  
#test add
	la a0, str3
    li a7, 4   
    ecall

	lw a3, 4(s0)
	add a3, a1, a1
	addi a0, a3, 0
	li a7, 1
	ecall

	jal printNewline 
#test addi
	la a0, str4
    li a7, 4   
    ecall

	lw a3, 4(s0)
	addi a3, a1, 9
	addi a0, a3, 0
	li a7, 1
	ecall

	jal printNewline 

#test jal
	la a0, str6
    li a7, 4   
    ecall

	jal TestBeq
	
#test beq
	la a0, str5
    li a7, 4   
    ecall
	
	lw a1, 0(s0)
	lw a2, 0(s0)
	beq a1, a2, TestBeq

	jal printNewline 

	j exit
printNewline:
    la a0, newline
    li a7, 4
    ecall
    jr x1

TestBeq:
	la a0, str7
    li a7, 4   
    ecall
    jr x1

exit:
   