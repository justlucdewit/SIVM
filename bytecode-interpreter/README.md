# SI-VM

## Usage
To run a sivm executable, use the following command: `sivm path/to/executable`

## Opcodes
| Adress | Opcode                | Done |
|:------:|-----------------------|:----:|
|  0x00  | OP_SYSCALL            |  ✅   |
|  0x01  | OP_JUMP \<address>    |      |
|  0x02  | OP_CSKIP              |      |
|  0x03  | OP_PUSH \<u32>        |  ✅   |
|  0x04  | OP_WRITE8 \<address>  |      |
|  0x05  | OP_READ8 \<address>   |      |
|  0x06  | OP_WRITE32 \<address> |      |
|  0x07  | OP_READ32 \<address>  |      |
|  0x08  | OP_CALL               |      |
|  0x09  | OP_RETURN             |      |
|  0x0A  | OP_RESERVE \<bytes>   |      |
|  0x0B  | OP_FREE \<bytes>      |      |
|  0x0C  | OP_UI_ADD             |  ✅   |
|  0x0D  | OP_UI_SUB             |      |
|  0x0E  | OP_UI_MUL             |      |
|  0x0F  | OP_UI_DIV             |      |
|  0x10  | OP_I_MOD              |      |
|  0x11  | OP_I_ADD              |      |
|  0x12  | OP_I_SUB              |      |
|  0x13  | OP_I_MUL              |      |
|  0x14  | OP_I_DIV              |      |
|  0x15  | OP_F_ADD              |      |
|  0x16  | OP_F_SUB              |      |
|  0x17  | OP_F_MUL              |      |
|  0x18  | OP_F_DIV              |      |
|  0x20  | OP_RAND               |      |


## Syscalls
| Syscall | Name      |
|:-------:|-----------|
|  0x00   | SYS_WRITE | 
|  0x01   | SYS_EXIT  |