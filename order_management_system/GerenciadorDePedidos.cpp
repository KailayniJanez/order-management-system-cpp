#include "GerenciadorDePedidos.h"
#include "GerenciadorDeProdutos.h"
#include "Item.h"
#include <stdexcept>


GerenciadorDePedidos::GerenciadorDePedidos() : pedidoAtual(nullptr) {}

//Libera a memória de todos os pedidos alocados
GerenciadorDePedidos::~GerenciadorDePedidos() {
    for (Pedido* p : pedidos) {
        delete p;
    }
    pedidos.clear();
}

Pedido* GerenciadorDePedidos::criar(int numero, const std::string& descricao, Cliente* cliente) {
    Pedido* novoPedido = new Pedido();
    novoPedido->setNumero(numero);
    novoPedido->setDescricao(descricao);
    novoPedido->setCliente(cliente);

    pedidos.push_back(novoPedido);
    pedidoAtual = novoPedido; // Define o novo pedido como o pedido em andamento

    return novoPedido;
}

// Finaliza a sessão do pedido atual,
void GerenciadorDePedidos::finalizarPedidoAtual() {
    pedidoAtual = nullptr;
}

void GerenciadorDePedidos::adicionarItemAoPedidoAtual(int produtoCodigo, int quantidade, GerenciadorDeProdutos& produtosManager) {
    if (!pedidoAtual) {
        throw runtime_error("Nao ha pedido em andamento para adicionar o item.");
    }

    Produto* produto = produtosManager.buscarPorCodigo(produtoCodigo);
    if (!produto) {
        throw invalid_argument("Produto nao encontrado.");
    }
    if (quantidade <= 0) {
        throw invalid_argument("A quantidade deve ser um numero positivo.");
    }
    if (quantidade > produto->getEstoque()) {
        throw out_of_range("Estoque insuficiente. Disponivel: " + std::to_string(produto->getEstoque()));
    }

    // A classe Pedido já lança uma exceção se o item for duplicado
    Item* novoItem = new Item(pedidoAtual->getItens().size() + 1, quantidade, produto);
    try {
        *pedidoAtual = *pedidoAtual + novoItem;
    } catch (...) {
        delete novoItem;
        throw;
    }
    int novoEstoque = produto->getEstoque() - quantidade;
    produtosManager.alterar(produto->getCodigo(), produto->getNome(), produto->getPreco(), produto->getCategoria(), novoEstoque);
}


void GerenciadorDePedidos::removerItemDoPedidoAtual(int codigoProduto, GerenciadorDeProdutos& produtosManager) {
    if (!pedidoAtual) {
        throw std::runtime_error("Nao ha pedido em andamento para remover itens.");
    }

    Item* itemParaRemover = nullptr;
    for (Item* item : pedidoAtual->getItens()) {
        if (item && item->getProduto() && item->getProduto()->getCodigo() == codigoProduto) {
            itemParaRemover = item;
            break;
        }
    }

    if (itemParaRemover) {
        Produto* produto = itemParaRemover->getProduto();
        int quantidadeRemovida = itemParaRemover->getQuantidade();
        int novoEstoque = produto->getEstoque() + quantidadeRemovida;
        produtosManager.alterar(produto->getCodigo(), produto->getNome(), produto->getPreco(), produto->getCategoria(), novoEstoque);


        // Usa a sobrecarga do operador '-' para remover o item do pedido.
        *pedidoAtual = *pedidoAtual - itemParaRemover;

    } else {
        throw std::invalid_argument("Produto nao encontrado no pedido atual.");
    }
}


Pedido* GerenciadorDePedidos::getPedidoAtual() const { return pedidoAtual; }

const std::vector<Pedido*>& GerenciadorDePedidos::listarTodos() const { return pedidos; }

bool GerenciadorDePedidos::haPedidoEmAndamento() const { return pedidoAtual != nullptr; }

bool GerenciadorDePedidos::estaVazio() const { return pedidos.empty(); }