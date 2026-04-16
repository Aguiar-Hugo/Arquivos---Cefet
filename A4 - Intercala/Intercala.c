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

int main (int argc, char ** argv)
{
    FILE *f[K], *saida;
	Endereco lista[K];
    int x[K];
    int arquivos = K;
    char nome[20];
    int cont = 0;

    for (int i = 0; i < K; i++) {
        sprintf(nome, "saida%d.dat", cont + 1);
        f[i] = fopen(nome, "rb");
        if (f[i] == NULL) {
            fprintf(stderr, "Erro ao abrir arquivo\n");
            return 1;
        }
        
        x[i] = 1;

        if (fread(&lista[i], sizeof(Endereco), 1, f[i]) <= 0) {
            x[i] = 0;
            arquivos--;
        }
        cont++;
    }

    saida = fopen("saida_final.dat", "wb");
    if (saida == NULL) {
            fprintf(stderr, "Erro ao abrir arquivo\n");
            return 1;
        }

    while (arquivos > 0) {

        int menor = -1;

        for (int i = 0; i < K; i++) {
            if (x[i]) {
                if (menor == -1 || strncmp(lista[i].cep, lista[menor].cep, 8) < 0) {
                    menor = i;
                }
            }
        } 

        fwrite(&lista[menor], sizeof(Endereco), 1, saida);

        if (fread(&lista[menor], sizeof(Endereco), 1, f[menor]) == 0) {
            x[menor] = 0;
            arquivos--;
        }
    }
    
    for (int i = 0; i < K; i++) {
        fclose(f[i]);
    }
    fclose(saida);

    return 0;
}