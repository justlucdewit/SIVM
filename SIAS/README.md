# SI-Assembler

The SI-Assembler takes assembly code and converts it to a SI-executable
to do this, use the command `sias path/to/code.asm` and it should output
the resulting executable.

# Syntax

### Stack operations

The si-virtual machine contains a stack of unsigned 32 bit numbers, but these
numbers can be interpreted as different data types like u8, u16, i8, i16, i32
and floats

To push a 32 bit number onto the stack, use the following opcode:
```asm
push 4
push 200
```

To add the top 2 values on the stack as unsigned 32 bit integers, and push
the result back onto the stack, use the following code (This will leave the
number 204 onto the stack):
```asm
push 4
push 200
ui32_add
```

### Comments
Comments can be placed in the code to make certain texts be ignored by the assembler
This can be used for the documentation of the code or in case something needs to be
make clear to developers.

Comments are initiaded using the ; and end at the end of the line

```asm
; push 15
push 15
```

### Syscalls

Syscalls are a way to ask the virtual machine to perform some action done by
the operating system, like killing the application with some exit code, or
printing something to STDOUT

The following table contains all of the syscall codes:
| Syscall | Name      |
|:-------:|-----------|
|  0x00   | SYS_WRITE | 
|  0x01   | SYS_EXIT  |

To exit the application with exit code 5:
```asm
push 5
push 1
syscall
```

To print hello world to STDOUT:
```asm
push string
push 12
push 0
syscall

string:
    bytes "Hello World!"
```

The bytes keyword in this example takes a string and puts the bytes of the string
at that location in the bytecode as raw bytes, The label 'string' is used to mark
the location of the string in the bytecode

# Future features:
 - Escape codes in string
 - Macros
 - Includes
 - Standard library
