#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <windows.h> //Para utilizar o sleep

#define total_vagas 21 // Número total de vagas no estacionamento

/* Estrutura principal para as vagas de estacionamento
 * Cada vaga guarda:
 * - placa do veículo
 * - status de ocupação (1 = Livre, 0 = Ocupado)
 * - hora e minuto de entrada
 */
struct vaga_estacionamento {
    char placa [8]; // Placa do carro
    int ocupado;    // (1) Livre | (0) Ocupado
    int hora, minuto; // Horário de entrada
};
struct vaga_estacionamento vaga[total_vagas]; // Vetor de vagas

// Declaração da função de pagamento
void pagamento_estacionamento(float valor);

//===================================================

// Função para limpar a tela (compatível com Windows e Linux)
void limpar_tela() {
    system("cls || clear"); // Limpa a tela no Windows e Linux
}

//===================================================

/* Função para estacionar um veículo
 * Procura uma vaga livre e registra os dados do veículo
 */
void estacionar_veiculo() {
    int i;
    int encontrou_vaga = 0; // Controla se encontrou vaga livre
    
    printf("===============================================\n");
    printf("           === Estacionar Veículo ===          \n");
    printf("===============================================\n");

    // Procura uma vaga livre
    for(i = 0; i < total_vagas; i++) {
        if(vaga[i].ocupado == 1) { // Se a vaga estiver livre
            encontrou_vaga = 1;
            
            printf("Digite a placa do carro: ");
            scanf("%s", vaga[i].placa);

            printf("Digite o tempo de entrada (hh:mm): ");
            scanf("%d:%d", &vaga[i].hora, &vaga[i].minuto);

            printf("Vaga %d com a placa: %s estacionado\n", i + 1, vaga[i].placa);
            printf("===============================================\n");

            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n'); // Limpa o buffer
            getchar(); // Aguarda o Enter

            vaga[i].ocupado = 0; // Marca a vaga como ocupada
            break; // Encerra o loop após encontrar uma vaga
        }
    }
    
    // Se não encontrou vaga livre
    if(!encontrou_vaga) {
        printf("===============================================\n");
        printf("     [INFO] Todas as vagas estão ocupadas!     \n");
        printf("===============================================\n");
        
        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n'); // Limpa o buffer
        getchar(); // Aguarda o Enter
    }
}

/* Função para processar o pagamento do estacionamento
 * Recebe o valor a ser pago e oferece diferentes métodos de pagamento
 */
void pagamento_estacionamento(float valor) {
    // Variáveis
    int menu_pagamento;
    float pago;

    printf("================================================\n");
    printf("======== Selecione a forma de pagamento ========\n");
    printf("================================================\n");
    printf("| Código |         Forma de Pagamento          |\n");
    printf("|--------|-------------------------------------|\n");
    printf("|   1    | PIX                                 |\n");
    printf("|   2    | Dinheiro                            |\n");
    printf("|   3    | Débito                              |\n");
    printf("|   4    | Crédito                             |\n");
    printf("================================================\n");
    printf("Digite o código da opção desejada: ");
    scanf("%d", &menu_pagamento);

    switch(menu_pagamento) {
        case 1: // Pagamento via PIX
            printf("Chave PIX: estacionamento@empresa.com\n");
            printf("Valor a ser pago: R$ %.2f\n", valor);
            printf("Simulando pagamento via PIX...\nPagamento confirmado!\n");
            break;

        case 2: // Pagamento em dinheiro
            printf("Valor a ser pago: R$ %.2f\n", valor);
            printf("Digite o valor entregue pelo cliente: R$ ");
            scanf("%f", &pago);
            if (pago >= valor) {
                printf("Pagamento confirmado!\nTroco: R$ %.2f\n", pago - valor);
            } else {
                printf("Valor insuficiente! Operação cancelada.\n");
            }
            break;

        case 3: // Pagamento com cartão de débito
            printf("Pagamento via cartão de débito\n");
            printf("Valor debitado: R$ %.2f\nPagamento aprovado!\n", valor);
            break;

        case 4: // Pagamento com cartão de crédito
            printf("Pagamento via cartão de crédito\n");
            printf("Valor creditado: R$ %.2f\nPagamento aprovado!\n", valor);
            break;

        default: // Opção inválida
            printf("Opção inválida. Cancelando pagamento.\n");
            break;
    }
    
    printf("\nObrigado pela preferência, volte sempre!\n");

    printf("\n\nPressione Enter para continuar...");
    while (getchar() != '\n'); // Limpa buffer
    getchar(); // Aguarda o Enter
}

