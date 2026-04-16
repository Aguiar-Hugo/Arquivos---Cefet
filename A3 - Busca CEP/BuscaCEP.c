#include <stdio.h>
#include <string.h>
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



int main (int argc, char **argv)
{
    FILE *indice, *fCep;
    EnderecoInd index;
    Endereco end;
    long pos = -1;

    if (argc != 2) {
        fprintf(stderr, "Uso correto: ./%s [CEP desejado]\n", argv[0]);
        return 1;
    }

    indice = fopen("saida.dat", "rb");
    if (indice == NULL) { 
        fprintf(stderr, "Erro ao abrir arquivo\n");
        return 1;
    }

    fseek(indice, 0, SEEK_END);
    long tamanho = ftell(indice);
    long numEndereco = tamanho / sizeof(EnderecoInd);
    long inicio = 0;
    long fim = numEndereco - 1;
    int contador = 0;

    while (inicio <= fim) {
        contador++;
        long meio = (inicio + fim) / 2;
        fseek(indice, meio*sizeof(EnderecoInd), SEEK_SET);
        fread (&index, sizeof(EnderecoInd), 1, indice);
        
        if (strncmp(index.cep, argv[1], 8) == 0) {
            pos = index.posicao;
            printf("Posição no arquivo: %ld \n", pos);
            break;
        } else if (strncmp(argv[1], index.cep, 8) < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (pos == -1) {
        printf("CEP não encontrado no arquivo.\n");
        return 0; 
    }

    fCep = fopen("cep_ordenado.dat", "rb");
    fseek(fCep, pos * sizeof(Endereco), SEEK_SET);
    fread(&end, sizeof(Endereco), 1, fCep);

    printf ("Total lido: %d \n", contador);
    printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",end.logradouro,end.bairro,end.cidade,end.uf,end.sigla,end.cep);

    fclose(indice);
    fclose(fCep);

    return 0;
}