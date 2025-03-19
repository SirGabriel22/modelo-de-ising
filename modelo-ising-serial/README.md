# Versão serial do Modelo de Ising

Destacamos inicialmente que não focaremos na teoria intrínseca ao modelo, mas explicaremos cada função da biblioteca *funcoesising.h*, exibiremos como cada uma se integra e, por fim, explicaremos o código principal *modeloising.c*.

## funcoesising.h

### Bibliotecas utilizadas

Utilizamos as seguintes bibliotecas:

- <stdio.h>, para entrada e saída de dados;
- <stdlib.h>, para operações com ponteiros;
- <math.h>, para operações matemáticas;
- <time.h>, para obter o tempo de execução e gerar números aleatórios.

### Constantes utilizadas

#### #define BOL 1.0
Como poderemos perceber no código, focamos mais na execução (ou seja, em dar certo) do que na fidelidade das constantes utilizadas no modelo. A ordem de grandeza da constante de Boltzmann é $-23$, ou seja, muito pequeno. Por "licença poética", utilizamos a constante de Boltzmann como sendo $1.0$.

#### #define J 2
Esse número corresponde ao coeficiente de interação entre os spins. Isso pode ser modificado de acordo com o caso que se quer modelar.

#### #define L 10
Nesse modelo, estamos supondo o caso de uma malha quadrada. A constante L se referencia justamente à quantidade de spins em uma linha/coluna da malha. Ou seja, o modelo em questão considera uma matriz de 100 elementos.

#### #define MAXITER 1e+6

Como a malha é pseudoaleatória, utilizamos um milhão de iterações a fim de que o resultado tenha menos flutuação possível. O usuário poderá notar que, quanto mais elementos a malha tiver, mais iterações serão necessárias para o resultado ser satisfatório e não possuir flutuação.

### Funções implementadas

(Continua)
