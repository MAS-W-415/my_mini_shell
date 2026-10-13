#ifndef BASIC_FUNCTION_H
#define BASIC_FUNCTION_H

extern int STATE;
#include <stdio.h>
#define INPUT_BUFF_SIZE 1024
#define TIME_SIZE 100
#define INIT_TOKENS_NUM 1 

typedef struct 
{
    char* data;
    size_t size;
}Buffer;

typedef struct
{
    char** datas;
    size_t size;
}Tokens;

void showPrompt();
int isTenNum(char* str);
void getUserInput(Buffer *buff, Tokens *tokens);
void addToken(char* token, Tokens *tokens);
void emptyTokens(Tokens *tokens);
void bangSwap(Buffer *buff);
void handleTokens(Tokens *tokens);
#endif
