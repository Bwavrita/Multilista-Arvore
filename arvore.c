#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct TreeNode {
    char produto[50];
    int quantidade;
    struct TreeNode* esquerda;
    struct TreeNode* direita;
};

typedef struct ListaLetras {
    char letra;
    struct TreeNode* raiz;
    struct ListaLetras* prox;
} ListaLetras;

struct TreeNode* novoNo(char* produto, int quantidade) {
    struct TreeNode* no = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    strcpy(no->produto, produto);
    no->quantidade = quantidade;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

struct TreeNode* inserir(struct TreeNode* raiz, char* produto, int quantidade) {
    if (raiz == NULL) {
        return novoNo(produto, quantidade);
    }
    if (quantidade > raiz->quantidade) {
        raiz->esquerda = inserir(raiz->esquerda, produto, quantidade);
    } else if (quantidade < raiz->quantidade ) {
        raiz->direita = inserir(raiz->direita, produto, quantidade);
    }
    return raiz;
}

ListaLetras* novaLetra(char letra) {
    ListaLetras* novo = (ListaLetras*)malloc(sizeof(ListaLetras));
    novo->letra = letra;
    novo->raiz = NULL;
    novo->prox = NULL;
    return novo;
}

ListaLetras* encontrarOuCriarLetra(ListaLetras** lista, char letra) {
    ListaLetras* atual = *lista;
    ListaLetras* anterior = NULL;
    while (atual != NULL && atual->letra < letra) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual != NULL && atual->letra == letra) {
        return atual;
    }
    ListaLetras* novo = novaLetra(letra);
    if (anterior == NULL) {
        novo->prox = *lista;
        *lista = novo;
    } else {
        novo->prox = anterior->prox;
        anterior->prox = novo;
    }
    return novo;
}

void inserirProduto(ListaLetras** lista, char* produto, int quantidade) {
    char letra = produto[0];
    letra = toupper(letra);
    ListaLetras* letraNode = encontrarOuCriarLetra(lista, letra);
    letraNode->raiz = inserir(letraNode->raiz, produto, quantidade);
}

int consultaProduto(ListaLetras* lista, char* produto) {
    char letra = produto[0];
    letra = toupper(letra);
    ListaLetras* letraNode = encontrarOuCriarLetra(&lista, letra);
    struct TreeNode* raiz = letraNode->raiz;
    while (raiz != NULL) {
        if (strcmp(raiz->produto, produto) == 0) {
            return raiz->quantidade;
        }
        if (strcmp(raiz->produto, produto) < 0) {
            raiz = raiz->direita;
        } else {
            raiz = raiz->esquerda;
        }
    }
    return -1;
}

