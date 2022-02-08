# Unix Environment


## Compiler

- preprocessing (cpp)
- lexical analysis (cc)
- syntax analysis (cc)
- semantic analysis (cc)
- code generation (cc)
- code optimization (cc)
- assembly (as)
- linking (ld)


```sh
cpp --help
cpp -P hello.c # -P disable linkemarker output in -E mode
cpp -P -DFOOD=\"tomato\" hello.c
```

```bash
cc -E hello.c
cc -E -DFOOD=\"tomato\" hello.c # output hello.i
cc -S hello.i                   # output hello.s
cc -c hello.s                   # output hello.o
```

```
-E: Stop after the preprocessing stage.
-D: Process the `#define`. 
-S: Only run preprocessing and compilation steps
-c: Only run preprocess, compile, and assemble steps
```

Or run as separately.

```bash
as -o hello.o hello.s

file ./apue-code/05/compilechain/hello.*
./apue-code/05/compilechain/hello.c:     c program text, ASCII text
./apue-code/05/compilechain/hello.i:     c program text, ASCII text
./apue-code/05/compilechain/hello.mac.i: c program text, ASCII text
./apue-code/05/compilechain/hello.mac.o: Mach-O 64-bit object arm64
./apue-code/05/compilechain/hello.mac.s: assembler source text, ASCII text
./apue-code/05/compilechain/hello.o:     ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
```

## Debugging

## 
