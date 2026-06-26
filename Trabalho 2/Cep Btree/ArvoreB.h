#ifndef __ARVORE_B__
#define __ARVORE_B__

#define TAM_CHAVE 8
#define TAM_PAG 300

#include <stdio.h>

typedef struct _ArvoreB ArvoreB;
typedef struct _ArvoreB_Cabecalho ArvoreB_Cabecalho;
typedef struct _ArvoreB_Elemento ArvoreB_Elemento;
typedef struct _ArvoreB_Pagina ArvoreB_Pagina;

struct _ArvoreB_Cabecalho
{
    long raiz;
};

struct _ArvoreB
{
    ArvoreB_Cabecalho* cabecalho;
    FILE* f;    
};

struct _ArvoreB_Elemento
{
    char chave[TAM_CHAVE];
    long posicaoRegistro;
    long paginaDireita;
};

struct _ArvoreB_Pagina
{
    int quantidadeElementos;
    long paginaEsquerda;
    ArvoreB_Elemento elementos[TAM_PAG];
};


ArvoreB* ArvoreB_Abre(const char* nomeArquivo);
void ArvoreB_Fecha(ArvoreB* arvore);
void ArvoreB_Insere(ArvoreB* arvore, char chave[TAM_CHAVE], long posicaoRegistro );
void ArvoreB_PrintDebug(ArvoreB* arvore);
long ArvoreB_Busca(ArvoreB* arvore, char chave[TAM_CHAVE]);

#endif
