

#include <string.h>
#include <stdarg.h>

#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#define NONE 0
#define SCENE 1
#define SHOW 2
#define TALK 3

#define TEXT_TYPE "type"  //text
#define TEXT_TAG "tag"  //text
#define TEXT_PATH "path" //text
#define TEXT_NAME "name" //text
#define TEXT_WORD "word" //text
#define TEXT_COLON ":"   //text冒号
#define TEXT_SEMICOLON ";" //text分号

#define TYPE_N 5
#define TYPE_TYPE 0
#define TYPE_TAG 1
#define TYPE_PATH 2
#define TYPE_NAME 3
#define TYPE_WORD 4

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

    int n = strlen(type_information_type);
    printf("%d\n", n);

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

                message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(char) *
                (strlen(message->type_list_information[message->type_list_N]) + strlen(TEXT_NAME) + strlen(TEXT_COLON) + strlen(data) + strlen(TEXT_SEMICOLON)));

                //message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(message->type_list_information[message->type_list_N]) +
                //sizeof(TEXT_NAME) + sizeof(TEXT_COLON) + sizeof(data) + sizeof(TEXT_SEMICOLON));

                strcat(message->type_list_information[message->type_list_N],TEXT_NAME);
                strcat(message->type_list_information[message->type_list_N],TEXT_COLON);
                strcat(message->type_list_information[message->type_list_N],data);
                strcat(message->type_list_information[message->type_list_N],TEXT_SEMICOLON);
                break;
            case 'w':
                data = va_arg(var_list,char*);
                printf("%s\n", data);

                message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(char) *
                (strlen(message->type_list_information[message->type_list_N]) + strlen(TEXT_WORD) + strlen(TEXT_COLON) + strlen(data) + strlen(TEXT_SEMICOLON)));

                //message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(message->type_list_information[message->type_list_N]) +
                //sizeof(TEXT_WORD) + sizeof(TEXT_COLON) + sizeof(data) + sizeof(TEXT_SEMICOLON));

                strcat(message->type_list_information[message->type_list_N],TEXT_WORD);
                strcat(message->type_list_information[message->type_list_N],TEXT_COLON);
                strcat(message->type_list_information[message->type_list_N],data);
                strcat(message->type_list_information[message->type_list_N],TEXT_SEMICOLON);
                break;
            case 't':
                data = va_arg(var_list,char*);
                printf("%s\n", data);

                message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(char) *
                (strlen(message->type_list_information[message->type_list_N]) + strlen(TEXT_TAG) + strlen(TEXT_COLON) + strlen(data) + strlen(TEXT_SEMICOLON)));

                //message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(message->type_list_information[message->type_list_N]) +
                //sizeof(TEXT_TAG) + sizeof(TEXT_COLON) + sizeof(data) + sizeof(TEXT_SEMICOLON));

                strcat(message->type_list_information[message->type_list_N],TEXT_TAG);
                strcat(message->type_list_information[message->type_list_N],TEXT_COLON);
                strcat(message->type_list_information[message->type_list_N],data);
                strcat(message->type_list_information[message->type_list_N],TEXT_SEMICOLON);
                break;
            case 'p':
                data = va_arg(var_list,char*);
                printf("%s\n", data);

                message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(char) *
                (strlen(message->type_list_information[message->type_list_N]) + strlen(TEXT_PATH) + strlen(TEXT_COLON) + strlen(data) + strlen(TEXT_SEMICOLON)));

                //message->type_list_information[message->type_list_N] = realloc(message->type_list_information[message->type_list_N],sizeof(message->type_list_information[message->type_list_N]) +
                //sizeof(TEXT_PATH) + sizeof(TEXT_COLON) + sizeof(data) + sizeof(TEXT_SEMICOLON));

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

char** message_get(Message* message)
{
    int return_N,i = 0;
    char** information = calloc(TYPE_N,sizeof(char*));

    if (message->type_list_N_useful == 0)//无可用消息
        return information;

    return_N = message->type_list_N - message->type_list_N_useful;//用到的消息
    message->type_list_N_useful--;//可用消息-1

    message->type = message->type_list[return_N];//将消息类型改为用到的消息的消息类型

    while (1)//获取用到的消息的信息
    {
        char* data = strsep(&message->type_list_information[return_N],";");
        char* data_type =  strsep(&data,":");

        printf("data_type:%s\n", data_type);
        printf("data:%s\n", data);

        if (data == NULL)
            return information;

        if (i == 0)
        {
            information[TYPE_TAG] = (char*)calloc(strlen(data),sizeof(char));
            memcpy(information[TYPE_TAG],data,strlen(data) * sizeof(char));
            printf("tag:%s\n", information[TYPE_TAG]);
        }
        else if (i == 1)
        {
            information[TYPE_PATH] = (char*)calloc(strlen(data),sizeof(char));
            memcpy(information[TYPE_PATH],data,strlen(data) * sizeof(char));
            printf("path:%s\n", information[TYPE_PATH]);
        }
        else if (i == 2)
        {
            information[TYPE_NAME] = (char*)calloc(strlen(data),sizeof(char));
            memcpy(information[TYPE_NAME],data,strlen(data) * sizeof(char));
            printf("name:%s\n", information[TYPE_NAME]);
        }
        else if (i == 3)
        {
            information[TYPE_WORD] = (char*)calloc(strlen(data),sizeof(char));
            memcpy(information[TYPE_WORD],data,strlen(data) * sizeof(char));
            printf("word:%s\n", information[TYPE_WORD]);
        }

        i++;
    }

    return information;//返回得到的消息信息
}













#endif //MESSAGE_H_INCLUDED
