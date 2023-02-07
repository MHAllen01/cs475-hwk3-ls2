#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"


// TODO: function definitions here for ls2


/**
 * Checks to see if the entered filepath is valid directory
 * 
 * @param   *filePath   Pointer to the filePath String
 * @return  0           If the directory is valid. Otherwise, 1
*/
int ActiveDirectory(char *filePath) {
    if (opendir(filePath) != NULL) {
        // File path is valid
        return 0;
    } else {
        // File path is invalid
        return 1;
    }
    //closedir(filePath);
}

int indent = 0;

/**
 * Recursively checks the file path's contents and displays 
 * if an item is a directory or file (with byte information);
 * 
 * @param   *filePath   Pointer to the filePath String
*/
void ScanDirectory(char *filePath) {
    // Create directory stream and stat struct
    DIR *dir;
    struct dirent *stream;
    struct stat stats;

    // Future String for concatenated path
    char *newPath;

    // Open the directory
    dir = opendir(filePath);

    // Recursion handling
    while ((stream = readdir(dir))!= NULL) {
        // Dynamically allocate memory for a new path
        newPath = malloc (strlen(filePath) + strlen(stream->d_name) + 2);

        // Concatenate the new path
        strcpy(newPath, filePath);
        strcat(newPath, "/");
        strcat(newPath, stream->d_name);

        // lstat...
        lstat(newPath, &stats);
        
        // Check its type
        if (S_ISDIR(stats.st_mode)) {
            // It's a directory
            if (strcmp(stream->d_name, ".") != 0 && strcmp(stream->d_name, "..") != 0) {
                // Print the indent(s)
                for (int i=0; i<indent; i++) {
                    printf("\t");
                }

                // Increment the indent amount
                indent++;
                
                // Print the directory
                printf("%s/ (Directory)\n", stream->d_name);

                // Recursively scan again until NULL
                ScanDirectory(newPath);

                // Decrement the indent amount
                indent--;
            }
        } else if (S_ISREG(stats.st_mode)) {
            // It's a file

            // Print the indent(s)
            for (int i=0; i<indent; i++) {
                printf("\t");
            }
            printf("%s (%ld bytes)\n", stream->d_name, stats.st_size);
        }

        // Free the newPath memory
        free(newPath);
        
    }

    // Close the directory
    closedir(dir);
}

void MatchFiles(char *filePath, char *fileName) {
    // Create directory stream and stat struct
    DIR *dir;
    struct dirent *stream;
    struct stat stats;

    // Future String for concatenated path
    char *newPath;

    // Open the directory
    dir = opendir(filePath);

    // Recursion handling
    while ((stream = readdir(dir))!= NULL) {
        // Dynamically allocate memory for a new path
        newPath = malloc (strlen(filePath) + strlen(stream->d_name) + 2);

        // Concatenate the new path
        strcpy(newPath, filePath);
        strcat(newPath, "/");
        strcat(newPath, stream->d_name);

        // lstat...
        lstat(newPath, &stats);
        
        // Check its type
        if (S_ISDIR(stats.st_mode)) {
            // It's a directory
            if (strcmp(stream->d_name, ".") != 0 && strcmp(stream->d_name, "..") != 0) {
                // Check if this directory has the desired file
                char *checkPath = malloc(strlen(newPath) + strlen(fileName) + 2);
                strcpy(checkPath, newPath);
                strcat(checkPath, "/");
                strcat(checkPath, fileName);

                if (access(checkPath, F_OK) != -1) {
                    // Print the indent(s)
                    for (int i=0; i<indent; i++) {
                        printf("\t");
                    }

                    // Increment the indent amount
                    indent++;
                    
                    // Print the directory
                    printf("%s/ (Directory)\n", stream->d_name);

                    // Recursively scan again until NULL
                    MatchFiles(newPath, fileName);

                    // Decrement the indent amount
                    indent--;
                } else {
                    // Recursively scan the subdirectory
                    MatchFiles(newPath, fileName);
                }

                
                // Free the checkPath memory
                free(checkPath);
            }
        } else if (S_ISREG(stats.st_mode)) {
            // It's a file

            // Check if it's the desired file
            if (strcmp(stream->d_name, fileName) == 0) {
                // Print the indent(s)
                for (int i=0; i<indent; i++) {
                    printf("\t");
                }
                printf("%s (%ld bytes)\n", stream->d_name, stats.st_size);
            }
        }

        // Free the newPath memory
        free(newPath);
    }

    // Close the directory
    closedir(dir);
}
