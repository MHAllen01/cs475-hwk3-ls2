#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// Create the filePath string the size of the first args
	char filePath[strlen(argv[1])];

	if (argc == 2) {
		// We are in Mode 1

		// Get the file path
		strcpy(filePath, argv[1]);

		// See if the path is valid
		
		int valid = ActiveDirectory(filePath);

		if (valid == 0) {
			// Path is valid
			ScanDirectory(filePath);
		} else {
			// Path was invalid
			printf("Couldn't find directory: %s\n", filePath);
		}
	} else if (argc == 3) {
		// We are in Mode 2

		// Create the fileName String the size of the args
		char fileName[strlen(argv[2])];

		// Get the file path
		strcpy(filePath, argv[1]);

		// Get the file name
		strcpy(fileName, argv[2]);
		
		int valid = ActiveDirectory(filePath);

		if (valid == 0) {
			// Path is valid
			MatchFiles(filePath, fileName);
		} else {
			// Path was invalid
			printf("Couldn't find directory: %s\n", filePath);
		}
	} else if (argc <= 1) {
		printf("Please provide one or two more arguments.\n");
	} else if (argc > 3) {
		printf("You provided too many arguments.\n");
	}
	return 0;
}
