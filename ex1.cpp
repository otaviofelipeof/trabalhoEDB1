// Trabalho 1 - EDB1 (DIM0119)
// Exercicio 1: Busca Linear Iterativa
// Autor: Otávio Felipe

#include <iostream>   // biblioteca de entrada/saida (cin para ler, cout para escrever)
#include <vector>     // biblioteca do tipo vector (array dinamico)
#include <chrono>     // biblioteca para medir tempo de execucao
using namespace std;  // evita precisar escrever std:: antes de cin, cout, vector, etc.

// Funcao que faz a busca linear.
// Parametros: A (o vetor), esq e dir (limites do intervalo [esq, dir)), chave (o que procuramos)
// Retorna: o indice onde achou a chave, ou -1 se nao encontrou
int buscaLinear(int A[], int esq, int dir, int chave) {
    // Percorre cada posicao i, comecando em esq e parando antes de chegar em dir
    // (i < dir, e nao i <= dir, porque dir e excluido na convencao [esq, dir))
    for (int i = esq; i < dir; i++) {
        // Compara o elemento da posicao atual com a chave procurada
        if (A[i] == chave) {
            // Se for igual, achamos: retorna o indice e a funcao termina aqui
            return i;
        }
        // Se nao for igual, o laco continua para o proximo i automaticamente
    }
    // Se o laco terminou sem nenhum "return i", e porque nao achou a chave
    return -1;
}

// Funcao principal: le a entrada, chama a busca, mede o tempo e imprime o resultado
int main() {
    int n;          // vai guardar o tamanho do vetor
    cin >> n;       // le o primeiro numero do arquivo de entrada (o tamanho)

    vector<int> A(n);  // cria um vetor de tamanho n (todos os elementos comecam em 0)
    for (int i = 0; i < n; i++) {  // percorre cada posicao do vetor
        cin >> A[i];                // le um numero da entrada e guarda na posicao i
    }

    int chave;      // vai guardar o numero que estamos procurando
    cin >> chave;    // le a chave (ultima linha do arquivo de entrada)

    // Guarda o instante de tempo atual, ANTES de comecar a busca
    auto inicio = chrono::high_resolution_clock::now();

    // A.data() pega o ponteiro para os dados internos do vector (para passar como int[])
    // 0 e n definem o intervalo [0, n), ou seja, o vetor inteiro
    int resultado = buscaLinear(A.data(), 0, n, chave);

    // Guarda o instante de tempo atual, DEPOIS que a busca terminou
    auto fim = chrono::high_resolution_clock::now();

    // Calcula a diferenca entre fim e inicio, convertendo para nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    // Imprime o indice encontrado (ou -1)
    cout << "Resultado: " << resultado << endl;
    // Imprime quanto tempo a busca levou, em nanossegundos
    cout << "Tempo (ns): " << duracao.count() << endl;

    return 0;  // indica que o programa terminou sem erros
}