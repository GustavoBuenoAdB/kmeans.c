#include <stdio.h>
#include "k-means.c"

void mostra_img(float*** img, int altura, int largura)
{
    for (int y = 0 ; y < altura ; y++)
    {
        printf("\n");
        for (int x = 0 ; x < largura ; x++)
                printf("(%.1lf , %.1lf , %.1lf)", img[y][x][0], img[y][x][1], img[y][x][2]);
    }
}
int main ()
{
    int altura = 4;
    int largura = 4;
    printf("t");
    float*** img = (float***) malloc(sizeof(float**) * altura);
    for (int y = 0 ; y < altura ; y++)
    {
        img[y] = (float**) malloc(sizeof(float*) * largura);
        for (int x = 0 ; x < largura ; x++)
        {
            img[y][x] = (float*) malloc(sizeof(float) * 3);
            for (int z = 0 ; z < 3 ; z++)
                img[y][x][z] = (float)(rand() % 256) / 255.0;
        }
    }


    printf("\n entrada:\n");
    mostra_img(img, altura, largura);

    k_means(img, altura, largura, 3, 10);

    printf("\n resultado:\n");
    mostra_img(img, altura, largura);
}
