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
    return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}

int main (int argc, char **argv)
{
    FILE *f;
    long pos, tam, qtd_bloco, qtd_resto;

    f = fopen("cep.dat", "rb");
    if (!f) {
        printf("Erro ao abrir o arquivo cep.dat\n");
        return 1;
    }
    
    fseek(f, 0, SEEK_END);
    pos = ftell(f);
    tam = pos / sizeof(Endereco);
    rewind(f);

    qtd_bloco = tam / K;
    qtd_resto = tam % K; 

    printf("Total de registros: %ld\n", tam);
    printf("Registros por bloco: %ld (Sobra no ultimo bloco: %ld)\n", qtd_bloco, qtd_resto);

    Endereco *end = (Endereco*) malloc(sizeof(Endereco) * (qtd_bloco + qtd_resto));
    if (!end) {
        printf("Erro de alocação de memória.\n");
        fclose(f);
        return 1;
    }

    for (int i = 0; i < K; i++) {

        long qtd_a_ler = (i == K - 1) ? (qtd_bloco + qtd_resto) : qtd_bloco;

        if (qtd_a_ler == 0) break; 

        long lidos = fread(end, sizeof(Endereco), qtd_a_ler, f);
        if (lidos == 0) break;

        qsort(end, lidos, sizeof(Endereco), compara);

        char nome_arquivo[30];
        sprintf(nome_arquivo, "bloco_%d.dat", i);
        
        FILE *f_bloco = fopen(nome_arquivo, "wb");
        if (f_bloco) {
            fwrite(end, sizeof(Endereco), lidos, f_bloco);
            fclose(f_bloco);
            printf("Bloco %d gerado com %ld registros.\n", i, lidos);
        } else {
            printf("Erro ao criar o arquivo %s\n", nome_arquivo);
        }
    }

    fclose(f);
    free(end);

    return 0;
}