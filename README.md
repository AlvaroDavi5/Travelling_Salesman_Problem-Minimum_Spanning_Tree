
# Travelling Salesman Problem with Minimum Spanning Tree

by **Álvaro S. Alves** - _2023201643_

First Assignment for the discipline of ```Técnicas de Busca e Ordenação (Search and Sorting Techniques)```.

#### Computer Science Class :computer:


### Federal University of Espírito Santo ([UFES](https://ufes.br))

<img src="https://www.ufes.br/sites/all/themes/padrao_ufes/images/marca_ufes.png" alt="logo da ufes" height="150px" width="250px">   

---

## To Do
- [x] Criar makefile para compilar os arquivos
- [x] Documentar com comentários (quando necessário) funções, estruturas, constantes, macros ou trechos complicados do código nos arquivos header em `include` ou source em `source`
- [x] Modularização
- [x] Gerenciamento de Memória
- [x] Tipos Abstratos de Dados (TADs)
- [x] Estruturas Opacas
- [x] Ponteiros para Funções
- [x] Funcionalidades
  - [x] TSP (Travelling Salesman Problem)
    - [x] Leitura de arquivos '.tsp'
    - [x] Criar TAD para TSP e para as cidades
    - [x] Calcular distância de uma cidade para outra com base nas coordenadas
    - [x] Criar tabela para representar o grafo de distância entre todas as cidades
    - [x] Refatorar e remover passos desnecessários (acessos e alocações)
      - [x] Tabela de distâncias
      - [x] Comparações
      - [x] Acréscimo de arestas
  - [x] MST (Minimum Spanning Tree)
    - [x] Implementar o _Algoritmo de Kruskal_ para criar MST e calcular o menor custo
    - [X] Criar TAD para MST (árvore/grafo)
    - [x] Imprimir MST em arquivo '.mst'
    - [x] Refatorar e remover passos desnecessários (acessos e alocações)
  - [x] Tour
    - [x] Criar TAD para armazenar Tour
      - [x] O TAD deve ser criado com base na MST
      - [x] O TAD deve conter um array para as arestas (assim como a MST)
      - [x] O TAD deve conter um array para os vértices já visitados e um contador
      - [x] O TAD deve calcular/verificar:
        1. As ocorrências de cidades repetidas
        1. As cidades (vértices) ao redor
        1. A menor distância (aresta de menor peso) entre as cidades ao redor
      - [x] O TAD deve voltar à MST sempre que possível
      - [x] O TAD deve conter um custo mínimo menor que o TSP pela MST e maior que o da MST
      - [x] O TAD deve ter as arestas ordenadas de forma que o destino de uma seja a origem da outra
    - [x] Imprimir Tour em arquivo '.tour'
    - [x] Refatorar e remover passos desnecessários (acessos e alocações)
- [ ] Relatório
  - [ ] Documentar complexidade dos algoritmos usados (_Big O, Big Omega, Big Theta_)
  - [ ] Documentar análise empírica com base no tempo de execução para cada etapa
    - [ ] TSP
      - [ ] Leitura da entrada
      - [ ] Criação do TSP
      - [ ] Cálculo das distancias
    - [ ] MST
      - [ ] Ordenação das distâncias
      - [ ] Criação da MST
      - [ ] Escrita da saída
    - [ ] Tour
      - [ ] Criação do Tour
      - [ ] Custo do Tour
      - [ ] Escrita da saída

___

## Documentation

### Introduction
...

### Methodology
...

#### Main Features Complexity Analysis
...

#### Tests Empirical Analysis
...

#### Implementation
```c
  int findSet(Subset *subsets, int component);
  void unionSet(Subset *subsets, int src, int dest);
  // Kruskal Algorithm
  Graph buildMST(Graph graph);
  // QuickSort Algorithm
  void quickSort(Item *array, size_t begin, size_t end);
```
<br>

O programa é dividido nos arquivos `tsp`, `mst`, `tour` e `utils`, onde a implementação das funções e dos tipos abstratos se encontram em arquivos de extensão <span style="color:#ffff00">_.c_</span> no diretório <span style="color:#f02c00">**source**</span> e suas definições e protótipos se encontram em arquivos de extensão <span style="color:#ff00ff">_.h_</span> no diretório <span style="color:#426cf5">**include**</span>.  
...

##### ADT(s)
A escolha das estruturas de cada TAD foi feita após a análise das funcionalidades pedidas, visando facilidade, clareza e versatilidade para o programa.

* **TSP**: TAD contendo o nome do problema, dimensão (quantidade de cidades) e lista de cidades.
  > _City_: TAD contendo ID e coordenadas euclidianas (x, y) de cada cidade.
* **Graph**: TAD utilizado para o <u>grafo geral de cidades</u> (arestas de uma cidade para todas as outras) e para a `MST` contendo quantidade de vértices, quantidade de arestas, lista de arestas e custo mínimo para percorrer todos os vértices (no caso da `MST`).
  > _Edge_: TAD contendo vértice de origem, vértice de destino e peso (tamanho) de cada aresta.
* **Subset**: TAD contendo ID da aresta pai do conjunto e seu ranking (para definir qual será o conjunto abrangente/pai).
* **Tour**: TAD contendo ...

### Conclusion
...

### Bibliography
[Travelling Salesman Problem | Wikipedia](https://en.wikipedia.org/wiki/Travelling_salesman_problem)  
[Kruskal Algorithm: Overview & Create Minimum Spanning Tree | Simplilearn](https://www.simplilearn.com/tutorials/data-structure-tutorial/kruskal-algorithm)  
[Kruskal's Minimum Spanning Tree (MST) Algorithm | Geeks for Geeks](https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/)  
