#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CSVParser.h"

#define READ_BUF_SIZE 8192

void callback(char** cols, int ncols, void* userData) {
    int *coluna = (int*) userData;    
    if (strncmp(cols[1], "South America", 13) == 0) {
        coluna[1] += atoi(cols[5]);
        coluna[2] += atoi(cols[8]);
    }
    (coluna[0])++;
}

int main(int argc, char *argv[])
{
    FILE *f = fopen("sinasc.csv", "r");

    CSVParser parser;
    CSVParser_init(&parser);

    char buffer[READ_BUF_SIZE];
    long dados[2] = {0, 0};
    int bytesLidos;

    while ((bytesLidos = fread(buffer, 1, READ_BUF_SIZE, f)) > 0)
    {
        CSVParser_processLines(&parser, buffer, bytesLidos, callback, dados);
    }

    fclose(f);

    printf("America do Sul\n");
    printf("Total de casos : %lld\n", dados[0]);
    printf("Total de mortes: %lld\n", dados[1]);

    return 0;
}