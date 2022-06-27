#include <stdio.h>
#include <stdlib.h>

#define M 8
#define N 10

void mostra_matriz( int matriz[][N], int cont);
void mostrar_um_conjunto(int matriz[][N], int cont);
void busca_valor(int matriz[M][N], int cont);
void inserir_dados(int a[], int cont,int aux);
void verifica_valor(int v, int escolhido, int i);
void remover_conjunto( int matriz[M][N], int cont);
int uniao_conjuntos(int a[],int b[],int c[]);
int busca_seq(int v[], int n,int escolhido);
int cont_valores(int v[]);
int interseccao_linha(int a[],int b[],int c[]);

int main(){

    int matriz[M][N] = {0},escolha,loop = 1, cont = 0,resultado;
    int lin1,lin2,aux;

    while( loop == 1 ){

        printf("\nOla, selecione um dos itens abaixo com apenas o numero\n\n");
        printf("1. Criar um novo conjunto na matriz\n");
        printf("2. Inserir dados em um conjunto\n");
        printf("3. Remover um conjunto\n");
        printf("4. Fazer a uniao entre conjuntos\n");
        printf("5. Fazer a interseccao entre dois conjuntos\n");
        printf("6. Mostrar um conjunto\n");
        printf("7. Mostrar todos os conjuntos\n");
        printf("8. Busca por um valor\n");
        printf("9. Sair do programa\n");
        scanf("%d", &escolha);

        switch (escolha){
            case 1:
                if(cont < 8){
                    cont++;
                    printf("\nFoi criado um conjunto com sucesso, ha %d conjunto(s) existente(s)\n", cont);
                }
                else
                    printf("Ja foi ultrapassado o limite de conjuntos que eh 8\n");
                break;

            case 2:
                printf("Escolha a linha que queira inserir dados: \n");
                scanf("%d", &aux);

                if( aux > cont || cont == 0 ){
                    printf("\n****ERROR!****");
                    printf("\n A linha %d nao foi criada\n", aux);
                    break;
                }

                if( aux == 0 && cont == 0 ){
                    printf("\n****ERROR!****");
                    printf("\n A linha %d nao foi criada\n", aux);
                    break;
                }

                inserir_dados(matriz[aux],cont,aux);

            break;

            case 3:
                remover_conjunto(matriz, cont);
                cont--;
            break;

            case 4:
                resultado = 0;
                if(cont == 1 || cont == 0){
                    printf("*******ERROR!*******\n");
                    printf("Nao eh possivel unir dois conjuntos pois so ha 1 conjunto:\n");
                    break;
                }

                printf("Digite uma linha para unir:\n");
                scanf("%d", &lin1);

                while(lin1 > cont){
                printf("Este conjunto nao foi criado digite outro:\n");
                scanf("%d", &lin1);
                }

                printf("Digite outra linha para unir com a linha %d:\n", lin1);
                scanf("%d", &lin2);

                while(lin2 > cont){
                    printf("Digite outro conjunto para unir com o conjunto %d: ",lin1);
                    scanf("%d", &lin2);
                }

                resultado = uniao_conjuntos(matriz[lin1],matriz[lin2],matriz[cont]);

                if(resultado == -1)
                    cont++;

            break;

            case 5:
                resultado = 0;
                if(cont == 1 || cont == 0){
                    printf("*******ERROR!*******\n");
                    printf("Nao eh possivel fazer a interseccao de duas linhas pois so ha 1 linha:\n");
                    break;
                }

                printf("Digite uma linha para intersecionar\n");
                scanf("%d", &lin1);

                while(lin1 > cont){
                printf("Esta linha nao foi criada digite outra:\n");
                scanf("%d", &lin1);
                }

                printf("Digite outra linha para intersecionar com a linha %d:\n", lin1);
                scanf("%d", &lin2);

                while(lin2 > cont){
                    printf("Digite outra linha para intersecionar com a linha %d: ",lin1);
                    scanf("%d", &lin2);
                }

                resultado = interseccao_linha(matriz[lin1],matriz[lin2],matriz[cont]);

                if(resultado == -1)
                    cont++;

            break;

            case 6:
                mostrar_um_conjunto(matriz,cont);
                break;

            case 7:
                mostra_matriz(matriz,cont);
                break;

            case 8:
                busca_valor(matriz,cont);
                break;

            case 9:
            loop = 0;
            printf("\nEncerrando programa...\nObrigado e volte sempre\n");
            break;

            default:
            printf("*******ERROR!*******\n");
            printf("Selecione um numero valido\n");
        }
    }

}

