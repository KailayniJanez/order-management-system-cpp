#ifndef CNPJ_H
#define CNPJ_H

#include <string>
#include <stdexcept>
using namespace std;
class CNPJ {
private:
    string numero;

    static string limparCNPJ(const std::string& cnpj);
    static bool validarFormato(const std::string& cnpj);
    static bool validarDigitos(const std::string& cnpj);

public:
    explicit CNPJ(const std::string& cnpj);

    string getNumero(bool formatado = false) const;
    static bool ehValido(const std::string& cnpj);
};

#endif