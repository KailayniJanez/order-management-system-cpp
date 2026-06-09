#include "Produto.h"
#include <iostream>

Produto::Produto(int c, std::string n, float p, Categoria cat, int est)
    : codigo(c), nome(n), preco(p), categoria(cat), estoque(est) {}

void Produto::imprimir() const {
    std::cout << "--- EXIBINDO DADOS DO PRODUTO ---\n";
    std::cout << "Codigo: " << codigo << "\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Preco: R$ " << preco << "\n";
    std::cout << "Categoria: " << getCategoriaAsString() << "\n";
    std::cout << "Estoque: " << estoque << "\n";
    std::cout << "-------------------------------\n";
}

// Implementação dos getters e setters
void Produto::setCodigo(int c) { codigo = c; }
int Produto::getCodigo() const { return codigo; }
void Produto::setNome(const std::string n) { nome = n; }
std::string Produto::getNome() const { return nome; }
void Produto::setPreco(float p) { preco = p; }
float Produto::getPreco() const { return preco; }
void Produto::setCategoria(Categoria cat) { categoria = cat; }
Categoria Produto::getCategoria() const { return categoria; }
void Produto::setEstoque(int est) { estoque = est; }
int Produto::getEstoque() const { return estoque; }

std::string Produto::getCategoriaAsString() const {
    switch (categoria) {
        case Categoria::ALIMENTO: return "Alimento";
        case Categoria::BEBIDA: return "Bebida";
        case Categoria::ELETRONICO: return "Eletronico";
        case Categoria::VESTUARIO: return "Vestuario";
        case Categoria::LIVRO: return "Livro";
        case Categoria::LIMPEZA: return "Limpeza";
        default: return "Desconhecida";
    }
}

// Implementação dos operadores
bool Produto::operator==(const Produto& outro) const {
    return codigo == outro.codigo;
}

bool Produto::operator!=(const Produto& outro) const {
    return !(*this == outro);
}

bool Produto::operator<(const Produto& outro) const {
    return preco < outro.preco;
}

bool Produto::operator>(const Produto& outro) const {
    return preco > outro.preco;
}

Produto& Produto::operator++() {
    estoque++;
    return *this;
}

Produto Produto::operator++(int) {
    Produto temp = *this;
    ++(*this);
    return temp;
}

// Implementação da função friend
void imprimirDetalhesEspeciais(const Produto& produto) {
    std::cout << "DETALHES ESPECIAIS: " << produto.nome
              << " (Código: " << produto.codigo << ")\n";
}

// Operador de saída
ostream& operator<<(ostream& os, const Produto& produto) {
    os << produto.nome << " (R$ " << produto.preco << ")";
    return os;
}