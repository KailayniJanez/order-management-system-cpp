#ifndef TESTERAPIDO_H
#define TESTERAPIDO_H

#include <string>

// aqui a ideia nao é nem aprofundar muito e so verificar se o sistema funciona quando tudo ocorre bem.
class Menu;
using namespace std;

class TesteRapido {
public:
    explicit TesteRapido(Menu& menu);

    void executarTestes();

private:
    Menu& menuAlvo;

    void testeAdicionarProduto();
    void testeAlterarProduto();
    void testeListarProdutos();
    void testeCadastrarClienteFisico();
    void testeCadastrarClienteJuridico();
    void testeListarClientes();
    void testeCriarPedido();
    void testeAdicionarItemAoPedido();
    void testeListarItensDoPedido();
    void testeRemoverItemDoPedido();
    void testeListarPedidos();
    void testeRemoverProduto();
    void testeCalculoDeDescontos();

    void reportar(const string& nomeTeste, bool sucesso);
};

#endif // TESTERAPIDO_H;

