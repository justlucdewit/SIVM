#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../libraries/color.h"

#define MAX_MATCH_DISTANCE 100
#define MAX_MATCH_COUNT 5

typedef struct SIDOC_Documentation {
  char* documentation_name;
  char* documentation_content;
} SIDOC_Documentation;

typedef struct levenshtein_match {
  char* word;
  int distance;
} levenshtein_match;

int SIDOC_min(int a, int b) {
    return a < b ? a : b;
}

int min(int a, int b, int c) {
    if (a < b && a < c)
        return a;

    else if (b < a && b < c)
        return b;

    else
        return c;
}

SIDOC_Documentation docs[] = {
    {
        .documentation_name = "instruction",
        .documentation_content =
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
            

    // Stack manipulation instructions
    {
        .documentation_name = "push",
        .documentation_content =
            "push is a SIVM assembly instruction used for pushing new items onto "
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
            "push 7\n"
            "u32_add\n"
            "// stack is now [12]\n"
    },
    {
        .documentation_name = "dup",
        .documentation_content =
            "dup is a SIVM assembly instruction used to duplicate data that is "
            "on the stack. The instruction takes no parameters, pops the top "
            "item of the stack into a temporary buffer, and then pushes it "
            "back twice."

            "\n\n--- Example ---\n"
            "push 5\n"
            "dup\n"
            "u32_add\n"
            "// stack is now [10]\n"
    },
    /*
    {
        .documentation_name = "rand",
        .documentation_content = ""
    },

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
    },
};

int min(int a, int b, int c)
{   
    if(a <= b && a <= c)
    {
        return a;
    }
    else if(b <= a && b <= c)
    {
        return b;
    }
    else if(c <= a && c <= b)
    {
        return c;
    } else {
        return 0;
    }*/
};

int matchesMade = 0;
levenshtein_match best_matches[MAX_MATCH_COUNT];

void considerMatch(char* matchName, int lev_distance) {
	levenshtein_match newLevDist = {
		.word = matchName,
		.distance = lev_distance
	};

    // Just add it if it fits
    if (matchesMade < MAX_MATCH_COUNT)
        best_matches[matchesMade++] = newLevDist;

    
    // Only add it if its a better one
    else {
        for (int i = 0; i < SIDOC_min(matchesMade, MAX_MATCH_COUNT); i++) {
            levenshtein_match currentLevDist = best_matches[i];

            if (currentLevDist.distance > newLevDist.distance) {
                best_matches[i] = newLevDist;
				return;
			}
        }
    }
}

void printMatches() {
    for (int i = 0; i < matchesMade; i++) {
        levenshtein_match currentLevDist = best_matches[i];
        printf("%i) %s\n", i + 1, currentLevDist.word);
    }
}

int levenshtein_distance(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = min(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);
}

char* SIDOC_get_chosen_match() {
	int chosenIndex = 0;

	printf("\n> ");
	scanf("%d", &chosenIndex);

	if (chosenIndex > matchesMade || chosenIndex < 0) {
		puts("index given is not valid, aborting");
		exit(-1);
	}

	puts("");
	return best_matches[chosenIndex - 1].word;
}

char* SIDOC_get_doc(char* docName) {
    
    // Try to find an exact documentation math
    for (int i = 0; i < sizeof(docs) / sizeof(SIDOC_Documentation); i++) {
        SIDOC_Documentation currDoc = docs[i];
        
        if (strcmp(currDoc.documentation_name, docName) == 0) {
			printf("----- %s -----\n", docName);
            return currDoc.documentation_content;
		}
    }
    
    for (int i = 0; i < sizeof(docs) / sizeof(SIDOC_Documentation); i++) {
        SIDOC_Documentation currDoc = docs[i];
        
        int lev_distance = levenshtein_distance(docName, currDoc.documentation_name);
        
        if (lev_distance < MAX_MATCH_DISTANCE)
            considerMatch(currDoc.documentation_name, lev_distance);
    }

	// Guess what the doc couldve been
	puts("No exact match found, choose number of relevant doc:\n");
    printMatches();
	char* chosen_doc_name = SIDOC_get_chosen_match();

	// Try to find an exact documentation math
    for (int i = 0; i < sizeof(docs) / sizeof(SIDOC_Documentation); i++) {
        SIDOC_Documentation currDoc = docs[i];
        
        if (strcmp(currDoc.documentation_name, chosen_doc_name) == 0) {
			printf("----- %s -----\n", chosen_doc_name);
            return currDoc.documentation_content;
		}
    }
    
    return "";
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		puts("SI Documentation, documentation utility for the Simple Virtual Machine");
		puts("Developed by Luke_\n");

        // printf(COLOR_WHITE COLOR_BG_GREEN COLOR_BOLD " SI ");
        // printf(COLOR_GREEN COLOR_BG_WHITE COLOR_BOLD " AS \n");

        char logo[] =
            "##########             \n"
            "#   ##   # ##  ### ### \n"
            "# ##### ## # # # # #   \n"
            "#   ### ## # # # # #   \n"
            "### ### ## # # # # #   \n"
            "#   ##   # ##  ### ### \n"
            "##########             \n";

        for (int i = 0; i < sizeof(logo); i++) {
            char logo_char = logo[i];

            if (logo_char == '#') {
                printf(COLOR_BG_MAGENTA "  ");
            } else if (logo_char == ' ') {
                printf(COLOR_BG_WHITE "  ");
            } else {
                printf(COLOR_NORMAL "%c", logo_char);
            }
        }

        puts(COLOR_NORMAL "");
	} else {
		char* search_term = argv[1];
		char* doc_content = SIDOC_get_doc(search_term);
		
		puts(doc_content);
		return 0;
	}
}