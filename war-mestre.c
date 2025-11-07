// Mestre (aula 1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio conforme especificado
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Vetor de missões pré-definidas (pelo menos 5)
char* missoes[] = {
    "Controlar pelo menos 5 territorios",
    "Eliminar todas as tropas do jogador vermelho",
    "Conquistar o territorio 'Centro'",
    "Controlar 3 territorios seguidos",
    "Eliminar pelo menos 10 tropas inimigas"
};
int totalMissoes = 5;

// Função para sortear e atribuir missão ao jogador
// Passa destino por referência (char*) para modificar o conteúdo
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Função para exibir a missão do jogador
// Passa missao por valor (char*) para apenas ler e exibir
void exibirMissao(char* missao) {
    printf("Sua missao: %s\n", missao);
}

// Função para verificar se a missão foi cumprida
// Passa missao por referência (char*) para acessar o conteúdo, mapa por referência
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Lógica simples baseada nas missões definidas
    if (strcmp(missao, "Controlar pelo menos 5 territorios") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {  // Assumindo jogador azul
                count++;
            }
        }
        return count >= 5;
    } else if (strcmp(missao, "Eliminar todas as tropas do jogador vermelho") == 0) {
        int totalVermelho = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) {
                totalVermelho += mapa[i].tropas;
            }
        }
        return totalVermelho == 0;
    } else if (strcmp(missao, "Conquistar o territorio 'Centro'") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].nome, "Centro") == 0 && strcmp(mapa[i].cor, "azul") == 0) {
                return 1;
            }
        }
        return 0;
    } else if (strcmp(missao, "Controlar 3 territorios seguidos") == 0) {
        // Simples: verificar se há 3 consecutivos da mesma cor (azul)
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && strcmp(mapa[i+1].cor, "azul") == 0 && strcmp(mapa[i+2].cor, "azul") == 0) {
                return 1;
            }
        }
        return 0;
    } else if (strcmp(missao, "Eliminar pelo menos 10 tropas inimigas") == 0) {
        // Assumindo que inimigo é vermelho, contar tropas perdidas (não implementado totalmente, lógica simples)
        // Para simplicidade, contar se há menos de 10 tropas vermelhas totais inicialmente (não rastreia perdas)
        // Em um jogo real, precisaria rastrear perdas, mas aqui é simples
        int totalVermelho = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) {
                totalVermelho += mapa[i].tropas;
            }
        }
        return totalVermelho < 10;  // Simulação simples
    }
    return 0;  // Missão não reconhecida
}

// Função para simular ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Nao pode atacar territorio proprio!\n");
        return;
    }
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    printf("Dado atacante: %d, Dado defensor: %d\n", dadoAtacante, dadoDefensor);
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence: transfere cor e metade das tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= atacante->tropas / 2;
        printf("Atacante venceu! Territorio conquistado.\n");
    } else {
        // Defensor vence: atacante perde 1 tropa
        atacante->tropas--;
        printf("Defensor venceu! Atacante perdeu 1 tropa.\n");
    }
}

// Função para exibir o mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\nMapa atual:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s - Cor: %s, Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função para liberar memória alocada
void liberarMemoria(Territorio* mapa, char* missaoJ1, char* missaoJ2) {
    free(mapa);
    free(missaoJ1);
    free(missaoJ2);
}

