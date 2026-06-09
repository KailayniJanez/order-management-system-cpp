#ifndef ITEM_H
#define ITEM_H

#include "Produto.h"

class Item {
private:
    int numero;
    int quantidade;
    Produto* produto;

public:
    Item(int numero, int quantidade, Produto* produto);
    ~Item();

    // Métodos existentes
    int getNumero() const;
    int getQuantidade() const;
    Produto* getProduto() const;
    void imprimir() const;
    float getValorTotal() const;

    // Sobrecarga de operadores
    Item operator+(int quantidade) const;
    void setQuantidade(int qtd);
};

#endif // ITEM_H