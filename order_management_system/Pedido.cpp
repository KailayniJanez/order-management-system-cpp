#include "Pedido.h"
#include <iostream>

Pedido::Pedido() : cliente(nullptr) {}

Pedido::~Pedido() {
    for (Item* item : itens) {
        delete item;
    }
}

void Pedido::setNumero(int num) { numero = num; }
int Pedido::getNumero() const { return numero; }

void Pedido::setDescricao(const string& desc) { descricao = desc; }
string Pedido::getDescricao() const { return descricao; }

void Pedido::setCliente(Cliente* cli) { cliente = cli; }
Cliente* Pedido::getCliente() const { return cliente; }

void Pedido::adicionarItem(Item* item) {
    // Verifica se já existe um item com o mesmo produto
    for (const auto& i : itens) {
        if (*(i->getProduto()) == *(item->getProduto())) {
            throw runtime_error("Já existe um item com este produto no pedido");
        }
    }
    itens.push_back(item);
}

void Pedido::removerItemPorNumero(int num) {
    for (auto it = itens.begin(); it != itens.end(); ) {
        if ((*it) != nullptr && (*it)->getNumero() == num) {
            Item* itemParaRemover = *it;
            it = itens.erase(it);
            delete itemParaRemover;
        } else {
            ++it;
        }
    }
}

void Pedido::imprimir() const {
    cout << "\n======= PEDIDO =======\n";
    cout << "Numero: " << numero << "\n";
    cout << "Descricao: " << descricao << "\n";

    if (cliente) {
        cliente->imprimir();
    } else {
        cout << "Cliente: Nao associado\n";
    }

    for (const auto& item : itens) {
        item->imprimir();
    }
    cout << "======================\n";
}

// Implementação dos operadores
Pedido& Pedido::operator+(Item* item) {
    adicionarItem(item);
    return *this;
}

Pedido& Pedido::operator-(Item* item) {
    if (item != nullptr) {
        removerItemPorNumero(item->getNumero());
    }
    return *this;
}

Item* Pedido::operator[](int index) {
    if (index >= 0 && index < itens.size()) {
        return itens[index];
    }
    throw out_of_range("Índice inválido para acesso ao pedido");
}

float Pedido::getValorTotalBruto() const {
    float total = 0.0f;
    for (const auto& item : itens) {
        if (item) {
            total += item->getValorTotal();
        }
    }
    return total;
}