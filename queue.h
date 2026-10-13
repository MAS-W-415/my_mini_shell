#ifndef QUEUE_H
#define QUEUE_H 
#define HISTORY_COMMANDS_SIZE 10 
#include "basicFunction.h"

typedef struct
{
    char** data[HISTORY_COMMANDS_SIZE];
    int front;
    int rear;
}HISTORY_QUEUE;

extern HISTORY_QUEUE history;

int isFull();
int isEmpty();
void addCommand(Tokens *command);
void rmCommand();
void printCommands();


#endif
