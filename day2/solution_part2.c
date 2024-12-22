#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Read the file into allocated memory.
// Return NULL on error.
char* readfile(FILE *f) {
    // f invalid? fseek() fail?
    if (f == NULL || fseek(f, 0, SEEK_END)) {
        return NULL;
    }

    long length = ftell(f);
    rewind(f);
    // Did ftell() fail?  Is the length too long?
    if (length == -1 || (unsigned long) length >= SIZE_MAX) {
        return NULL;
    }

    // Convert from long to size_t
    size_t ulength = (size_t) length;
    char *buffer = malloc(ulength + 1);
    // Allocation failed? Read incomplete?
    if (buffer == NULL || fread(buffer, 1, ulength, f) != ulength) {
        free(buffer);
        return NULL;
    }
    buffer[ulength] = '\0'; // Now buffer points to a string

    return buffer;
}

int check_level(long *level) {
    /* check a level for whether its save or not
     * args:
     *     level int: pointer to list of 5 ints
     * returns: 
     *     bool: whether level is safe
     * */
    int i;
    int previous = -1;
    int increasing = -1;
    int difference;
    for (i = 0; i < 10; i++) {
        /*printf("previous %d, level[i] %ld;  ", previous, level[i]);*/
        
        if (level[i] == -1) continue;

        if (previous != -1) {
            if (increasing == -1) {
                // if no increase had been reportet, calculate now
                if (previous < level[i]) {
                    increasing = 1;
                } else {
                    increasing = 0;
                }
            }
            // get absolute difference
            difference = level[i] - previous;
            if (difference < 0) {
                difference *= -1;
            }

            // if the absolute difference is greater 3 or they're the same number it's unsafe
            if (difference > 3 || difference == 0) {
                /*printf("bad diff %d at index %d\n",difference, i);*/
                return 0;
            }
            // if it first increased and then decreased or vice versa, it's unsafe
            if (increasing && previous > level[i] || !increasing && previous < level[i]) {
                /*printf("bad increment at index %d\n", i);*/
                return 0;
            } 
        }
        previous = level[i];
    }
    return 1;
}

int main(void) {
    FILE * f = fopen("./input.txt", "rb");
    long input_list[1000][10];
    int i, j;
    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 10; j++) {
            input_list[i][j] = -1;
        }
    }

    int list_index = 0;
    int level_index = 0;

    char *in_string = "";

    // get input file as string
    in_string = readfile(f);

    char *end = in_string;

    for (list_index = 0; list_index < 1000; list_index++) {
        /*printf("converting in level %d\n", list_index);*/
        level_index = 0;
        while (end[0] != '\n') {
            input_list[list_index][level_index++] = strtol(in_string, &end, 10);
            /*printf(" %ld", input_list[list_index][level_index - 1]);*/
            in_string = end;
        }
        /*printf("\n");*/
        end = &end[1];
    }

    int number_of_safe_reports = 0;
    int level_safety;
    int temp_int;

    for (list_index = 0; list_index < 1000; list_index++) {
        /*printf("current level");*/
        /*for (i = 0; i < 10; i++) {*/
        /*    printf(" %ld", input_list[list_index][i]);*/
        /*}*/
        /*printf("\n");*/
        level_safety = check_level(input_list[list_index]);
        if (level_safety) {
            number_of_safe_reports += check_level(input_list[list_index]);
        } else {
            for (i = 0; i < 10; i++) {
                if (input_list[list_index][i] == -1) continue;
                
                // store current index
                temp_int = input_list[list_index][i];
                // replace with -1
                input_list[list_index][i] = -1;
                // recheck level without index i
                level_safety = check_level(input_list[list_index]);
                // if safe, save and break loop
                if (level_safety) {
                    printf("redeemed level: ");
                    for (i = 0; i < 10; i++) {
                        printf(" %ld", input_list[list_index][i]);
                    }
                    printf("\n");

                    number_of_safe_reports++;
                    break;
                }
                // put stored number back
                input_list[list_index][i] = temp_int;
            }
        }
    }

    printf("there are %d safe reports.\n", number_of_safe_reports);
}
