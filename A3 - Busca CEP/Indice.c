#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;
typedef struct _EnderecoInd EnderecoInd;

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

struct _EnderecoInd
{
    char cep[8];
    unsigned int posicao;
};



int compara(const void *e1, const void *e2)
{
	return strncmp(((EnderecoInd*)e1)->cep,((EnderecoInd*)e2)->cep,8);
}

int main (int argc, char *argv[])
{
    FILE *f, *saida;
    Endereco end;
    long tamanho, numEnd;

    f = fopen("cep_ordenado.dat", "rb");

    fseek(f, 0, SEEK_END);
    tamanho = ftell(f);
    printf("Tamanho: %ld // Registros: %ld\n", tamanho, numEnd);
    numEnd = tamanho/sizeof(Endereco);
    rewind(f);

    EnderecoInd *indices = (EnderecoInd*) malloc(numEnd*sizeof(EnderecoInd));

    int qt = fread(&end, sizeof(Endereco), 1, f);
    unsigned int i = 0;
    
    while (qt > 0) {
        strncpy(indices[i].cep, end.cep, 8);
        indices[i].posicao = i;

        qt = fread(&end, sizeof(Endereco), 1, f);
        i++;
    }
    qsort(indices, numEnd, sizeof(EnderecoInd), compara);
    saida = fopen("saida.dat", "wb");

    fwrite(indices, sizeof(EnderecoInd), numEnd, saida);
    fclose(f);
    fclose(saida);
    
    return 0;
}