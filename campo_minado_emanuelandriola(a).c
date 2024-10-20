#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** resultado_final(int** mat, int acum, int n, int n4){ 
for (int x = 0; x < n; x++){
   for (int y = 0; y < n; y++){
     if (mat[x][y] == - 1) acum = -1;
      else { 
        acum = 0; //acum = acum + 1 para cada termo próximo da coordenada desejada
      if (x < n4 && mat[x + 1][y] == -1) acum++;
      if (x > 0 && mat[x - 1][y] == -1) acum++;
      if (y < n4 && mat[x][y + 1] == -1) acum++;
      if (y > 0 && mat[x][y - 1] == -1) acum++;
      if (x > 0 && y > 0 && mat[x - 1][y - 1] == -1) acum++;
      if (x > 0 && y < n4 && mat[x - 1][y + 1] == -1) acum++;
      if (x < n4 && y > 0 && mat[x + 1][y - 1] == -1) acum++;
      if (x < n4 && y < n4 && mat[x + 1][y + 1] == -1) acum++;
      }
     mat[x][y] = acum;
    }
   } 
   return mat;   
}

int leitura_das_coordenadas(int n, int acum, int cont, int n3, int n4, int** mat){
  //x e y serão lidos pelo usuário como as coordenadas do jogo
  // ok retornará 1 em caso de vitória e 0 em caso de derrota
  int ok, x, y;
  while (scanf("%d,%d" , &x, &y)){ 
    //verifica se as coordenadas são válidas
    if ((x < 1 || y < 1) || (x > n4 + 1 || y > n4 + 1)){
      printf("Coordenadas indisponíveis, tente outros números.\n");
    }
      //verifica se as coordenadas já foram usadas no jogo
    else if (mat[x - 1][y - 1] != - 10 && mat[x - 1][y - 1] != -1){
      printf("Coordenadas repetidas, tente outros números.\n");
    }
    else {
    x -= 1; //para o usuario digitar numeros entre 1 e 10, 20 ou 30
    y -= 1; 
     if (mat[x][y] == - 1) acum = -1;
    else { 
        acum = 0; //acum = acum + 1 para cada termo próximo da coordenada desejada
      if (x < n4 && mat[x + 1][y] == -1) acum++;
      if (x > 0 && mat[x - 1][y] == -1) acum++;
      if (y < n4 && mat[x][y + 1] == -1) acum++;
      if (y > 0 && mat[x][y - 1] == -1) acum++;
      if (x > 0 && y > 0 && mat[x - 1][y - 1] == -1) acum++;
      if (x > 0 && y < n4 && mat[x - 1][y + 1] == -1) acum++;
      if (x < n4 && y > 0 && mat[x + 1][y - 1] == -1) acum++;
      if (x < n4 && y < n4 && mat[x + 1][y + 1] == -1) acum++;
    }
    mat[x][y] = acum; //a coordenada será igual ao acumulador calculado
    
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (mat[i][j] == -10) printf("x "); //se a matriz nao foi inicializa com -1 ou acum
      else if (mat[i][j] == -1 && (x != i || y != j)){
        printf("x "); //todo m[i][j] = -1 ja foi inicilizado, logo ele só aparece caso o usuario digite suas coordenadas
      }
      else if (mat[i][j] == -1 && (x == i && y == j)){
        printf("%d " , mat[i][j]); //imprime -1, somente caso x == i e y == j
      }
      else printf("%d " , mat[i][j]); //imprime os acumuladores já inicializados
      }
    printf("\n");
    }
    
  cont++;
     //critério de parada que finaliza o jogo em caso tanto de vitória quanto de derrota
    if (mat[x][y] == -1 || cont == n3){
      break;
    }
   }
  }

  if (cont == n3) ok = 1;
  else ok = 0;

  return ok;
  }
  
