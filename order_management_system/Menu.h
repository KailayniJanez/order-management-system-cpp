#ifndef MENU_H
#define MENU_H

#include "GerenciadorDeProdutos.h"
#include "GerenciadorDeClientes.h"
#include "GerenciadorDePedidos.h"

class Menu {
private:
    GerenciadorDeProdutos gerenciadorProdutos;
    GerenciadorDeClientes gerenciadorClientes;
    GerenciadorDePedidos gerenciadorPedidos;

    void exibirMenuPrincipal() const;
    void pausar() const;
    void limparTela() const;

    // Métodos de UI (Interface do Usuário)
    void ui_adicionarProduto();
    void ui_removerProduto();
    void ui_alterarProduto();
    void ui_listarProdutos() const;

    void ui_cadastrarClienteFisico();
    void ui_cadastrarClienteJuridico();
    void ui_listarClientes() const;

    void ui_criarPedido();
    void ui_adicionarItemPedido();
    void ui_removerItemPedido();
    void ui_listarItensPedido() const;
    void ui_listarPedidos() const;

    Endereco ui_solicitarEndereco();
    Cliente* ui_selecionarCliente();


public:
    Menu();
    void executar();
    friend class TesteRapido;
};

#endif // MENU_H