//===================================================

/* Função para retirar um veículo do estacionamento
 * Busca o veículo pela placa, calcula o tempo e valor,
 * processa o pagamento e libera a vaga
 */
void retirar_veiculo() {
    int i, saida_hora, saida_minuto;
    // Variáveis para o cálculo do valor
    int tempo_entrada_min, tempo_saida_min, tempo_total_min;
    int horas_completas, minutos_restantes;
    float valor_total;
    char retirar_placa[8];
    int encontrou = 0; // Controla se encontrou o veículo
    
    printf("===============================================\n");
    printf("           === Retirar o Carro ===            \n");
    printf("===============================================\n");
    printf("\nDigite a placa do carro para retirar: ");
    scanf("%s", retirar_placa);
    
    // Busca o veículo em todas as vagas
    for(i = 0; i < total_vagas; i++) {
        if(strcmp(vaga[i].placa, retirar_placa) == 0) {
            encontrou = 1; // Marca que encontrou o veículo
            
            // Mensagem quando o carro é encontrado
            limpar_tela();
            printf("===============================================\n");
            printf("  O carro com a placa: %s foi encontrado      \n", vaga[i].placa);
            printf("===============================================\n");
            printf("\nDigite o tempo de retirada (hh:mm): ");
            scanf("%d:%d", &saida_hora, &saida_minuto);

            // Cálculo do tempo e valor
            tempo_entrada_min = vaga[i].hora * 60 + vaga[i].minuto;
            tempo_saida_min = saida_hora * 60 + saida_minuto;
            
            // Verifica se o horário de saída não é anterior ao de entrada
            if (tempo_saida_min < tempo_entrada_min) {
                // Mensagem de erro
                limpar_tela();
                printf("===============================================\n");
                printf("        Erro: Horário de retirada              \n");
                printf("        não pode ser anterior ao horário       \n");
                printf("        de entrada.                            \n");
                printf("===============================================\n");

                printf("\nPressione Enter para continuar...");
                while (getchar() != '\n'); // Limpa o buffer
                getchar(); // Aguarda o Enter

                return;
            }

            // Calcula o tempo total em minutos
            tempo_total_min = tempo_saida_min - tempo_entrada_min;
            
            // Converte para horas e minutos
            horas_completas = tempo_total_min / 60;
            minutos_restantes = tempo_total_min % 60;
            
            // Calcula o valor a pagar (R$5 por hora, R$2 adicionais para frações >= 30min)
            valor_total = horas_completas * 5;
            if (minutos_restantes >= 30) {
                valor_total += 2;
            }
            
            limpar_tela();
            // Exibe o tempo e o valor a ser pago
            printf("Tempo total: %02d hora(s) e %02d minuto(s)\n", horas_completas, minutos_restantes);
            printf("Valor a ser pago: R$ %.2f\n", valor_total);
            printf("===============================================\n\n\n");
            
            // Processa o pagamento
            pagamento_estacionamento(valor_total);
            
            // Após o pagamento, libera a vaga
            vaga[i].ocupado = 1; // Marca como livre
            strcpy(vaga[i].placa, ""); // Limpa a placa
            vaga[i].hora = 0;
            vaga[i].minuto = 0; // Zera os horários
            
            break; // Encerra o loop após encontrar o veículo
        }
    }
    
    // Se não encontrou o veículo após verificar todas as vagas
    if(!encontrou) {
        limpar_tela();
        printf("===============================================\n");
        printf("         Placa não encontrada                  \n");
        printf("===============================================\n");
        
        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n'); // Limpa o buffer
        getchar(); // Aguarda o Enter
    }
}

