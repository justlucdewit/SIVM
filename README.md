# SIVM
## ARCHITECTURE

sizeof opcode = 8<br />
sizeof stackitem = 32<br />
sizeof memitem = 8

## OPCODES
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
|  0x0C  | OP_ADD_UI             |  ✅   |
|  0x0D  | OP_SUB_UI             |      |
|  0x0E  | OP_MUL_UI             |      |
|  0x0F  | OP_DIV_UI             |      |
|  0x10  | OP_MOD_UI             |      |
|  0x11  | OP_ADD_I              |      |
|  0x12  | OP_SUB_I              |      |
|  0x13  | OP_MUL_I              |      |
|  0x14  | OP_DIV_I              |      |
|  0x15  | OP_ADD_F              |      |
|  0x16  | OP_SUB_F              |      |
|  0x17  | OP_MUL_F              |      |
|  0x18  | OP_DIV_F              |      |
|  0x20  | OP_RAND               |      |


## SYSCALLS
| SYSCALL | Name      |
|:-------:|-----------|
|  0x00   | SYS_WRITE | 
|  0x01   | SYS_EXIT  |