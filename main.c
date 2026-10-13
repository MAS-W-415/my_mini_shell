#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "basicFunction.h"

int STATE = 1; // process working
HISTORY_QUEUE history = {.data = {NULL}, .front = -1, .rear = -1};

int main(int argc, char *argv[])
{
    Buffer buff = {.data = malloc(INPUT_BUFF_SIZE), .size = INPUT_BUFF_SIZE};
    Tokens tokens = {.datas = malloc(INIT_TOKENS_NUM * sizeof(char*)), .size = INIT_TOKENS_NUM};
    while (STATE == 1)
    {
        showPrompt();
        getUserInput(&buff, &tokens);
        handleTokens(&tokens);
    }
    free(buff.data);
    free(tokens.datas);
    return 0;
}
