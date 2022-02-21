#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define SIVM_STACK_CAPACITY 255
#define SIVM_MEMORY_CAPACITY 255

typedef u_int8_t u8;
typedef u_int32_t u32;
typedef int32_t i32;

u32* sivm_stack;
u32 sivm_stack_pointer = 0;
u32 program_counter = 0;
u8 sivm_debug = 0;

u8* sivm_memory;

char* sivm_instr_names[] = {
        "OP_SYSCALL",
        "OP_JUMP",
        "OP_CSKIP",
        "OP_PUSH"
};

u8 sivm_fetch8() {
    ++program_counter;
    return sivm_memory[program_counter];
}

u32 sivm_fetch32() {
    u32 result = 1;

    for(i32 i = 0; i < 4; i++) {
        u32 nextByte = sivm_fetch8();
        result = (result << 8) | nextByte;
    }

    return result;
}

void sivm_stack_push(u32 number) {
    sivm_stack[sivm_stack_pointer] = number;
    ++sivm_stack_pointer;
}

u32 sivm_stack_pop() {
   --sivm_stack_pointer;
   u32 ret = sivm_stack[sivm_stack_pointer];
   return ret;
}

void sivm_sys_write() {
    u32 string_length = sivm_stack_pop();
    u32 string_ptr = sivm_stack_pop();
    fwrite(((char *)sivm_memory) + string_ptr, sizeof(char), string_length, stdout);
}

void sivm_sys_exit() {
    u32 exit_code = sivm_stack_pop();
    exit(exit_code);
}

void sivm_op_syscall() {
    u8 syscall_type = sivm_stack_pop();

    if (syscall_type == 0)
        sivm_sys_write();
    else if (syscall_type == 1)
        sivm_sys_exit();
    else
        printf("unknown syscall (0x%.2X)\n", syscall_type);
}

void sivm_op_push() {
    u32 num = sivm_fetch32();
    sivm_stack_push(num);
}

void sivm_op_ui32_add() {
    u32 a = sivm_stack_pop();
    u32 b = sivm_stack_pop();
    sivm_stack_push(a + b);
}

void sivm_init() {
    sivm_stack = malloc(sizeof(u32) * SIVM_STACK_CAPACITY);
    sivm_memory = malloc(sizeof(u8) * SIVM_MEMORY_CAPACITY);
}

void sivm_load_program(char* file_name) {
    // open file
    FILE *fp = fopen(file_name, "rb");

    // error detection
    if (fp == NULL) {
        printf("[ERROR] could not open file: %s", file_name);
        exit(-1);
    }

    // get buffer size
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // buffer allocation
    unsigned char *program = (unsigned char *) malloc(size);

    if(fread(program, sizeof *program, size, fp) != size) {
        printf("[ERROR] while reading file: %s", file_name);
        exit(1);
    }

    fclose(fp);

    sivm_memory = memcpy(sivm_memory, program, size);
}

_Noreturn void sivm_run_program() {
    u8 opcode = sivm_memory[program_counter];

    while(1) {
        if (sivm_debug)
            printf("0x%.8X %s\n", program_counter, sivm_instr_names[opcode]);

        if (opcode == 0x00)
            sivm_op_syscall();
        else if (opcode == 0x03)
            sivm_op_push();
        else if (opcode == 0x0C)
            sivm_op_ui32_add();
        else
            printf("unknown opcode (0x%.2X)\n", opcode);

        opcode = sivm_fetch8();
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1)
        puts("Simple assembler, assembler for the Simple Virtual Machine\nDeveloped by Luke_");
    else {
        char* file_name = argv[1];
        sivm_init();
        sivm_load_program(file_name);
        sivm_run_program();
    }

    return 0;
}