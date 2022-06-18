.data
        in1: .word 1       #The value of the first element initialization
	in2: .word 2       #The value of the secnd element initialization
		        

.text
        la s0, in1
        lw a1, 0(s0)       #Enter the first element of the sequence
	addi a0, a1, 0
	li a7, 1
	ecall
	jal PrintSpace   
        lw a2, 4(s0)       #Enter the second element of the sequence
	addi a0, a2, 0   
	li a7, 1  
	ecall 
	jal PrintSpace   
LOOP:   addi a3, a2, 0  
        add a2, a1 ,a2
	addi a0, a2, 0   
	li a7, 1  
	ecall 
	jal PrintSpace   
        addi a1, a3, 0
        j LOOP  

PrintSpace:
	li a0 32
	li a7 11
	ecall
	jr x1