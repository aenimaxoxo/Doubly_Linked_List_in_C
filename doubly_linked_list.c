# include <stdio.h>
# include <stdlib.h>

struct Node {
  int data;
  int y[5];
  struct Node* next; 
  struct Node* prev;
};

/* add node to front of list */

void push(struct Node** head, int new_node_data){
  // create node
  struct Node* new_node = (struct  Node*) malloc(sizeof(struct Node));

  // add the data
  new_node -> data = new_node_data;

  // make new nodes prev null and next the former head
  new_node -> next = (*head);
  new_node -> prev = NULL;

  // change prev of former head to new node
  if ((*head) != NULL){
    (*head) -> prev = new_node;
  }

  // move the head point to our new node
  (*head) = new_node;  
}

void insertAt(struct Node** head, int new_node_data, int index_num){

  int count = index_num;

  // check if head is null
  if (head == NULL){
    printf("Head Node is NULL.\n\n");
    return;
  }
  
  // allocate new node
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  struct Node* index_finder = *head;

  if (count == 0){
    push(head, new_node_data);
  } else {
    // go to index point of list
    while ((count-2) > 0){
      count--;
      index_finder = index_finder -> next;
    }
  }

  // add data to our new node
  new_node -> data = new_node_data;

  // make next of new node prev nodes next
  new_node -> next = index_finder -> next;

  // make next of prev node new node
  index_finder -> next = new_node;

  // make prev of new node prev node
  new_node -> prev = index_finder;

  // change prev of new nodes next to new node
  if (new_node -> next != NULL){
    new_node -> next -> prev = new_node;
  }
}

/* Add a node to the end of the list */

void append(struct Node** head, int new_node_data){
  // allocate new node
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

  // allocate traversal node
  struct Node* last_finder = *head;
  
  // make new node's next null since its the last node
  new_node -> next = NULL; 
  
  // add data to our new node
  new_node -> data = new_node_data;

  // check to see if list is empty
  if (*head == NULL){
    new_node -> prev = NULL;
    *head = new_node;
    return; 
  } else {
    // go to end of list
    while (last_finder -> next != NULL){
      last_finder = last_finder -> next;
    }

    // change the last node to new_node
    last_finder -> next = new_node;

    // change new nodes prev to head
    new_node -> prev = last_finder;

    return; 
  }
}

/* Delete a Node */

void deleteNode(struct Node** head, struct Node *del){
  // check for null nodes
  if (head == NULL || del == NULL){
    printf("Head is NULL. There is nothing to delete.\n");
    return;
  }

  // delete head node
  if (*head == del){
    *head = del -> next; 
  }

  // if not last node, delete it
  if (del -> next != NULL){
    del -> next -> prev = del -> prev;
  }

  // if not first node, delete it
  if (del -> prev != NULL){
    del -> prev -> next = del -> next; 
  }

  // free memory taken up by del
  free(del);
  return;
}

void deleteNodeAtIndex(struct Node** head, int index_num){
  int count = index_num;
  struct Node* index_finder = *head;

  if (head == NULL){
    printf("Head is NULL. There is nothing to delete.\n");
    return;
  }

  if (index_num == 1){
    deleteNode(head, index_finder);
    return;
  }

  while ((count - 1) > 0){
    count--;
    index_finder = index_finder -> next;
  }
  deleteNode(head, index_finder);
  return;
}

void deleteLastNode(struct Node** head){
  struct Node* last_finder = *head;

  if (head == NULL){
    printf("Head is NULL. There is nothing to delete.\n");
    return;
  }
  // loop to last node
  while (last_finder -> next != NULL){
    last_finder = last_finder -> next;
  }
  deleteNode(head, last_finder);
  return;
}

// modify node at index
void modifyNode(struct Node** head, int index_num, int new_data){
  int count = index_num;
  struct Node* index_finder = *head;
  
  if (head == NULL){
    printf("Head is Null. No data to modify.\n");
    return;
  }

  if (index_num == 1){
    deleteNode(head, index_finder);
    push(head, new_data);
    return;
  }
  while ((count-2) > 0){
    count--;
    index_finder = index_finder -> next;
    }
    //    index_finder -> data = new_data;
    deleteNode(head, index_finder-> next);
    insertAt(head, new_data, index_num);
    return;
  }

// Reverse list

