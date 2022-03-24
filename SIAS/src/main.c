#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../../libraries/color.h"

#define true 1
#define false 0

typedef struct {
	char* buffer;
	size_t length;
} string_buffer;

int sias_str_is_instruction(char* str) {
    return
        strcmp(str, "syscall") == 0 ||
        strcmp(str, "dynamic_load") == 0 ||

        strcmp(str, "push") == 0 ||
        strcmp(str, "dup") == 0 ||
        strcmp(str, "rand") == 0 ||
        strcmp(str, "swap") == 0 ||
        strcmp(str, "cycle") == 0 ||
        strcmp(str, "pop") == 0 ||

        strcmp(str, "cjump") == 0 ||
        strcmp(str, "jump") == 0 ||
        strcmp(str, "call") == 0 ||
        strcmp(str, "return") == 0 ||

        strcmp(str, "write8") == 0 ||
        strcmp(str, "write16") == 0 ||
        strcmp(str, "write32") == 0 ||
        strcmp(str, "read8") == 0 ||
        strcmp(str, "read16") == 0 ||
        strcmp(str, "read32") == 0 ||

        strcmp(str, "alloc") == 0 ||
        strcmp(str, "free") == 0 ||
        strcmp(str, "realloc") == 0 ||

        strcmp(str, "eq") == 0 ||
        strcmp(str, "neq") == 0 ||
        strcmp(str, "less") == 0 ||
        strcmp(str, "more") == 0 ||

        strcmp(str, "u64_add") == 0 ||
        strcmp(str, "u64_sub") == 0 ||
        strcmp(str, "u64_mul") == 0 ||
        strcmp(str, "u64_div") == 0 ||
        strcmp(str, "u64_pow") == 0 ||
        strcmp(str, "u64_sqrt") == 0 ||
        strcmp(str, "u64_mod") == 0 ||

        strcmp(str, "u32_add") == 0 ||
        strcmp(str, "u32_sub") == 0 ||
        strcmp(str, "u32_mul") == 0 ||
        strcmp(str, "u32_div") == 0 ||
        strcmp(str, "u32_pow") == 0 ||
        strcmp(str, "u32_sqrt") == 0 ||
        strcmp(str, "u32_mod") == 0 ||

        strcmp(str, "u16_add") == 0 ||
        strcmp(str, "u16_sub") == 0 ||
        strcmp(str, "u16_mul") == 0 ||
        strcmp(str, "u16_div") == 0 ||
        strcmp(str, "u16_pow") == 0 ||
        strcmp(str, "u16_sqrt") == 0 ||
        strcmp(str, "u16_mod") == 0 ||

        strcmp(str, "u8_add") == 0 ||
        strcmp(str, "u8_sub") == 0 ||
        strcmp(str, "u8_mul") == 0 ||
        strcmp(str, "u8_div") == 0 ||
        strcmp(str, "u8_pow") == 0 ||
        strcmp(str, "u8_sqrt") == 0 ||
        strcmp(str, "u8_mod") == 0 ||

        strcmp(str, "i64_add") == 0 ||
        strcmp(str, "i64_sub") == 0 ||
        strcmp(str, "i64_mul") == 0 ||
        strcmp(str, "i64_div") == 0 ||
        strcmp(str, "i64_pow") == 0 ||
        strcmp(str, "i64_sqrt") == 0 ||
        strcmp(str, "i64_mod") == 0 ||

        strcmp(str, "i32_add") == 0 ||
        strcmp(str, "i32_sub") == 0 ||
        strcmp(str, "i32_mul") == 0 ||
        strcmp(str, "i32_div") == 0 ||
        strcmp(str, "i32_pow") == 0 ||
        strcmp(str, "i32_sqrt") == 0 ||
        strcmp(str, "i32_mod") == 0 ||

        strcmp(str, "i16_add") == 0 ||
        strcmp(str, "i16_sub") == 0 ||
        strcmp(str, "i16_mul") == 0 ||
        strcmp(str, "i16_div") == 0 ||
        strcmp(str, "i16_pow") == 0 ||
        strcmp(str, "i16_sqrt") == 0 ||
        strcmp(str, "i16_mod") == 0 ||

        strcmp(str, "i8_add") == 0 ||
        strcmp(str, "i8_sub") == 0 ||
        strcmp(str, "i8_mul") == 0 ||
        strcmp(str, "i8_div") == 0 ||
        strcmp(str, "i8_pow") == 0 ||
        strcmp(str, "i8_sqrt") == 0 ||
        strcmp(str, "i8_mod") == 0 ||

        strcmp(str, "f64_add") == 0 ||
        strcmp(str, "f64_sub") == 0 ||
        strcmp(str, "f64_mul") == 0 ||
        strcmp(str, "f64_div") == 0 ||
        strcmp(str, "f64_pow") == 0 ||
        strcmp(str, "f64_sqrt") == 0 ||

        strcmp(str, "f32_add") == 0 ||
        strcmp(str, "f32_sub") == 0 ||
        strcmp(str, "f32_mul") == 0 ||
        strcmp(str, "f32_div") == 0 ||
        strcmp(str, "f32_pow") == 0 ||
        strcmp(str, "f32_sqrt") == 0 ||

        strcmp(str, "f16_add") == 0 ||
        strcmp(str, "f16_sub") == 0 ||
        strcmp(str, "f16_mul") == 0 ||
        strcmp(str, "f16_div") == 0 ||
        strcmp(str, "f16_pow") == 0 ||
        strcmp(str, "f16_sqrt") == 0 ||

        strcmp(str, "f8_add") == 0 ||
        strcmp(str, "f8_sub") == 0 ||
        strcmp(str, "f8_mul") == 0 ||
        strcmp(str, "f8_div") == 0 ||
        strcmp(str, "f8_pow") == 0 ||
        strcmp(str, "f8_sqrt") == 0 ||
        
        strcmp(str, "bytes") == 0;
}

