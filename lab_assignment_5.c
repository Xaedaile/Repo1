/*  Amelia Nelligan
    COP 3502C-001
    Lab Assignment #4
    6/9/2023
    Stores string as linked list of characters.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
    //Define variables.
    int i = 0;
    node* current = head;

    //Count nodes.
    while(current != NULL)
    {
            i++;
            current = current->next;
    }
    return i;
}

// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char* toCString(node* head)
{
    //Define variables.
    node* current = head;
    int i = 0;
    int j = length(head);

    //Allocate memory for the string.
    char* str = (char*)malloc((j + 1) * sizeof(char));

    //Compose string of characters from linked list.
    while(current != NULL)
    {
        str[i] = current->letter;
        current = current->next;
        i++;
    }

    //Add null terminator to end of string.
    str[i] = '\0';

    return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
    //Define variables.
    node* current = *pHead;
    node* temp;

    //Create new node.
    temp = (node*) malloc(sizeof(node));
    temp->letter = c;
    temp->next = NULL;
    
    if(!*pHead)
        *pHead = temp;
    else
    {
        while(current->next != NULL)
        {
            current = current->next;
        }
        //Insert new node at end of linked list.
        current->next = temp;
    }
    
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
    //Define variables.
    node* current = *pHead;
    node*next;
    while (current!=NULL)
    {
      next=current->next;
      free(current);
      current=next;
    }
    
    *pHead = NULL;
}

int main(void)
{
    //Define variables.
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt","r");

    //Read number of inputs from file.
    fscanf(inFile, " %d\n", &numInputs);

    //Loop through inputs.
    while (numInputs-- > 0)
    {
        //Read length of string.
        fscanf(inFile, " %d\n", &strLen);

        //Incorporates each character into a linked list.
        for (i = 0; i < strLen; i++)
        {
            fscanf(inFile," %c", &c);
            insertChar(&head, c);
        }
        //Output string.
        str = toCString(head);
        printf("String is : %s\n", str);

        //Delete list and free memory.
        free(str);
        deleteList(&head);

        //Indicate deleteList failure.
        if (head != NULL)
        {
            printf("deleteList is not correct!");
            break;
        }
    }
    //Close file.
    fclose(inFile);
}