// SIDOC_Documentation
// struct for storing documentation articles
typedef struct SIDOC_Documentation {
  char* content;
  int   label_count;
  char* labels[10];
} SIDOC_Documentation;

// List of available documentation articles in SIDOC
SIDOC_Documentation docs[] = {
    {
        .labels = { "instructions", "instruction", "opcodes", "opcode" },
        .label_count = 4,
        .content =
            "The SI-Assembly language contains a bunch of instructions, each "
            "corresponding to a single-byte number representation in the "
            "bytecode.\n\n"

            "Whilst these instructions represented in numeric form (like 0x21) might seem "
            "completely random, the SIVM instruction set has quite a lot of "
            "structure to it.\n\n"

            "Each instruction contains 2 parts, one called the 'instruction group' (lets call that one A) "
            "and one called the 'instruction identifier' (lets call that one B). "
            "Every instruction is composed of both an instruction identifier, and an instruction group in the form of 0xAB\n\n"

            "In the case of instruction 0x43, the instruction group would be 4 (u64 math) and the instruction identifier would be 3 (meaning it is an u64_div instruction).\n\n"

            "Here is a list of all the instruction groups:\n"

            "0x0. = Miscelaneous\n"
            "0x1. = Stack operations\n"
            "0x2. = Control flow\n"
            "0x3. = Heap read/write\n"
            "0x4. = u64 Math\n"
            "0x5. = u32 Math\n"
            "0x6. = u16 Math\n"
            "0x7. = u8 Math\n"
            "0x8. = i64 Math\n"
            "0x9. = i32 Math\n"
            "0xA. = i16 Math\n"
            "0xB. = i8 Math\n"
            "0xC. = f64 Math\n"
            "0xD. = f32 Math\n"
            "0xE. = f16 Math\n"
            "0xF. = f8 Math\n"
    },

    // Miscelaneous instructions
    {
        .labels = { "syscall", "0x00", "00" },
        .label_count = 3,
        .content =
            "syscall is a SIVM assembly instruction corresponding to the opcode 0x00 used for executing SIVM "
            "system calls, which can do various different things like priting, "
            "reading input, or creating a websocket\n\n"

            "The syscall instruction always needs at least 1 numeric argument "
            "which it pops from the stack and interprets as a u64 number. This "
            "number is then considered the 'syscall id', and each id corresponds "
            "to a different syscall.\n\n"

            "Some syscall id's need extra arguments, which they will then also "
            "pop off the stack, for example: the SYS_EXIT syscall needs 1 argument "
            "which is the exit code, we notate this like SYS_EXIT <exit_code>\n\n"

            "--- SYSCALL list ---\n"

            "0 - SYS_PRINT <string_pointer> <string_length>\n"
            "1 - SYS_EXIT <exit_code>\n\n"

            "--- Example ---\n"

            "// exit code\n"
            "push 7\n\n"

            "// SYS_EXIT\n"
            "push 0\n"
            "syscall\n\n"
            "// stack is now empty\n"
            "// program exists with code 7\n"
    },            

    // Stack manipulation instructions
    {
        .labels = { "push", "0x10", "10" },
        .label_count = 3,
        .content =
            "push is a SIVM assembly instruction corresponding to the opcode 0x10 used for pushing new items onto "
            "the stack, the instruction takes one single argument in the form of 8 "
            "bytes, this data will then be pushed onto the stack as a unsigned 64 "
            "bit integer."

            "\n\npush <8bytes - the data to be pushed>"

            "\n\nThis data can then later be used in the program as "
            "other data types, depending on what function you call, or what "
            "operation you use, for example: you can do floating point math with "
            "this data by using an instruction like f32_div to divide the data, as "
            "if it was a 32 bit float."

            "\n\n--- Example ---\n"

            "push 5\n"
            "// stack is now [5]\n"
    },
    {
        .labels = { "dup", "0x11", "11", "duplicate", "duplication" },
        .label_count = 3,
        .content =
            "dup is a SIVM assembly instruction corresponding to the opcode 0x11 used to duplicate data that is "
            "on the stack. The instruction takes no parameters, pops the top "
            "item of the stack into a temporary buffer, and then pushes it "
            "back twice."

            "\n\n--- Example ---\n"
            "push 5\n"
            "dup\n"
            "u32_add\n"
            "// stack is now [10]\n"
    },
    
    {
        .labels = { "rand", "0x12", "12", "random" },
        .label_count = 4,
        .content =
            "rand is a SIVM assembly instruction corresponding to the opcode 0x12 used to "
            "insert random data onto the stack, once this instruction is executed, a randomized"
            "64bit value is pushed onto the stack"

            "\n\n--- Example ---\n"
            "rand\n"
            "// stack is now [<random number>]\n"
    },

    /*
    // Miscellaneous instructions
    {
        .documentation_name = "syscall",
        .documentation_content = ""
    },
    {
        .documentation_name = "dynamic_load",
        .documentation_content = ""
    },
    {
        .documentation_name = "dynamic_load",
        .documentation_content = ""
    },

    // Control flow instructions
    {
        .documentation_name = "cskip",
        .documentation_content = ""
    },
    {
        .documentation_name = "jump",
        .documentation_content = ""
    },
    {
        .documentation_name = "call",
        .documentation_content = ""
    },
    {
        .documentation_name = "return",
        .documentation_content = ""
    },

    // Heap read/write
    {
        .documentation_name = "write8",
        .documentation_content = ""
    },
    {
        .documentation_name = "write16",
        .documentation_content = ""
    },
    {
        .documentation_name = "write32",
        .documentation_content = ""
    },
    {
        .documentation_name = "write64",
        .documentation_content = ""
    },
    {
        .documentation_name = "read8",
        .documentation_content = ""
    },
    {
        .documentation_name = "read16",
        .documentation_content = ""
    },
    {
        .documentation_name = "read32",
        .documentation_content = ""
    },
    {
        .documentation_name = "read64",
        .documentation_content = ""
    },

    // Memory management instructions
    {
        .documentation_name = "alloc",
        .documentation_content = ""
    },
    {
        .documentation_name = "free",
        .documentation_content = ""
    },
    {
        .documentation_name = "realloc",
        .documentation_content = ""
    },

    // UI8 math instructions
    {
        .documentation_name = "ui8_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui8_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui8_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui8_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui8_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui8_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui8_mod",
        .documentation_content = ""
    },

    // UI16 math instructions
    {
        .documentation_name = "ui16_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui16_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui16_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui16_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui16_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui16_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui16_mod",
        .documentation_content = ""
    },

    // UI32 math instructions
    {
        .documentation_name = "ui32_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui32_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui32_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui32_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui32_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui32_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui32_mod",
        .documentation_content = ""
    },

    // UI64 math instructions
    {
        .documentation_name = "ui64_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui64_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui64_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui64_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui64_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui64_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "ui64_mod",
        .documentation_content = ""
    },

    // I8 math instructions
    {
        .documentation_name = "i8_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "i8_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "i8_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "i8_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "i8_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "i8_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "i8_mod",
        .documentation_content = ""
    },

    // I16 math instructions
    {
        .documentation_name = "i16_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "i16_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "i16_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "i16_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "i16_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "i16_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "i16_mod",
        .documentation_content = ""
    },

    // I32 math instructions
    {
        .documentation_name = "i32_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "i32_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "i32_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "i32_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "i32_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "i32_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "i32_mod",
        .documentation_content = ""
    },

    // I64 math instructions
    {
        .documentation_name = "i64_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "i64_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "i64_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "i64_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "i64_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "i64_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "i64_mod",
        .documentation_content = ""
    },

    // F8 math instructions
    {
        .documentation_name = "f8_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "f8_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "f8_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "f8_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "f8_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "f8_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "f8_mod",
        .documentation_content = ""
    },

    // F16 math instructions
    {
        .documentation_name = "f16_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "f16_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "f16_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "f16_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "f16_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "f16_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "f16_mod",
        .documentation_content = ""
    },

    // F32 math instructions
    {
        .documentation_name = "f32_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "f32_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "f32_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "f32_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "f32_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "f32_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "f32_mod",
        .documentation_content = ""
    },

    // F64 math instructions
    {
        .documentation_name = "f64_add",
        .documentation_content = ""
    },
    {
        .documentation_name = "f64_sub",
        .documentation_content = ""
    },
    {
        .documentation_name = "f64_div",
        .documentation_content = ""
    },
    {
        .documentation_name = "f64_mul",
        .documentation_content = ""
    },
    {
        .documentation_name = "f64_pow",
        .documentation_content = ""
    },
    {
        .documentation_name = "f64_sqrt",
        .documentation_content = ""
    },
    {
        .documentation_name = "f64_mod",
        .documentation_content = ""
    },*/
};