void mostra_matriz( int matriz[][N], int cont){

    int i, j;

    if(cont == 0){
        printf("Nao ha conjunto(s) para mostrar\n");
        return 1;
    }

    for(i = 0; i < cont; i++){
        for(j = 0; j < N; j++){
            printf("%3d   ", matriz[i][j]);
        }

        printf("\n\n");
    }
}

void inserir_dados(int a[], int cont,int aux){

    int i,escolhido;

    for(i = 0; i < 10 ; i++){
            printf("Digite o valor 0 para parar");
            printf("\nDigite o valor para o campo de coordenada [%d][%d]:",aux, i);
            scanf("%d", &escolhido);
            if(escolhido == 0){
                return 1;
            }
            while(busca_seq(a,i,escolhido) != -1){
                printf("\nValor repetido escolha outro a coordenada [%d][%d]:\n",aux, i);
                scanf("%d", &escolhido);
                if(escolhido == 0){
                    return 1;
                }
            }
            a[i] = escolhido;

    }

    printf("\nConjuntos inseridos com sucesso!\n");

}

void mostrar_um_conjunto(int matriz[][N], int cont){

    int i,j,aux;

    if(cont == 0){
        printf("Nao ha conjunto(s) para mostrar\n");
        return 1;
    }

    printf("Digite a linha que queira mostrar:\n");
    scanf("%d",&aux);
    printf("\n");

    for(i = 0; i < aux + 1; i++){
        for(j = 0; j < N; j++){
            printf("%4d   ", matriz[aux][j]);
        }
    printf("\n\n");
    }
}

void busca_valor(int matriz[M][N], int cont){

    int i,j,chave,aux = 0;

    printf("Qual valor voce deseja buscar?\n");
    scanf("%d", &chave);

    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            if(matriz[i][j] == chave){
                printf(" O valor %d se encontra na coordenarda[%d][%d] %d\n", chave,i,j);
                aux++;
            }
        }
    }

    if(aux == 0){
        printf("\n*********VALOR NAO ENCONTRADO!*********\n");
        printf("Nao ha nenhum conjunto com este valor\n");
    }

}

void remover_conjunto( int matriz[M][N], int cont){

    int i,j,deletado;

    printf("Qual conjunto voce deseja excluir?");
    scanf("%d", &deletado);

    if(cont == 0 || deletado > cont){
        printf("\n*********ERROR!*********\n");
        printf("Nao ha linhas para excluir ou vc digitou uma linha que nao existe\n");
        return 1;
    }

    for(j = deletado + 1; j < cont; j++){
        for(i = 0; i < N; i++){
            matriz[deletado][i] = matriz[j][i];
        }
    }

    printf("\nConjunto deletado com sucesso!\n");
}

int uniao_conjuntos(int a[],int b[],int c[]){

    int i,j;

    for(i = 0; a[i] != 0; i++){
        c[i] = a[i];
    }

    int n = cont_valores(a);

    for(j = 0; b[j] != 0; j++){
        if( busca_seq(a,n,b[j]) == -1 ){
            c[i] = b[j];
            i++;
        }
    }

    if( i > N){
        printf("*****ERROR*****\n");
        printf("A quantidade de conjuntos ultrapassou o limite ");
        return 1;
    }

    for(; i < N; i++)
        c[i] = 0;

    return -1;

}

int busca_seq(int v[], int n,int escolhido){
    int i;
    for( i = 0 ; i < n ; i++ )
        if (v[i] == escolhido )
            return i;

    return -1;
}

int cont_valores(int v[]){

    int i,aux=0;

    for(i = 0; v[i] != 0; i++){
        aux++;
    }

    return aux;
}

int interseccao_linha(int a[],int b[],int c[]){

    int i ,j,aux = 0;

    int n = cont_valores(a);

    int m = cont_valores(b);

    for(i = 0; i < n; i++){
        for(j = 0; j < m ; j++){
            if(busca_seq(c,m,a[i]) == -1){
               if(a[i] == b[j]){
                    c[aux] = a[i];
                    aux++;
                    break;
               }
            }
        }
    }

    if(aux == 0){
        printf("*****ERROR*****\n");
        printf("Nao ha nenhum numero igual entre as linhas");
        return 1;
    }

    for(; aux < N; aux++)
        c[aux] = 0;

    return -1;
}
