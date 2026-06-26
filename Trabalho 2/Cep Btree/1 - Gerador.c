#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _IndiceEndereco IndiceEndereco;
typedef struct _Endereco Endereco;

struct _IndiceEndereco
{
    char cep[8];
    unsigned int posicao;
};

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

int main() {
    srand(time(NULL));

    FILE *cepIn, *cepOut;
    cepIn = fopen("cep.dat", "rb");
    cepOut = fopen("80Cep.dat", "wb");
    Endereco e;
    fseek(cepIn, 0, SEEK_END);
    long numReg = ftell(cepIn);
    long tam = numReg / sizeof(Endereco);
    rewind(cepIn);

    int cont = 0;
    for(int i=0; i<tam; i++) {
        float random_num = 1.0*rand()/RAND_MAX;
        fread(&e, sizeof(Endereco), 1, cepIn);
        if(random_num < 0.8) {
            cont++;
            fwrite(&e, sizeof(Endereco), 1, cepOut);
        }
    }
    printf("%d\n",cont);
    fclose(cepIn);
    fclose(cepOut);
    
    return 0;
}