struct TreeNode* encontrarMinimo(struct TreeNode* raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

struct TreeNode* removerNo(struct TreeNode* raiz, char* produto) {
    if (raiz == NULL) {
        return NULL;
    }
    if (strcmp(produto, raiz->produto) < 0) {
        raiz->esquerda = removerNo(raiz->esquerda, produto);
    } else if (strcmp(produto, raiz->produto) > 0) {
        raiz->direita = removerNo(raiz->direita, produto);
    } else {
        if (raiz->esquerda == NULL) {
            struct TreeNode* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            struct TreeNode* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        struct TreeNode* temp = encontrarMinimo(raiz->direita);
        strcpy(raiz->produto, temp->produto);
        raiz->quantidade = temp->quantidade;
        raiz->direita = removerNo(raiz->direita, temp->produto);
    }
    return raiz;
}

void removeProduto(ListaLetras** lista, char* produto) {
    char letra = produto[0];
    letra = toupper(letra);
    ListaLetras* letraNode = encontrarOuCriarLetra(lista, letra);
    if (letraNode->raiz != NULL) {
        letraNode->raiz = removerNo(letraNode->raiz, produto);
    }
    if (letraNode->raiz == NULL) {
        if (*lista == letraNode) {
            *lista = letraNode->prox;
        } else {
            ListaLetras* atual = *lista;
            while (atual->prox != letraNode) {
                atual = atual->prox;
            }
            atual->prox = letraNode->prox;
        }
        free(letraNode);
    }
}

void exibirArvore(struct TreeNode* raiz) {
    if (raiz != NULL) {
        exibirArvore(raiz->esquerda);
        printf("%s (%d)\n", raiz->produto, raiz->quantidade);
        exibirArvore(raiz->direita);
    }
}

void exibirTodosProdutos(ListaLetras* lista) {
    ListaLetras* atual = lista;
    while (atual != NULL) {
        printf("Letra: %c\n", atual->letra);
        exibirArvore(atual->raiz);
        atual = atual->prox;
    }
}

void exibirProdutosLetra(ListaLetras* lista, char letra) {
    letra = toupper(letra);
    ListaLetras* atual = lista;
    while (atual != NULL) {
        if (atual->letra == letra) {
            exibirArvore(atual->raiz);
            return;
        }
        atual = atual->prox;
    }
    printf("Nenhum produto encontrado para a letra %c\n", letra);
}

void exibirProdutosAcima(struct TreeNode* raiz, int quantidade) {
    if (raiz != NULL) {
        exibirProdutosAcima(raiz->esquerda, quantidade);
        if (raiz->quantidade >= quantidade) {
            printf("%s (%d)\n", raiz->produto, raiz->quantidade);
        }
        exibirProdutosAcima(raiz->direita, quantidade);
    }
}

void exibirProdutosAbaixo(struct TreeNode* raiz, int quantidade) {
    if (raiz != NULL) {
        exibirProdutosAbaixo(raiz->esquerda, quantidade);
        if (raiz->quantidade <= quantidade) {
            printf("%s (%d)\n", raiz->produto, raiz->quantidade);
        }
        exibirProdutosAbaixo(raiz->direita, quantidade);
    }
}

void liberarArvore(struct TreeNode* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

void liberarLista(ListaLetras* lista) {
    ListaLetras* atual = lista;
    while (atual != NULL) {
        ListaLetras* temp = atual;
        liberarArvore(atual->raiz);
        atual = atual->prox;
        free(temp);
    }
}

int contarProdutos(struct TreeNode* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarProdutos(raiz->esquerda) + contarProdutos(raiz->direita);
}

int totalProdutos(ListaLetras* lista) {
    int total = 0;
    ListaLetras* atual = lista;
    while (atual != NULL) {
        total += contarProdutos(atual->raiz);
        atual = atual->prox;
    }
    return total;
}

int somarQuantidades(struct TreeNode* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return raiz->quantidade + somarQuantidades(raiz->esquerda) + somarQuantidades(raiz->direita);
}

int totalQuantidadesProdutos(ListaLetras* lista) {
    int total = 0;
    ListaLetras* atual = lista;
    while (atual != NULL) {
        total += somarQuantidades(atual->raiz);
        atual = atual->prox;
    }
    return total;
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Inserir produto\n");
    printf("2. Exibir todos os produtos\n");
    printf("3. Consultar produto\n");
    printf("4. Remover produto\n");
    printf("5. Total de produtos\n");
    printf("6. Total de quantidades de produtos\n");
    printf("7. Exibir produtos por letra\n");
    printf("8. Exibir produtos por quantidade acima\n");
    printf("9. Exibir produtos por quantidade abaixo\n");
    printf("10. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    ListaLetras* lista = NULL;
    int opcao;
    char produto[50];
    int quantidade;
    char letra;
    int exit = 0;
    while (!exit) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o nome do produto: ");
                fgets(produto, 50, stdin);
                produto[strcspn(produto, "\n")] = 0; // Remover a nova linha do final

                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                inserirProduto(&lista, produto, quantidade);
                break;
            case 2:
                exibirTodosProdutos(lista);
                break;
            case 3:
                printf("Digite o nome do produto: ");
                fgets(produto, 50, stdin);
                produto[strcspn(produto, "\n")] = 0;

                int quantidadeProduto = consultaProduto(lista, produto);
                if (quantidadeProduto != -1) {
                    printf("Quantidade do produto: %d\n", quantidadeProduto);
                } else {
                    printf("Produto n�o encontrado\n");
                }
                break;
            case 4:
                printf("Digite o nome do produto: ");
                fgets(produto, 50, stdin);
                produto[strcspn(produto, "\n")] = 0;

                removeProduto(&lista, produto);
                printf("Removido com sucesso");
                break;
            case 5:
                printf("Total de produtos: %d\n", totalProdutos(lista));
                break;
            case 6:
                printf("Total de quantidades de produtos: %d\n", totalQuantidadesProdutos(lista));
                break;
            case 7:
                printf("Digite a letra: ");
                scanf(" %c", &letra);
                letra = toupper(letra);
                exibirProdutosLetra(lista, letra);
                break;
            case 8:
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                ListaLetras* atual = lista;
                while (atual != NULL) {
                    exibirProdutosAcima(atual->raiz, quantidade);
                    atual = atual->prox;
                }
                break;
            case 9:
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                ListaLetras* atual2 = lista;
                while (atual2 != NULL) {
                    exibirProdutosAbaixo(atual2->raiz, quantidade);
                    atual2 = atual2->prox;
                }
                break;
            case 10:
                liberarLista(lista);
                exit = 1;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    return 0;
}
