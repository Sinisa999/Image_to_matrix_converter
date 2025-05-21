#include "stacklib.h"
#include <stdio.h>
#include <stdlib.h>

/*funkcija za kreiranje povezane liste*/
node* createNode(data_type data)
{
    /*alokacija memorije*/
    node* newNode = (node*)malloc(sizeof(node));

    /*ukoliko alokacija ne uspe*/
    if (newNode == NULL)
    {
        return NULL;
    }

    /*dodavanje elementa u listu*/
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/*funkcija za dodavanje elementa pre head cvora*/
int_least32_t insertBeforeHead(node** head, data_type data)
{
    /*pravljenje novog cvora*/
    node* newNode = createNode(data);

    /*ako malloc ne uspe, vraca error*/
    if (!newNode)
    {
        return EXIT_FAILURE;
    }

    /* ako je lista prazna postaviti novi cvor za head*/
    if (*head == NULL)
    {
        *head = newNode;
        return 0;
    }

    newNode->next = *head;
    *head = newNode;
    return 0;

}

/*funkcija za brisanje head cvora*/
int_least32_t deleteHead(node** head)
{
    node* temp = *head;
    *head = (*head)->next;
    free(temp);
    return 0;
}

/*funkcija za proveru da li je stek prazan*/
int_least32_t isEmpty(node** stack)
{
    return (*stack == NULL);
}

/*funkcija za dodavanje elemenata na stek*/
void push(node** stack, data_type data)
{
    /*dodavanje podatka na pocetak povezane liste.
    Ako funkcija za dodavanje vrati vrednost razlicitu od 0 znaci da imamo stack overflow*/
    if (insertBeforeHead(stack, data))
    {
        printf("Stack Overflow");
    }
}

/*funkcija za izbacivanje elementa iz steka*/
int_least32_t pop(node** stack)
{
    /*provera da li je stek prazan*/
    if (isEmpty(stack))
    {
        printf("Stack Underflow\n");
        return EXIT_FAILURE;
    }

    int_fast8_t data = (*stack)->data;

    /*brisanje glave*/
    deleteHead(stack);
    return data;
}

/*funkcija koja vraca element sa vrha steka*/
int_least32_t peek(node** stack)
{
    if (!isEmpty(stack))
    {
        return (*stack)->data;
    }
    else
    {
        return EXIT_FAILURE;
    }
}



