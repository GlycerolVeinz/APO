.globl _start
.option norelax

.text

_start:
# Preparations, of arguments and counters
	la		x1, arr_len // x1 will be used for as array lenght
	lw		x1, 0x0(x1) 

	add		x3, x0, x0 // counter for outer for loop
	outer_for_loop:
		beq		x1, x3, sorted // EO loop

		la		x2, arr_1 // x2 will mark starting adress of array

		add 	x5, x1, x0 // create N-1-i in x5 every loop 
		addi 	x5, x5, -1  
		sub 	x5, x5, x3 
		
		add		x4, x0, x0 // couter for inner for loop
		inner_for_loop:
			beq		x5, x4, eo_inner_loop // EO loop

			lw 		x7, 0x0(x2) // load value of arr[x2] 
			addi 	x9, x2, 4 // next in arr 
			lw 		x8, 0x0(x9) // load value of arr[x2 (+ 1)]

			# IF statement
			slt 	x6, x7, x8 //store bool arr[x2] < arr[x2 + 1]
			bne 	x6, x0, noswap
				sw 		x8, 0x0(x2)
				sw 		x7, 0x0(x9)

			noswap:

			addi 	x2, x2, 4 	// go to next pair
			addi 	x4, x4, 1	// increment before looping
			j 	 	inner_for_loop // loop around

		eo_inner_loop:
		addi  	x3, x3, 1  // increment before looping
		j  		outer_for_loop // loop around

sorted:
	nop
	nop
	ebreak //end



.data
.org 0x400
    arr_len:
    .word 4
    arr_1:
    .word 1,4,5,7