#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int boolean;

void get_public_ip(char ip[15]);

const char *command = "nslookup myip.opendns.com resolver1.opendns.com 2>&1";

int main() {
    char public_ip[15];
    char new_ip[15];
    boolean first_time = FALSE;

    while(1) {
        get_public_ip(new_ip);
        if(first_time == FALSE) {
            strcpy(public_ip, new_ip);
            printf("ip publico atual: %s\n", public_ip);
            first_time = TRUE;
        }

        if(strcmp(public_ip, new_ip) != 0) {
            printf("o endereco publico da rede mudou!\n");
            printf("antigo: %s", public_ip);
            printf("novo: %s\n", new_ip);
            strcpy(public_ip, new_ip);
        }
    }

    return EXIT_SUCCESS;
}

void get_public_ip(char ip[15]) {
    FILE *pipe = _popen(command, "r");
    while(!pipe)
        pipe = _popen(command, "r");

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (strstr(buffer, "myip")) {
            fgets(buffer, sizeof(buffer), pipe);
            strcpy(ip, strchr(buffer, ' ') + 2);
            break;
        }
    }
}
