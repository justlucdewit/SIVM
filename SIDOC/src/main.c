// Import STD libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Import 3rd party libraries
#include "../../libraries/color.h"

// Import headers
#include "./docs.h"

// List of documents (max 10)
// used to store all the docs that matched the search query
SIDOC_Documentation foundDocs[10];
int docsFoundCount = 0;

// Function to print out all of the docs that match the search query along with
// the indexes, so that later on the user can input the index to choose that
// article.
void printMatches() {
    for (int i = 0; i < docsFoundCount; i++) {
        SIDOC_Documentation currDoc = foundDocs[i];
        printf("%i) %s\n", i + 1, currDoc.labels[0]);
    }
}

// Input a numeric character to choose that article in the foundDocs array
// prints out the title of that document, and then returns the content to be
// printed
char* SIDOC_get_chosen_match() {
	int chosenIndex = 0;
	printf("\n> ");
	scanf("%d", &chosenIndex);

	if (chosenIndex > docsFoundCount || chosenIndex < 1) {
		puts("Invalid index given, aborting");
		exit(-1);
	}

	puts("");

    printf("----- %s -----\n", foundDocs[chosenIndex - 1].labels[0]);
	return foundDocs[chosenIndex - 1].content;
}

// Function to find an article given a search query, it either finds an exact
// match with one single documentation article, or it finds multiple, meaning
// it will let you choose using an index
char* SIDOC_get_doc(char* docName) {    
    // Try to find an exact documentation math
    for (int i = 0; i < sizeof(docs) / sizeof(SIDOC_Documentation); i++) {
        SIDOC_Documentation currDoc = docs[i];
        
        for (int j = 0; j < currDoc.label_count; j++) {
            char* currLabel = currDoc.labels[j];

            if (strcmp(currLabel, docName) == 0) {
			    foundDocs[docsFoundCount++] = currDoc;
		    }
        }
    }

    if (docsFoundCount == 0) {
        printf("no documentation found labled '%s'\n", docName);
        exit(1);
    } else if (docsFoundCount == 1) {
        SIDOC_Documentation doc = foundDocs[0];
        printf("----- %s -----\n", doc.labels[0]);
        return doc.content;
    } else {
        printMatches();
        return SIDOC_get_chosen_match();
    }
}

int main(int argc, char* argv[]) {

    // Print out the SI DOC logo when no args given
	if (argc <= 1) {
		puts("SI Documentation, documentation utility for the Simple Virtual Machine");
		puts("Developed by Luke_\n");

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

            if (logo_char == '#')
                printf(COLOR_BG_MAGENTA "  ");
            else if (logo_char == ' ')
                printf(COLOR_BG_WHITE "  ");
            else
                printf(COLOR_NORMAL "%c", logo_char);
        }

        puts(COLOR_NORMAL "");
	}
    
    // If search query given, use it to print out the documentation article
    else {
		char* search_term = argv[1];
		char* doc_content = SIDOC_get_doc(search_term);
		
		puts(doc_content);
		return 0;
	}
}