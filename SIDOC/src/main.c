#include <stdio.h>
#include <string.h>

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

SIDOC_Documentation docs[] = {
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
    }
}

int matchesMade = 0;
levenshtein_match best_matches[MAX_MATCH_COUNT];

void considerMatch(char* matchName, int lev_distance) {
    // Just add it if it fits
    if (matchesMade < MAX_MATCH_COUNT) {
        levenshtein_match newLevDist = {
            .word = matchName,
            .distance = lev_distance
        };
        
        best_matches[matchesMade++] = newLevDist;
    }
    
    // Only add it if its a better one
    else if (0) {
        levenshtein_match newLevDist = {
            .word = matchName,
            .distance = lev_distance
        };

        for (int i = 0; i < SIDOC_min(matchesMade, MAX_MATCH_COUNT); i++) {
            levenshtein_match currentLevDist = best_matches[i];

            if (currentLevDist.distance > newLevDist.distance)
                best_matches[i] = newLevDist;
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

char* SIDOC_get_doc(char* docName) {
    
    // Try to find an exact documentation math
    for (int i = 0; i < sizeof(docs) / sizeof(SIDOC_Documentation); i++) {
        SIDOC_Documentation currDoc = docs[i];
        
        if (strcmp(currDoc.documentation_name, docName) == 0)
            return currDoc.documentation_content;
    }
    
    for (int i = 0; i < sizeof(docs) / sizeof(SIDOC_Documentation); i++) {
        SIDOC_Documentation currDoc = docs[i];
        
        int lev_distance = levenshtein_distance(docName, currDoc.documentation_name);
        
        if (lev_distance < MAX_MATCH_DISTANCE)
            considerMatch(currDoc.documentation_name, lev_distance);
    }

    printMatches();
    
    printf("no documentation named '%s' was found\n", docName);
    
    return "";
}

int main() {
    char* search_term = "pesh";
    char* doc_content = SIDOC_get_doc(search_term);
    printf("----- %s -----\n", search_term);
    puts(search_term);
    return 0;
}