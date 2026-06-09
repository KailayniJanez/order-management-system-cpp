#ifndef CLIENTE_H
#define CLIENTE_H

#include "Endereco.h"
#include "Nome.h"
#include "CPF.h"

// Classe base abstrata para clientes
class Cliente {
protected:
    Nome nome;            // Nome do cliente 
    Endereco endereco;    // Endereço do cliente 

public:
    // Construtor
    Cliente(const Nome& nome, const Endereco& endereco)
        : nome(nome), endereco(endereco) {}

    // Destrutor virtual
    virtual ~Cliente() = default;

    // Getters
    Nome getNome() const { return nome; }
    Endereco getEndereco() const { return endereco; }

    // Métodos virtuais puros
    virtual void imprimir() const = 0;
};

#endif // CLIENTE_H