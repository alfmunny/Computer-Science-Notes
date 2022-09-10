#include <ucontext.h>
#include <stdio.h>

ucontext_t ut[3];

void f1() {
    for (int i = 0; i != 10; ++i) {
        printf("f1:%d\n", i);
        swapcontext(&ut[1], &ut[2]);
    }
}

void f2() {
    for (int i = 0; i != 10; ++i) {
        printf("f1:%d\n", i);
        swapcontext(&ut[2], &ut[1]);
    }
}

int main() {
    char stack_buff1[4096];
    char stack_buff2[4096];

    // https://stackoverflow.com/questions/19503925/what-does-the-getcontext-system-call-ucontext-h-really-do
    getcontext(&ut[1]);
    ut[1].uc_stack.ss_sp = stack_buff1;
    ut[1].uc_stack.ss_size = sizeof(stack_buff1);
    ut[1].uc_link = &ut[2];

    makecontext(&ut[1], f1, 0);

    getcontext(&ut[2]);
    ut[2].uc_stack.ss_sp = stack_buff2;
    ut[2].uc_stack.ss_size = sizeof(stack_buff2);
    ut[2].uc_link = &ut[0];
    makecontext(&ut[2], f2, 0);

    swapcontext(&ut[0], &ut[1]);

    printf("Back to main\n");
}