char* replace(const char *in, const char *pattern, const char *by) {
    size_t outsize = strlen(in) + 1;

    char *res = malloc(outsize);

    // use this to iterate over the output
    size_t resoffset = 0;

    char *needle;
    while (needle = strstr(in, pattern)) {
        // copy everything up to the pattern
        memcpy(res + resoffset, in, needle - in);
        resoffset += needle - in;

        // skip the pattern in the input-string
        in = needle + strlen(pattern);

        // adjust space for replacement
        outsize = outsize - strlen(pattern) + strlen(by);
        res = realloc(res, outsize);

        // copy the pattern
        memcpy(res + resoffset, by, strlen(by));
        resoffset += strlen(by);
    }

    // copy the remaining input
    strcpy(res + resoffset, in);

    return res;
}

string_buffer sias_read_file_content(char* file_name) {
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
    unsigned char *buffer = (unsigned char *) malloc(size);

    if(fread(buffer, sizeof *buffer, size, fp) != size) {
        printf("[ERROR] while reading file: %s", file_name);
        exit(1);
    }

    fclose(fp);

    string_buffer ret = {0};
    ret.buffer = buffer;
    ret.length = size;

    return ret;
}

typedef enum {
    SIAS_TOKEN_INSTRUCTION,
    SIAS_TOKEN_U_INTEGER,
    SIAS_TOKEN_STRING,
    SIAS_TOKEN_MARKER,
    SIAS_TOKEN_KEYWORD
} sias_token_type;

typedef struct {
   sias_token_type type;
   size_t line_found;
   size_t col_found;

   union {
        char* string_value;
        uint64_t uint64_value;
   };
} sias_token;

typedef struct {
    sias_token* tokens;
    size_t token_count;
} sias_parse_result;

