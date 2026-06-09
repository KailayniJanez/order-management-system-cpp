#ifndef PEDIDO_H
#define PEDIDO_H

#include <vector>
#include <string>
#include "Item.h"
#include "Cliente.h"

using namespace std;

class Pedido {
private:
    vector<Item*> itens;
    int numero;
    string descricao;
    Cliente* cliente;

public:
    Pedido();
    ~Pedido();

    float getValorTotalBruto() const;
    void setNumero(int numero);
    int getNumero() const;
    void setDescricao(const string& desc);
    string getDescricao() const;
    void setCliente(Cliente* cliente);
    Cliente* getCliente() const;

    const vector<Item*>& getItens() const { return itens; }
    void adicionarItem(Item* item);
    void removerItemPorNumero(int num);
    void imprimir() const;

    // Sobrecarga de operadores
    Pedido& operator+(Item* item);
    Pedido& operator-(Item* item);
    Item* operator[](int index);
};

#endif