#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#define MINA -1
#define MAGIC_NUMBER 10

int** aloca_campo(int tamanho){
    int** campo = malloc(tamanho * sizeof(int*));
    if (campo == NULL){
        printf("Memoria insuficiente\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++){
        campo[i] = malloc(tamanho * sizeof(int));
        if (campo[i] == NULL){
            printf("Memoria insuficiente\n");
            exit(1); 
        }
    }
    return campo; 
}

void preenche_minas(int** campo, int tam, int mina){
    int x, y;
    for (int i = 0; i < mina; i++){
        x = rand() % (tam - 2) + 1;
        y = rand() % (tam - 2) + 1;
        if (campo[x][y] == MINA) i--; 
        else campo[x][y] = MINA;
        //printf("x: %d, y: %d\n" , x, y); 
    }
}

int calcula_coordenada(int** campo, int tamanho, int x, int y){
    int cont = 0;
    if (campo[x - 1][y - 1] == MINA) cont++;
    if (campo[x][y - 1] == MINA) cont++;
    if (campo[x + 1][y - 1] == MINA) cont++;
    if (campo[x - 1][y] == MINA) cont++;
    if (campo[x + 1][y] == MINA) cont++;
    if (campo[x - 1][y + 1] == MINA) cont++;
    if (campo[x][y + 1] == MINA) cont++;
    if (campo[x + 1][y + 1] == MINA) cont++;
    return cont; 
}

void imprimeCampo(int** campo, int tam){
    for (int i = 1; i < tam - 1; i++){
        for (int j = 1; j < tam - 1; j++){
            if (campo[i][j] != MINA) campo[i][j] = calcula_coordenada(campo, tam, i, j);
        }
    }

    for (int i = 1; i < tam - 1; i++){
        for (int j = 1; j < tam - 1; j++){
            if (campo[i][j] == MINA) printf(" %d" , MINA);
            else printf("  %d" , campo[i][j]);
        }
        printf("\n"); 
    }
}

void liberaMatriz(int** campo, int tam){
    for (int i = 0; i < tam; i++){
        free(campo[i]);
    }
    free(campo); 
}

void nivel_jogo(int nivel, int* tamanho, int* venceu, int* mina){
    if (nivel == 1) {
        *tamanho = 12;
        *venceu = 85; 
        *mina = 15;
    } else if (nivel == 2){
        *tamanho = 22;
        *venceu = 370;
        *mina = 30;
    } else {
        *tamanho = 32;
        *venceu = 840;
        *mina = 60;
    }
}

int main(){

    printf("Deseja jogar em qual nivel?\n");
    printf("1 - Facil (10x10)\n2 - Medio (20x20)\n3 - Dificil (30x30)\n");
    printf("Digite o numero correspondente: ");
    int nivel, tamanho, mina, venceu;
    scanf("%d" , &nivel);
    if (nivel > 3 || nivel < 1){
        printf("Nivel invalido!\n");
        exit(1); 
    }

    nivel_jogo(nivel, &tamanho, &venceu, &mina);
    //tamanho representa as dimensões da matriz que representa o campo
    //venceu representa a quantidade de 'casas' sem minas
    //mina representa a quantidade de minas  

    int** campo = aloca_campo(tamanho);
    for (int i = 0; i < tamanho; i++){
        for (int j = 0; j < tamanho; j++){
            campo[i][j] = MAGIC_NUMBER; 
        }
    }
    printf("\n");

    srand(time(NULL));
    preenche_minas(campo, tamanho, mina);
    //coloca a quantidade de minas definidas aleatoriamente no campo

    for (int i = 0; i < tamanho; i++){
        for (int j = 0; j < tamanho; j++){
            printf("  x");
        }
        printf("\n");
    }
    //imprime o campo com 'x' para o usuário ter noção das dimensões

    int x, y, cont_vitoria;
    cont_vitoria = 0;
    //x e y representam as tentativas do usuário, linha e coluna no campo, respectivamente
    //cont_vitoria vai contar a quantidade de jogas ate 'venceu' para indicar a vitoria no jogo
    while(1){
        printf("Digite as coordenadas (no estilo x, y): ");
        scanf("%d, %d" , &x, &y);

        if (x < 1 || x > tamanho - 2 || y < 1 || y > tamanho - 2){
            printf("Coordenadas invalidas!\n\n");

        } else if (campo[x][y] == MINA){
            printf("Fim de jogo!\n");
            break; 

        } else if (campo[x][y] != 10){
            printf("Coordenadas repetidas!\n\n");

        } else {
             campo[x][y] = calcula_coordenada(campo, tamanho, x, y); 
             //a função 'calcula_coordenada' calcula a quantidade de minas proximas a coordenada escolhida
             for (int i = 1; i < tamanho - 1; i++){
                for (int j = 1; j < tamanho - 1; j++){
                    if (campo[i][j] != MAGIC_NUMBER && campo[i][j] != MINA) printf("  %d" , campo[i][j]);
                    else printf("  x");
                }
                printf("\n");
            }

            cont_vitoria++;
            if (cont_vitoria == venceu){
                printf("Parabens, voce venceu!\n");
                break;
            }
        }
    }

    imprimeCampo(campo, tamanho);
    liberaMatriz(campo, tamanho);
    return 0; 
}
