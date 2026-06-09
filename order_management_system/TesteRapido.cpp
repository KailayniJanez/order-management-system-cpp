#include "TesteRapido.h"
#include "Menu.h"
#include "TemplateDesconto.h"
#include "GerenciadorDeProdutos.h"
#include "GerenciadorDeClientes.h"
#include "GerenciadorDePedidos.h"
#include "Produto.h"
#include "Cliente.h"
#include "Pedido.h"
#include "Excecoes.h"
#include <iostream>

TesteRapido::TesteRapido(Menu& menu) : menuAlvo(menu) {}

void TesteRapido::reportar(const string& nomeTeste, bool sucesso) {
    cout << "Teste: " << nomeTeste << " - " << (sucesso ? "[boa]" : "[nao boa]") << endl;
}

void TesteRapido::executarTestes() {
    cout << "\n===== inicio dos testes =====\n" << endl;

    testeAdicionarProduto();
    testeAlterarProduto();
    testeListarProdutos();
    testeCadastrarClienteFisico();
    testeCadastrarClienteJuridico();
    testeListarClientes();
    testeCriarPedido();
    testeAdicionarItemAoPedido();
    testeListarItensDoPedido();
    testeCalculoDeDescontos();
    testeRemoverItemDoPedido();
    testeListarPedidos();
    testeRemoverProduto();

    cout << "\n===== testes finalizados =====\n" << endl;
}

void TesteRapido::testeAdicionarProduto() {
    menuAlvo.gerenciadorProdutos.adicionar(1, "Banana", 5.0f, Categoria::ALIMENTO, 100);
    Produto* p = menuAlvo.gerenciadorProdutos.buscarPorCodigo(1);
    reportar("Adicionar Produto", p != nullptr && p->getNome() == "Banana");
}

void TesteRapido::testeAlterarProduto() {
    menuAlvo.gerenciadorProdutos.alterar(1, "Banana Prata", 6.0f, Categoria::ALIMENTO, 90);
    Produto* p = menuAlvo.gerenciadorProdutos.buscarPorCodigo(1);
    reportar("Alterar Produto", p != nullptr && p->getNome() == "Banana Prata" && p->getPreco() == 6.0f);
}

void TesteRapido::testeListarProdutos() {
    reportar("Listar Produtos (Verifica se nao esta vazio)", !menuAlvo.gerenciadorProdutos.estaVazio());
}

void TesteRapido::testeCadastrarClienteFisico() {
    try {
        Endereco end("Rua Teste", "123", "", "Bairro Teste", "Cidade Teste", "SP", "12345678");
        CPF cpf("41538152843");
        Nome nome("Cliente Fisico Teste", Nome::Tipo::PESSOA);
        menuAlvo.gerenciadorClientes.cadastrarFisico(nome, end, cpf);
        reportar("Cadastrar Cliente Fisico", menuAlvo.gerenciadorClientes.getQuantidade() == 1);
    } catch (const std::exception& e) {
        reportar("Cadastrar Cliente Fisico", false);
        cerr << "  -> Erro inesperado ao cadastrar Cliente Fisico: " << e.what() << endl;
    }
}

void TesteRapido::testeCadastrarClienteJuridico() {
    try {
        Endereco end("Av. Principal", "456", "", "Centro", "Cidade Teste", "RJ", "13212321");
        CNPJ cnpj("00.000.000/0001-91");
        Nome nome("Empresa Teste SA", Nome::Tipo::RAZAO_SOCIAL);
        menuAlvo.gerenciadorClientes.cadastrarJuridico(nome, end, cnpj);
        reportar("Cadastrar Cliente Juridico", menuAlvo.gerenciadorClientes.getQuantidade() == 2);
    } catch (const std::exception& e) {
        reportar("Cadastrar Cliente Juridico", false);
        cerr << "  -> Erro inesperado ao cadastrar Cliente Juridico: " << e.what() << endl;
    }
}

void TesteRapido::testeListarClientes() {
    reportar("Listar Clientes (Verifica quantidade)", menuAlvo.gerenciadorClientes.getQuantidade() == 2);
}

void TesteRapido::testeCriarPedido() {
    if (menuAlvo.gerenciadorClientes.estaVazio()) {
        reportar("Criar Pedido", false);
        cerr << "  -> Teste 'Criar Pedido' pulado pois nenhum cliente foi cadastrado." << endl;
        return;
    }
    Cliente* c = menuAlvo.gerenciadorClientes.selecionar(0);
    menuAlvo.gerenciadorPedidos.criar(101, "Pedido de teste", c);
    reportar("Criar Pedido", menuAlvo.gerenciadorPedidos.haPedidoEmAndamento());
}

