#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// --- Protótipos das Funções ---
void limparBuffer();
void converterBase(int n);
void operacoesBasicas();

int main() {
    int opcao;
    int numeroParaConversao;

    do {
        printf("\n====================================");
        printf("\n   CALCULADORA KIRSTEN 2000");
        printf("\n====================================");
        printf("\n1. Operacoes Basicas (+, -, *, /)");
        printf("\n2. Conversor de Base (Hex/Bin)");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        
        // Validação simples de entrada do menu
        if (scanf("%d", &opcao) != 1) {
            printf("\nErro: Digite apenas numeros!\n");
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1:
                operacoesBasicas();
                break;
            case 2:
                printf("Digite um numero decimal inteiro: ");
                scanf("%d", &numeroParaConversao);
                converterBase(numeroParaConversao);
                break;
            case 0:
                printf("Encerrando a calculadora... Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

void limparBuffer() {
    // Essencial em C para evitar que o '\n' do Enter suje o próximo scanf
    while (getchar() != '\n');
}

void operacoesBasicas() {
    float n1, n2, resultado;
    char op;

    printf("\nDigite a expressao: ");
    // O espaço antes do %c ignora espaços em branco na entrada
    if (scanf("%f %c %f", &n1, &op, &n2) != 3) {
        printf("Erro: Formato invalido. Use 'numero operador numero'.\nOs operadores validos sao: '+', '-', '*', e '/'\n");
        limparBuffer();
        return;
    }

    switch (op) {
        case '+': resultado = n1 + n2; break;
        case '-': resultado = n1 - n2; break;
        case '*': resultado = n1 * n2; break;
        case '/':
            if (n2 == 0) {
                printf("ERRO: Divisao por zero detectada!\n");
                return;
            }
            resultado = n1 / n2;
            break;
        default:
            printf("Operador '%c' nao reconhecido.\nOs operadores validos sao: '+', '-', '*', e '/'\n", op);
            return;
    }

    printf(">>> Resultado: %.2f\n", resultado);
    limparBuffer(); 
}

void converterBase(int n) {
    printf("\n--- RESULTADOS DE CONVERSAO ---");
    printf("\nDECIMAL:     %d", n);
    printf("\nHEXADECIMAL: %X", n); // %X imprime em Hexa maiúsculo
    
    printf("\nBINARIO:     ");
    // Lógica de Bitwise: percorre os 32 bits de um inteiro
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
        if (i % 8 == 0) printf(" "); // Espaço visual entre bytes
    }
    printf("\n-------------------------------\n");
}
