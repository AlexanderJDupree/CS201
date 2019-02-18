## Terms/Skills to know from week 6 x86-64 CPU

CPU is an interpreter:

    registers are like global variables for storing intermediate values

    instruction pointer (program counter) is a register for what address 
    in memory starts the next instruction

Instructions
    
    Instructions contains:
        
        opcode: what the instruction does

        operands: what registers/memory does the opcode manipulate

Read up on the loader

x86-64 Assembly

    We use linux at&t C calling conventions

    Two assembly syntaxes AT&T and Intel.

    For binary operators it goes

        opcode source, dest (AT&T)
        opcode dest, source (intel)

Helpful debug flags:

    gcc -g -Wall -Werror -fno-pic -no-pie -static -c -o driver.o driver.c
    gcc -g -Wall -Werror -fno-pic -no-pie -static -c xor.S
    gcc -g -Wall -Werror -fno-pic -no-pie -static -o xor driver.o xor.o

display symbol table 
    nm -op <binary>
remove symbol table
    strip [binary] 


