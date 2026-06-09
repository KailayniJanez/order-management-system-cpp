#include "Nome.h"
#include <algorithm>
#include <cctype>
#include <vector>
#include <regex>

using namespace std;

bool Nome::validarPessoa(const string& nome) {
    if (nome.empty() || nome.length() < 2 || nome.length() > 100) {
        return false;
    }

    static const regex padrao("^[A-Za-zÀ-ÿ][A-Za-zÀ-ÿ '\\-]+$");
    return regex_match(nome, padrao);
}

bool Nome::validarRazaoSocial(const string& nome) {
    if (nome.empty() || nome.length() < 3 || nome.length() > 150) {
        return false;
    }

    static const regex padrao("^[A-Za-zÀ-ÿ0-9][A-Za-zÀ-ÿ0-9 .,'\\-&]+$");
    return regex_match(nome, padrao);
}

void Nome::validar(const string& nome) const {
    if (!validador(nome)) {
        throw invalid_argument("Nome inválido para este contexto");
    }
}

Nome::Nome(const string& nome, Tipo tipo) {
    switch (tipo) {
        case Tipo::PESSOA:
            validador = validarPessoa;
            break;
        case Tipo::RAZAO_SOCIAL:
            validador = validarRazaoSocial;
            break;
    }
    validar(nome);
    valor = nome;
}

void Nome::set(const string& novoNome, Tipo tipo) {
    switch (tipo) {
        case Tipo::PESSOA:
            validador = validarPessoa;
            break;
        case Tipo::RAZAO_SOCIAL:
            validador = validarRazaoSocial;
            break;
    }
    validar(novoNome);
    valor = novoNome;
}