void modifyLastNode(struct Node** head, int new_data){
  // create traversal node
  struct Node* last_finder = *head;

  // loop through nodes and print
  while (last_finder -> next != NULL){
    last_finder = last_finder -> next; 
  }
  deleteNode(head, last_finder);
  append(head, new_data);
  return;
}

void reverseList(struct Node** head){
  struct Node* temp = NULL;
  struct Node* current = *head;

  // swap next for prev in all nodes
  while (current != NULL){
    temp = current -> prev;
    current -> prev = current -> next;
    current -> next = temp;
    current = current -> prev; 
  }

  // change head
  if (temp != NULL){
    *head = temp -> prev;
    }
  
}

/* Print the Contents of our linked list from given node */

void printList(struct Node* node){
  // create traversal node
  struct Node* last_finder;

  printf("Your List: \n\n");

  // loop through nodes and print
  while (node != NULL){
    printf("%d | ", node -> data);
    last_finder = node;
    node = node -> next; 
  }
  printf("\n\n");
}

void sumList(struct Node** head){
  // create traversal node
  struct Node* last_finder = *head;

  // create summation
  int sum = 0;

  // loop through nodes and add
  printf("(+ ");
  while (last_finder != NULL){
    sum += last_finder -> data; 
    printf("%d ", last_finder -> data);
    last_finder = last_finder -> next;
  }
  printf(")");
  printf("\nFinal Sum: %d\n\n", sum);
}

int main(){
  // make empty list
  struct Node* head = NULL;
  int input_var; 
  int choice_var, choice_var_2;
  char run_time_char;

  while ((run_time_char = getchar()) != EOF){

  // push, insertAt, printList, append, reverseList, delete, addlist
  printf("Choose option number:\n\n\tAdd \n\t\t1 - Add to Front\n\t\t2 - Add by Index\n\t\t3 - Add to End\n\n\tModify\n\t\t4 - Modify at Front\n\t\t5 - Modify at Index\n\t\t6 - Modify Last Node\n\n\tDelete\n\t\t7 - Delete First Node\n\t\t8 - Delete at Index\n\t\t9 - Delete Last Node\n\n\t10. Reverse Linked List\n\n\t11. Sum Linked List Data\n\n\t12. Exit Program\n\nEnter Your Choice:\n");

  scanf("%d", &input_var);
  
  if (input_var < 1 || input_var > 12){
    printf("Choice Does Not Exist.\n\n");
      } else { 
    printf("Your choice was: %d\n\n", input_var);
  }

  switch(input_var){
  case 1:
    printf("Choose Data Int:\t\n");
    scanf("%d", &choice_var);
    push(&head, choice_var);
    printList(head);
    break;

  case 2:
    printf("Choose Data Int:\t\n");
    scanf("%d", &choice_var);
    printf("Choose Index Number:\t\n");
    scanf("%d", &choice_var_2);
    insertAt(&head, choice_var, choice_var_2);
    printList(head);
    break;

  case 3:
    printf("Choose Data Int:\t\n");
    scanf("%d", &choice_var);
    append(&head, choice_var);
    printList(head);
    break;

  case 4:
    printf("Choose New Data Int:\t\n");
    scanf("%d", &choice_var);
    deleteNode(&head, head);
    push(&head, choice_var);
    printList(head);
    break;

  case 5:
    printf("Choose New Data Int:\t\n");
    scanf("%d", &choice_var);
    printf("Choose Index Number\t\n");
    scanf("%d", &choice_var_2);
    modifyNode(&head, choice_var_2, choice_var);
    printList(head);
    break;

  case 6:
    printf("Choose New Data Int:\t\n");
    scanf("%d", &choice_var);
    modifyLastNode(&head, choice_var);
    printList(head);
    break;

  case 7:
    printf("Deleting First Node.\n");
    deleteNode(&head, head);
    printList(head);
    break;

  case 8:
    printf("Which Node Index Would You Like to Delete?\n");
    scanf("%d", &choice_var);
    deleteNodeAtIndex(&head, choice_var);
    printList(head);
    break;

  case 9:
    printf("Deleting Last Node.\n");
    deleteLastNode(&head);
    printList(head);
    break;

  case 10:
    printf("Reversing List. \n");
    reverseList(&head);
    printList(head);
    break;

  case 11:
    printf("Summing List Data: \n");
    sumList(&head);
    printList(head);
    break;

  case 12:
    return 1;
  }
  }
  return 0;
}
