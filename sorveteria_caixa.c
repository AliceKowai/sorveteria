#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_RECORDS 100
#define PRECO_SORVETE 1.0

typedef struct {
    char sabor[50];
    int quantidade;
    float valor;
    char dataHora[100];
} Venda;

typedef struct {
    char descricao[50];
    float valor;
    char dataHora[100];
} Despesa;

Venda vendas[MAX_RECORDS];
Despesa despesas[MAX_RECORDS];
int totalVendas = 0, totalDespesas = 0;
float saldo = 0.0;

void registrarVenda();
void registrarDespesa();
void exibirRelatorioDiario();
void exibirSaldo();
void fecharCaixa();
void obterDataHoraAtual(char *buffer, int tamanho);

int main() {
    int opcao;
    
    do {
        printf("\nControle de Caixa da Sorveteria\n");
        printf("1. Registrar Venda de Sorvete\n");
        printf("2. Registrar Despesa\n");
        printf("3. Exibir Relatório Diário\n");
        printf("4. Exibir Saldo\n");
        printf("5. Fechar Caixa e Exibir Valor do Dia\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrarVenda();
                break;
            case 2:
                registrarDespesa();
                break;
            case 3:
                exibirRelatorioDiario();
                break;
            case 4:
                exibirSaldo();
                break;
            case 5:
                fecharCaixa();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    return 0;
}

void registrarVenda() {
    if (totalVendas < MAX_RECORDS) {
        float dinheiroRecebido, troco;
        int quantidade;
        
        printf("Informe o sabor do sorvete: ");
        scanf(" %[^\n]", vendas[totalVendas].sabor); // Lê uma string com espaços
        
        printf("Quantidade de sorvetes: ");
        scanf("%d", &quantidade);

        vendas[totalVendas].quantidade = quantidade;
        vendas[totalVendas].valor = quantidade * PRECO_SORVETE; // Valor baseado na quantidade

        printf("Dinheiro recebido: ");
        scanf("%f", &dinheiroRecebido);

        if (dinheiroRecebido >= vendas[totalVendas].valor) {
            troco = dinheiroRecebido - vendas[totalVendas].valor;
            printf("Troco: R$ %.2f\n", troco);
            
            saldo += vendas[totalVendas].valor; // Adiciona o valor da venda ao saldo
            obterDataHoraAtual(vendas[totalVendas].dataHora, 100); // Registra data e hora
            
            totalVendas++;
        } else {
            printf("Dinheiro insuficiente!\n");
        }
    } else {
        printf("Limite de registros de vendas atingido!\n");
    }
}

void registrarDespesa() {
    if (totalDespesas < MAX_RECORDS) {
        float valorDespesa;
        
        printf("Motivo da despesa: ");
        scanf(" %[^\n]", despesas[totalDespesas].descricao);
        printf("Valor da despesa: ");
        scanf("%f", &valorDespesa);

        if (valorDespesa <= saldo) {
            saldo -= valorDespesa; // Subtrai a despesa do saldo
            despesas[totalDespesas].valor = valorDespesa;
            obterDataHoraAtual(despesas[totalDespesas].dataHora, 100); // Registra data e hora
            
            totalDespesas++;
        } else {
            printf("Saldo insuficiente para essa despesa!\n");
        }
    } else {
        printf("Limite de registros de despesas atingido!\n");
    }
}

void exibirRelatorioDiario() {
    printf("\n--- Relatório Diário ---\n");
    
    printf("\nVendas:\n");
    for (int i = 0; i < totalVendas; i++) {
        printf("  Sabor: %s, Quantidade: %d, Valor: R$ %.2f, Data/Hora: %s\n",
               vendas[i].sabor, vendas[i].quantidade, vendas[i].valor, vendas[i].dataHora);
    }

    printf("\nDespesas:\n");
    for (int i = 0; i < totalDespesas; i++) {
        printf("  %s: R$ %.2f, Data/Hora: %s\n", despesas[i].descricao, despesas[i].valor, despesas[i].dataHora);
    }

    printf("\nSaldo atual: R$ %.2f\n", saldo);
}

void exibirSaldo() {
    printf("Saldo atual: R$ %.2f\n", saldo);
}

void fecharCaixa() {
    printf("\n--- Fechamento do Caixa ---\n");
    exibirRelatorioDiario();
    printf("\nValor final do caixa: R$ %.2f\n", saldo);
    // Zerar os valores para o próximo dia
    totalVendas = 0;
    totalDespesas = 0;
    saldo = 0.0;
}

void obterDataHoraAtual(char *buffer, int tamanho) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, tamanho, "%02d/%02d/%04d %02d:%02d:%02d", 
             tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 
             tm.tm_hour, tm.tm_min, tm.tm_sec);
}
