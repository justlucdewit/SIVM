#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef struct {
	char* buffer;
	size_t length;
} string_buffer;

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
    SIAS_TOKEN_STRING
} sias_token_type;

typedef struct {
   sias_token_type type;
   size_t line_found;
   size_t col_found;

   union {
        char* string_value;
        u_int32_t uint32_value;
   };
} sias_token;

typedef struct {
    sias_token* tokens;
    size_t token_count;
} sias_parse_result;

sias_parse_result sias_parse_source_code(string_buffer source_code) {
    // Initialize memory to store tokens
    size_t token_count = 0;
    size_t token_capacity = 100;
    sias_token* tokens = malloc((sizeof (sias_token)) * token_capacity);

    // Set up token memory
    size_t acc_count = 0;
    size_t acc_capacity = 100;
    char* acc = malloc(sizeof (char) * acc_capacity);

    // Storage for line number and column
    size_t current_line = 0;
    size_t current_col = 0;

    char string_mode = false;

    // Iterate over the source code
    for (size_t reading_index = 0; reading_index < source_code.length; reading_index++) {
        // Get the current character in the source code
        char current_character = source_code.buffer[reading_index];

        // Handle strings
        if (!string_mode && current_character == '"') {
            string_mode = true;
            continue;
        } else if (string_mode) {
            if (current_character == '"') {
                sias_token tok = { 0 };
                tok.line_found = current_line;
                tok.col_found = current_col;
                acc[acc_count] = '\0';
                tok.type = SIAS_TOKEN_STRING;
                tok.string_value = acc;
                tokens[token_count++] = tok;
                acc_count = 0;
                acc = malloc(sizeof (char) * acc_capacity);
                string_mode = false;
                continue;
            } else {
                acc[acc_count++] = current_character;
                continue;
            }
        }

        // Handle comments
        if (current_character == ';') {
            // Store the current token if needed
            if (acc_count > 0) {
                sias_token tok = { 0 };
                tok.line_found = current_line;
                tok.col_found = current_col;
                char first_character = acc[0];

                acc[acc_count] = '\0';

                if (first_character >= '0' && first_character <= '9') {
                    tok.type = SIAS_TOKEN_U_INTEGER;
                    tok.uint32_value = strtoul(acc, NULL, 10);
                } else {
                    tok.type = SIAS_TOKEN_INSTRUCTION;
                    tok.string_value = acc;
                }

                tokens[token_count++] = tok;
                acc_count = 0;
                acc = malloc(sizeof (char) * acc_capacity);
            }

            // Continue until new line or EOF
            while(current_character != '\n' && reading_index < source_code.length) {
                current_character = source_code.buffer[++reading_index];
            }

            continue;
        }

        // Check if end of token
        if ((current_character == ' ' || current_character == '\n') && acc_count > 0) {
            sias_token tok = { 0 };
            tok.line_found = current_line;
            tok.col_found = current_col;
            char first_character = acc[0];

            acc[acc_count] = '\0';

            if (first_character >= '0' && first_character <= '9') {
                tok.type = SIAS_TOKEN_U_INTEGER;
                tok.uint32_value = strtoul(acc, NULL, 10);
            } else {
                tok.type = SIAS_TOKEN_INSTRUCTION;
                tok.string_value = acc;
            }

            tokens[token_count++] = tok;
            acc_count = 0;
            acc = malloc(sizeof (char) * acc_capacity);
            continue;
        }

        if (current_character == ' ' || current_character == '\n')
            continue;

        // Store the character
        acc[acc_count++] = current_character;
    }

    // Check if there is a token left in the temp buffer
    if (acc_count > 0) {
        sias_token tok = { 0 };
        tok.type = SIAS_TOKEN_INSTRUCTION;
        acc[acc_count] = '\0';
        tok.string_value = acc;
        tokens[token_count++] = tok;
    }

    // Print how many tokens got parsed
//    printf("Tokens parsed: %ld\n\n", token_count);
//
//    for (int i = 0; i < token_count; i++) {
//        sias_token tok = tokens[i];
//
//        printf("Token %d\n", i);
//
//        if (tok.type == SIAS_TOKEN_INSTRUCTION) {
//            puts(" - TYPE: Instruction");
//            printf(" - VALUE: %s", tok.string_value);
//        } else if (tok.type == SIAS_TOKEN_U_INTEGER) {
//            puts(" - TYPE: Unsigned integer");
//            printf(" - VALUE: %d", tok.uint32_value);
//        } else if (tok.type == SIAS_TOKEN_STRING) {
//            puts(" - TYPE: String");
//            printf(" - VALUE: \"%s\"", tok.string_value);
//        } else {
//            puts(" - TYPE: Unkown");
//            puts(" - VALUE: Unknown");
//        }
//
//        puts("\n");
//    }

    // Create and return the parse result
    sias_parse_result parse_result = { 0 };
    parse_result.token_count = token_count;
    parse_result.tokens = tokens;
    return parse_result;
}

void sias_generate_bytecode(sias_parse_result tokens, char* file_name) {
    size_t bytecode_length = 0;
    size_t bytecode_capacity = 200;
    char* bytecode = malloc((sizeof (char)) * bytecode_capacity);

    for (int i = 0; i < tokens.token_count; i++) {
        sias_token tok = tokens.tokens[i];

        if (tok.type == SIAS_TOKEN_INSTRUCTION) {
            if (strcmp(tok.string_value, "syscall") == 0) {
                bytecode[bytecode_length++] = 0x00;
            } else if (strcmp(tok.string_value, "ui32_add") == 0) {
                bytecode[bytecode_length++] = 0x0c;
            } else if (strcmp(tok.string_value, "push") == 0) {
                bytecode[bytecode_length++] = 0x03;

                // Handle arguments
                tok = tokens.tokens[++i];
                u_int32_t arg1 = tok.uint32_value;

                bytecode[bytecode_length++] = (char) arg1 >> 24;
                bytecode[bytecode_length++] = (char) arg1 >> 16;
                bytecode[bytecode_length++] = (char) arg1 >> 8;
                bytecode[bytecode_length++] = (char) arg1;
            } else if (strcmp(tok.string_value, "bytes") == 0) {
                tok = tokens.tokens[++i];
                char* arg1 = tok.string_value;

                size_t i = 0;
                while (*(arg1 + i) != '\0')
                    bytecode[bytecode_length++] = *(arg1 + i++);
            } else {
                printf("[ERROR] Unknown instruction at %s:0:0 '%s'\n", file_name, tok.string_value);
                exit(1);
            }
        }
    }

    FILE *fp = fopen("output", "w");
    fwrite(bytecode, sizeof(char), bytecode_length, fp);
    fclose(fp);
}

void sias_assembler(char argc, char* argv[]) {
    // Get the file name from the arguments
	char* file_name = argv[1];

    // Read the file into a file buffer
	string_buffer file_content = sias_read_file_content(file_name);

    // Parse the source code
    sias_parse_result tokens = sias_parse_source_code(file_content);

    // Generate the output
    sias_generate_bytecode(tokens, file_name);
}

int main(int argc, char* argv[]) {
	if (argc <= 1)
		puts("Simple assembler, assembler for the Simple Virtual Machine\nDeveloped by Luke_");
	else
		sias_assembler(argc, argv);

	return 0;
}