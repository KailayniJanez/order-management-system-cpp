#ifndef ENDERECO_H
#define ENDERECO_H

#include <string>
#include <stdexcept>
#include <vector>
using namespace  std;
class Endereco {
private:
    string logradouro;
    string numero;
    string complemento;
    string bairro;
    string cidade;
    string estado;
    string cep;

    // Métodos de validação
    void validarLogradouro(const string& logradouro);
    void validarNumero(const string& numero);
    void validarBairro(const string& bairro);
    void validarCidade(const string& cidade);
    void validarEstado(const string& estado);
    void validarCEP(const string& cep);

public:
    // Construtor que já valida tudo
    Endereco(const string& logradouro, const string& numero,
             const string& complemento, const string& bairro,
             const string& cidade, const string& estado,
             const string& cep);


    string getLogradouro() const { return logradouro; }
    string getNumero() const { return numero; }
    string toString() const;
};

#endif // ENDERECO_H