sias_parse_result sias_parse_source_code(string_buffer source_code) {
    // Initialize dynamic memory
    size_t token_capacity = 100;
    size_t token_length = 0;
    sias_token* tokens = malloc(sizeof(sias_token) * token_capacity);

    size_t acc_capacity = 100;
    size_t acc_length = 0;
    char* acc = malloc(sizeof(char) * acc_capacity);

    // Storage for line number and column
    size_t current_line = 1;
    size_t current_col = 1;

    char string_mode = false;

    // Iterate over the source code
    for (size_t reading_index = 0; reading_index < source_code.length; reading_index++) {
        // Get the current character in the source code
        char current_character = source_code.buffer[reading_index];

        if (current_character == '\r')
            continue;

        // Handle keeping track of current line and column
        ++current_col;
        if (current_character == '\n') {
            ++current_line;
            current_col = 1;
        }

        // Handle strings
        if (!string_mode && current_character == '"') {
            string_mode = true;
            continue;
        } else if (string_mode) {
            if (current_character == '"') {
                
                // Add \0 to acc
                acc[acc_length++] = '\0';

                // Create token
                sias_token tok = {
                    .line_found = current_line,
                    .col_found = current_col,
                    .type = SIAS_TOKEN_STRING,
                    .string_value = replace(acc, "\\n", "\n")
                };

                tokens[token_length++] = tok;
                
                acc = malloc(sizeof(char) * 100);
                acc_capacity = 100;
                acc_length = 0;
                
                string_mode = false;
                
                continue;
            } else {
                acc[acc_length++] = current_character;
                continue;
            }
        }

        // Handle comments
        if (current_character == ';') {
            // Store the current token if needed
            if (acc_length > 0) {
                sias_token tok = {
                    .line_found = current_line,
                    .col_found = current_col
                };

                acc[acc_length++] = '\0';

                char first_character = acc[0];

                if (first_character >= '0' && first_character <= '9') {
                    tok.type = SIAS_TOKEN_U_INTEGER;
                    tok.uint64_value = strtoull(acc, NULL, 10);
                } else {
                    tok.type = SIAS_TOKEN_INSTRUCTION;
                    tok.string_value = acc;
                }

                tokens[token_length++] = tok;
                
                acc = malloc(sizeof(char) * 100);
                acc_capacity = 100;
                acc_length = 0;
            }

            // Continue until new line or EOF
            while(current_character != '\n' && reading_index < source_code.length) {
                current_character = source_code.buffer[++reading_index];
            }

            continue;
        }

        // Check if end of token
        if ((current_character == ' ' || current_character == '\n' || current_character == '\t') && acc_length > 0) {
            sias_token tok = {
                .line_found = current_line,
                .col_found = current_col
            };

            acc[acc_length++] = '\0';

            char first_character = acc[0];

            if (first_character >= '0' && first_character <= '9') {
                tok.type = SIAS_TOKEN_U_INTEGER;
                tok.uint64_value = strtoull(acc, NULL, 10);
            } else {
                if (sias_str_is_instruction(acc))
                    tok.type = SIAS_TOKEN_INSTRUCTION;
                else
                    tok.type = SIAS_TOKEN_MARKER;
                tok.string_value = acc;
            }

            tokens[token_length++] = tok;
                
            acc = malloc(sizeof(char) * 100);
            acc_capacity = 100;
            acc_length = 0;

            continue;
        }

        if (current_character == ' ' || current_character == '\t' || current_character == '\n')
            continue;

        // Store the character
        acc[acc_length++] = current_character;
    }

    

    // Check if there is a token left in the temp buffer
    if (acc_length > 0) {
        sias_token tok = {
            .line_found = current_line,
            .col_found = current_col
        };

        acc[acc_length++] = '\0';

        char first_character = acc[0];

        if (first_character >= '0' && first_character <= '9') {
            tok.type = SIAS_TOKEN_U_INTEGER;
            tok.uint64_value = strtoull(acc, NULL, 10);
        } else {
            if (sias_str_is_instruction(acc))
                tok.type = SIAS_TOKEN_INSTRUCTION;
            else
                tok.type = SIAS_TOKEN_MARKER;
            tok.string_value = acc;
        }

        tokens[token_length++] = tok;
    }

   // Print how many tokens got parsed
//    printf("Tokens parsed: %ld\n\n", token_length);

//     for (int i = 0; i < token_length; i++) {
//         sias_token tok = tokens[i];

//         printf("Token %d\n", i);

//         if (tok.type == SIAS_TOKEN_INSTRUCTION) {
//             puts(" - TYPE: Instruction");
//             printf(" - VALUE: %s", tok.string_value);
//         } else if (tok.type == SIAS_TOKEN_MARKER) {
//             puts(" - TYPE: Marker");
//             printf(" - VALUE: \"%s\"", tok.string_value);
//         } else if (tok.type == SIAS_TOKEN_U_INTEGER) {
//             puts(" - TYPE: Unsigned integer");
//             printf(" - VALUE: %ld", tok.uint64_value);
//         } else if (tok.type == SIAS_TOKEN_STRING) {
//             puts(" - TYPE: String");
//             printf(" - VALUE: \"%s\"", tok.string_value);
//         } else { 
//             puts(" - TYPE: Unkown");
//             puts(" - VALUE: Unknown");
//         }

//         puts("\n");
//     }

    // Create and return the parse result
    sias_parse_result result = {
        .tokens = tokens,
        .token_count = token_length
    };

    return result;
}

