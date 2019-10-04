

#include <string.h>
#include <stdarg.h>

#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#define NONE 0
#define SCENE 1
#define SHOW 2
#define TALK 3

#define TEXT_PATH "path"
#define TEXT_NAME "name"
#define TEXT_WORD "word"
#define TEXT_COLON ":"
#define TEXT_SEMICOLON ";"

typedef struct
{
    int type;
    int type_list_N;
    int type_list_N_useful;
    int* type_list;
    char** type_list_information;
}Message;

Message* message_new()
{
    Message* message = (Message*)malloc(sizeof(Message));

    message->type_list_N = 0;
    message->type_list_N_useful = 0;
    message->type_list = (int*)malloc(sizeof(int) * (message->type_list_N + 1));
    message->type_list_information = (char**)malloc(sizeof(char*));
    message->type_list_information[message->type_list_N] = (char*)malloc(sizeof(char));

    return message;
}

void message_add(Message* message,int type,char* type_information_type,...)
{
    int i;
    va_list var_list;
    void* data;

    int n = sizeof(type_information_type) / sizeof(char);

    message->type_list = realloc(message->type_list,sizeof(int) * (message->type_list_N + 1));
    message->type_list[message->type_list_N] = type;

    message->type_list_information = (char**)realloc(message->type_list_information,sizeof(char*) * (message->type_list_N + 1));
    message->type_list_information[message->type_list_N] = calloc(1,sizeof(char));

    va_start(var_list,type_information_type);

    for (i = 0; i < n; i++)
    {
        switch (type_information_type[i])
        {
            case 'n':
                data = va_arg(var_list,char*);
                printf("%s\n", data);

                message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(char) * (strlen(message->type_list_information[message->type_list_N])
                                                                                                                              + strlen(TEXT_NAME) + strlen(TEXT_COLON) + strlen(data) + strlen(TEXT_SEMICOLON)));
                strcat(message->type_list_information[message->type_list_N],TEXT_NAME);
                strcat(message->type_list_information[message->type_list_N],TEXT_COLON);
                strcat(message->type_list_information[message->type_list_N],data);
                strcat(message->type_list_information[message->type_list_N],TEXT_SEMICOLON);
                break;
            case 'w':
                data = va_arg(var_list,char*);
                printf("%s\n", data);

                message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(char) * (strlen(message->type_list_information[message->type_list_N])
                                                                                                                              + strlen(TEXT_WORD) + strlen(TEXT_COLON) + strlen(data) + strlen(TEXT_SEMICOLON)));

                strcat(message->type_list_information[message->type_list_N],TEXT_WORD);
                strcat(message->type_list_information[message->type_list_N],TEXT_COLON);
                strcat(message->type_list_information[message->type_list_N],data);
                strcat(message->type_list_information[message->type_list_N],TEXT_SEMICOLON);
                break;
            case 'p':
                data = va_arg(var_list,char*);
                printf("%s\n", data);

                message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(char) * (strlen(message->type_list_information[message->type_list_N])
                                                                                                                              + strlen(TEXT_PATH) + strlen(TEXT_COLON) + strlen(data) + strlen(TEXT_SEMICOLON)));
                strcat(message->type_list_information[message->type_list_N],TEXT_PATH);
                strcat(message->type_list_information[message->type_list_N],TEXT_COLON);
                strcat(message->type_list_information[message->type_list_N],data);
                strcat(message->type_list_information[message->type_list_N],TEXT_SEMICOLON);
                break;
        }
    }

    printf("%s\n",message->type_list_information[message->type_list_N]);

    message->type_list_N++;
    message->type_list_N_useful++;

    va_end(var_list);
}

char* message_get(Message* message)
{
    if (message->type_list_N_useful == 0)
        return NULL;

    int return_N = message->type_list_N - message->type_list_N_useful;
    message->type_list_N_useful--;

    message->type = message->type_list[return_N];

    return message->type_list_information[return_N];
}














#endif //MESSAGE_H_INCLUDED
