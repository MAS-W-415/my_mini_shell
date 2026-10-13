#include "queue.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int isFull()
{
    return (history.rear + 1) % HISTORY_COMMANDS_SIZE == history.front;
}

int isEmpty()
{
    return history.front == -1;
}

void addCommand(Tokens *command)
{
    if (isFull()) {
        printf("history is full\n");
        return;
    }
    if (history.front == -1) history.front = 0;    
    
    history.rear = (history.rear + 1) % HISTORY_COMMANDS_SIZE;
    history.data[history.rear] = malloc((*command).size * sizeof(char*));
    for(int i = 0; i < (*command).size - 1; ++i)
    {
        history.data[history.rear][i] = strdup((*command).datas[i]);
    }
    history.data[history.rear][(*command).size - 1] = NULL;
}

void rmCommand()
{
    if (isEmpty()) {
        printf("history is empty\n");
        return;
    }
    for(int i = 0; history.data[history.front][i] != NULL; ++i)
    {
        free(history.data[history.front][i]);
    }
    free(history.data[history.front]);
    if (history.front == history.rear) {
        history.front = history.rear = -1; // Reset history
    } else {
        history.front = (history.front + 1) % HISTORY_COMMANDS_SIZE;
    }
    return;
}

void printCommands()
{
    if (isEmpty()) {
        printf("history is empty\n");
        return;
    }
    int i = history.front;
    int count = 0;
    while (count < (history.rear - history.front + HISTORY_COMMANDS_SIZE) % HISTORY_COMMANDS_SIZE + 1) {
        ++count;
        printf("%d\t", count);
        for(int j = 0; history.data[i][j] != NULL; ++j)
        {
            printf("%s ", history.data[i][j]);
        }
        printf("\n");
        i = (i + 1) % HISTORY_COMMANDS_SIZE;
    }
}
