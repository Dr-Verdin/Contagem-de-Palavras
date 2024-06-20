#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void caixaAlta(char *str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            *str = (*str) + 32;
        }
        str++;
    }
}

int contador(char *file, char *procurada) {
    FILE *fp;
    char *buffer;
    
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Erro na leitura do arquivo.\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long int tamArq = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = (char*) malloc(tamArq + 2);
    if (buffer == NULL) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    caixaAlta(procurada);

    int cont = 0;
    while (fgets(buffer, tamArq + 2, fp) != NULL) {
        caixaAlta(buffer);

        char *token = strtok(buffer, " \t\n\r,.;");
        while (token != NULL) {
            if (strcmp(token, procurada) == 0) {
                cont++;
            }
            token = strtok(NULL, " \t\n\r.,;");
        }
    }

    fclose(fp);
    free(buffer);
    return cont;
}

int main() {
    char file[20];
    char *p, *procurada;

    scanf("%s", file);

    p = (char *) malloc(sizeof(char) * 10);
    scanf("%s", p);
    procurada = (char *) malloc(sizeof(char) * (strlen(p) + 1));
    strcpy(procurada, p);
    free(p);

    int quantPalavras = contador(file, procurada);

    printf("quantidade: %d\n", quantPalavras);

    free(procurada);
    return 0;
}
