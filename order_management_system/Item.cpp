#include "Item.h"
#include "Produto.h"
#include <iostream>

// Construtor - inicializa as variáveis membro
Item::Item(int num, int qtd, Produto* prod)
        : numero(num), quantidade(qtd), produto(prod) {}

// Destrutor
Item::~Item() {
    // Não deleta produto, pois é gerenciado por outra classe
}

int Item::getNumero() const {
    return numero;
}

int Item::getQuantidade() const {
    return quantidade;
}

void Item::setQuantidade(int qtd) {
    quantidade = qtd;
}

Produto* Item::getProduto() const {
    return produto;
}

float Item::getValorTotal() const {
    if (produto != nullptr) {
        return quantidade * produto->getPreco();
    }
    return 0.0f;
}

void Item::imprimir() const {
    std::cout << "\n=== ITEM ===\n";
    std::cout << "Número: " << numero << "\n";
    std::cout << "Quantidade: " << quantidade << "\n";
    if (produto != nullptr) {
        std::cout << "Produto: " << produto->getNome() << "\n";
    }
}

Item Item::operator+(int qtd) const {
    Item novo = *this;
    novo.quantidade += qtd;
    return novo;
}