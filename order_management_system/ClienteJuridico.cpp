#include "ClienteJuridico.h"
#include <iostream>
using namespace std;
ClienteJuridico::ClienteJuridico(const Nome& nome, const Endereco& endereco, const CNPJ& cnpj)
    : Cliente(nome, endereco), cnpj(cnpj) {}

CNPJ ClienteJuridico::getCNPJ() const {
    return cnpj;
}

void ClienteJuridico::imprimir() const {
    cout << "\n=== CLIENTE JURÍDICO ===" << endl;
    cout << "Razão Social: " << getNome().get() << endl;
    cout << "CNPJ: " << cnpj.getNumero(true) << endl;
    cout << "Endereço:\n" << getEndereco().toString() << endl;
    cout << "=======================" << endl;
}

