#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include <stdint.h>

typedef int_least32_t data_type;

typedef struct node_s
{
    data_type data;
    struct node_s* next;
} node;

node* createNode(data_type data);
int_least32_t insertBeforeHead(node** head, data_type data);
int_least32_t deleteHead(node** head);
int_least32_t isEmpty(node** stack);
void push(node** stack, data_type data);
int_least32_t pop(node** stack);
int_least32_t peek(node ** stack);

#endif



