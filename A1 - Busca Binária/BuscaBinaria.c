#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)
{
    FILE *f;
	Endereco end;
	int qt;
	int contador = 0;

    if (argc != 2) {
        fprintf(stderr, "Uso correto: ./%s [CEP desejado]\n", argv[0]);
        return 1;
    }

    f = fopen("cep_ordenado.dat", "rb");
    if (f == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo\n");
        return 1;
    }

    printf("Tamanho total: %ld \n", sizeof(Endereco));

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    long numReg = tam / sizeof(Endereco); 
    long inicio = 0;
    long fim = numReg - 1;

    while (inicio <= fim) {
        contador++;
        long meio = (inicio + fim) / 2;
        fseek(f, meio*sizeof(Endereco), SEEK_SET);
        qt = fread (&end, sizeof(Endereco), 1, f);

        if (strncmp(argv[1], end.cep, 8) == 0) {
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",end.logradouro,end.bairro,end.cidade,end.uf,end.sigla,end.cep);
            break;
        } else if (strncmp(argv[1], end.cep, 8) < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf ("Total lido: %d", contador);
    fclose(f);

    return 0;
}