void sias_generate_bytecode(sias_parse_result parse_result, char* file_name) {
    size_t bytecode_length = 0;
    size_t bytecode_capacity = 200;
    char* bytecode = malloc((sizeof (char)) * bytecode_capacity);

    sias_token* tokens = parse_result.tokens;
    size_t tokens_count = parse_result.token_count;

    // for (int i = 0; i < tokens_count; i++) {
    //     sias_token tok = tokens[i];

    //     printf("Token %d\n", i);

    //     if (tok.type == SIAS_TOKEN_INSTRUCTION) {
    //         puts(" - TYPE: Instruction");
    //         printf(" - VALUE: %s", tok.string_value);
    //     } else if (tok.type == SIAS_TOKEN_MARKER) {
    //         puts(" - TYPE: Marker");
    //         printf(" - VALUE: \"%s\"", tok.string_value);
    //     } else if (tok.type == SIAS_TOKEN_U_INTEGER) {
    //         puts(" - TYPE: Unsigned integer");
    //         printf(" - VALUE: %ld", tok.uint64_value);
    //     } else if (tok.type == SIAS_TOKEN_STRING) {
    //         puts(" - TYPE: String");
    //         printf(" - VALUE: \"%s\"", tok.string_value);
    //     } else { 
    //         puts(" - TYPE: Unkown");
    //         puts(" - VALUE: Unknown");
    //     }

    //     puts("\n");
    // }

    for (int i = 0; i < tokens_count; i++) {
        sias_token tok = tokens[i];

        printf("now at type %d", tok.type);

        if (tok.type == SIAS_TOKEN_INSTRUCTION) {
            // Miscelaneous
            if (strcmp(tok.string_value, "syscall") == 0) {
                bytecode[bytecode_length++] = 0x00;
            } else if (strcmp(tok.string_value, "dynamic_load") == 0) {
                bytecode[bytecode_length++] = 0x01;
            } else if (strcmp(tok.string_value, "alloc") == 0) {
                bytecode[bytecode_length++] = 0x02;
            } else if (strcmp(tok.string_value, "free") == 0) {
                bytecode[bytecode_length++] = 0x03;
            } else if (strcmp(tok.string_value, "realloc") == 0) {
                bytecode[bytecode_length++] = 0x04;
            
            // Stack
            } else if (strcmp(tok.string_value, "push") == 0) {
                puts("test");
                bytecode[bytecode_length++] = 0x10;

                // Handle arguments
                tok = tokens[++i];

                if (tok.type != SIAS_TOKEN_U_INTEGER) {
                    printf("[ERROR] Expected integer value after 'push' operation at %s:%ld:%ld\n", file_name, tok.line_found, tok.col_found);
                    exit(1);
                }

                uint64_t arg1 = tok.uint64_value;

                bytecode[bytecode_length++] = (char) ((arg1 >> 56) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 48) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 40) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 32) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 24) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 16) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 8) & 0xff);
                bytecode[bytecode_length++] = (char) arg1;
            } else if (strcmp(tok.string_value, "dup") == 0) {
                bytecode[bytecode_length++] = 0x11;
            } else if (strcmp(tok.string_value, "rand") == 0) {
                bytecode[bytecode_length++] = 0x12;
            } else if (strcmp(tok.string_value, "swap") == 0) {
                bytecode[bytecode_length++] = 0x13;
            } else if (strcmp(tok.string_value, "cycle") == 0) {
                bytecode[bytecode_length++] = 0x14;
            } else if (strcmp(tok.string_value, "pop") == 0) {
                bytecode[bytecode_length++] = 0x15;

            // Controll flow & equality & bitwise
            } else if (strcmp(tok.string_value, "cjump") == 0) {
                bytecode[bytecode_length++] = 0x20;

                // Handle arguments
                tok = tokens[++i];

                if (tok.type != SIAS_TOKEN_U_INTEGER) {
                    printf("[ERROR] Expected integer value after 'push' operation at %s:%ld:%ld\n", file_name, tok.line_found, tok.col_found);
                    exit(1);
                }

                uint64_t arg1 = tok.uint64_value;

                bytecode[bytecode_length++] = (char) ((arg1 >> 56) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 48) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 40) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 32) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 24) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 16) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 8) & 0xff);
                bytecode[bytecode_length++] = (char) arg1;
            } else if (strcmp(tok.string_value, "jump") == 0) {
                bytecode[bytecode_length++] = 0x21;

                // Handle arguments
                tok = tokens[++i];

                if (tok.type != SIAS_TOKEN_U_INTEGER) {
                    printf("[ERROR] Expected integer value after 'push' operation at %s:%ld:%ld\n", file_name, tok.line_found, tok.col_found);
                    exit(1);
                }

                uint64_t arg1 = tok.uint64_value;

                bytecode[bytecode_length++] = (char) ((arg1 >> 56) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 48) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 40) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 32) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 24) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 16) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 8) & 0xff);
                bytecode[bytecode_length++] = (char) arg1;
            } else if (strcmp(tok.string_value, "call") == 0) {
                bytecode[bytecode_length++] = 0x22;

                // Handle arguments
                tok = tokens[++i];

                if (tok.type != SIAS_TOKEN_U_INTEGER) {
                    printf("[ERROR] Expected integer value after 'push' operation at %s:%ld:%ld\n", file_name, tok.line_found, tok.col_found);
                    exit(1);
                }

                uint64_t arg1 = tok.uint64_value;

                bytecode[bytecode_length++] = (char) ((arg1 >> 56) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 48) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 40) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 32) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 24) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 16) & 0xff);
                bytecode[bytecode_length++] = (char) ((arg1 >> 8) & 0xff);
                bytecode[bytecode_length++] = (char) arg1;
            } else if (strcmp(tok.string_value, "return") == 0) {
                bytecode[bytecode_length++] = 0x23;

            } else if (strcmp(tok.string_value, "eq") == 0) {
                bytecode[bytecode_length++] = 0x24;
            } else if (strcmp(tok.string_value, "neq") == 0) {
                bytecode[bytecode_length++] = 0x25;
            } else if (strcmp(tok.string_value, "less") == 0) {
                bytecode[bytecode_length++] = 0x26;
            } else if (strcmp(tok.string_value, "more") == 0) {
                bytecode[bytecode_length++] = 0x27;
            } else if (strcmp(tok.string_value, "and") == 0) {
                bytecode[bytecode_length++] = 0x28;
            } else if (strcmp(tok.string_value, "or") == 0) {
                bytecode[bytecode_length++] = 0x29;
            } else if (strcmp(tok.string_value, "xor") == 0) {
                bytecode[bytecode_length++] = 0x2a;
            } else if (strcmp(tok.string_value, "nor") == 0) {
                bytecode[bytecode_length++] = 0x2b;

            // Heap memory read/write
            } else if (strcmp(tok.string_value, "write8") == 0) {
                bytecode[bytecode_length++] = 0x30;
            } else if (strcmp(tok.string_value, "write16") == 0) {
                bytecode[bytecode_length++] = 0x31;
            } else if (strcmp(tok.string_value, "write32") == 0) {
                bytecode[bytecode_length++] = 0x32;
            } else if (strcmp(tok.string_value, "read8") == 0) {
                bytecode[bytecode_length++] = 0x33;
            } else if (strcmp(tok.string_value, "read16") == 0) {
                bytecode[bytecode_length++] = 0x34;
            } else if (strcmp(tok.string_value, "read32") == 0) {
                bytecode[bytecode_length++] = 0x35;

            // ui64 math
            } else if (strcmp(tok.string_value, "u64_add") == 0) {
                bytecode[bytecode_length++] = 0x40;
            } else if (strcmp(tok.string_value, "u64_sub") == 0) {
                bytecode[bytecode_length++] = 0x41;
            } else if (strcmp(tok.string_value, "u64_mul") == 0) {
                bytecode[bytecode_length++] = 0x42;
            } else if (strcmp(tok.string_value, "u64_div") == 0) {
                bytecode[bytecode_length++] = 0x43;
            } else if (strcmp(tok.string_value, "u64_pow") == 0) {
                bytecode[bytecode_length++] = 0x44;
            } else if (strcmp(tok.string_value, "u64_sqrt") == 0) {
                bytecode[bytecode_length++] = 0x45;
            } else if (strcmp(tok.string_value, "u64_mod") == 0) {
                bytecode[bytecode_length++] = 0x46;

            // ui32 math
            } else if (strcmp(tok.string_value, "u32_add") == 0) {
                bytecode[bytecode_length++] = 0x50;
            } else if (strcmp(tok.string_value, "u32_sub") == 0) {
                bytecode[bytecode_length++] = 0x51;
            } else if (strcmp(tok.string_value, "u32_mul") == 0) {
                bytecode[bytecode_length++] = 0x52;
            } else if (strcmp(tok.string_value, "u32_div") == 0) {
                bytecode[bytecode_length++] = 0x53;
            } else if (strcmp(tok.string_value, "u32_pow") == 0) {
                bytecode[bytecode_length++] = 0x54;
            } else if (strcmp(tok.string_value, "u32_sqrt") == 0) {
                bytecode[bytecode_length++] = 0x55;
            } else if (strcmp(tok.string_value, "u32_mod") == 0) {
                bytecode[bytecode_length++] = 0x56;

            // ui16 math
            } else if (strcmp(tok.string_value, "u16_add") == 0) {
                bytecode[bytecode_length++] = 0x60;
            } else if (strcmp(tok.string_value, "u16_sub") == 0) {
                bytecode[bytecode_length++] = 0x61;
            } else if (strcmp(tok.string_value, "u16_mul") == 0) {
                bytecode[bytecode_length++] = 0x62;
            } else if (strcmp(tok.string_value, "u16_div") == 0) {
                bytecode[bytecode_length++] = 0x63;
            } else if (strcmp(tok.string_value, "u16_pow") == 0) {
                bytecode[bytecode_length++] = 0x64;
            } else if (strcmp(tok.string_value, "u16_sqrt") == 0) {
                bytecode[bytecode_length++] = 0x65;
            } else if (strcmp(tok.string_value, "u16_mod") == 0) {
                bytecode[bytecode_length++] = 0x66;

            // ui8 math
            } else if (strcmp(tok.string_value, "u8_add") == 0) {
                bytecode[bytecode_length++] = 0x70;
            } else if (strcmp(tok.string_value, "u8_sub") == 0) {
                bytecode[bytecode_length++] = 0x71;
            } else if (strcmp(tok.string_value, "u8_mul") == 0) {
                bytecode[bytecode_length++] = 0x72;
            } else if (strcmp(tok.string_value, "u8_div") == 0) {
                bytecode[bytecode_length++] = 0x73;
            } else if (strcmp(tok.string_value, "u8_pow") == 0) {
                bytecode[bytecode_length++] = 0x74;
            } else if (strcmp(tok.string_value, "u8_sqrt") == 0) {
                bytecode[bytecode_length++] = 0x75;
            } else if (strcmp(tok.string_value, "u8_mod") == 0) {
                bytecode[bytecode_length++] = 0x76;

            // i64 math
            } else if (strcmp(tok.string_value, "i64_add") == 0) {
                bytecode[bytecode_length++] = 0x80;
            } else if (strcmp(tok.string_value, "i64_sub") == 0) {
                bytecode[bytecode_length++] = 0x81;
            } else if (strcmp(tok.string_value, "i64_mul") == 0) {
                bytecode[bytecode_length++] = 0x82;
            } else if (strcmp(tok.string_value, "i64_div") == 0) {
                bytecode[bytecode_length++] = 0x83;
            } else if (strcmp(tok.string_value, "i64_pow") == 0) {
                bytecode[bytecode_length++] = 0x84;
            } else if (strcmp(tok.string_value, "i64_sqrt") == 0) {
                bytecode[bytecode_length++] = 0x85;
            } else if (strcmp(tok.string_value, "i64_mod") == 0) {
                bytecode[bytecode_length++] = 0x86;

            // i32 math
            } else if (strcmp(tok.string_value, "i32_add") == 0) {
                bytecode[bytecode_length++] = 0x90;
            } else if (strcmp(tok.string_value, "i32_sub") == 0) {
                bytecode[bytecode_length++] = 0x91;
            } else if (strcmp(tok.string_value, "i32_mul") == 0) {
                bytecode[bytecode_length++] = 0x92;
            } else if (strcmp(tok.string_value, "i32_div") == 0) {
                bytecode[bytecode_length++] = 0x93;
            } else if (strcmp(tok.string_value, "i32_pow") == 0) {
                bytecode[bytecode_length++] = 0x94;
            } else if (strcmp(tok.string_value, "i32_sqrt") == 0) {
                bytecode[bytecode_length++] = 0x95;
            } else if (strcmp(tok.string_value, "i32_mod") == 0) {
                bytecode[bytecode_length++] = 0x96;

            // i16 math
            } else if (strcmp(tok.string_value, "i16_add") == 0) {
                bytecode[bytecode_length++] = 0xa0;
            } else if (strcmp(tok.string_value, "i16_sub") == 0) {
                bytecode[bytecode_length++] = 0xa1;
            } else if (strcmp(tok.string_value, "i16_mul") == 0) {
                bytecode[bytecode_length++] = 0xa2;
            } else if (strcmp(tok.string_value, "i16_div") == 0) {
                bytecode[bytecode_length++] = 0xa3;
            } else if (strcmp(tok.string_value, "i16_pow") == 0) {
                bytecode[bytecode_length++] = 0xa4;
            } else if (strcmp(tok.string_value, "i16_sqrt") == 0) {
                bytecode[bytecode_length++] = 0xa5;
            } else if (strcmp(tok.string_value, "i16_mod") == 0) {
                bytecode[bytecode_length++] = 0xa6;

            // i8 math
            } else if (strcmp(tok.string_value, "i8_add") == 0) {
                bytecode[bytecode_length++] = 0xb0;
            } else if (strcmp(tok.string_value, "i8_sub") == 0) {
                bytecode[bytecode_length++] = 0xb1;
            } else if (strcmp(tok.string_value, "i8_mul") == 0) {
                bytecode[bytecode_length++] = 0xb2;
            } else if (strcmp(tok.string_value, "i8_div") == 0) {
                bytecode[bytecode_length++] = 0xb3;
            } else if (strcmp(tok.string_value, "i8_pow") == 0) {
                bytecode[bytecode_length++] = 0xb4;
            } else if (strcmp(tok.string_value, "i8_sqrt") == 0) {
                bytecode[bytecode_length++] = 0xb5;
            } else if (strcmp(tok.string_value, "i8_mod") == 0) {
                bytecode[bytecode_length++] = 0xb6;

            // f64 math
            } else if (strcmp(tok.string_value, "f64_add") == 0) {
                bytecode[bytecode_length++] = 0xc0;
            } else if (strcmp(tok.string_value, "f64_sub") == 0) {
                bytecode[bytecode_length++] = 0xc1;
            } else if (strcmp(tok.string_value, "f64_mul") == 0) {
                bytecode[bytecode_length++] = 0xc2;
            } else if (strcmp(tok.string_value, "f64_div") == 0) {
                bytecode[bytecode_length++] = 0xc3;
            } else if (strcmp(tok.string_value, "f64_pow") == 0) {
                bytecode[bytecode_length++] = 0xc4;
            } else if (strcmp(tok.string_value, "f64_sqrt") == 0) {
                bytecode[bytecode_length++] = 0xc5;

            // f32 math
            } else if (strcmp(tok.string_value, "f32_add") == 0) {
                bytecode[bytecode_length++] = 0xd0;
            } else if (strcmp(tok.string_value, "f32_sub") == 0) {
                bytecode[bytecode_length++] = 0xd1;
            } else if (strcmp(tok.string_value, "f32_mul") == 0) {
                bytecode[bytecode_length++] = 0xd2;
            } else if (strcmp(tok.string_value, "f32_div") == 0) {
                bytecode[bytecode_length++] = 0xd3;
            } else if (strcmp(tok.string_value, "f32_pow") == 0) {
                bytecode[bytecode_length++] = 0xd4;
            } else if (strcmp(tok.string_value, "f32_sqrt") == 0) {
                bytecode[bytecode_length++] = 0xd5;

            // f16 math
            } else if (strcmp(tok.string_value, "f16_add") == 0) {
                bytecode[bytecode_length++] = 0xe0;
            } else if (strcmp(tok.string_value, "f16_sub") == 0) {
                bytecode[bytecode_length++] = 0xe1;
            } else if (strcmp(tok.string_value, "f16_mul") == 0) {
                bytecode[bytecode_length++] = 0xe2;
            } else if (strcmp(tok.string_value, "f16_div") == 0) {
                bytecode[bytecode_length++] = 0xe3;
            } else if (strcmp(tok.string_value, "f16_pow") == 0) {
                bytecode[bytecode_length++] = 0xe4;
            } else if (strcmp(tok.string_value, "f16_sqrt") == 0) {
                bytecode[bytecode_length++] = 0xe5;

            // f8 math
            } else if (strcmp(tok.string_value, "f8_add") == 0) {
                bytecode[bytecode_length++] = 0xf0;
            } else if (strcmp(tok.string_value, "f8_sub") == 0) {
                bytecode[bytecode_length++] = 0xf1;
            } else if (strcmp(tok.string_value, "f8_mul") == 0) {
                bytecode[bytecode_length++] = 0xf2;
            } else if (strcmp(tok.string_value, "f8_div") == 0) {
                bytecode[bytecode_length++] = 0xf3;
            } else if (strcmp(tok.string_value, "f8_pow") == 0) {
                bytecode[bytecode_length++] = 0xf4;
            } else if (strcmp(tok.string_value, "f8_sqrt") == 0) {
                bytecode[bytecode_length++] = 0xf5;
            
            
            } else if (strcmp(tok.string_value, "bytes") == 0) {
                tok = tokens[++i];
                char* arg1 = tok.string_value;

                size_t i = 0;
                while (*(arg1 + i) != '\0')
                    bytecode[bytecode_length++] = *(arg1 + i++);
            } else {
                printf("[ERROR] Unknown instruction at %s:%ld:%ld '%s'\n", file_name, tok.line_found, tok.col_found, tok.string_value);
                exit(1);
            }
        } else if (tok.type == SIAS_TOKEN_KEYWORD) {
            puts("KEYWORD");
        } else {
            char* tt_str = NULL;

            if (tok.type == SIAS_TOKEN_INSTRUCTION)
                tt_str = "Instruction";
            else if (tok.type == SIAS_TOKEN_KEYWORD)
                tt_str = "Keyword";
            else if (tok.type == SIAS_TOKEN_MARKER)
                tt_str = "Marker";
            else if (tok.type == SIAS_TOKEN_STRING)
                tt_str = "String";
            else if (tok.type == SIAS_TOKEN_U_INTEGER)
                tt_str = "Int";

            printf("[ERROR] Unexpected token of type %s\n%ld", tt_str, tok.uint64_value);
            exit(1);
        }
    }

    FILE *fp = fopen("output", "w");
    fwrite(bytecode, sizeof(char), bytecode_length, fp);
    fclose(fp);
}

