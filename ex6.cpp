// Trabalho 1 - EDB1 (DIM0119)
// Exercicio 6: Busca Binaria Recursiva
// Autor: Otávio Felipe

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Mesma logica do exercicio 5, mas cada "descarte de metade" e uma chamada recursiva
int buscaBinariaRecursiva(int A[], int esq, int dir, int chave) {
    // Caso base: intervalo vazio, elemento nao existe no vetor
    if (esq >= dir) {
        return -1;
    }

    // Calcula o meio do intervalo (mesma formula do exercicio 5, evita overflow)
    int m = esq + (dir - esq) / 2;

    // Compara o elemento do meio com a chave
    if (A[m] == chave) {
        return m;  // achou no meio
    } else if (chave < A[m]) {
        // Chama a funcao de novo, agora so na metade esquerda [esq, m)
        return buscaBinariaRecursiva(A, esq, m, chave);
    } else {
        // Chama a funcao de novo, agora so na metade direita [m + 1, dir)
        return buscaBinariaRecursiva(A, m + 1, dir, chave);
    }
}
// Observacao: como cada chamada reduz o intervalo pela metade, a profundidade
// maxima de chamadas e O(log n) por isso nao ha risco de estouro de pilha
// aqui, diferente do que acontece na busca linear recursiva (exercicio 2)

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
    int resultado = buscaBinariaRecursiva(A.data(), 0, n, chave);

    // marca o tempo depois da busca
    auto fim = chrono::high_resolution_clock::now();

    // calcula a duracao em nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    cout << "Resultado: " << resultado << endl;          // imprime o indice (ou -1)
    cout << "Tempo (ns): " << duracao.count() << endl;   // imprime o tempo gasto

    return 0;
}
