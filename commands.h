#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_PATH_LENGTH 100
#define MAX_COMMANDS_NUM 100
#define CHOSE_HISTORY_IC "chose_history"

typedef struct
{
    char* commands[MAX_COMMANDS_NUM];
    void (*functions_P[MAX_COMMANDS_NUM]) (char** args);
}COMMANDS_MAP;

extern const COMMANDS_MAP map;

void do_history(char** args);
void do_exit(char** args);
void do_cd(char** args);
void do_chose_history(char** args);
void do_pwd(char** args);
#endif   
