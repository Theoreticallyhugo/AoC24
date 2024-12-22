
#include <iso646.h>
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

// Comparison function
int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int main(void) {
    // setup vars
    char *in_string = "";
    char *end;
    int list_index = 0;
    long left[1000];
    long left_clean[1000];
    long left_in_right_count[1000] = {0};
    long right[1000];
    FILE * f = fopen("./input.txt", "rb");

    // get input file as string
    in_string = readfile(f);
    /*printf("in: %s", in_string);*/
    
    // parse string to two lists of int
    while (list_index < 1000)
    {
        left[list_index] = strtol(in_string, &end, 10);
        in_string = end;
        right[list_index++] = strtol(in_string, &end, 10);
        in_string = end;
        /*printf("conversion; left: %ld; right: %ld\n", left[list_index - 1], right[list_index - 1]);*/
    }
    int i;
    int j;
    /*for (i = 0; i < 1000; i++) {*/
    /*    printf("left: %ld\n", left[i]);*/
    /*}*/

    // remove double occurrences by setting them to -1
    int first_found;  
    for (i = 0; i < 1000; i++) {
        // set to false to keep the first instance alive
        first_found = 0;
        left_clean[i] = left[i];
        for (j = 0; j < 1000; j++) {
            if (left[i] == left[j] && first_found) {
                // if the first had been found, this is a double
                left_clean[j] = -1;
            } else if (left[i] == left[j] && not first_found) {
                // if the first had not been found, this is a has to be kept alive
                first_found = 1;
            }
        }
    }
    for (i = 0; i < 1000; i++) {
        printf("left_clean: %ld\n", left_clean[i]);
    }

    // count occurrences
    for (i = 0; i < 1000; i++) {
        // skip cleaned values
        if (left_clean[i] == -1) continue;
        for (j = 0; j < 1000; j++) {
            if (left_clean[i] == right[j]) {
                left_in_right_count[i]++;
            } 
        }
    }

    int temp;
    long long sum = 0;
    for (i = 0; i < 1000; i++) {
        // skip cleaned values
        if (left_clean[i] == -1) continue;
        temp = left_clean[i] * left_in_right_count[i];
        /*printf("step %d with %ld %ld results in %d\n", i, left[i], right[i], temp);*/
        sum += temp;
    }

    // FIXME: this is wrong
    printf("total sum: %lld\n", sum);
}
