#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <vector>
#include <functional>

template <typename T>
class Resultado {
private:
    T valor;
    bool sucesso;
    std::string mensagemErro;

public:
    Resultado(T val) : valor(val), sucesso(true) {}
    Resultado(std::string erro) : mensagemErro(erro), sucesso(false) {}

    bool obteveSucesso() const { return sucesso; }
    T obterValor() const {
        if (!sucesso) throw std::runtime_error(mensagemErro);
        return valor;
    }
    string obterErro() const { return mensagemErro; }
};

template <typename T, typename Key>
T* buscarEmVetor(std::vector<T*>& vetor, Key chave, std::function<bool(T*, Key)> comparador) {
    for (auto item : vetor) {
        if (comparador(item, chave)) {
            return item;
        }
    }
    return nullptr;
}

#endif // TEMPLATE_H