//===================================================

/* Função para mostrar as vagas ocupadas
 * Lista todas as vagas que estão atualmente em uso
 */
void mostrar_vagas() {
    int i;
    int encontrou = 0; // Controla se encontrou alguma vaga ocupada
    int vagas_livres = 0; // Contador de vagas livres
    
    printf("===============================================\n");
    printf("           === Status das Vagas ===           \n");
    printf("===============================================\n\n");
    
    // Verifica todas as vagas
    for(i = 0; i < total_vagas; i++) {
        if(vaga[i].ocupado == 0) { // Se a vaga estiver ocupada
            encontrou = 1; // Marca que encontrou pelo menos uma vaga ocupada
            
            printf("---------------------------------------------------\n");
            printf(" Vaga Nº %02d\n", i + 1);
            printf(" Placa do veículo : %s\n", vaga[i].placa);
            printf(" Horário de entrada: %02d:%02d\n", vaga[i].hora, vaga[i].minuto);
            printf("---------------------------------------------------\n\n");
        } else {
            vagas_livres++; // Incrementa o contador de vagas livres
        }
    }
    
    // Exibe o resumo das vagas
    printf("\n===============================================\n");
    printf(" Total: %d vagas | %d ocupadas | %d livres\n",	
			total_vagas, total_vagas - vagas_livres, vagas_livres);
    printf("===============================================\n");
    
    // Se não encontrou nenhuma vaga ocupada
    if(!encontrou) {
        printf("\n===============================================\n");
        printf("     [INFO] Nenhuma vaga está ocupada no momento\n");
        printf("===============================================\n");
    }
    
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n'); // Limpa o buffer
    getchar(); // Aguarda o Enter
}

//===================================================

int main(void) {
    setlocale(LC_ALL, "portuguese"); // Define idioma português para acentuação

    int i, menu;

    // Inicializa todas as vagas como livres
    for(i = 0; i < total_vagas; i++) {
        vaga[i].ocupado = 1; // 1 = livre
        strcpy(vaga[i].placa, ""); // Inicializa placa vazia
        vaga[i].hora = 0;
        vaga[i].minuto = 0; // Zera os horários
    }
    
    // Loop principal do programa
    do {
        printf("===============================================\n");
        printf("       SISTEMA DE ESTACIONAMENTO - PRINCIPAL    \n");
        printf("===============================================\n");
        printf("                1 - Estacionar Veículo          \n");
        printf("                2 - Retirar Veículo             \n");
        printf("                3 - Mostrar Vagas               \n");
        printf("                4 - Sair                        \n");
        printf("===============================================\n");
        printf("        Escolha uma opção [1-4]: ");
        scanf("%d", &menu);

        switch(menu) {
            case 1: // Estacionar veículo
                limpar_tela();
                estacionar_veiculo();
                Sleep(1000); // Pausa de 1 segundo
                limpar_tela();
                break;

            case 2: // Retirar veículo
                limpar_tela();
                retirar_veiculo();
                Sleep(1000); // Pausa de 1 segundo
                limpar_tela();
                break;

            case 3: // Mostrar vagas
                limpar_tela();
                mostrar_vagas();
                Sleep(1000); // Pausa de 1 segundo
                limpar_tela();
                break;

            case 4: // Sair do programa
                limpar_tela();
                printf("Saindo do sistema...\n");
                break;
                
            default: // Opção inválida
                printf("Opção inválida.\n");
                Sleep(2000); // Pausa de 2 segundos
        }
        limpar_tela();
    } while(menu != 4); // Continua até escolher a opção Sair

    return 0;
}
