#ifndef EXCECOES_H
#define EXCECOES_H

#include <stdexcept>
#include <string>
using namespace std;

class ExcecaoCPFInvalido : public invalid_argument {
public:
    ExcecaoCPFInvalido() : invalid_argument("CPF invalido") {}
};

class ExcecaoCNPJInvalido : public invalid_argument {
public:
    ExcecaoCNPJInvalido() : invalid_argument("CNPJ invalido") {}
};

class ExcecaoProdutoNaoEncontrado : public runtime_error {
public:
    ExcecaoProdutoNaoEncontrado() : runtime_error("Produto nao encontrado") {}
};

class ExcecaoClienteNaoEncontrado : public runtime_error {
public:
    ExcecaoClienteNaoEncontrado() : runtime_error("Cliente nao encontrado") {}
};

class ExcecaoItemNaoEncontrado : public runtime_error {
public:
    ExcecaoItemNaoEncontrado() : runtime_error("Item nao encontrado") {}
};

#endif // EXCECOES_H