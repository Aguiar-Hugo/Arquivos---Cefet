#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define K 4

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

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main (int argc, char **argv)
{
    FILE *f;
    Endereco *end;
    long numReg, tamanhoTotal;

    f = fopen("cep.dat", "rb");
    if (f == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo\n");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    tamanhoTotal = ftell(f);
    numReg = tamanhoTotal / sizeof(Endereco);
    rewind(f);

    int tamanho = numReg / K;
    int resto = numReg % K;
    end = (Endereco*) malloc(sizeof(Endereco)*(tamanho + resto));

    for (int i = 0; i < K; i++) {     
        int qtd;
        if (i != (K - 1)) {
            fread(end,sizeof(Endereco),tamanho,f);
            qsort(end, tamanho, sizeof(Endereco), compara);
            qtd = tamanho;
        } else {
            fread(end,sizeof(Endereco),(tamanho) + resto,f);
            qsort(end, (tamanho + resto), sizeof(Endereco), compara);
            qtd = tamanho + resto;
        }

        char nomeArq[20];
        snprintf(nomeArq, sizeof(nomeArq), "saida%d.dat", i + 1);
        FILE *a = fopen(nomeArq, "wb");

        fwrite(end, sizeof(Endereco), qtd, a);

        fclose(a);
    }

    free(end);
    fclose(f);

    return 0;
}