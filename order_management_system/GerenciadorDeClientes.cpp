#include "GerenciadorDeClientes.h"
#include <stdexcept>



GerenciadorDeClientes::~GerenciadorDeClientes() {
    for (Cliente* c : clientes) {
        delete c;
    }
    clientes.clear();
}

void GerenciadorDeClientes::cadastrarFisico(const Nome& nome, const Endereco& endereco, const CPF& cpf) {
    clientes.push_back(new ClienteFisico(nome, endereco, cpf));
}

void GerenciadorDeClientes::cadastrarJuridico(const Nome& nome, const Endereco& endereco, const CNPJ& cnpj) {
    clientes.push_back(new ClienteJuridico(nome, endereco, cnpj));
}


Cliente* GerenciadorDeClientes::selecionar(size_t index) {
    if (index < clientes.size()) {
        return clientes[index];
    }
    throw out_of_range("Indice de cliente invalido.");
}


const vector<Cliente*>& GerenciadorDeClientes::listarTodos() const {
    return clientes;
}

// Verifica se o vetor de clientes está vazio.
bool GerenciadorDeClientes::estaVazio() const {
    return clientes.empty();
}

// Retorna a quantidade de clientes cadastrados.
size_t GerenciadorDeClientes::getQuantidade() const {
    return clientes.size();
}