#include <bits/types/locale_t.h>
#include <errno.h>
#include <stddef.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "basicFunction.h"
#include "commands.h"
#include "queue.h"

void addToken(char* token, Tokens *tokens)
{
   (*tokens).size++;
   (*tokens).datas = realloc((*tokens).datas, (*tokens).size * sizeof(char*));
    (*tokens).datas[(*tokens).size - 2] = token;
    (*tokens).datas[(*tokens).size - 1] = NULL;
}

void emptyTokens(Tokens *tokens)
{
    (*tokens).size = 1;
    (*tokens).datas = realloc((*tokens).datas, (*tokens).size * sizeof(char*));
    (*tokens).datas[0] = NULL;
}

void showPrompt() 
{
    time_t t = time(NULL);
    char* time_buf = malloc(TIME_SIZE);
    strftime(time_buf, TIME_SIZE, "%Y-%m-%d %H:%M:%S", localtime(&t));
    printf("%s@miniShell$[%s]\n->", getenv("USER"), time_buf);
    free(time_buf);
}

void getUserInput(Buffer *buff, Tokens *tokens) 
{
    
    emptyTokens(tokens);
    memset((*buff).data, 0, (*buff).size);
    if(NULL == fgets((*buff).data, (*buff).size, stdin))
    {
        STATE = 0;
        return;
    }
    if((*buff).data[0] == '!')
    {
        bangSwap(buff);
    }
    char* saveBuff = NULL;
    char* token = strtok_r((*buff).data, " \t\n", &saveBuff);
    while(token != NULL)
    {
        addToken(token, tokens);
        token = strtok_r(NULL, " \t\n", &saveBuff);
    }
}

void bangSwap(Buffer *buff) 
{
    char* tmp = strdup((*buff).data);
    snprintf((*buff).data, (*buff).size, "%s %s", CHOSE_HISTORY_IC, tmp+1);
    free(tmp);
}

void handleTokens(Tokens *tokens)
{
    bool isInterCommand = false;
    bool isOuterCommand = false;
    bool isBangCommand = false;
    char* command = (*tokens).datas[0];
    if(NULL == command) return;
    for(int i = 0; i < MAX_COMMANDS_NUM; i++)
    {
        if(NULL != map.commands[i] && 
            0 == strcmp(map.commands[i], command))
        {
            isInterCommand = true;
            if(strcmp(map.commands[i], CHOSE_HISTORY_IC) == 0) isBangCommand = true;
            char** args = (*tokens).datas + 1;
            (*map.functions_P[i])(args);
            break;
        }
    }
    if(!isInterCommand && !isBangCommand)
    {
        int p = fork();
        if(p == 0)
        {
            if(-1 == execvp(command, (*tokens).datas))
            {
                perror(command);
            }
            _exit(errno);
        }
        else if (p < 0) {
            perror("fork");
        }
        else {
            int status;
            waitpid(p, &status, 0);
            if(WIFEXITED(status))
            {
                isOuterCommand = true;
            }
        }
    }
    if((isInterCommand || isOuterCommand) && !isBangCommand)
    {
        if(isFull())
        {
            rmCommand();
        }
        addCommand(tokens);
    }
}

int isTenNum(char *str)
{
    char* endptr;
    int answer = strtol(str, &endptr, 10);
    if(answer >= 1 && answer <= 10 && endptr != str && *endptr == '\0')
    {
        return answer;
    }
    else 
    {
        return -1;
    }
}
