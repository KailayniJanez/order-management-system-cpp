#ifndef TEMPLATE_DESCONTO_H
#define TEMPLATE_DESCONTO_H

#include "Pedido.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"

//padrão de projeto Strategy



class EstrategiaDeDesconto {
public:
    virtual ~EstrategiaDeDesconto() = default;
    // O método que para ser implementado para calcular a estrategia de desconto.
    virtual float calcularDesconto(const Pedido& pedido) const = 0;
};



//Desconto com base no tipo do cliente
class DescontoPorCliente : public EstrategiaDeDesconto { // Herda da interface em português
public:
    float calcularDesconto(const Pedido& pedido) const override {
        Cliente* cliente = pedido.getCliente();
        if (!cliente) return 0.0f;

        if (dynamic_cast<ClienteFisico*>(cliente)) {
            return pedido.getValorTotalBruto() * 0.05; // 5% para cliente físico
        }
        if (dynamic_cast<ClienteJuridico*>(cliente)) {
            return pedido.getValorTotalBruto() * 0.10; // 10% para cliente jurídico
        }
        return 0.0f;
    }
};

//Desconto com base no valor total do pedido
class DescontoPorValorPedido : public EstrategiaDeDesconto {
public:
    float calcularDesconto(const Pedido& pedido) const override {
        float valorTotal = pedido.getValorTotalBruto();
        if (valorTotal > 1000.0f) {
            return valorTotal * 0.15f; // 15%
        }
        if (valorTotal > 500.0f) {
            return valorTotal * 0.07f; // 7%
        }

        return 0.0f;
    }
};

//template calculadora"
// Recebe uma estratégia de desconto como parâmetro
// Verifica se a estratégia é válida
// Aplica o desconto ao pedido usando a estratégia escolhida.

    template<typename Estrategia>
    class CalculadoraDesconto {
    public:
        static float calcular(const Pedido &pedido) {
            static_assert(std::is_base_of<EstrategiaDeDesconto, Estrategia>::value,
                          "A estrategia deve herdar de EstrategiaDeDesconto");

            Estrategia estrategia;
            return estrategia.calcularDesconto(pedido);
        }
    };


#endif // TEMPLATE_DESCONTO_H