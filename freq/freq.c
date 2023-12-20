#include <stdio.h>
#include <string.h>

typedef struct list_t list_t;
typedef struct node_t node_t;

struct node_t
{
  char data[BUFSIZ];
  struct node_t *next;
  int count;
};

struct list_t
{
  struct list_t *succ;
  node_t *head;
};

list_t init(void)
{
  list_t newList;
  newList.succ = NULL;
  newList.head = NULL;
  return newList;
}

void add(list_t *list, const char *newData)
{
  node_t *current = list->head;
  while (current != NULL)
  {
    if (strcmp(current->data, newData) == 0)
    {
      current->count++;
      return;
    }
    current = current->next;
  }

  node_t *newNode = (node_t *)malloc(sizeof(node_t));

  strncpy(newNode->data, newData, BUFSIZ - 1);
  newNode->data[BUFSIZ - 1] = '\0';
  newNode->count = 1;
  newNode->next = list->head;
  list->head = newNode;
}

void freeList(list_t *list)
{
  node_t *current = list->head;
  while (current != NULL)
  {
    node_t *temp = current;
    current = current->next;
    free(temp);
  }
  list->head = NULL; // Set list head to NULL after freeing all nodes
}

int is_Prime(int n)
{
  if (n <= 1)
  {
    return 0;
  }
  for (int i = 2; i * i <= n; i++)
  {
    if (n % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

int delete(list_t *list, const char *dataToDelete)
{
  node_t *current = list->head;
  node_t *prev = NULL;

  while (current != NULL)
  {
    if (strcmp(current->data, dataToDelete) == 0)
    {
      if (prev == NULL)
      {
        list->head = current->next;
      }
      else
      {
        prev->next = current->next;
      }
      free(current);
      return 1; // Item found and deleted
    }
    prev = current;
    current = current->next;
  }

  return 0; // Item not found, not deleted
}

int contains(list_t *list, const char *dataToCheck)
{
  node_t *current = list->head;

  while (current != NULL)
  {
    if (strcmp(current->data, dataToCheck) == 0)
    {
      current->count++;
      return 1; // Item found
    }
    current = current->next;
  }
  return 0; // Item not found
}

void traverseList(list_t *list) {
    node_t* current = list->head;

    // Traverse the list until reaching the end (NULL)
    while (current != NULL) {
        // Process or print data in the current node
        printf("word: %s, count: %d \n", current->data, current->count); // Example: printing integer data
        // Move to the next node
        current = current->next;
    }
}

node_t* findMaxCountNode(list_t *list) {
    if (list == NULL || list->head == NULL) {
        return NULL; // Empty list or invalid input
    }

    node_t* current = list->head;
    node_t* maxCountNode = current;

    // Traverse the list to find the node with the highest count
    while (current != NULL) {
        if (current->count > maxCountNode->count ||
            (current->count == maxCountNode->count && strcmp(current->data, maxCountNode->data) < 0)) {
            // Update maxCountNode if the current node has a higher count
            // or lexicographically less if counts are equal
            maxCountNode = current;
        }
        // Move to the next node
        current = current->next;
    }

    return maxCountNode; // Return the node with the highest count
}

int main(void)
{
  char buffer[BUFSIZ];
  list_t list;
  list = init();
  int line = 1;
  while (fgets(buffer, BUFSIZ, stdin) != NULL)
  {
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
      buffer[len - 1] = '\0'; // Remove the newline character
      len--;                  // Adjust the length after removing the newline
    }
    if (!is_Prime(line))
    {
      if (contains(&list, buffer))
      {
        printf("counted %s\n", buffer);
      }
      else
      {
        add(&list, buffer);
        printf("added %s\n", buffer);
      }
    }
    else
    {
      if (delete (&list, buffer))
      {
        printf("trying to delete %s: deleted\n", buffer);
      }
      else
      {
        printf("trying to delete %s: not found\n", buffer);
      }
    }
    line++;
  }
  printf("result: %s %d\n", findMaxCountNode(&list)->data, findMaxCountNode(&list)->count);
  freeList(&list);
  return 0;
}
