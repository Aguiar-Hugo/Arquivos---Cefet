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

int main (int argc, char **argv)
{
    FILE *saida, *arvore, *cep;
    saida = fopen("Interseções.dat", "wb");
    ArvoreB* a = ArvoreB_Abre("arvore.dat");
    cep = fopen("80Cep.dat", "rb");
    Endereco e;
    int lidos = 0;
    int cont_intersec = 0;

    if (!saida) {
        fprintf(stderr, "Não foi possível abrir o arquivo de saída."); 
        return 1;
    }
    if (!cep) {
        fprintf(stderr, "Não foi possível abrir o arquivo de CEP."); 
        return 1;
    }

    while(fread(&e, sizeof(Endereco), 1, cep) > 0) {
        char chave[TAM_CHAVE+1];
        sprintf(chave, "%.8s", e.cep);
        
        if (ArvoreB_Busca(a, chave) != -1) {
            fwrite(&e, sizeof(Endereco), 1, saida);
            cont_intersec++;
        }

        lidos++;

        if (lidos % 10000 == 0) {
            printf("Lidos: %d \n Interseções: %d\n", lidos, cont_intersec);
        }
    }
    printf("Total de interseções: %d\n", cont_intersec);

    fclose(cep);
    fclose (saida);
    ArvoreB_Fecha(a);

    return 0;
}