int** inicializa_randomico(int** mat, int n2, int n){
  int random, random2;
  srand(time(NULL)); //util para que os termos deêm números distintos
  for (int i = 0; i < n2; i++){
    random = rand() % n; //gera numeros aleatorios que serao as coordenadas das minas
    random2 = rand() % n; // e faz com que estes numeros aleatorios sejam de 1 ate 10,20 ou 30
   //printf("%d %d\n" , random + 1, random2 + 1); -> caso queira vizulaizar a eficiência do código imprima as coord com minas
    mat[random][random2] = -1;
  }
  return mat;
}

int** inicializa_matriz(int n){
   int** mat = malloc(n * sizeof(int*)); 
  for (int i = 0; i < n; i++){
    mat[i] = malloc(n * sizeof(int));
  }

//inicializa todos os termos da matriz com -10 por ser um número impossível no jogo
 for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      mat[i][j] = -10;
    }
  }  
  return mat;
}

void variaveis_dificuldade(int dif, int *n, int *n2, int *n3, int *n4){
 if (dif == 1){
    *n = 10;
    *n2 = 3;
    *n3 = 97;
    *n4 = 9;
  }
  else if (dif == 2){
    *n = 20;
    *n2 = 6;
    *n3 = 394;
    *n4 = 19;
  }
  else if (dif == 3){
    *n = 30;
    *n2 = 9;
    *n3 = 891;   
    *n4 = 29;
  } 
  else printf("Erro, numeração inválida!\n");  
}

int main(){
  int dif, n, n2, n3, n4; 
  //dif lê a dificuldade do jogo, podendo ser fácil, médio ou difícil
  //n será a ordem da matriz conforme a dificuldade desejada
  //n2 vai ser a quantidade de 'minas' no jogo, referente ao numero -1
  //n3 é o máximo de casas do jogo sem a presença das bombas
  //n4 é o útimo termo de x

  printf("Bem-Vindo ao Campo Minado!\n");
  printf("Digite o número da dificuldade que deseja jogar:\n");
  printf("1 - Fácil\n2 - Médio\n3 - Difícil\n");  
  
  scanf("%d" , &dif); //lê a dificuldade do jogo conforme especificado no enunciado
  variaveis_dificuldade(dif, &n, &n2, &n3, &n4);

  if(dif == 1 || dif == 2 || dif == 3){ //só permite a entrada em caso de numeros validos

  //matriz nxn alocada dinamicamente
 int* *mat = inicializa_matriz(n);

  //inclui as minas em posições aleatórias de acordo coma dificuldade do jogo
 int* *mat2 = inicializa_randomico(mat, n2, n);


  int cont, acum;
  acum = 0; //contará quantas bombas tem próximo a cada coordenada, exceto -1
  cont = 0; //irá de 0 a n3 para indicar se o usuario ganhou o jogo
  
  printf("Coloque as coordenadas desejadas no estilo x,y ");
  printf("e repita o processo ao final de cada rodada.\n");
  printf("obs: não se esqueça da vírgula.\n");
  
//lerá as coordenadas fornecidas pelo usuário e vai imprimir o campo com as devidas mudanças
//ao final da função, será retornado 1 ou 0
  int ok = leitura_das_coordenadas(n, acum, cont, n3, n4, mat2); 

  //imprime a mensagem em caso de vitória
  if (ok){
    printf("parabéns, vc eh fera!\n");
  }
  //imprime a mensagem em caso de derrota
  else {
    printf("game over\n");
  } 

 int* *mat3 = resultado_final(mat2, acum, n, n4);
 //imprime o resulatdo final do jogo sem o 'x'
 for (int i = 0; i < n; i++){
   for (int j = 0; j < n; j++){
     printf("%d " , mat3[i][j]);
   }
   printf("\n");
 }
      
  //libera o espaço da matriz alocada dinamicamente
  for(int i = 0; i < n; i++){
    free(mat3[i]);
  }
  free(mat3);
} 
 return 0;
}
