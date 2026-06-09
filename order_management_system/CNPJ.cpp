#include "CNPJ.h"
#include <algorithm>
#include <regex>

using namespace std;

CNPJ::CNPJ(const string& cnpj) {
    if (!ehValido(cnpj)) {
        throw invalid_argument("CNPJ inválido");
    }
    numero = limparCNPJ(cnpj);
}

string CNPJ::limparCNPJ(const string& cnpj) {
    string cnpjLimpo;
    for (char c : cnpj) {
        if (isdigit(c)) {
            cnpjLimpo += c;
        }
    }
    return cnpjLimpo;
}

bool CNPJ::validarFormato(const string& cnpj) {
    // Aceita 00.000.000/0000-00 ou 00000000000000
    regex formato("^\\d{2}\\.?\\d{3}\\.?\\d{3}/?\\d{4}-?\\d{2}$");
    return regex_match(cnpj, formato);
}

bool CNPJ::validarDigitos(const string& cnpj) {
    string cnpjLimpo = limparCNPJ(cnpj);

    // Verifica se tem 14 dígitos e não é sequência repetida
    if (cnpjLimpo.length() != 14 ||
        all_of(cnpjLimpo.begin(), cnpjLimpo.end(), [cnpjLimpo](char c) { return c == cnpjLimpo[0]; })) {
        return false;
    }

    // Cálculo do primeiro dígito verificador
    int pesos1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int soma = 0;
    for (int i = 0; i < 12; i++) {
        soma += (cnpjLimpo[i] - '0') * pesos1[i];
    }
    int resto = soma % 11;
    int digito1 = (resto < 2) ? 0 : 11 - resto;

    // Cálculo do segundo dígito verificador
    int pesos2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    soma = 0;
    for (int i = 0; i < 13; i++) {
        soma += (cnpjLimpo[i] - '0') * pesos2[i];
    }
    resto = soma % 11;
    int digito2 = (resto < 2) ? 0 : 11 - resto;

    // Verifica os dígitos (posições 12 e 13 do array)
    return (digito1 == cnpjLimpo[12] - '0') && (digito2 == cnpjLimpo[13] - '0');
}

bool CNPJ::ehValido(const string& cnpj) {
    return validarFormato(cnpj) && validarDigitos(cnpj);
}

string CNPJ::getNumero(bool formatado) const {
    if (formatado) {
        return numero.substr(0, 2) + "." +
               numero.substr(2, 3) + "." +
               numero.substr(5, 3) + "/" +
               numero.substr(8, 4) + "-" +
               numero.substr(12, 2);
    }
    return numero;
}