void TesteRapido::testeAdicionarItemAoPedido() {
    if (!menuAlvo.gerenciadorPedidos.haPedidoEmAndamento()) {
        reportar("Adicionar Item ao Pedido", false);
        cerr << "  -> Teste 'Adicionar Item' pulado pois nenhum pedido foi criado." << endl;
        return;
    }
    try {
        menuAlvo.gerenciadorPedidos.adicionarItemAoPedidoAtual(1, 5, menuAlvo.gerenciadorProdutos);
        Pedido* p = menuAlvo.gerenciadorPedidos.getPedidoAtual();
        reportar("Adicionar Item ao Pedido", p != nullptr && !p->getItens().empty());
    } catch (const std::exception& e) {
        reportar("Adicionar Item ao Pedido", false);
        cerr << "  -> Erro inesperado ao adicionar item: " << e.what() << endl;
    }
}
void TesteRapido::testeCalculoDeDescontos() {
    if (!menuAlvo.gerenciadorPedidos.haPedidoEmAndamento()) {
        reportar("Cálculo de Descontos", false);
        cerr << "  -> Teste pulado pois não há pedido ativo." << endl;
        return;
    }

    Pedido* pedidoAtual = menuAlvo.gerenciadorPedidos.getPedidoAtual();

    // pedido atual de um cliente físico de valor  30.0f.

    // Testa DescontoPorCliente (esperado 5% de 30.0 = 1.5)
    float descClienteCalculado = CalculadoraDesconto<DescontoPorCliente>::calcular(*pedidoAtual);
    float descClienteEsperado = 1.5f;

    // Usar uma pequena tolerância para comparar floats
    bool clienteOk = abs(descClienteCalculado - descClienteEsperado) < 0.001f;
    reportar("Desconto por Tipo de Cliente (5%)", clienteOk);

 //Testar DescontoPorValorPedido (esperado: 0, 30.0f < 500.0f)
    float descValorCalculado = CalculadoraDesconto<DescontoPorValorPedido>::calcular(*pedidoAtual);
    float descValorEsperado = 0.0f;
    bool valorOk = std::abs(descValorCalculado - descValorEsperado) < 0.001f;
    reportar("Desconto por Valor do Pedido (0%)", valorOk);
}


void TesteRapido::testeListarItensDoPedido() {
    Pedido* p = menuAlvo.gerenciadorPedidos.getPedidoAtual();
    reportar("Listar Itens do Pedido (Verifica se nao esta vazio)", p != nullptr && !p->getItens().empty());
}

void TesteRapido::testeRemoverItemDoPedido() {
    if (!menuAlvo.gerenciadorPedidos.haPedidoEmAndamento() || menuAlvo.gerenciadorPedidos.getPedidoAtual()->getItens().empty()) {
        reportar("Remover Item do Pedido", false);
        cerr << "  -> Teste 'Remover Item' pulado pois não há itens no pedido." << endl;
        return;
    }
    try {
        menuAlvo.gerenciadorProdutos.adicionar(2, "Maca", 3.0f, Categoria::ALIMENTO, 50);
        menuAlvo.gerenciadorPedidos.adicionarItemAoPedidoAtual(2, 10, menuAlvo.gerenciadorProdutos);
        menuAlvo.gerenciadorPedidos.removerItemDoPedidoAtual(1, menuAlvo.gerenciadorProdutos);
        Pedido* p = menuAlvo.gerenciadorPedidos.getPedidoAtual();
        bool itemRemovido = true;
        for(const auto& item : p->getItens()){
            if(item->getProduto()->getCodigo() == 1){
                itemRemovido = false;
                break;
            }
        }
        reportar("Remover Item do Pedido", itemRemovido && p->getItens().size() == 1);

    } catch (const exception& e) {
        reportar("Remover Item do Pedido", false);
        std::cerr << "  -> Erro inesperado ao remover item: " << e.what() << endl;
    }
}

void TesteRapido::testeListarPedidos() {
    reportar("Listar Pedidos (Verifica se nao esta vazio)", !menuAlvo.gerenciadorPedidos.estaVazio());
}

void TesteRapido::testeRemoverProduto() {
    menuAlvo.gerenciadorProdutos.remover(1);
    Produto* p = menuAlvo.gerenciadorProdutos.buscarPorCodigo(1);
    reportar("Remover Produto", p == nullptr);
}