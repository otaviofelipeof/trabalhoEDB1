// Trabalho 1 - EDB1 (DIM0119)
// Exercicio 8: Busca Ternaria Recursiva
// Autor: Otávio Felipe

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Mesma logica do exercicio 7, mas cada divisao em 3 partes vira uma chamada recursiva
int buscaTernariaRecursiva(int A[], int esq, int dir, int chave) {
    // Caso base: intervalo vazio, a chave nao existe no vetor
    if (esq >= dir) {
        return -1;
    }

    // Calcula o tamanho do intervalo atual
    int tamanho = dir - esq;
    // m1 e o primeiro ponto de corte
    int m1 = esq + tamanho / 3;
    // m2 e o segundo ponto de corte
    int m2 = esq + (2 * tamanho) / 3;

    // Verifica se a chave esta em algum dos pontos de corte
    if (A[m1] == chave) {
        return m1;  // achou no primeiro ponto
    }
    if (A[m2] == chave) {
        return m2;  // achou no segundo ponto
    }

    // Decide em qual dos 3 tercos a busca deve continuar, e chama
    // a funcao de novo (recursao) apenas com aquele pedaco do vetor
    if (chave < A[m1]) {
        // busca so no primeiro terco: intervalo [esq, m1)
        return buscaTernariaRecursiva(A, esq, m1, chave);
    } else if (chave < A[m2]) {
        // busca so no terco do meio: intervalo [m1 + 1, m2)
        return buscaTernariaRecursiva(A, m1 + 1, m2, chave);
    } else {
        // busca so no ultimo terco: intervalo [m2 + 1, dir)
        return buscaTernariaRecursiva(A, m2 + 1, dir, chave);
    }
}
// Observacao: como o intervalo diminui para 1/3 do tamanho a cada chamada,
// a profundidade maxima de recursao e O(log n) na base 3 -- entao, assim como
// na busca binaria recursiva, nao ha risco de estouro de pilha aqui

int main() {
    int n;                  // tamanho do vetor
    cin >> n;               // le o tamanho

    vector<int> A(n);        // cria o vetor
    for (int i = 0; i < n; i++) {
        cin >> A[i];          // le cada elemento (ja ordenado)
    }

    int chave;                // valor procurado
    cin >> chave;              // le a chave

    // marca o tempo antes da busca
    auto inicio = chrono::high_resolution_clock::now();

    // executa a busca no vetor inteiro [0, n)
    int resultado = buscaTernariaRecursiva(A.data(), 0, n, chave);

    // marca o tempo depois da busca
    auto fim = chrono::high_resolution_clock::now();

    // calcula a duracao em nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    cout << "Resultado: " << resultado << endl;          // imprime o indice (ou -1)
    cout << "Tempo (ns): " << duracao.count() << endl;   // imprime o tempo gasto

    return 0;
}