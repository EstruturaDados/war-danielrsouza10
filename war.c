// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5

typedef struct {
    char nome[50];
    char corExercito[20];
    int numTropas;
} Territorio;

typedef enum { MISSao_DESTRUIR_VERDE, MISSao_CONQUISTAR_3 } Missao;

void inicializarTerritorios(Territorio territorios[]);
void exibirTerritorios(const Territorio territorios[]);
void atacar(Territorio territorios[]);
int verificarMissao(const Territorio territorios[], Missao missao);
void menu();


// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    Territorio territorios[MAX_TERRITORIOS];
    Missao missao;
    int escolha;
    srand(time(NULL));

    inicializarTerritorios(territorios);
    missao = (rand() % 2 == 0) ? MISSao_DESTRUIR_VERDE : MISSao_CONQUISTAR_3;

    do {
        menu();
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:
                atacar(territorios);
                break;
            case 2:
                if (verificarMissao(territorios, missao))
                    printf("Missão cumprida! Parabéns!\n");
                else
                    printf("Missão ainda não concluída.\n");
                break;
            case 0:
                printf("Saindo do jogo.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    return 0;
}

void inicializarTerritorios(Territorio territorios[]) {
    // Exemplo de inicialização automática
    strcpy(territorios[0].nome, "Território 1\n");
    strcpy(territorios[0].corExercito, "Verde\n");
    territorios[0].numTropas = 5;

    strcpy(territorios[1].nome, "Território 2\n");
    strcpy(territorios[1].corExercito, "Vermelho\n");
    territorios[1].numTropas = 3;

    strcpy(territorios[2].nome, "Território 3\n");
    strcpy(territorios[2].corExercito, "Azul\n");
    territorios[2].numTropas = 4;

    strcpy(territorios[3].nome, "Território 4\n");
    strcpy(territorios[3].corExercito, "Verde\n");
    territorios[3].numTropas = 2;

    strcpy(territorios[4].nome, "Território 5\n");
    strcpy(territorios[4].corExercito, "Amarelo\n");
    territorios[4].numTropas = 6;
}

void exibirTerritorios(const Territorio territorios[]) {
    printf("\nEstado atual dos territórios:\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d: %sCor: %sNúmero de Tropas: %d\n",
               i + 1,
               territorios[i].nome,
               territorios[i].corExercito,
               territorios[i].numTropas);
    }
}

void atacar(Territorio territorios[]) {
    int atacante, defensor;
    int dadosAtacante, dadosDefensor;

    exibirTerritorios(territorios);

    printf("Digite o território atacante (1-5): ");
    scanf("%d", &atacante);
    printf("Digite o território defensor (1-5): ");
    scanf("%d", &defensor);

    dadosAtacante = rand() % 6 + 1;
    dadosDefensor = rand() % 6 + 1;

    printf("Dados do atacante: %d\n", dadosAtacante);
    printf("Dados do defensor: %d\n", dadosDefensor);

    if (dadosAtacante >= dadosDefensor) {
        territorios[defensor - 1].numTropas--;
        printf("Atacante venceu! Defensor perde uma tropa.\n");
        if (territorios[defensor - 1].numTropas <= 0) {
            printf("Território %d conquistado!\n", defensor);
            strcpy(territorios[defensor - 1].corExercito, territorios[atacante - 1].corExercito);
            territorios[defensor - 1].numTropas = 1;
        }
    } else {
        printf("Defensor venceu! Nenhuma tropa perdida.\n");
    }
}

int verificarMissao(const Territorio territorios[], Missao missao) {
    int countVerde = 0;
    int countTerritoriosConquistados = 0;
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        if (strcmp(territorios[i].corExercito, "Verde\n") == 0) {
            countVerde++;
        } else {
            countTerritoriosConquistados++;
        }
    }

    if (missao == MISSao_DESTRUIR_VERDE) {
        return countVerde == 0;
    } else if (missao == MISSao_CONQUISTAR_3) {
        return countTerritoriosConquistados >= 3;
    }
    return 0;
}

void menu() {
    printf("\nMenu:\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
