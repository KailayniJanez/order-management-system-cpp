#ifndef GERENCIADORDECLIENTES_H
#define GERENCIADORDECLIENTES_H
#include "Cliente.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"
#include "Endereco.h"
#include "Nome.h"
#include "CPF.h"
#include "CNPJ.h"
#include <vector>

class GerenciadorDeClientes {
private:
    vector<Cliente*> clientes;

public:
    ~GerenciadorDeClientes();

    void cadastrarFisico(const Nome& nome, const Endereco& endereco, const CPF& cpf);
    void cadastrarJuridico(const Nome& nome, const Endereco& endereco, const CNPJ& cnpj);
    Cliente* selecionar(size_t index);
    const vector<Cliente*>& listarTodos() const;
    bool estaVazio() const;
    size_t getQuantidade() const;
};

#endif // GERENCIADORDECLIENTES_H