# ⚔️ C++ Dungeon Crawler: Explorando Matrizes e Estados

Este projeto foi desenvolvido como parte da formação **C/C++ Developer** na [DIO.pro](https://www.dio.me/). Fugindo do óbvio, implementei um jogo de exploração de masmorras via terminal que aplica conceitos fundamentais de computação de baixo nível.

## 🎯 Objetivo do Projeto
O objetivo foi construir um motor de jogo simples que gerencia uma **matriz bidimensional**, processa entradas do usuário em tempo real e mantém um sistema de estados (vida, energia e eventos) persistente durante a execução.

---

## 🧠 Conceitos de Aprendizado Aplicados

### 1. Manipulação de Matrizes (Dataframes de Baixo Nível)
Para um aspirante a Cientista de Dados, entender como o C++ organiza uma matriz na memória é fundamental. O mapa do jogo é uma `char[][]`, onde cada célula representa um dado geoespacial. 
* **Colisão:** Verificação de índices da matriz para impedir movimento em 'paredes'.
* **Spawn Aleatório:** Uso de `rand()` e `time.seed` para distribuição estocástica de itens e inimigos.

### 2. Gerenciamento de Memória e Ponteiros
Diferente do Python, onde a passagem de objetos é automática, aqui utilizei **Passagem por Referência** (`&`) para permitir que as funções de movimento alterassem diretamente o objeto do jogador, economizando memória e aumentando a performance.

### 3. Programação Estruturada e Modular
O código foi dividido em três partes para seguir boas práticas de engenharia:
* `jogo.h`: Interface e contratos (Protótipos e Structs).
* `jogo.cpp`: Implementação da lógica de negócio.
* `main.cpp`: Ponto de entrada e gerenciamento do Game Loop.

---

## 🕹️ Como Jogar

### Pré-requisitos
* Compilador G++ (GCC) instalado.

### Compilação e Execução
No terminal, dentro da pasta do projeto, execute:
```bash
g++ main.cpp jogo.cpp -o dungeon_game
./dungeon_game
```

Comandos
- ``W``: Mover para Cima
- ``A``: Mover para Esquerda
- ``S``: Mover para Baixo
- ``D``: Mover para Direita

O jogo aceita comandos em maiúsculo ou minúsculo.
