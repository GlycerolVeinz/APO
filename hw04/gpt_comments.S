00010200 <subroutine_fnc>:
   10200:   addi sp, sp, -80    // Allocate 80 bytes of space on the stack for local variables
   10204:   sw s0, 76(sp)       // Save the value of the previous stack pointer in the saved register s0
   10208:   addi s0, sp, 80     // Set s0 to point to the current stack frame
   1020c:   sw a0, -68(s0)      // Store the value of the first function argument at -68 bytes offset from s0
   10210:   sw a1, -72(s0)      // Store the value of the second function argument at -72 bytes offset from s0
   10214:   sw zero, -24(s0)    // Store zero at -24 bytes offset from s0
   10218:   j 1026c:             // Jump to label 1026c

   1021c:   addi a5, s0, -57    // Label 1021c: Add -57 to s0 and store the result in register a5
   10220:   li a4, 64           // Load the immediate value 64 into register a4
   10224:   sw a4, -28(s0)      // Store the value of a4 at -28 bytes offset from s0
   10228:   lw a4, -72(s0)      // Load the value at -72 bytes offset from s0 into a4
   1022c:   sw a4, -32(s0)      // Store the value of a4 at -32 bytes offset from s0
   10230:   sw a5, -36(s0)      // Store the value of a5 at -36 bytes offset from s0
   10234:   li a5, 1            // Load the immediate value 1 into register a5
   10238:   sw a5, -40(s0)      // Store the value of a5 at -40 bytes offset from s0
   1023c:   lw a7, -28(s0)      // Load the value at -28 bytes offset from s0 into a7
   10240:   lw a0, -32(s0)      // Load the value at -32 bytes offset from s0 into a0
   10244:   lw a1, -36(s0)      // Load the value at -36 bytes offset from s0 into a1
   10248:   lw a2, -40(s0)      // Load the value at -40 bytes offset from s0 into a2
   1024c:   ecall               // Call the system call specified in a7, passing arguments in a0-a2 and return value in a0
   10250:   mv a5, a0           // Copy the return value in a0 to a5
   10254:   sw a5, -20(s0)      // Store the value of a5 at -20 bytes offset from s0
   10258:   lw a5, -20(s0)      // Load the value at -20 bytes offset from s0 into a5
   1025c:   bltz a5, 102b8:      // Branch to label 102b8 if a5 is less than zero
   10260:   lw a5, -24(s0)      // Load the value at -24 bytes
   10264:   addi	a5,a5,1     // Increment the value in register a5 by 1.
   10268:   sw	a5,-24(s0)      // Store the value in a5 at the memory location s0-24.

   1026c:   addi	a5,s0,-5    // Store the value s0-57 in a5.
   10270:   li	a4,63           // Load the immediate value 63 into register a4.
   10274:   sw	a4,-44(s0)      // Store the value in a4 at the memory location s0-44.
   10278:   lw	a4,-68(s0)      // Load the value at the memory location s0-68 into register a4.
   1027c:   sw	a4,-48(s0)      // Store the value in a4 at the memory location s0-48.
   10280:   sw	a5,-52(s0)      // Store the value in a5 at the memory location s0-52.
   10284:   li	a5,1            // Load the immediate value 1 into register a5.
   10288:   sw	a5,-56(s0)      // Store the value in a5 at the memory location s0-56.
   1028c:   lw	a7,-44(s0)      // Load the value at the memory location s0-44 into register a7.
   10290:   lw	a0,-48(s0)      // Load the value at the memory location s0-48 into register a0.
   10294:   lw	a1,-52(s0)      // Load the value at the memory location s0-52 into register a1.
   10298:   lw	a2,-56(s0)      // Load the value at the memory location s0-56 into register a2.
   1029c:   ecall               // Perform a system call based on the values in the registers.
   102a0:   mv	a5,a0           // Move the value in register a0 to register a5.
   102a4:   sw	a5,-20(s0)      // Store the value in a5 at the memory location s0-20.
   102a8:   lw	a4,-20(s0)      // Load the value at the memory location s0-20 into register a4.
   102ac:   li	a5,1            // Load the immediate value 1 into register a5.
   102b0:   beq	a4,a5,1021c:     // If the values in registers a4 and a5 are equal, jump to the memory location 1021c.
   102b4:   j	102bc:           // Jump to the memory location 102bc.
   
   102b8:   nop         
   102bc:   lw	a5,-20(s0)      // Load the value at the memory location s0-20 into register a5.
   102c0:   bgez	a5,102cc:    // If the value in register a5 is greater than or equal to zero, jump to the memory location 102cc.
   
   102c4:   li	a5,-1           // Load the immediate value -1 into register a5.
   102c8:   j	102d0:           // Jump to the memory location 102d0.
   
   102cc:   lw	a5,-24(s0)      // Load the value at the memory location s0-24 into register a5.
   102d0:   mv	a0,a5           // Move the value in register a5 to register a0.
   102d4:   lw	s0,76(sp)       // Load the value at the memory location sp+76 into register s0.
   102d8:   addi sp,sp,80       // Increment the value in register sp by 80.
   102dc:   ret
