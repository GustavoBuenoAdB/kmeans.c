#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    FILE *arquivo;
    uint8_t buffer;
    int posicao_bit;
} Leitor_de_bytes;

///criando e inicializando o leitor de bytes
Leitor_de_bytes* criar_Leitor_de_bytes(char *nome_arquivo)
{
    Leitor_de_bytes *byte_lido = (Leitor_de_bytes*)malloc(sizeof(Leitor_de_bytes));

    //abrindo o arquivo e salvando no leitor
    byte_lido -> arquivo = fopen(nome_arquivo, "rb");
    if (!byte_lido -> arquivo)
    {
        printf("\n Erro ao abrir o arquivo \"%s\"\n", nome_arquivo);
        free(byte_lido);
        return NULL;
    }

    byte_lido -> buffer = 0;
    //inicializa um bit "ja lido"
    byte_lido -> posicao_bit = 8;
    return byte_lido;
}

///funcao que le o proximo bit do leitor
int ler_bit(Leitor_de_bytes *byte_lido) {
    //se o byte ja foi lido, le o proximo
    if (byte_lido -> posicao_bit == 8) {
        if (fread(&byte_lido -> buffer, 1, 1, byte_lido -> arquivo) != 1)
            return -1; //nao tem mais o que ler
        byte_lido -> posicao_bit = 0;
    }
    //isola e le o bit de posicao_bit
    int bit = (byte_lido -> buffer >> (7 - byte_lido -> posicao_bit));
    byte_lido -> posicao_bit++;
    return bit;
}

///destruindo o leitor de bytes e fechar o arquivo lido
void fechar_Leitor_de_bytes(Leitor_de_bytes *byte_lido) {
    fclose(byte_lido -> arquivo);
    free(byte_lido);
}

///realmente o descompactador -----------------
#define ARQUIVO "arquivo.kh4"
#define TAM_PILHA 100

typedef struct {
    float cor;
    Arvore* esq;
    Arvore* dir;
} Arvore;

Arvore* aloca_arvore()
{
    Arvore* arv (Arvore*) malloc(sizeof(Arvore));
    arv -> cor = NULL;
    arv -> esq = nullptr;
    arv -> dir = nullptr;
    return arv;
}
Arvore* aloca_arvore(float cor)
{
    Arvore* arv (Arvore*) malloc(sizeof(Arvore));
    arv -> cor = cor;
    arv -> esq = nullptr;
    arv -> dir = nullptr;
    return arv;
}
void concatena_Arvore(Arvore* pai, Arvore* esq, Arvore* dir)
{
    pai -> esq = esq;
    pai -> dir = dir;
}
void le_cor(Arvore* atual, Leitor_de_bytes *byte_lido)
{
    //ler a proxima cor do arquivo, ir lendo os numeros
}

typedef struct {
    Arvore** vetor_Arvores;
    int quantidade;
} Pilha;

Pilha* inicializa_pilha(int tam)
{
    Pilha* pil = (Pilha*) malloc(sizeof(Pilha));
    pil -> vetor_Arvores = (Arvore**) malloc(sizeof(Arvore*) * tam);
    pil -> quantidade = 0;
}

void coloca_na_pilha(Pilha* pil, Arvore* arv)
{
        pil -> vetor_Arvores[pil -> quantidade] = arv;
        pil -> quantidade++;
}

Arvore* retira_da_pilha(Pilha* pil)
{
    if (pil -> quantidade == 0)
        return nullptr;
    pil -> quantidade--;
    return pil -> vetor_Arvores[pil -> quantidade];
}

int main() {
    //abrindo o arquivo
    Leitor_de_bytes *byte_lido = criar_Leitor_de_bytes(ARQUIVO);
    if (!byte_lido)
      return 1;


    int bit1, bit2;
    Arvore* raiz = aloca_arvore();
    Arvore* atual = raiz;
    Pilha pilha_de_filhos = inicializa_pilha(TAM_PILHA);

    //lendo cada bit
    while (bit1 = (ler_bit(byte_lido) != -1) & 1) {
        bit2 =  ler_bit(byte_lido);
        if (bit1)
            coloca_na_pilha(pilha_de_filhos, atual -> esq);
        if(bit2)
            coloca_na_pilha(pilha_de_filhos, atual -> dir);
        if(bit1 == 0 && bit2 == 0)
            le_cor(atual);
        atual = retira_da_pilha(pilha_de_filhos)
        //se acabou a arvore
        if (atual == nullptr)
            break;
    }

    fechar_Leitor_de_bytes(byte_lido);
    return 0;
}
