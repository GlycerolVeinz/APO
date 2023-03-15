/* Hello world example to demonstrate on multiple architectures */

/*
 * compile, run and examine for different instruction set architectures
 * build by make command where ARCH is chisen as one of
 *   native, x86, riscv, riscv64, mips, arm or aarch64
 *   make ARCH=riscv
 */

#include <stdio.h>

int pole[5]={5,3,4,1,2};

int main(){
    int N = 5,i,j,tmp;
    for(i=0; i<N; i++) {
        for(j=0; j<N-1-i; j++) {
            if(pole[j+1]<pole[j]) {
                tmp = pole[j+1];
                pole[j+1] = pole[j];
                pole[j] = tmp;
            }
        }
    }
    return 0;
}
