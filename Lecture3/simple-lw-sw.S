.globl _start
.option norelax


.text


_start:


    la      x1, vec_a
    la      x2, vec_b
    la      x3, size_a


loop:
    beq     x3, x0, end
    lw      x4, 0x0(x1)
    lw      x5, 0x0(x2)
    add     x4, x4, x5


    sw      x4, 0x0(x1)


    addi    x1, x1, 4
    addi    x2, x2, 4


    addi    x3, x3, -1
    j       loop  
end:
    nop
    nop
    ebreak


.data
.org 0x400
size_a:
    .word 5
vec_a:
    .word 1,2,3,4,1
vec_b:
    .word 5,6,7,8,1