// Authored by: Marios Stavrou

#include "helpers.h"

extern void print(const char*);
extern void print_dec(unsigned int);

void clear_registers(){
    asm volatile ("csrw mcycle, zero");
    asm volatile ("csrw mcycleh, zero"); 

    asm volatile ("csrw minstret, zero");
    asm volatile ("csrw minstreth, zero"); 

    asm volatile ("csrw mhpmcounter3, zero");
    asm volatile ("csrw mhpmcounter3h, zero"); 

    asm volatile ("csrw mhpmcounter4, zero");
    asm volatile ("csrw mhpmcounter4h, zero"); 

    asm volatile ("csrw mhpmcounter5, zero");
    asm volatile ("csrw mhpmcounter5h, zero"); 

    asm volatile ("csrw mhpmcounter6, zero");
    asm volatile ("csrw mhpmcounter6h, zero"); 

    asm volatile ("csrw mhpmcounter7, zero");
    asm volatile ("csrw mhpmcounter7h, zero"); 

    asm volatile ("csrw mhpmcounter8, zero");
    asm volatile ("csrw mhpmcounter8h, zero"); 

    asm volatile ("csrw mhpmcounter9, zero");
    asm volatile ("csrw mhpmcounter9h, zero"); 
}

void read_registers(){
    unsigned int mcycle, mcycleh;
    unsigned int minstret, minstreth;
    unsigned int mhpmcounter3, mhpmcounter3h;
    unsigned int mhpmcounter4, mhpmcounter4h;
    unsigned int mhpmcounter5, mhpmcounter5h;
    unsigned int mhpmcounter6, mhpmcounter6h;
    unsigned int mhpmcounter7, mhpmcounter7h;
    unsigned int mhpmcounter8, mhpmcounter8h;
    unsigned int mhpmcounter9, mhpmcounter9h;

    asm("csrr %0, mcycle" : "=r"(mcycle));
    asm("csrr %0, mcycleh" : "=r"(mcycleh));

    asm("csrr %0, minstret" : "=r"(minstret));
    asm("csrr %0, minstreth" : "=r"(minstreth));

    asm("csrr %0, mhpmcounter3" : "=r"(mhpmcounter3));
    asm("csrr %0, mhpmcounter3h" : "=r"(mhpmcounter3h));

    asm("csrr %0, mhpmcounter4" : "=r"(mhpmcounter4));
    asm("csrr %0, mhpmcounter4h" : "=r"(mhpmcounter4h));

    asm("csrr %0, mhpmcounter5" : "=r"(mhpmcounter5));
    asm("csrr %0, mhpmcounter5h" : "=r"(mhpmcounter5h));

    asm("csrr %0, mhpmcounter6" : "=r"(mhpmcounter6));
    asm("csrr %0, mhpmcounter6h" : "=r"(mhpmcounter6h));

    asm("csrr %0, mhpmcounter7" : "=r"(mhpmcounter7));
    asm("csrr %0, mhpmcounter7h" : "=r"(mhpmcounter7h));

    asm("csrr %0, mhpmcounter8" : "=r"(mhpmcounter8));
    asm("csrr %0, mhpmcounter8h" : "=r"(mhpmcounter8h));

    asm("csrr %0, mhpmcounter9" : "=r"(mhpmcounter9));
    asm("csrr %0, mhpmcounter9h" : "=r"(mhpmcounter9h));

    print_dec(mcycle);
    print("\n");

    print_dec(mcycleh);
    print("\n");

    print_dec(minstret);
    print("\n");

    print_dec(mhpmcounter3);
    print("\n");

    print_dec(mhpmcounter4);
    print("\n");

    print_dec(mhpmcounter5);
    print("\n");

    print_dec(mhpmcounter6);
    print("\n");

    print_dec(mhpmcounter7);
    print("\n");

    print_dec(mhpmcounter8);
    print("\n");

    print_dec(mhpmcounter9);
    print("\n");
}

