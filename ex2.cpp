// Trabalho 1 - EDB1 (DIM0119)
// Exercicio 2: Busca Linear Recursiva
// Autor: Otávio Felipe

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Versao recursiva da busca linear: em vez de um laco for, a funcao chama a si mesma
int buscaLinearRecursiva(int A[], int esq, int dir, int chave) {
    // Caso base 1: se esq chegou a dir (ou passou), o intervalo esta vazio
    // Isso significa que percorremos tudo e nao achamos a chave
    if (esq >= dir) {
        return -1;
    }

    // Caso base 2: verifica se o elemento na posicao esq e a chave procurada
    if (A[esq] == chave) {
        return esq;  // achou: retorna a posicao atual
    }

    // Caso recursivo: nao achou na posicao esq, entao chama a funcao de novo,
    // mas agora buscando a partir de esq + 1 (uma posicao a frente)
    return buscaLinearRecursiva(A, esq + 1, dir, chave);
}

int main() {
    int n;              // tamanho do vetor
    cin >> n;           // le o tamanho

    vector<int> A(n);   // cria o vetor de tamanho n
    for (int i = 0; i < n; i++) {
        cin >> A[i];     // le cada elemento do vetor
    }

    int chave;           // valor que sera buscado
    cin >> chave;        // le a chave

    auto inicio = chrono::high_resolution_clock::now();  // marca o tempo antes de buscar

    // Chama a busca recursiva no intervalo [0, n), passando o ponteiro do vetor
    int resultado = buscaLinearRecursiva(A.data(), 0, n, chave);

    auto fim = chrono::high_resolution_clock::now();  // marca o tempo depois de buscar

    // Calcula quanto tempo passou entre inicio e fim, em nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    cout << "Resultado: " << resultado << endl;         // mostra o indice encontrado (ou -1)
    cout << "Tempo (ns): " << duracao.count() << endl;  // mostra o tempo gasto

    return 0;
}