# 🔢 Calculadora Padrão Programador em C

Este projeto foi desenvolvido para o módulo de "Lógica de Programação utilizando C" da formação **C/C++ Developer** na [DIO.pro](https://www.dio.me/). O objetivo foi criar uma ferramenta que execute operações aritméticas e conversões de bases numéricas diretamente no terminal.

## 🎯 Objetivo do Projeto

Diferente de calculadoras convencionais, este projeto foca na **representação de dados**. Implementei uma lógica que permite ao usuário realizar cálculos matemáticos e visualizar como esses valores são estruturados na memória do computador (Binário e Hexadecimal).

---

## 🧠 Conceitos de Aprendizado Aplicados

### 1. Manipulação de Bits (Bitwise Operations)

Como o C não possui um especificador nativo de impressão binária para todas as versões, implementei a lógica de **Deslocamento de Bits (`>>`)** e **Máscara de Bits (`&`)**.

* Isso demonstra o entendimento de como os dados de 32 bits (inteiros) são armazenados fisicamente.
* Em Ciência de Dados, esse conceito é a base para compressão de arquivos e otimização de performance.

### 2. Parsing de Entrada com `scanf`

Utilizei o `scanf` de forma estruturada para interpretar expressões complexas (Ex: `10.5 * 2`) em uma única linha.

* **Desafio Superado:** Gerenciamento do buffer do teclado (`stdin`) usando a limpeza manual de caracteres para evitar "lixo" na memória entre uma operação e outra.

### 3. Robustez e Controle de Fluxo

Em vez de depender de exceções (como o `try/except` do Python), o código utiliza **verificações proativas**:

* Tratamento de **Divisão por Zero**.
* Validação de tipos de dados no menu principal para evitar loops infinitos.

---

## 🕹️ Funcionalidades

- **Operações Aritméticas:** Adição, Subtração, Multiplicação e Divisão (com suporte a números reais).
- **Conversor de Bases:** - **Decimal para Hexadecimal:** Utilizando formatação direta de memória.
  - **Decimal para Binário:** Visualização por bytes (grupos de 8 bits).

---
