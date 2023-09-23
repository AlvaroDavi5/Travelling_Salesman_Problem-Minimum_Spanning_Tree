
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
  - [x] Documentar complexidade dos algoritmos usados (_Big O_)
  - [x] Documentar análise empírica com base no tempo de execução para cada etapa
    - [ ] TSP
      - [ ] Leitura da entrada
      - [x] Criação do TSP
      - [ ] Cálculo das distancias
    - [ ] MST
      - [ ] Ordenação das distâncias
      - [x] Criação da MST
      - [ ] Escrita da saída
    - [ ] Tour
      - [ ] Criação do Tour
      - [x] Custo do Tour
      - [ ] Escrita da saída

___

## Documentation

### Introduction
This report is divided into methodology (containing implementation details, analysis, and tests), conclusion, and bibliography.  

### Methodology
Below are the details about the development methodology used.

#### Implementation
The program is divided into the following files: `tsp` (for Travelling Salesman Problem), `mst` (for Minimum Spanning Tree), `tour` (for Tour functions), `utils` (general functions used in all other 4 modules), and `main` (the main module). The implementation of functions and abstract data types (ADTs) interfaces can be found in files with the extension <span style="color:#ffff00">_.c_</span> in the <span style="color:#f02c00">**source**</span> directory, while their definitions and prototypes are in files with the extension <span style="color:#ff00ff">_.h_</span> in the <span style="color:#426cf5">**include**</span> directory.  

##### ADT(s)
The choice of structures for each ADT was made after analyzing the required functionalities, aiming for ease, clarity, and versatility in the program, while still considering performance.

* **TSP**: ADT containing the problem name, dimension (number of cities), and a list of cities.
  > _City_: ADT containing the ID and euclidean coordinates (x, y) of each city.
* **Graph**: ADT used for the <u>general city graph</u> (edges from one city to all others) and for the `MST`, containing the number of vertices, number of edges, a list of edges, and the minimum cost to traverse all vertices (in the case of `MST`).
  > _Edge_: ADT containing the source vertex, destination vertex, and weight (size) of each edge.
* **Subset**: ADT containing the ID of the parent edge in the set and its rank (to determine the covering/set parent).
* **Tour**: ADT containing the number of vertices and the list of visited vertices in order.

#### Functions
For the creation of the Minimum Spanning Tree (MST), Kruskal's Algorithm was used, which sorts all edges in a graph by weight and selects the edges with the lowest weight that connect all vertices.  
The QuickSort algorithm through the `qsort` function from the `stdlib` library was used for edge sorting.  
The concept of sets and simple methods like `unionSet` and `findSet` were used for edge separation and selection based on their vertices.  

For the Tour, recursive functions were used to stack accesses to MST edges in order to maintain code clarity during tree traversal.  

#### Main Features Complexity Analysis
Below are some of the main functions and their complexity based on code analysis:

```c
  // O(N)
  void readTSPFile(char *fileName, TravellingSalesmanProblem tsp);

  // O(N * lg(N)) + O(N^2)
  Graph buildMST(Graph graph);
  // O(N)
  bool isEdgeInGraph(Edge *edgesArray, int edgesAmount, int v1, int v2);
  // O(N^2)
  void calculateDistanceBetweenCities(TravellingSalesmanProblem tsp, Graph graph);
  // O(N)
  void writeMSTFile(char *fileSteam, Graph mst);

  // O(M * N * P)
  Tour buildTour(Graph mst);
  // O(N)
  void writeTourFile(char *fileSteam, Tour tour);
```

Most of the functions above, such as file reading and writing functions and the graph query function, have linear complexity (`O(N)`), which can be considered acceptable.  
However, the MST construction function involves sorting (`O(N * lg(N))`) and searching in the general graph (`O(N²)`), assuming very high complexity that can lead to slow execution.  
Finally, the Tour construction function assumes high complexity as it uses tree traversal (`O(M)`) while searching in the edges of the general graph (`O(N)`) and stacking its execution via recursion (`O(P)`), assuming even higher complexity than tree construction.  

#### Empirical Analysis Based on Tests
Below are some execution results (time in seconds):

```txt
berlin52
Read TSP Interval:        0.00010
Build Graph Interval:     0.00016
Build MST Interval:       0.00026
Build Tour Interval:      0.00028
Full Execution Interval:  0.00090
OPT TOUR LEN:   7544.365901904087
DEF TOUR LEN:  10203.849730879328
MY TOUR LEN:   10403.860360720962

eil101
Read TSP Interval:       0.00025
Build Graph Interval:    0.00116
Build MST Interval:      0.00168
Build Tour Interval:     0.00334
Full Execution Interval: 0.00683
OPT TOUR LEN:  642.3095357906022
MY TOUR LEN:   886.1115549507533
DEF TOUR LEN:  913.8415442402764

tsp225
Read TSP Interval:       0.00063
Build Graph Interval:    0.00678
Build MST Interval:      0.00813
Build Tour Interval:     0.01476
Full Execution Interval: 0.03092
OPT TOUR LEN:  3859.0
DEF TOUR LEN:  5276.38793936093
MY TOUR LEN:   5324.876857440186

a280
Read TSP Interval:       0.00055
Build Graph Interval:    0.00912
Build MST Interval:      0.00893
Build Tour Interval:     0.03144
Full Execution Interval: 0.05088
OPT TOUR LEN:  2586.7696475631606
MY TOUR LEN:   3480.2108772142674
DEF TOUR LEN:  3878.37390654869

pr1002
Read TSP Interval:       0.00144
Build Graph Interval:    0.06983
Build MST Interval:      0.20555
Build Tour Interval:     1.54358
Full Execution Interval: 1.84821
OPT TOUR LEN:  259066.6630526768
MY TOUR LEN:   351350.5630052579
DEF TOUR LEN:  359325.00846265815

d18512
Read TSP Interval:          0.01357
Build Graph Interval:      18.03470
Build MST Interval:       148.88872
Build Tour Interval:     9260.80673
Full Execution Interval: 9459.46471
MY TOUR LEN:   889565.7047727136
DEF TOUR LEN:  928233.6749880624
```

It is evident that, for all cases, reading TSP files and building the general graph occurred quickly.
Building and writing the MST also yielded good results in most test cases (up to `pr1002`).
However, during the execution of the `d18512` test, the poor performance of the algorithm for constructing the tour became noticeable.

### Conclusion
After analysis, it is clear that the bottleneck of the application lies primarily in the construction of the Tour, which executes in less than 2 seconds for just over 1000 cities but struggles to process 18000 cities (running for more than 2 hours).

### Bibliography
Below is the bibliography consulted for understanding the problem and its potential solutions.

[Travelling Salesman Problem | Wikipedia](https://en.wikipedia.org/wiki/Travelling_salesman_problem)  
[Kruskal Algorithm: Overview & Create Minimum Spanning Tree | Simplilearn](https://www.simplilearn.com/tutorials/data-structure-tutorial/kruskal-algorithm)  
[Kruskal's Minimum Spanning Tree (MST) Algorithm | Geeks for Geeks](https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/)  
