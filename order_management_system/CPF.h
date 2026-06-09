#ifndef CPF_H
#define CPF_H

#include <string>
#include <stdexcept>
#include "Excecoes.h"

class CPF {
private:
    std::string numero;

    static bool validarFormato(const std::string& cpf);
    static bool validarDigitos(const std::string& cpf);
    static std::string limparCPF(const std::string& cpf);
    static int calcularDigito(const std::string& cpf, int pesoInicial);

public:
    explicit CPF(const std::string& cpf);

    std::string getNumero(bool formatado = false) const;
    static bool ehValido(const std::string& cpf);
};

#endif // CPF_H