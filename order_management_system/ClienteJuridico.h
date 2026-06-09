#ifndef CLIENTE_JURIDICO_H
#define CLIENTE_JURIDICO_H

#include "Cliente.h"
#include "CNPJ.h"
#include "Endereco.h"

class ClienteJuridico final : public Cliente {
private:
    CNPJ cnpj;

public:
    ClienteJuridico(const Nome& nome, const Endereco& endereco, const CNPJ& cnpj);

    CNPJ getCNPJ() const;
    void imprimir() const override;

};

#endif // CLIENTE_JURIDICO_H