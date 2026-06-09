#ifndef GERENCIADORDEPEDIDOS_H
#define GERENCIADORDEPEDIDOS_H

#include "Pedido.h"
#include <vector>
#include <string>

class GerenciadorDeProdutos;
class Cliente;
class Item;

class GerenciadorDePedidos {
private:
    vector<Pedido*> pedidos;
    Pedido* pedidoAtual;

public:
    GerenciadorDePedidos();
    ~GerenciadorDePedidos();

    Pedido* criar(int numero, const std::string& descricao, Cliente* cliente);
    void finalizarPedidoAtual();

    void adicionarItemAoPedidoAtual(int produtoCodigo, int quantidade, GerenciadorDeProdutos& produtosManager);
    void removerItemDoPedidoAtual(int codigoProduto, GerenciadorDeProdutos& produtosManager);

    Pedido* getPedidoAtual() const;
    const vector<Pedido*>& listarTodos() const;
    bool haPedidoEmAndamento() const;
    bool estaVazio() const;
};

#endif // GERENCIADORDEPEDIDOS_H