#include <iostream>
#include <string>

// Simulação do Aspecto: Função Transversal de Log
void verificarSaldoAspecto(float saldo, float saque, std::string tipoConta) {
    if (saque > saldo) {
        std::cout << "[LOG DE ERRO - " << tipoConta << "]: Saldo insuficiente! "
                  << "Tentativa de saque: R$" << saque << " | Saldo atual: R$" << saldo << std::endl;
    }
}

class Conta {
    protected:
        float saldo;
        std::string nome;
        
    public:
        Conta(std::string n, float s) : nome(n), saldo(s) {}
        
        // O saque chama o "Aspecto" antes de executar
        void sacar(float valor) {
            verificarSaldoAspecto(saldo, valor, nome);
            if (valor <= saldo) {
                saldo -= valor;
                std::cout << "Saque de R$" << valor << " realizado na " << nome << ".\n";
            }
        }
};

int main() {
    Conta corrente("Conta Corrente", 500.0);
    Conta investimento("Conta Investimento", 1000.0);

    corrente.sacar(600.0);    // Deve disparar o Log (Aspecto)
    investimento.sacar(200.0); // Deve processar normalmente
    
    return 0;
}