#include "Endereco.h"
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

// Lista de estados válidos
const vector<string> ESTADOS_BR = {
        "AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO",
        "MA", "MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI",
        "RJ", "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO"
};

string Endereco::toString() const {
    stringstream ss;
    ss << logradouro << ", " << numero;
    if (!complemento.empty()) {
        ss << " - " << complemento;
    }
    ss << "\n" << bairro << "\n"
       << cidade << " - " << estado << "\n"
       << "CEP: " << cep;
    return ss.str();
}

void Endereco::validarLogradouro(const string& logradouro) {
    if (logradouro.empty()) {
        throw invalid_argument("Logradouro não pode ser vazio");
    }
    if (logradouro.length() > 100) {
        throw invalid_argument("Logradouro muito longo");
    }
}

void Endereco::validarNumero(const string& numero) {
    if (numero.empty()) {
        throw invalid_argument("Número não pode ser vazio");
    }
}

void Endereco::validarBairro(const string& bairro) {
    if (bairro.empty()) {
        throw invalid_argument("Bairro não pode ser vazio");
    }
}

void Endereco::validarCidade(const string& cidade) {
    if (cidade.empty()) {
        throw invalid_argument("Cidade não pode ser vazia");
    }
}

void Endereco::validarEstado(const string& estado) {
    string estadoUpper = estado;
    transform(estadoUpper.begin(), estadoUpper.end(), estadoUpper.begin(), ::toupper);

    if (find(ESTADOS_BR.begin(), ESTADOS_BR.end(), estadoUpper) == ESTADOS_BR.end()) {
        throw invalid_argument("Estado inválido");
    }
}

void Endereco::validarCEP(const string& cep) {
    int digitos = 0;
    for (char c : cep) {
        if (isdigit(c)) digitos++;
    }

    if (digitos != 8) {
        throw invalid_argument("CEP deve conter 8 dígitos");
    }
}

// Construtor que valida todos os campos
Endereco::Endereco(const string& logradouro, const string& numero,
                   const string& complemento, const string& bairro,
                   const string& cidade, const string& estado,
                   const string& cep) {
    validarLogradouro(logradouro);
    validarNumero(numero);
    validarBairro(bairro);
    validarCidade(cidade);
    validarEstado(estado);
    validarCEP(cep);

    this->logradouro = logradouro;
    this->numero = numero;
    this->complemento = complemento;
    this->bairro = bairro;
    this->cidade = cidade;
    this->estado = estado;
    this->cep = cep;
}