#include "CPF.h"
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <string>
using namespace std;

// Construtor que recebe um CPF e valida
// Se o CPF não for válido, lança uma exceção
CPF::CPF(const std::string& cpf) {
    if (!ehValido(cpf)) {
        throw ExcecaoCPFInvalido();
    }
    numero = limparCPF(cpf);
}
// Método para limpar o CPF, removendo caracteres não numéricos
// Retorna uma string contendo apenas os dígitos do CPF
string CPF::limparCPF(const string& cpf) {
    string cpfLimpo;
    for (char c : cpf) {
        if (isdigit(c)) {
            cpfLimpo += c;
        }
    }
    return cpfLimpo;
}

// Método para validar o formato do CPF
// O CPF deve ter 11 dígitos numéricos  
bool CPF::validarFormato(const string& cpf) {
    string cpfLimpo = limparCPF(cpf);
    return cpfLimpo.length() == 11 && all_of(cpfLimpo.begin(), cpfLimpo.end(), ::isdigit);
}

//  Método para calcular o dígito verificador do CPF
// O CPF deve ter 11 dígitos, e não pode ser uma sequência de números iguais
int CPF::calcularDigito(const string& cpf, int pesoInicial) {
    int soma = 0;
    for (int i = 0; i < pesoInicial - 1; i++) {
        soma += (cpf[i] - '0') * (pesoInicial - i);
    }
    int resto = soma % 11;
    return (resto < 2) ? 0 : 11 - resto;
}


/**
  Valida os dígitos verificadores de um CPF conforme o algoritmo oficial

  Um CPF válido deve:
 Ter exatamente 11 dígitos numéricos
 Não ser composto por todos os mesmos dígitos (ex: 111.111.111-11)

    - Ter dígitos verificadores calculados corretamente:
    - O 10º dígito (1º verificador) é calculado a partir dos 9 primeiros dígitos
      usando pesos decrescentes de 10 a 2

    - O 11º dígito (2º verificador) é calculado a partir dos 10 primeiros dígito
    (9 originais + 1º verificador) usando pesos decrescentes de 11 a 2

  @return bool - Retorna true se o CPF possui dígitos verificadores válidos,
                false caso contrário.
 */
bool CPF::validarDigitos(const string& cpf) {
    string cpfLimpo = limparCPF(cpf);
    if (cpfLimpo.length() != 11 || 
        all_of(cpfLimpo.begin(), cpfLimpo.end(), [cpfLimpo](char c) { return c == cpfLimpo[0]; })) {
        return false;
    }

    int digito1 = calcularDigito(cpfLimpo, 10);
    int digito2 = calcularDigito(cpfLimpo, 11);

    return (digito1 == cpfLimpo[9] - '0') && (digito2 == cpfLimpo[10] - '0');
}

// Método estático para validar um CPF
// Chama os métodos de validação de formato e dígitos   
// Retorna true se o CPF for válido
// Retorna false se o CPF não for válido
bool CPF::ehValido(const string& cpf) {
    return validarFormato(cpf) && validarDigitos(cpf);
}
// Método para obter o número do CPF
// Se formatado for true, retorna o CPF formatado com pontos e traço
// Se formatado for false, retorna o CPF sem formatação
string CPF::getNumero(bool formatado) const {
    if (formatado) {
        string formattedNumero = numero;
        return formattedNumero.insert(3, ".").insert(7, ".").insert(11, "-");
    }
    return numero;
}