// Daniel Higley
// CSC 362.001: Computer System
// Programming Assignment #6 - Decoding a message
// Due: Friday, December 2nd

/*
 * Bin Packing Problem: create a node struct itemrom each item name/weight pair
 * and use itemirst itemit strategy to insert each node into an ordered linked
 * list inside oitem a bin struct. itemor each item pair, binSelect() determines
 * which bin the item will be placed in based on how much the item weighs and how
 * much capacity is left in the bin (max capacity for each bin is 1.0). Once the
 * correct bin has been selected, the bin’s head node and the new item information
 * are sent to insertNode() where the a new node is created and the item is placed
 * in the correct position in that bin’s linked list.
 */

#include <stdio.h>      // included for the use of printf
#include <string.h>     // included for the use of strcmp
#include <stdlib.h>     // included for the use of malloc

// define constants
#define BINCOUNT 20

// define function prototypes
struct node *insertNode(struct node *, char *, double);
void binSelect(char *, double);
void destroy(struct node *);
void printList();

// define node structure
struct node {
  char *item_name;
  double item_weight;
  struct node *next;
};

// define bin structure
struct bin {
  double capacity;
  struct node *head;
} space[BINCOUNT]; // initialize an array of 20 bins

/* main */
int main(void) {
  // initialize all the things
  int i, j;
  /* char *names[] = {"Vase", "Bowling_ball", "Book", "Umbrella", "Gold_medal", "Speaker_1", "Walkman", "Speaker_2"}; */
  /* double weights[] = {0.5, 0.9, 0.3, 0.4, 0.7, 0.4, 0.2, 0.4}; */
  /* char *names[] = {"Small_dog", "Moose_skull", "Squirrel", "Mouse", "Goldfish", "Snake", "Human_finger", "Pig_head", "Eagle_feather", "Shark_teeth", "Camel_hump", "Crocodile", "Elephant_tusk", "Cat", "Horse_manure", "Monkey_hand", "Octopus eye", "Sheep_coat", "Bat", "Chicken_wing"}; */
  /* double weights[] = { 0.63, 0.25, 0.41, 0.15, 0.06, 0.52, 0.09, 0.39, 0.02, 0.11, 0.24, 0.94, 0.63, 0.28, 0.04, 0.21, 0.05, 0.33, 0.42, 0.12}; */
  char *names[] = {"Operating_system", "Computer_graphics", "The_History_of_the_Universe", "Discrete_Mathematics", "Statistics", "English_for_Dummies", "American_History_2000-", "Computer_Architecture", "C_Programming", "Hitchhicker's_Guide", "English-Minbari_Dictionary", "Zen_and_the_Art_of_Programming", "The_Joy_of_Cooking", "Cincinnati_Yellow_Pages", "Artificial_Intelligence", "Business_Programming:_Why?", "Heart_of_Darkness", "The_History_of_the_Ohio_State_Buckeyes"};
  double weights[] = {0.75, 0.62, 0.27, 0.78, 0.41, 0.55, 0.20, 0.90, 0.21, 0.23, 0.42, 0.33, 0.56, 0.98, 0.32, 0.12, 0.21, 0.82};
  int list_size = (int)(sizeof(names) / sizeof(char *));  // return the number of names in the names array
  struct node temp;

  // initialize array bins with b.capacity = 1.0 and b.list = NULL
  for (i = 0; i < BINCOUNT; i++) {
    space[i].capacity = 1.0;
    space[i].head = NULL;
  }

  // insert the contents of each list into the bins
  for (i = 0; i < list_size; i++) {
    // import the item's name/weight pair, select the correct bin, and insert the new node into the bins linked list
    binSelect(names[i], weights[i]);
  }

  // print the contents of all of the bins
  printList();

  for (i = 0; i < BINCOUNT; i++) {
    destroy(space[i].head);
  }

  return 0;
}

/* binSelect: decide which bin to place a node in based on the nodes weight and the bin capacity */
void binSelect(char *name, double weight) {
  int i;            // loop counter
  double cap = 0;   // update the capacity after a node has been assigned to a bin

  // determine which bin an item can be placed where the weight of the bin remains less than 1.0
  for (i = 0; i < BINCOUNT; i++) {
    // if item can be placed into b (b.capacity - weight >= 0.0)
    if ((cap = space[i].capacity - weight) > 0.00001) {
      // insert this node into b
      space[i].head = insertNode(space[i].head, name, weight);
      // modify b.capacity
      space[i].capacity = cap;
      break;
    }
  }
}

/* insertNode: create a node and insert it into the ordered list */
struct node *insertNode(struct node *head, char *name, double weight) {
  // initialize current and previous pointers
  struct node *previous = NULL;
  struct node *current = head;

  // initialize the new node with the given information
  struct node *newNode = (struct node *) malloc(sizeof(struct node));
  newNode->item_name = strdup(name);
  newNode->item_weight = weight;
  newNode->next = NULL;

  // move the previous and current pointers to where the new node needs to be inserted
  while(current != NULL && (strcmp(newNode->item_name, current->item_name)) > 0) {
    previous = current;
    current = current->next;
  }

  // if previous is still null then the list is empty
  if (previous == NULL) {
    head = newNode;   // make the new node the head node
  }
  else {              // insert the new node between the previous and current nodes
    previous->next = newNode;
  }
  newNode->next = current;

  return head;
}

/* printList: print the information and contents of each bin */
void printList() {
  int i, count = 0;       // loop counter and used bin counter
  struct node *current;   // iteration pointer

  // iterate through each bin in the bin array and print the contents of the bin if it has been used
  for (i = 0; i < BINCOUNT && space[i].capacity < 1.0; i++) {
    count++; // increment the count of the number of bins used
    printf("Bin %d (%1.2f): ", i + 1, space[i].capacity);
    current = space[i].head;
    // iterate over and print the items in the bin's linked list
    while (current != NULL) {
      printf("%s (%1.2f)%s", current->item_name, current->item_weight, (current->next != NULL) ? ", " : "");
      current = current->next;
    }
    printf("\n");
  }

  printf("There were %d bins used for sorting this list.", count);
}

/* destory: deallocate all heap memory */
void destroy(struct node *head) {
  struct node *tmp;

  while (head != NULL) {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}
