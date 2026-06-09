#include "ClienteFisico.h"
#include <iostream>

using namespace std;
ClienteFisico::ClienteFisico(const Nome& nome, const Endereco& endereco, const CPF& cpf)
    : Cliente(nome, endereco), cpf(cpf) {}

CPF ClienteFisico::getCPF() const {
    return cpf;
}

void ClienteFisico::imprimir() const {
    cout << "\n=== CLIENTE FÍSICO ===" << endl;
    cout << "Nome: " << getNome().get() << endl;
    cout << "CPF: " << cpf.getNumero(true) << endl;
    cout << "Endereço:\n" << getEndereco().toString() << endl;
    cout << "=====================" << endl;
}

