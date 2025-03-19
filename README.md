# ⚠️⚠️⚠️ATENÇÃO⚠️⚠️⚠️

O presente código é funcional, mas devido a erros de planejamento da parte do autor no semestre em que esse programa foi feito, o usuário poderá encontrar problemas de execução. Em caso positivo, abra uma issue do projeto.

# Modelo de Ising

## Sobre o projeto
Esse repositório consta de um projeto do Modelo de Ising, programado no período 2024.2 do curso de *Computação Científica de Alto Desempenho*, ministrado pelo professor Marcos Veríssimo Alves, da Universidade Federal Fluminense no polo de Volta Redonda - RJ.

Mais informações sobre o modelo [neste vídeo](https://www.youtube.com/watch?v=K--1hlv9yv0&t=420s&pp=ugMICgJwdBABGAHKBQtpc2luZyBtb2RlbNIHCQlPCQGHKiGM7w%3D%3D).

## O conteúdo
Em cada pasta há um tipo de código (serial ou paralelizado) e arquivos relacionados.

### Pasta *modelo-ising-serial*
Como diz o nome, nessa pasta temos o código serial, isso é, sem ser paralelizado. O arquivo *analise.txt* contém um flat profile, mostrando qual parte do código consome mais tempo de execução.

Além disso, o arquivo *optims.txt* contém otimizações do compilador. O arquivo *Makefile* contém o caminho de execução do código. O arquivo *funcoesising.h* é a biblioteca de funções programada para a execução do programa. Por fim, o arquivo *modeloising.c* contém a main() do programa.

Mais informações sobre cada arquivo no README do programa.

### Pasta *modelo-ising-paralelizado-openmp*
Apesar de conter a parte mais importante do projeto, essa pasta contém menos arquivos. Justo como na pasta anterior, o arquivo *Makefile* está presente para fornecer o caminho de execução do código. O arquivo *funcoesisingParalelizacao.h* contém a biblioteca de funções, com as devidas paralelizações. Por fim, o arquivo *modeloisingParalelizacao.c* contém a main() do programa.

Mais informações no README do programa.
