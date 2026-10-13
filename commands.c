#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "basicFunction.h"
#include "queue.h"

const COMMANDS_MAP map = {
    .commands = {"exit", "cd", "pwd", "history", CHOSE_HISTORY_IC},
    .functions_P = {&do_exit, &do_cd, &do_pwd, &do_history, &do_chose_history}
};

void do_chose_history(char **args)
{
    int args_n = 0;
    while(args[args_n] != NULL)
    {
        ++args_n;
    }
    if(args_n > 1) 
    {
        fprintf(stderr, "!: too many arguments\n");
    }
    else if(args_n == 0){;}
    else if(-1 == isTenNum(args[0]))
    {
        fprintf(stderr, "!: wrong argument type\n");
    }
    else 
    {
        if(isEmpty()) 
        {
            fprintf(stderr, "!: no history\n");
            return;
        }
        int index = isTenNum(args[0]);
        int history_size = (history.rear + HISTORY_COMMANDS_SIZE - history.front) % HISTORY_COMMANDS_SIZE + 1;
        if(index > history_size) 
        {
            fprintf(stderr, "!: no NO.%d history\n", index);
            return;
        }

        char** command = history.data[(history.front + index - 1) % HISTORY_COMMANDS_SIZE];
        int size = 0;
        while(command[size] != NULL)
        {
            ++size;
        }
        char** tmp = malloc((size + 1) * sizeof(char*));
        for(int i = 0; i < size; ++i)
        {
            tmp[i] = strdup(command[i]);
        }
        tmp[size] = NULL;
        Tokens history_command = {.datas = tmp, .size = size + 1};
        handleTokens(&history_command);
        for(int i = 0; i < size; ++i)
        {
            free(tmp[i]);
        }
        free(tmp);
    }
}

void do_history(char** args)
{
    printCommands();
}

void do_exit(char** args)
{
    STATE = 0;
}

void do_pwd(char** args)
{
    char* buf = malloc(MAX_PATH_LENGTH);
    if(NULL == getcwd(buf, MAX_PATH_LENGTH))
    {
        perror("pwd");
    }
    else printf("%s\n", buf);
    free(buf);
}

void do_cd(char** args)
{
    int args_n = 0;
    while(args[args_n] != NULL)
    {
        args_n++;
    }
    if(args_n >= 2) 
    {
        fprintf(stderr, "cd: too many arguments\n");return;
    }
    else if(args_n == 1)
    {
        if(chdir(args[0]) != 0)
        {
            perror("cd");
        }
    }
    else
    {
        chdir(getenv("HOME"));
    }

}