int main() {
    srand(time(NULL));  // Inicializar semente para rand()

    // Alocar mapa dinamicamente (exemplo com 10 territórios)
    int tamanhoMapa = 10;
    Territorio* mapa = (Territorio*)malloc(tamanhoMapa * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para mapa.\n");
        return 1;
    }

    // Inicializar mapa com dados de exemplo
    strcpy(mapa[0].nome, "Norte");
    strcpy(mapa[0].cor, "azul");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Sul");
    strcpy(mapa[1].cor, "vermelho");
    mapa[1].tropas = 4;

    strcpy(mapa[2].nome, "Leste");
    strcpy(mapa[2].cor, "azul");
    mapa[2].tropas = 3;

    strcpy(mapa[3].nome, "Oeste");
    strcpy(mapa[3].cor, "vermelho");
    mapa[3].tropas = 6;

    strcpy(mapa[4].nome, "Centro");
    strcpy(mapa[4].cor, "vermelho");
    mapa[4].tropas = 7;

    strcpy(mapa[5].nome, "Nordeste");
    strcpy(mapa[5].cor, "azul");
    mapa[5].tropas = 2;

    strcpy(mapa[6].nome, "Sudeste");
    strcpy(mapa[6].cor, "vermelho");
    mapa[6].tropas = 5;

    strcpy(mapa[7].nome, "Noroeste");
    strcpy(mapa[7].cor, "azul");
    mapa[7].tropas = 4;

    strcpy(mapa[8].nome, "Sudoeste");
    strcpy(mapa[8].cor, "vermelho");
    mapa[8].tropas = 3;

    strcpy(mapa[9].nome, "Meio");
    strcpy(mapa[9].cor, "azul");
    mapa[9].tropas = 6;

    // Alocar missões dinamicamente para dois jogadores
    char* missaoJ1 = (char*)malloc(100 * sizeof(char));  // Tamanho suficiente para string
    char* missaoJ2 = (char*)malloc(100 * sizeof(char));
    if (missaoJ1 == NULL || missaoJ2 == NULL) {
        printf("Erro ao alocar memoria para missoes.\n");
        liberarMemoria(mapa, missaoJ1, missaoJ2);
        return 1;
    }

    // Atribuir missões sorteadas
    atribuirMissao(missaoJ1, missoes, totalMissoes);
    atribuirMissao(missaoJ2, missoes, totalMissoes);

    // Exibir missões uma vez no início (passando por valor)
    printf("Jogador 1:\n");
    exibirMissao(missaoJ1);
    printf("Jogador 2:\n");
    exibirMissao(missaoJ2);

    // Loop de turnos (simplificado para 2 jogadores)
    int turno = 1;
    int vencedor = 0;
    while (!vencedor) {
        printf("\n--- Turno %d ---\n", turno);
        exibirMapa(mapa, tamanhoMapa);

        // Turno do Jogador 1 (azul)
        printf("Turno do Jogador 1 (azul):\n");
        // Simulação: escolher ataque (exemplo fixo para simplicidade)
        int idxAtacante = 0;  // Norte (azul)
        int idxDefensor = 1;  // Sul (vermelho)
        if (strcmp(mapa[idxAtacante].cor, "azul") == 0 && strcmp(mapa[idxDefensor].cor, "vermelho") == 0) {
            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
        }

        // Verificar missão do Jogador 1
        if (verificarMissao(missaoJ1, mapa, tamanhoMapa)) {
            printf("Jogador 1 venceu! Missao cumprida.\n");
            vencedor = 1;
            break;
        }

        // Turno do Jogador 2 (vermelho)
        printf("Turno do Jogador 2 (vermelho):\n");
        idxAtacante = 1;  // Sul (agora possivelmente azul)
        idxDefensor = 2;  // Leste (azul)
        if (strcmp(mapa[idxAtacante].cor, "vermelho") == 0 && strcmp(mapa[idxDefensor].cor, "azul") == 0) {
            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
        }

        // Verificar missão do Jogador 2
        if (verificarMissao(missaoJ2, mapa, tamanhoMapa)) {
            printf("Jogador 2 venceu! Missao cumprida.\n");
            vencedor = 1;
            break;
        }

        turno++;
        if (turno > 20) {  // Limite para evitar loop infinito
            printf("Jogo encerrado sem vencedor.\n");
            break;
        }
    }

    // Liberar memória
    liberarMemoria(mapa, missaoJ1, missaoJ2);

    return 0;
}
