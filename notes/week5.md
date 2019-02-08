## Terms/Skills to know from week 5 C and Linux

C has no exceptions:

    Using errno: 
     learn about global var errno
     perror() for printing errors

UNIX IO
    UNIX IO uses "system calls" and "file descriptors"

    System calls are library wrapped "software interrupts" into OS kernel code. 
    Can treat them like any other library routine. Section 2 of the manual has 
    the system calls

    File descriptors are small integers the OS kernel uses as names for files 
    (and things like files)

    fds 0, 1, 2 are always stdin, stdout, stderr files
    open()/creat(), read()/write(), close()

    There is no buffering: each read()/write() is a call into the OS kernel

C stdio
    stdio is the name for the generic buffered IO provided by the C library 
    through stdio.h

    stdin, stdout, stderr are stdio file pointers.

    fopen() will return a FILE * for using with stdio.

    fdopen() will take a file descriptor and return a file pointer for that

    fclose() closes a file pointer

stdio Buffering
    Three modes: unbuffered, line buffered, block buffered (at specified block 
    size)

    stdin and stdout are speshul: line buffered if "a terminal" and otherwise 
    block-buffered. Reading from stdin flushes stdout first. stderr is unbuffered

    Use fflush() to flush any output buffering

Compiler Pipeline
    Compiler driver (program called gcc) runs things, invokes

    cpp -- C preprocessor: C → C

    cc1 -- Main compiler pass: C → assembly

    as -- Assemble compiler textual output: assembly → object file
    a.out = assembler output

    ld -- Processes object and library files: objects → executable
    (linker)

Helpful utilities:

    nm -op <file.o> gives a view of the symbol table
    objdump <file.o> gives a convenient view of the whole obj file

Separate Compilation

    Compile code without ld step to get .o file

    gcc -c file.c

    Object code contains "symbol table"

    What symbols does this file use that are not in it?

    What symbols does this file define?

    nm -op gives a convenient view of symbol table

    objdump gives a convenient view of whole object file

Separate Compilation: Include Headers
    Object file contains no type information: compiler throws it away

    "Include headers" define interface: test that a name has the same type where 
    it is defined as where it is used

    C has extern and static scopes:

      static int f(int x) { return x + 1; }
    declares a function whose name f never makes it into the symbol table, vs

      int f(int x) { return x + 1; }
    In a header file you would write

      extern int f(int x);
    then include that header file in both the source file defining f and the 
    source file using f

Relocating ("Linking") Loader
    The job of ld is to create an executable file by:

    Placing each defined thing from a .o file in the executable at a specific 
    memory address

    Adjusting references to the thing to have the right address

    An executable file is a map of what memory should look like when the program 
    starts

Learn Static and Dynamic Libraries and how to build them and use them
