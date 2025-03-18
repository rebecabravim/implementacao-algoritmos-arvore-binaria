#include <stdio.h>
#include <stdlib.h>

// definicao de no da arvore
struct NO {
    int info;
    struct NO *esq;
    struct NO *dir;
};

// prototipo das funcoes

// insere na arvore binaia
int inserir(struct NO** raiz, int valor);

// exclui na arvore binaria
int excluir(struct NO** raiz, int valor);

//altera o valor de um no
int alterar(struct NO** raiz, int antigo, int novo);

// funcao auxiliar de "excluir()"
struct NO* excluir_atual(struct NO* no);

// percorre e imprime arvore em pre-ordem
void imprimePreOrdem(struct NO** raiz);

// percorre e imprime arvore em-ordem
void imprimeEmOrdem(struct NO** raiz);

// percorre e imprime arvore em pos-ordem
void imprimePosOrdem(struct NO** raiz);

// calcula altura da arvore
int altura_ArvBin(struct NO** raiz);

// menu para interagir com o usuario
void menu() {
    printf("Escolha uma opcao:\n");
    printf("1. Inserir valor\n");
    printf("2. Excluir valor\n");
    printf("3. Listar pre-ordem\n");
    printf("4. Listar em-ordem\n");
    printf("5. Listar pos-ordem\n");
    printf("6. Alterar valor\n");
    printf("7. Sair\n");
}

int main()
{
		
    // ponteiro para ponteiro para o no da arvore
    struct NO** raiz = (struct NO**) malloc (sizeof(struct NO*));
    
    int altura;
    int valor, antigo, novo;
    int opcao;
    
    menu();
    do {
    	altura = altura_ArvBin(raiz);
        printf("Altura atual da arvore: %i\n", altura);
        printf("Digite a opcao: ");
        scanf("%d", &opcao);
        switch(opcao) {
            
            case 1: // Inserir valor
                printf("Digite o valor para inserir: ");
                scanf("%d", &valor);
                inserir(raiz, valor);
                break;
            case 2: // Excluir valor
                printf("Digite o valor para excluir: ");
                scanf("%d", &valor);
                excluir(raiz, valor);
                break;
            case 3: // Listar pre-ordem
                printf("Listando pre-ordem: ");
                imprimePreOrdem(raiz);
                printf("\n");
                break;

            case 4: // Listar em-ordem
                printf("Listando em-ordem: ");
                imprimeEmOrdem(raiz);
                printf("\n");
                break;

            case 5: // Listar pos-ordem
                printf("Listando pos-ordem: ");
                imprimePosOrdem(raiz);
                printf("\n");
                break;
            case 6: // Alterar valor
                printf("Digite o valor antigo: ");
                scanf("%d", &antigo);
                printf("Digite o novo valor: ");
                scanf("%d", &novo);
                alterar(raiz, antigo, novo);
                break;
            case 7: // Sair
                printf("Saindo do programa...\n");
                break;
            default:
                printf("****Opcao invalida. Tente novamente.****\n");
    	}
    } while (opcao != 7);
    
}

int inserir(struct NO** raiz, int valor){

    if(raiz==NULL){
        return 0;
    }
    
    struct NO* novo = (struct NO*) malloc(sizeof(struct NO));
    
    if(novo == NULL){
        return 0;
    }
    
    novo->info = valor;
    novo->dir=NULL;
    novo->esq=NULL;
    
    if(*raiz == NULL) {
        *raiz = novo; // raiz aponta para primeiro elemento

    } else{
    	
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        
        while(atual != NULL){
            
            ant = atual;
            
            if(valor == atual -> info){
            	
                free(novo);
                return 0;
            }
            
            if(valor > atual->info){
                atual = atual->dir;
            } else {
                atual = atual->esq;
            }
        }
        
        if(valor>ant->info){
            ant->dir=novo;
        }else{
            ant->esq=novo;
        }
    }
    
    return 1;
}

struct NO* excluir_atual(struct NO* atual){
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual){
       no1->dir=no2->esq;
       no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int excluir(struct NO** raiz, int valor){
    if(raiz == NULL){
        return -1;
    }
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    
    while(atual!=NULL){
        if(valor==atual->info){
            if(atual == *raiz){
                *raiz = excluir_atual(atual);
                return 0;
            }else{
                if(ant->dir==atual){
                    ant->dir = excluir_atual(atual);
                    return 0;
                } else{
                    ant->esq = excluir_atual(atual);
                    return 0;
                }
            }
        }
        
        ant = atual;
        if(valor>atual->info){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
    printf("Valor nao encontrado\n");
    return 1;
}

int alterar(struct NO** raiz, int antigo, int novo)
{
    if (excluir(raiz,antigo) == 0)
    {
        inserir(raiz,novo);
    }

}

void imprimePreOrdem(struct NO** raiz){
    if(raiz==NULL){
        return;
    }
    if(*raiz!= NULL){
        printf("%d ", (*raiz)->info);
        imprimePreOrdem(&((*raiz)->esq));
        imprimePreOrdem(&((*raiz)->dir));
    }
}

void imprimeEmOrdem(struct NO** raiz){
    if(raiz==NULL){
        return;
    }
    if(*raiz!= NULL){
        imprimeEmOrdem(&((*raiz)->esq));
        printf("%d ", (*raiz)->info);
        imprimeEmOrdem(&((*raiz)->dir));
    }
}

void imprimePosOrdem(struct NO** raiz){
    if(raiz==NULL){
        return;
    }
    if(*raiz!= NULL){
        imprimePosOrdem(&((*raiz)->esq));
        imprimePosOrdem(&((*raiz)->dir));
        printf("%d ", (*raiz)->info);
    }
}

int altura_ArvBin(struct NO** raiz){
    if(raiz==NULL){
        return -1;
    }
    if(*raiz==NULL){
        return -1;
    }
    
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if(alt_esq > alt_dir) {
        return (alt_esq+1);
    } else {
        return(alt_dir+1);
    }
}


