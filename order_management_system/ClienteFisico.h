#ifndef CLIENTE_FISICO_H
#define CLIENTE_FISICO_H

#include "Cliente.h"
#include "Cpf.h"
#include "Endereco.h"

class ClienteFisico final : public Cliente {
private:
    CPF cpf;

public:
    ClienteFisico(const Nome& nome, const Endereco& endereco, const CPF& cpf);
    
    CPF getCPF() const;
    void imprimir() const override;
};

#endif // CLIENTE_FISICO_H