#include "ArvoreB.h"
#include <stdio.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char** argv)
{
    ArvoreB* a = ArvoreB_Abre("arvore.dat");
    char chave[TAM_CHAVE+1];
    long posicao = 0;
    int i;

    FILE *f = fopen("80cep.dat", "rb");
    Endereco e;
    fseek(f, 0, SEEK_END);
    long numReg = ftell(f);
    long tam = numReg / sizeof(Endereco);
    rewind(f);

    printf("%d\n", tam);
    printf("%d\n", numReg);

    for(i=0; i<tam; i++)
    {
        fread(&e, sizeof(Endereco), 1, f);
        sprintf(chave, "%.8s", e.cep);
        posicao = i;
        ArvoreB_Insere(a, chave, posicao);

        if (i % 10000 == 0) {
            printf(".");
            fflush(stdout);
        }
    }

    fclose(f);
    ArvoreB_Fecha(a);
    return 0;
}