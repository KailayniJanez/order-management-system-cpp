#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>
#include <iostream>

enum class Categoria {
    ALIMENTO, BEBIDA, ELETRONICO, VESTUARIO, LIVRO, LIMPEZA
};
using namespace std;
class Produto {
private:
    int codigo;
    string nome;
    float preco;
    Categoria categoria;
    int estoque;

public:
    Produto(int c, string n, float p, Categoria cat, int est = 0);

    void imprimir() const;

    // Setters e Getters
    void setCodigo(int c);
    int getCodigo() const;
    void setNome(const string n);
    string getNome() const;
    void setPreco(float preco);
    float getPreco() const;
    void setCategoria(Categoria cat);
    Categoria getCategoria() const;
    void setEstoque(int est);
    int getEstoque() const;

    std::string getCategoriaAsString() const;

    // Sobrecarga de operadores
    bool operator==(const Produto& outro) const;
    bool operator!=(const Produto& outro) const;
    bool operator<(const Produto& outro) const;
    bool operator>(const Produto& outro) const;
    Produto& operator++();    // Pré-incremento
    Produto operator++(int);  // Pós-incremento

    // Função friend
    friend void imprimirDetalhesEspeciais(const Produto& produto);
    friend ostream& operator<<(std::ostream& os, const Produto& produto);
};

#endif // PRODUTO_H