typedef struct {
    char* marker_name;
    size_t byte_index;
} marker_position;

void sias_post_processor(sias_parse_result parse_result) {
    // Loop over tokens to gather marker locations
    size_t current_byte_index = 0;
    size_t marker_count = 0;
    size_t marker_capacity = 100;
    marker_position* markers = malloc(sizeof(marker_position) * marker_capacity);

    sias_token* tokens = parse_result.tokens;
    size_t tokens_count = parse_result.token_count;

    for (size_t i = 0; i < tokens_count; i++) {
        sias_token tok = tokens[i];
        
        if (tok.type == SIAS_TOKEN_INSTRUCTION && strcmp(tok.string_value, "bytes") != 0) {
            current_byte_index += 1;
        } else if (tok.type == SIAS_TOKEN_STRING) {
            current_byte_index += strlen(tok.string_value);
        } else if (tok.type == SIAS_TOKEN_U_INTEGER) {
            current_byte_index += 8;
        } else if (tok.type == SIAS_TOKEN_MARKER) {
            if (tok.string_value[strlen(tok.string_value) - 1] == ':') {
                tok.type = SIAS_TOKEN_MARKER;

                marker_position new_maker = {
                    .marker_name = tok.string_value,
                    .byte_index = current_byte_index
                };

                markers[marker_count++] = new_maker;
            } else {
                current_byte_index += 8;
            }
        }
    }

    // Loop over markers
    for (size_t i = 0; i < marker_count; i++) {
        marker_position mark = markers[i];
        printf("marker '%s' at byte index 0x%.2X\n", mark.marker_name, mark.byte_index);
    }

    // Loop over tokens to replace markers
    for (size_t i = 0; i < tokens_count; i++) {
        sias_token* tok = tokens + i;
        
        if (tok->type == SIAS_TOKEN_MARKER && tok->string_value[strlen(tok->string_value) - 1] != ':') {

            // Try to find marker
            marker_position* found_mark = NULL;
            for (size_t i = 0; i < marker_count; i++) {
                marker_position* mark = &markers[i];

                if (strcmp(tok->string_value, mark->marker_name) == 0) {
                    found_mark = mark;
                    break;
                }
            }

            if (found_mark != NULL) {
                tok->type = SIAS_TOKEN_U_INTEGER;
                tok->uint64_value = found_mark->byte_index;
            }
        }
    }
}

