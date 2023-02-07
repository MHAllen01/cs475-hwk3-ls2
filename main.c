#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "ls2.h"

int mode1 = 0; // Used to identify the mode we're in
int mode2 = 0; // Used to identify the mode we're in

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	char filePath[strlen(argv[1])];
	if (argc == 2) {
		// We are in Mode 1
		mode1 = 1;

		// Get the file path
		strcpy(filePath, argv[1]);

		// See if the path is valid
		ScanDirectory(filePath);
		int valid = ActiveDirectory(filePath);

		if (valid == 0) {
			// Path is valid
			
		} else {
			// Path was invalid
			printf("Couldn't find directory: %s\n", filePath);
		}
	} else if (argc == 3) {
		char fileName[strlen(argv[2])];
		// We are in Mode 2

		// Get the file path
		strcpy(filePath, argv[1]);

		strcpy(fileName, argv[2]);
		MatchFiles(filePath, fileName);
		mode2 = 1;
	} else if (argc <= 1) {
		printf("Please provide one or two more arguments.\n");
	} else if (argc > 3) {
		printf("You provided too many arguments.\n");
	}


	// stack stores the lines to print out
	// stack_t *s = initstack();

	// push(s, "Hello1");
	// push(s, "Hello2");
	// push(s, "Hello3");

	// // print stack
	// printstack(s);

	// // free up stack
	// freestack(s);
	// //free(filePath);
	return 0;
}
