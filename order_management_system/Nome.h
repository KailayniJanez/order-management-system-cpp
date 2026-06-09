#ifndef NOME_H
#define NOME_H

#include <string>
#include <functional>

using namespace std;

class Nome {
private:
    string valor;
    function<bool(const string&)> validador;

    void validar(const string& nome) const;

public:
    enum class Tipo { PESSOA, RAZAO_SOCIAL };

    Nome(const string& nome, Tipo tipo = Tipo::PESSOA);

    static bool validarPessoa(const string& nome);
    static bool validarRazaoSocial(const string& nome);

    string get() const { return valor; }
    void set(const string& novoNome, Tipo tipo = Tipo::PESSOA);
};

#endif // NOME_H