void sias_assembler(char argc, char* argv[]) {
    // Get the file name from the arguments
	char* file_name = argv[1];

    // Read the file into a file buffer
	string_buffer file_content = sias_read_file_content(file_name);

    // Parse the source code
    sias_parse_result tokens = sias_parse_source_code(file_content);

    // Post processor
    // - figures out label location
    // - label replacement
    sias_post_processor(tokens);

    // Generate the output
    sias_generate_bytecode(tokens, file_name);
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		puts("Simple assembler, assembler for the Simple Virtual Machine\nDeveloped by Luke_\n");

        // printf(COLOR_WHITE COLOR_BG_GREEN COLOR_BOLD " SI ");
        // printf(COLOR_GREEN COLOR_BG_WHITE COLOR_BOLD " AS \n");

        char logo[] =
            "##########          \n"
            "#   ##   # ### ###  \n"
            "# ##### ## # # #    \n"
            "#   ### ## ### ###  \n"
            "### ### ## # #   #  \n"
            "#   ##   # # # ###  \n"
            "##########          \n";

        for (int i = 0; i < sizeof(logo); i++) {
            char logo_char = logo[i];

            if (logo_char == '#') {
                printf(COLOR_GREEN COLOR_BG_GREEN "  ");
            } else if (logo_char == ' ') {
                printf(COLOR_WHITE COLOR_BG_WHITE "  ");
            } else {
                printf(COLOR_NORMAL "%c", logo_char);
            }
        }
        puts(COLOR_NORMAL "");
    } else {
		sias_assembler(argc, argv);
    }

	return 0;
}