// Trabalho 1 - EDB1 (DIM0119)
// Exercicio 4: Busca Sequencial Alternativa - Versao Recursiva
// Autor: Otávio Felipe

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Junta a recursao do exercicio 2 com o corte antecipado do exercicio 3
int buscaSeqAlternativaRecursiva(int A[], int esq, int dir, int chave) {
    // Caso base 1: intervalo vazio, nao ha mais nada a verificar
    if (esq >= dir) {
        return -1;
    }

    // Caso base 2: encontrou a chave na posicao atual
    if (A[esq] == chave) {
        return esq;
    }

    // Caso base 3: o elemento atual ja e maior que a chave.
    // Como o vetor esta ordenado, a chave nao pode estar mais adiante,
    // entao paramos aqui em vez de continuar chamando a funcao.
    if (A[esq] > chave) {
        return -1;
    }

    // Caso recursivo: nenhuma das condicoes acima se aplicou.
    // Chama a funcao de novo, avancando uma posicao (esq + 1)
    return buscaSeqAlternativaRecursiva(A, esq + 1, dir, chave);
}

int main() {
    int n;                 // tamanho do vetor
    cin >> n;              // le o tamanho

    vector<int> A(n);       // cria o vetor de tamanho n
    for (int i = 0; i < n; i++) {
        cin >> A[i];         // le cada elemento (ja ordenado)
    }

    int chave;               // valor procurado
    cin >> chave;             // le a chave

    // marca o instante antes de chamar a funcao de busca
    auto inicio = chrono::high_resolution_clock::now();

    // executa a busca no intervalo [0, n)
    int resultado = buscaSeqAlternativaRecursiva(A.data(), 0, n, chave);

    // marca o instante depois que a busca terminou
    auto fim = chrono::high_resolution_clock::now();

    // calcula a diferenca de tempo, em nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    cout << "Resultado: " << resultado << endl;          // mostra o indice (ou -1)
    cout << "Tempo (ns): " << duracao.count() << endl;   // mostra o tempo gasto

    return 0;
}