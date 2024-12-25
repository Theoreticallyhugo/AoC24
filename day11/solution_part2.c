/*
 * this is a recursive tree search solution
 * */
#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_BLINKS 75

typedef struct node *link;
struct node {
  long long item;
  link child1;
  link child2;
};

long long llpow(long long base, long long exponent) {
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
  while (int_to_count / llpow(10, num_zeros) > 0) {
    /*printf("%ld / 10^%ld = %ld / %ld = %ld ;   ", int_to_count, num_zeros,
     * int_to_count, pow(10, num_zeros), int_to_count / pow(10, num_zeros));*/
    /*printf("%ld has more than %ld digits\n", int_to_count, num_zeros);*/
    num_zeros++;
  }
  return num_zeros;
}

long long traverse(link curr_stone, int blinks_left, link single_digits[]) {
  /*printf("traversing curr_stone=%lld, with %d blinks left.\n", curr_stone->item,*/
  /*       blinks_left);*/
  /*
   * go from this node to the next two until there are no blinks left
   * */

  // if there are no blinks left, end of recursion, return 1
  if (blinks_left == 0) {
    return 1;
  }

  // saving root nodes for all single digit numbers
  if (curr_stone->item < 10) {
    if (single_digits[curr_stone->item] != NULL) {
      // if the current stones number is already in the tree, follow the link to
      // its child and keep traversing
      return traverse(single_digits[curr_stone->item]->child1, blinks_left - 1,
                      single_digits);
    } else {
      // if the current stones number is not known, set current stone as its
      // root
      /*printf("found %lld for the first time.\n", curr_stone->item);*/

      single_digits[curr_stone->item] = curr_stone;
    }
  }

  if (curr_stone->child2 != NULL) {
    // if we already know the node, and it has two children, traverse both
    return traverse(curr_stone->child1, blinks_left - 1, single_digits) +
           traverse(curr_stone->child2, blinks_left - 1, single_digits);
  } else if (curr_stone->child1 != NULL) {
    // if we already know the node and it has one child, traverse that one
    return traverse(curr_stone->child1, blinks_left - 1, single_digits);
  }
  // otherwise, calculate new

  // the number isnt known yet, so we calculate the next
  long long num_digits = count_digits(curr_stone->item);
  if (curr_stone->item == 0) {
    /*printf("found zero\n");*/

    // 0 becomes 1
    //
    // create a new stone, give it the new number
    link new_stone = malloc(sizeof *new_stone);
    new_stone->item = 1;
    // point current stone to new stone
    curr_stone->child1 = new_stone;
    // traverse the new stone and return the count
    return traverse(new_stone, blinks_left - 1, single_digits);

  } else if (num_digits % 2 == 0) {
    /*printf("found %lld, splitting.\n", curr_stone->item);*/

    // is even number or digits, split
    //

    // left half of curr_stone goes to new link child1_stone
    link child1_stone = malloc(sizeof *child1_stone);
    child1_stone->item = (curr_stone->item / llpow(10, (num_digits / 2)));
    curr_stone->child1 = child1_stone;

    // right half of curr_stone goes to new link child2_stone
    link child2_stone = malloc(sizeof *child2_stone);
    child2_stone->item =
        curr_stone->item - (child1_stone->item * llpow(10, (num_digits / 2)));
    curr_stone->child2 = child2_stone;

    // traverse both child nodes, add results and return
    return traverse(child1_stone, blinks_left - 1, single_digits) +
           traverse(child2_stone, blinks_left - 1, single_digits);
  } else {
    /*printf("found %lld, multiplying.\n", curr_stone->item);*/

    // otherwise, multiply by 2024
    //
    // create a new stone, give it the new number
    link new_stone = malloc(sizeof *new_stone);
    new_stone->item = curr_stone->item * 2024;
    // point current stone to new stone
    curr_stone->child1 = new_stone;
    // traverse the new stone and return the count
    return traverse(new_stone, blinks_left - 1, single_digits);
  }
}

int main(int argc, char *argv[]) {
  /*
   * expect all args to be numbers
   * */

  // set up initial list of ints from cli args
  long long initial[argc - 1];
  char *end;
  long long i;
  printf("%d inputs:", argc - 1);
  for (i = 1; i < argc; i++) {
    initial[i - 1] = (long long)strtol(argv[i], &end, 10);
    printf(" %lld", initial[i - 1]);
  }
  printf("\n");

  link single_digits[10] = {NULL, NULL, NULL, NULL, NULL,
                            NULL, NULL, NULL, NULL, NULL};

  // work through input stones individually
  long long total_sum_of_stones = 0;
  for (i = 0; i < argc - 1; i++) {
    printf(">>> processing input of %lld at index %lld has started.\n",
           initial[i], i);
    link stones = malloc(sizeof *stones);
    stones->item = initial[i];
    total_sum_of_stones += traverse(stones, NUM_OF_BLINKS, single_digits);
    printf(">>> processing input of %lld at index %lld has finished with "
           "total_sum_of_stones=%lld.\n",
           initial[i], i, total_sum_of_stones);
  }
}
