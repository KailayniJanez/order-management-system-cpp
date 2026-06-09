#include "GerenciadorDeProdutos.h"
#include <algorithm>
#include <stdexcept>
#include "Template.h"




// Destrutor: Libera a memória de todos os produtos alocados

GerenciadorDeProdutos::~GerenciadorDeProdutos() {
    for (Produto* p : produtos) {
        delete p;
    }
    produtos.clear();
}


void GerenciadorDeProdutos::adicionar(int codigo, const std::string& nome, float preco, Categoria categoria, int estoque) {
    if (buscarPorCodigo(codigo) != nullptr) {
        throw invalid_argument("Erro: Ja existe um produto com o codigo " + to_string(codigo));
    }

    Produto* novoProduto = new Produto(codigo, nome, preco, categoria, estoque);
    produtos.push_back(novoProduto);
}


bool GerenciadorDeProdutos::remover(int codigo) {
    auto it = find_if(produtos.begin(), produtos.end(),
                           [codigo](const Produto* p) {
                               return p->getCodigo() == codigo;
                           });

    if (it != produtos.end()) {
        delete *it;
        produtos.erase(it); // Remove o ponteiro do vetor
        return true;
    }
    return false;
}


bool GerenciadorDeProdutos::alterar(int codigo, const string& novoNome, float novoPreco, Categoria novaCategoria, int novoEstoque) {
    Produto* produtoParaAlterar = buscarPorCodigo(codigo);
    if (produtoParaAlterar != nullptr) {
        produtoParaAlterar->setNome(novoNome);
        produtoParaAlterar->setPreco(novoPreco);
        produtoParaAlterar->setCategoria(novaCategoria);
        produtoParaAlterar->setEstoque(novoEstoque);
        return true;
    }
    return false;
}

//uso do template para busca
Produto* GerenciadorDeProdutos::buscarPorCodigo(int codigo) {
    auto comparador = [](const Produto* p, int cod) {
        return p->getCodigo() == cod;
    };
    return buscarEmVetor<Produto, int>(produtos, codigo, comparador);
}


const vector<Produto*>& GerenciadorDeProdutos::listarTodos() const {
    return produtos;
}

// Verifica se o vetor de produtos está vazio.
bool GerenciadorDeProdutos::estaVazio() const {
    return produtos.empty();
}