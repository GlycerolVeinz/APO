00010200 <subroutine_fnc>:
   10200:          	addi	sp,sp,-80   //80 bytes stack space 
   10204:          	sw	s0,76(sp)
   10208:          	addi	s0,sp,80
   1020c:          	sw	a0,-68(s0)
   10210:          	sw	a1,-72(s0)
   10214:          	sw	zero,-24(s0)
   10218:          	j	1026c
   1021c:          	addi	a5,s0,-57
   10220:          	li	a4,64
   10224:          	sw	a4,-28(s0)
   10228:          	lw	a4,-72(s0)
   1022c:          	sw	a4,-32(s0)
   10230:          	sw	a5,-36(s0)
   10234:          	li	a5,1
   10238:          	sw	a5,-40(s0)
   1023c:          	lw	a7,-28(s0)
   10240:          	lw	a0,-32(s0)
   10244:          	lw	a1,-36(s0)
   10248:          	lw	a2,-40(s0)
   1024c:          	ecall
   10250:          	mv	a5,a0
   10254:          	sw	a5,-20(s0)
   10258:          	lw	a5,-20(s0)
   1025c:          	bltz	a5,102b8
   10260:          	lw	a5,-24(s0)
   10264:          	addi	a5,a5,1
   10268:          	sw	a5,-24(s0)
   1026c:          	addi	a5,s0,-57 
   10270:          	li	a4,63
   10274:          	sw	a4,-44(s0)
   10278:          	lw	a4,-68(s0)
   1027c:          	sw	a4,-48(s0)
   10280:          	sw	a5,-52(s0)
   10284:          	li	a5,1
   10288:          	sw	a5,-56(s0)
   1028c:          	lw	a7,-44(s0)
   10290:          	lw	a0,-48(s0)
   10294:          	lw	a1,-52(s0)
   10298:          	lw	a2,-56(s0)
   1029c:          	ecall
   102a0:          	mv	a5,a0
   102a4:          	sw	a5,-20(s0)
   102a8:          	lw	a4,-20(s0)
   102ac:          	li	a5,1
   102b0:          	beq	a4,a5,1021c
   102b4:          	j	102bc
   102b8:          	nop
   102bc:          	lw	a5,-20(s0)
   102c0:          	bgez	a5,102cc
   102c4:          	li	a5,-1
   102c8:          	j	102d0
   102cc:          	lw	a5,-24(s0)
   102d0:          	mv	a0,a5
   102d4:          	lw	s0,76(sp)
   102d8:          	addi	sp,sp,80
   102dc:          	ret