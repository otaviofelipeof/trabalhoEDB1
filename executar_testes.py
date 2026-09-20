# executar_testes.py
# Script auxiliar (nao faz parte da implementacao dos algoritmos em si).
# Roda cada um dos 8 programas varias vezes para cada tamanho de vetor,
# calcula a media dos tempos e salva tudo em um arquivo CSV.

import subprocess  # biblioteca para rodar programas externos (os .exe) e capturar a saida
import csv         # biblioteca para gravar os resultados em formato de tabela CSV

START_SIZE = 0        # menor tamanho testado (deve bater com gerar_testes.py)
END_SIZE = 500000      # maior tamanho testado
STEP = 10000            # intervalo entre tamanhos

REPETICOES = 10  # quantas vezes cada teste roda, para calcular a media (TRIALS do professor)

# Gera a mesma lista de tamanhos usada na geracao dos arquivos de teste
TAMANHOS = list(range(START_SIZE, END_SIZE + 1, STEP))

# Dicionario que associa o numero de cada exercicio ao nome do .exe correspondente
EXECUTAVEIS = {
    1: "ex1.exe", 2: "ex2.exe", 3: "ex3.exe", 4: "ex4.exe",
    5: "ex5.exe", 6: "ex6.exe", 7: "ex7.exe", 8: "ex8.exe",
}

def rodar_uma_vez(executavel, arquivo_entrada):
    # Roda o programa UMA vez, usando o arquivo de entrada como se fosse digitado
    # Retorna o tempo em nanossegundos, ou None se o programa falhar (ex: stack overflow)
    with open(arquivo_entrada, "r") as f:  # abre o arquivo de teste para leitura
        resultado = subprocess.run(
            [executavel],       # qual programa rodar (ex: "ex1.exe")
            stdin=f,             # o conteudo do arquivo vira a entrada padrao do programa
            capture_output=True, # captura tudo que o programa imprime
            text=True            # trata a saida como texto (nao como bytes)
        )

    # returncode diferente de 0 significa que o programa terminou com erro
    # (por exemplo, crash por estouro de pilha na recursao profunda)
    if resultado.returncode != 0:
        return None  # avisa que essa execucao falhou

    # Percorre cada linha da saida do programa procurando o padrao "Tempo (ns): <numero>"
    for linha in resultado.stdout.splitlines():
        if linha.startswith("Tempo (ns):"):
            # Pega o texto depois dos dois pontos, remove espacos extras,
            # e converte de texto para numero inteiro
            return int(linha.split(":")[1].strip())

    # Se nao achou a linha esperada na saida, algo deu errado
    return None

def media_de_execucoes(executavel, arquivo_entrada, repeticoes=REPETICOES):
    # Roda o mesmo teste varias vezes e calcula a media, para reduzir ruido do sistema
    tempos = []  # lista vazia que vai guardar o tempo de cada execucao
    for _ in range(repeticoes):  # repete "repeticoes" vezes (o _ significa que nao usamos o contador)
        tempo = rodar_uma_vez(executavel, arquivo_entrada)  # roda uma vez e pega o tempo
        if tempo is None:
            # Se uma unica execucao falhar, descartamos a media inteira
            # (mais seguro do que tirar a media so das que deram certo)
            return None
        tempos.append(tempo)  # adiciona o tempo na lista
    return sum(tempos) / len(tempos)  # calcula a media: soma de tudo dividido pela quantidade

def main():
    # Lista que vai acumular uma linha por combinacao de (exercicio, caso, tamanho, tempo)
    linhas = []

    # Percorre cada um dos 8 exercicios (item.items() devolve pares chave-valor do dicionario)
    for num_exercicio, exe in EXECUTAVEIS.items():
        # Percorre cada tamanho de vetor
        for n in TAMANHOS:
            # Testa tanto o melhor caso ("m") quanto o pior caso ("p")
            for caso in ["m", "p"]:
                # Monta o nome do arquivo de teste correspondente (ex: "p1v10000.txt")
                arquivo = f"{caso}{num_exercicio}v{n}.txt"

                # Roda o teste varias vezes e calcula a media
                media = media_de_execucoes(exe, arquivo)

                if media is None:
                    # Avisa no terminal que esse ponto foi pulado (ex: stack overflow do ex2/ex4)
                    print(f"Exercicio {num_exercicio} | caso={caso} | n={n} | FALHOU (pulado)")
                    continue  # pula para a proxima combinacao, sem gravar nada

                # Guarda o resultado valido na lista de linhas
                linhas.append([num_exercicio, caso, n, media])
                # Mostra o progresso no terminal, formatando a media com 2 casas decimais
                print(f"Exercicio {num_exercicio} | caso={caso} | n={n} | media={media:.2f}ns")

    # Grava todos os resultados coletados no arquivo CSV
    with open("resultados.csv", "w", newline="") as f:  # abre o arquivo para escrita
        writer = csv.writer(f)                            # cria um "escritor" de CSV
        writer.writerow(["exercicio", "caso", "n", "tempo_ns"])  # escreve o cabecalho da tabela
        writer.writerows(linhas)                            # escreve todas as linhas de uma vez

    print("Concluido! Resultados salvos em resultados.csv")  # avisa que terminou

# So roda o main() se este arquivo for executado diretamente
if __name__ == "__main__":
    main()