#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

#include "../../libraries/color.h"

#define SIVM_STACK_CAPACITY 255
#define SIVM_MEMORY_CAPACITY 255
#define SIVM_DEBUG 1

typedef u_int8_t u8;
typedef u_int16_t u16;
typedef u_int32_t u32;
typedef u_int64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

u64* sivm_stack;
u64 sivm_stack_pointer = 0;
u64 program_counter = 0;

u8* sivm_memory;

char* sivm_instr_names[] = {
    "syscall", "dynamic_load", "alloc", "free", "realloc", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop",
    "push", "dup", "rand", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop",
    "cskip", "jump", "call", "return", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop", "nop"
};

// Generate u64 random numbers
#define IMAX_BITS(m) ((m)/((m)%255+1) / 255%255*8 + 7-86/((m)%255+12))
#define RAND_MAX_WIDTH IMAX_BITS(RAND_MAX)
_Static_assert((RAND_MAX & (RAND_MAX + 1u)) == 0, "RAND_MAX not a Mersenne number");

u64 rand64() {
  u64 r = 0;
  for (int i = 0; i < 64; i += RAND_MAX_WIDTH) {
    r <<= RAND_MAX_WIDTH;
    r ^= (unsigned) rand();
  }
  return r;
}

u8 sivm_fetch8() {
    ++program_counter;
    return sivm_memory[program_counter];
}

u64 sivm_fetch64() {
    u64 result = 1;

    for(u8 i = 0; i < 8; i++) {
        u64 nextByte = sivm_fetch8();
        result = (result << 8) | nextByte;
    }

    return result;
}

void sivm_stack_push(u64 number) {
    sivm_stack[sivm_stack_pointer] = number;
    ++sivm_stack_pointer;
}

u64 sivm_stack_pop() {
   --sivm_stack_pointer;
   u64 ret = sivm_stack[sivm_stack_pointer];
   return ret;
}

void sivm_sys_write() {
    u64 string_length = sivm_stack_pop();
    u64 string_ptr = sivm_stack_pop();

    fwrite(((char *)sivm_memory) + string_ptr, sizeof(char), string_length, stdout);
}

void sivm_sys_exit() {
    u64 exit_code = sivm_stack_pop();

    if (SIVM_DEBUG) {
        puts("\n--- stack result ---");

        while (sivm_stack_pointer > 0)
            printf(" - %lu\n", sivm_stack_pop());

        puts("--------------------");
    }

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

void sivm_op_jump() {
    u64 num = sivm_fetch64();
    program_counter = num - 1;
}

void sivm_op_push() {
    u64 num = sivm_fetch64();
    sivm_stack_push(num);
}

void sivm_op_dup() {
    u64 num = sivm_stack[sivm_stack_pointer - 1];
    sivm_stack_push(num);
}

void sivm_op_rand() {
    sivm_stack_push(rand64());
}

void sivm_op_alloc() {
    u64 bytes = sivm_fetch64();
    void* ptr = malloc(sizeof(u8) * bytes);
    sivm_stack_push((u64) ptr);
}

void sivm_op_ui32_add() {
    u64 a = sivm_stack_pop();
    u64 b = sivm_stack_pop();
    sivm_stack_push(a + b);
}

void sivm_op_ui32_sub() {
    u64 a = sivm_stack_pop();
    u64 b = sivm_stack_pop();
    sivm_stack_push(a - b);
}

void sivm_op_ui32_mul() {
    u64 a = sivm_stack_pop();
    u64 b = sivm_stack_pop();
    sivm_stack_push(a * b);
}

void sivm_op_ui32_div() {
    u64 a = sivm_stack_pop();
    u64 b = sivm_stack_pop();
    sivm_stack_push(a / b);
}

void sivm_init() {
    sivm_stack = malloc(sizeof(u64) * SIVM_STACK_CAPACITY);
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
        if (SIVM_DEBUG)
            printf("0x%.2X @ 0x%.8lX %s\n", opcode, program_counter, sivm_instr_names[opcode]);

        if (opcode == 0x00)
            sivm_op_syscall();

        else if (opcode == 0x10)
            sivm_op_push();
        else if (opcode == 0x11)
            sivm_op_dup();
        else if (opcode == 0x12)
            sivm_op_rand();

        // else if (opcode == 0x21)
        //     sivm_op_jump();
        // else if (opcode == 0x40)
        //     sivm_op_alloc();
        // else if (opcode == 0x50)
        //     sivm_op_ui32_add();
        // else if (opcode == 0x51)
        //     sivm_op_ui32_sub();
        // else if (opcode == 0x52)
        //     sivm_op_ui32_div();
        // else if (opcode == 0x53)
        //     sivm_op_ui32_mul();
        
        else
            printf("unknown opcode (0x%.2X)\n", opcode);

        opcode = sivm_fetch8();
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        puts("Simple Virtual machine\nDeveloped by Luke_\n");
        char logo[] =
            "##########           \n"
            "#   ##   # # # ## ## \n"
            "# ##### ## # # ## ## \n"
            "#   ### ## # # # # # \n"
            "### ### ##  #  #   # \n"
            "#   ##   #  #  #   # \n"
            "##########           \n";

        for (int i = 0; i < sizeof(logo); i++) {
            char logo_char = logo[i];

            if (logo_char == '#') {
                printf(COLOR_BLUE COLOR_BG_BLUE "  ");
            } else if (logo_char == ' ') {
                printf(COLOR_WHITE COLOR_BG_WHITE "  ");
            } else {
                printf(COLOR_NORMAL "%c", logo_char);
            }
        }

        printf(COLOR_RED COLOR_BG_RED "");
        puts("");

    } else {
        srand(time(0));
        char* file_name = argv[1];
        sivm_init();
        sivm_load_program(file_name);
        sivm_run_program();
    }

    return 0;
}