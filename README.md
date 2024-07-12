# Multilista-Árvore

Este projeto implementa uma estrutura de dados que combina uma multilista com árvores binárias de busca (ABP) em C. Cada nó da multilista representa uma letra do alfabeto e contém uma árvore binária de produtos cujos nomes começam com aquela letra.

## Funcionalidades

- Inserção de produtos com quantidade.
- Consulta de produtos por nome.
- Remoção de produtos.
- Exibição de todos os produtos.
- Exibição de produtos por letra inicial.
- Exibição de produtos com quantidade acima ou abaixo de um valor especificado.
- Cálculo do total de produtos.
- Cálculo do total de quantidades de produtos.

## Estrutura do Projeto

- `TreeNode`: Estrutura que representa um nó na árvore binária.
- `ListaLetras`: Estrutura que representa um nó na multilista.
- Funções para manipulação das árvores e da multilista.
## Uso

Ao executar o programa, um menu interativo será exibido, permitindo que você insira produtos, consulte produtos, remova produtos, e exiba informações sobre os produtos armazenados.

### Menu

1. **Inserir produto**: Adicione um novo produto com a quantidade especificada.
2. **Exibir todos os produtos**: Exibe todos os produtos na estrutura.
3. **Consultar produto**: Consulta a quantidade de um produto específico pelo nome.
4. **Remover produto**: Remove um produto específico pelo nome.
5. **Total de produtos**: Exibe o total de produtos.
6. **Total de quantidades de produtos**: Exibe o total de quantidades de todos os produtos.
7. **Exibir produtos por letra**: Exibe produtos que começam com uma letra específica.
8. **Exibir produtos por quantidade acima**: Exibe produtos com quantidade acima de um valor especificado.
9. **Exibir produtos por quantidade abaixo**: Exibe produtos com quantidade abaixo de um valor especificado.
10. **Sair**: Encerra o programa.

## Exemplo de Uso

```plaintext
Menu:
1. Inserir produto
2. Exibir todos os produtos
3. Consultar produto
4. Remover produto
5. Total de produtos
6. Total de quantidades de produtos
7. Exibir produtos por letra
8. Exibir produtos por quantidade acima
9. Exibir produtos por quantidade abaixo
10. Sair
Escolha uma opcao: 1

Digite o nome do produto: Maçã
Digite a quantidade: 10

Menu:
1. Inserir produto
2. Exibir todos os produtos
3. Consultar produto
4. Remover produto
5. Total de produtos
6. Total de quantidades de produtos
7. Exibir produtos por letra
8. Exibir produtos por quantidade acima
9. Exibir produtos por quantidade abaixo
10. Sair
Escolha uma opcao: 2

Letra: M
Maçã (10)
