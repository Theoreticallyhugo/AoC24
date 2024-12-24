/*
 * this is a breadth first iterative solution.
 * works well for 25, but breaks down at 49, for an input of 8 numbers
 * */
#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_BLINKS 25

typedef struct node *link;
struct node {
  long long item;
  link next;
};

void print_stones(link curr_stone) {
  /*
   * print all stones
   * */
  while (curr_stone->next != NULL) {
    curr_stone = curr_stone->next;
    printf("reading %lld\n", curr_stone->item);
  }
}

long long pow(long long base, long long exponent) {
  /*
   * takes a base and an exponend
   * returns the result
   * all as long
   * */
  long long i;
  long long result = 1;
  for (i = 0; i < exponent; i++) {
    result *= base;
  }
  return result;
}

long long count_digits(long long int_to_count) {
  /*
   * count the digits of a number (long)
   * return the result as int
   * */
  long long num_zeros = 0;
  /*printf("pow(%ld)\n", pow(10, 2));*/
  while (int_to_count / pow(10, num_zeros) > 0) {
    /*printf("%ld / 10^%ld = %ld / %ld = %ld ;   ", int_to_count, num_zeros,
     * int_to_count, pow(10, num_zeros), int_to_count / pow(10, num_zeros));*/
    /*printf("%ld has more than %ld digits\n", int_to_count, num_zeros);*/
    num_zeros++;
  }
  return num_zeros;
}

long long blink(link curr_stone) {
  /*
   * take the linked list of stones and "blink" once
   * */
  long long sum_stones = 0;
  long long num_digits;
  while (curr_stone->next != NULL) {
    sum_stones++;
    curr_stone = curr_stone->next;
    num_digits = count_digits(curr_stone->item);
    if (curr_stone->item == 0) {
      // 0 becomes 1
      curr_stone->item = 1;
      /*printf("encountered 0, changed to 1\n");*/
    } else if (num_digits % 2 == 0) {
      /*printf("encountered even number of digits %lld in %lld;  ", num_digits,*/
      /*       curr_stone->item);*/
      // is even number or digits, split
      //
      // create new link
      link temp_stone = malloc(sizeof *temp_stone);
      // right half of curr_stone goes to new link
      temp_stone->item =
          curr_stone->item - ((curr_stone->item / pow(10, (num_digits / 2))) *
                              pow(10, (num_digits / 2)));
      // left half of curr_stone goes to old link
      curr_stone->item = (curr_stone->item / pow(10, (num_digits / 2)));
      /*printf("left half: %lld;  ", curr_stone->item);*/
      /*printf("right half: %lld\n", temp_stone->item);*/
      // incorporate new link
      temp_stone->next = curr_stone->next;
      curr_stone->next = temp_stone;
      // skip new stone and add to sum for it
      curr_stone = temp_stone;
      sum_stones++;
      /*printf("even number of digits\n");*/
    } else {
      /*printf("else case with %lld", curr_stone->item);*/
      // otherwise, multiply by 2024
      curr_stone->item *= 2024;
      /*printf("now %lld\n", curr_stone->item);*/
    }
    /*printf("reading %d\n", curr_stone->item);*/
  }
  return sum_stones;
}

int main(int argc, char *argv[]) {
  /*
   * expect all args to be numbers
   * */ 
  long long initial[argc - 1];
  char *end;
  long long i;
  printf("%d inputs:", argc - 1);
  for (i=1; i < argc; i++) {
    initial[i-1] = (long long)strtol(argv[i], &end, 10);
    printf(" %lld", initial[i-1]);
  }
  printf("\n");
  link stones = malloc(sizeof *stones);
  stones->item = -1;
  link curr_stone = stones;
  /*stones->item = initial[0];*/
  /*stones->next = stones;*/
  for (i = 0; i < argc - 1; i++) {
    printf("adding %lld, with lenght %lld\n", initial[i], count_digits(initial[i]));
    // create new node
    curr_stone->next = malloc(sizeof *stones);
    // move to new node
    curr_stone = curr_stone->next;
    // set values of new node
    curr_stone->item = initial[i];
    curr_stone->next = NULL;
  }
  curr_stone = stones;
  print_stones(curr_stone);
  curr_stone = stones;
  long long sum_stones;
  for (i=0; i<NUM_OF_BLINKS; i++) {
    printf("%lld blinking!\n", i + 1);
    sum_stones = blink(curr_stone);
    printf("%lld stones present\n", sum_stones);
  }
  printf("we have %lld stones in total!\n", sum_stones);
  /*curr_stone = stones;*/
  /*print_stones(curr_stone);*/
}
