#ifndef GERENCIADORDEPRODUTOS_H
#define GERENCIADORDEPRODUTOS_H

#include "Produto.h"
#include <vector>
#include <string>

using namespace std;
class GerenciadorDeProdutos {

private:
    vector<Produto*> produtos;

public:
    ~GerenciadorDeProdutos();

    void adicionar(int codigo, const std::string& nome, float preco, Categoria categoria, int estoque);
    bool remover(int codigo);
    bool alterar(int codigo, const std::string& novoNome, float novoPreco, Categoria novaCategoria, int novoEstoque);
    Produto* buscarPorCodigo(int codigo);
    const vector<Produto*>& listarTodos() const;
    bool estaVazio() const;
};

#endif // GERENCIADORDEPRODUTOS_H