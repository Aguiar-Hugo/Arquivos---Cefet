#include <stdio.h>
#include <stdlib.h>
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
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main (int argc, char **argv)
{
    FILE *f, *s1, *s2;
    Endereco *end;
    long posicao, qtd;

    f = fopen("cep.dat", "rw");
    
    fseek(f, 0, SEEK_END);
    posicao = ftell(f);
    qtd = posicao/sizeof(Endereco);
    
    end = (Endereco*) malloc(sizeof(Endereco)*qtd);
    rewind(f);
    if(fread(end,sizeof(Endereco),qtd,f) == qtd)
	{
		printf("Todos lidos = OK\n");
	}
    qsort(end, qtd, sizeof(Endereco), compara);
    printf("Ordenado = OK\n");

    s1 = fopen("cep_ordenado1.dat", "wb");
    fwrite(end, sizeof(Endereco), (qtd / 2), s1);

    s2 = fopen("cep_ordenado2.dat", "wb");
    fwrite(end, sizeof(Endereco), (qtd / 2) + 1, s2);

    fclose(f);
    fclose(s1);
    fclose(s2);
    free(end);

    return 0;
}