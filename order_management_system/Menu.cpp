#include "Menu.h"
#include "TemplateDesconto.h"
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>
#include "Nome.h"
#include "CPF.h"
#include "CNPJ.h"


using namespace std;

Menu::Menu() {}


void Menu::pausar() const {
    cout << "\nPressione Enter para continuar...";

    cin.get();
}

void Menu::limparTela() const {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Menu::executar() {
    int opcao = -1;
    do {
        exibirMenuPrincipal();
        cin >> opcao;


        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, digite um numero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pausar();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
            case 1:  ui_adicionarProduto(); break;
            case 2:  ui_alterarProduto(); break;
            case 3:  ui_removerProduto(); break;
            case 4:  ui_listarProdutos(); break;
            case 5:  ui_cadastrarClienteFisico(); break;
            case 6:  ui_cadastrarClienteJuridico(); break;
            case 7:  ui_listarClientes(); break;
            case 8:  ui_criarPedido(); break;
            case 9:  ui_adicionarItemPedido(); break;
            case 10: ui_removerItemPedido(); break;
            case 11: ui_listarPedidos(); break;
            case 12: ui_listarItensPedido(); break;
            case 0:  cout << "Saindo do sistema...\n"; break;
            default: cout << "Opcao invalida! Tente novamente.\n";
        }

        if (opcao != 0) {
            pausar();
        }

    } while (opcao != 0);
}

void Menu::exibirMenuPrincipal() const {
    cout << "===== SISTEMA DE VENDAS =====\n\n"
         << "--- PRODUTOS ---\n"
         << "1. Adicionar Produto\n"
         << "2. Alterar Produto\n"
         << "3. Remover Produto\n"
         << "4. Listar Todos os Produtos\n\n"
         << "--- CLIENTES ---\n"
         << "5. Cadastrar Cliente (Pessoa Fisica)\n"
         << "6. Cadastrar Cliente (Pessoa Juridica)\n"
         << "7. Listar Clientes\n\n"
         << "--- PEDIDOS ---\n"
         << "8. Criar Novo Pedido\n"
         << "9. Adicionar Item ao Pedido Atual\n"
         << "10. Remover Item do Pedido Atual\n"
         << "11. Listar Todos os Pedidos\n"
         << "12. Listar Itens do Pedido Atual\n\n"
         << "0. Sair\n"
         << "Escolha uma opcao: ";
    cout.flush();
}

// --- MÉTODOS  PARA PRODUTOS ---

void Menu::ui_adicionarProduto() {
    cout << "\n--- ADICIONAR NOVO PRODUTO ---\n";
    int codigo, catInt, estoque;
    string nome;
    float preco;

    cout << "Codigo: ";
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa para o getline funcionar

    cout << "Nome: ";
    getline(cin, nome);

    cout << "Preco: R$ ";
    cin >> preco;

    cout << "Categoria (0-Alimento, 1-Bebida, 2-Eletronico, 3-Vestuario, 4-Livro, 5-Limpeza): ";
    cin >> catInt;

    cout << "Quantidade em estoque: ";
    cin >> estoque;


    try {
        gerenciadorProdutos.adicionar(codigo, nome, preco, static_cast<Categoria>(catInt), estoque);
        cout << "\n[SUCESSO] Produto adicionado!\n";
    } catch (const exception& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}


void Menu::ui_alterarProduto() {
    cout << "\n--- ALTERAR PRODUTO ---\n";
    if(gerenciadorProdutos.estaVazio()) {
        cout << "Nenhum produto cadastrado para alterar.\n";
        return;
    }
    ui_listarProdutos();
    int codigo;
    cout << "\nDigite o codigo do produto a alterar: ";
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa após ler o código

    try {
        Produto* p = gerenciadorProdutos.buscarPorCodigo(codigo);
        if (!p) throw runtime_error("Produto nao encontrado.");

        int catInt, estoque;
        string nome;
        float preco;

        cout << "Novo nome (" << p->getNome() << "): ";
        getline(cin, nome);

        cout << "Novo preco (" << p->getPreco() << "): ";
        cin >> preco;

        cout << "Nova categoria (" << static_cast<int>(p->getCategoria()) << "): ";
        cin >> catInt;

        cout << "Novo estoque (" << p->getEstoque() << "): ";
        cin >> estoque;

        if(gerenciadorProdutos.alterar(codigo, nome, preco, static_cast<Categoria>(catInt), estoque)) {
            cout << "\n[SUCESSO] Produto alterado!\n";
        }
    } catch (const exception& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}


void Menu::ui_removerProduto() {
    cout << "\n--- REMOVER PRODUTO ---\n";
    if(gerenciadorProdutos.estaVazio()) {
        cout << "Nenhum produto cadastrado para remover.\n";
        return;
    }
    ui_listarProdutos();
    int codigo;
    cout << "\nDigite o codigo do produto a remover: ";
    cin >> codigo;

    if (gerenciadorProdutos.remover(codigo)) {
        cout << "\n[SUCESSO] Produto removido!\n";
    } else {
        cout << "\n[ERRO] Produto com o codigo informado nao foi encontrado.\n";
    }
}

void Menu::ui_listarProdutos() const {
    cout << "\n--- LISTA DE PRODUTOS ---\n";
    if (gerenciadorProdutos.estaVazio()) {
        cout << "Nenhum produto cadastrado.\n";
        return;
    }
    for (const auto& produto : gerenciadorProdutos.listarTodos()) {

        // UTILIZANDO A SOBRECARGA DO OPERADOR <<
        cout << "Codigo: " << produto->getCodigo()
             << " | " << *produto
             << " | Estoque: " << produto->getEstoque() << " un.\n";
    }
}

void Menu::ui_cadastrarClienteFisico() {
    cout << "\n--- CADASTRO CLIENTE FISICO ---\n";
    try {
        string nomeStr;
        cout << "Nome completo: ";
        getline(cin, nomeStr);

        string cpfStr;
        cout << "CPF (somente numeros): ";
        getline(cin, cpfStr);

        Endereco endereco = ui_solicitarEndereco();
        Nome nome(nomeStr, Nome::Tipo::PESSOA);
        CPF cpf(cpfStr);

        gerenciadorClientes.cadastrarFisico(nome, endereco, cpf);
        cout << "\n[SUCESSO] Cliente fisico cadastrado!\n";

    } catch (const exception& e) {
        cout << "\n[ERRO] no cadastro: " << e.what() << "\n";
    }
}

void Menu::ui_cadastrarClienteJuridico() {
    cout << "\n--- CADASTRO CLIENTE JURIDICO ---\n";
    try {
        string razaoSocial;
        cout << "Razao Social: ";
        getline(cin, razaoSocial);

        string cnpjStr;
        cout << "CNPJ (somente numeros): ";
        getline(cin, cnpjStr);

        Endereco endereco = ui_solicitarEndereco();
        Nome nome(razaoSocial, Nome::Tipo::RAZAO_SOCIAL);
        CNPJ cnpj(cnpjStr);

        gerenciadorClientes.cadastrarJuridico(nome, endereco, cnpj);
        cout << "\n[SUCESSO] Cliente juridico cadastrado!\n";

    } catch (const exception& e) {
        cout << "\n[ERRO] no cadastro: " << e.what() << "\n";
    }
}

void Menu::ui_listarClientes() const {
    cout << "\n--- LISTA DE CLIENTES ---\n";
    if (gerenciadorClientes.estaVazio()) {
        cout << "Nenhum cliente cadastrado.\n";
        return;
    }
    for (const auto& cliente : gerenciadorClientes.listarTodos()) {
        cliente->imprimir();
    }
}

void Menu::ui_criarPedido() {
    cout << "\n--- CRIAR NOVO PEDIDO ---\n";
    if (gerenciadorClientes.estaVazio()) {
        cout << "Nao e possivel criar um pedido, pois nao ha clientes cadastrados.\n";
        return;
    }

    int numero;
    string descricao;

    cout << "Numero do pedido: ";
    cin >> numero;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Descricao: ";
    getline(cin, descricao);

    Cliente* clienteSelecionado = ui_selecionarCliente();
    if (clienteSelecionado) {
        gerenciadorPedidos.criar(numero, descricao, clienteSelecionado);
        cout << "\n[sucesso] Pedido criado e ja definido como pedido atual!\n";
    } else {
        cout << "\n[aviso] Criacao de pedido cancelada.\n";
    }
}

void Menu::ui_adicionarItemPedido() {
    cout << "\n--- ADICIONAR ITEM AO PEDIDO ---\n";
    try {
        if (!gerenciadorPedidos.haPedidoEmAndamento()) {
            throw runtime_error("Nao ha pedido em andamento. Crie um pedido primeiro.");
        }
        if (gerenciadorProdutos.estaVazio()) {
            throw runtime_error("Nao ha produtos cadastrados para adicionar.");
        }

        ui_listarProdutos();
        int codigo, quantidade;
        cout << "\nDigite o codigo do produto: ";
        cin >> codigo;

        cout << "Digite a quantidade: ";
        cin >> quantidade;

        gerenciadorPedidos.adicionarItemAoPedidoAtual(codigo, quantidade, gerenciadorProdutos);
        cout << "\n[sucesso] Item adicionado!\n";

    } catch (const exception& e) {
        cout << "\n[erro] " << e.what() << endl;
    }
}

void Menu::ui_removerItemPedido() {
    cout << "\n--- REMOVER ITEM DO PEDIDO ---\n";
    try {
        if (!gerenciadorPedidos.haPedidoEmAndamento()) {
            throw runtime_error("Nao ha pedido em andamento.");
        }
        if (gerenciadorPedidos.getPedidoAtual()->getItens().empty()){
            throw runtime_error("O pedido atual esta vazio.");
        }

        ui_listarItensPedido();
        int codigo;
        cout << "\nDigite o codigo do produto a ser removido: ";
        cin >> codigo;

        gerenciadorPedidos.removerItemDoPedidoAtual(codigo, gerenciadorProdutos);
        cout << "\n[sucesso] Item removido e estoque atualizado!\n";

    } catch (const exception& e) {
        cout << "\n[erro] " << e.what() << endl;
    }
}

void Menu::ui_listarPedidos() const {
    cout << "\n--- LISTA DE TODOS OS PEDIDOS ---\n";
    if (gerenciadorPedidos.estaVazio()) {
        cout << "Nenhum pedido foi realizado.\n";
        return;
    }
    for (const auto& pedido : gerenciadorPedidos.listarTodos()) {
        cout << "---------------------------------\n"
             << "Numero: " << pedido->getNumero()
             << " | Cliente: " << pedido->getCliente()->getNome().get() << "\n"
             << "Descricao: " << pedido->getDescricao() << "\n";
        if (gerenciadorPedidos.getPedidoAtual() == pedido) {
            cout << "Status: EM ANDAMENTO\n";
        }
    }
    cout << "---------------------------------\n";
}

void Menu::ui_listarItensPedido() const {
    cout << "\n--- ITENS DO PEDIDO ATUAL ---\n";
    try {
        if (!gerenciadorPedidos.haPedidoEmAndamento()) {
            throw runtime_error("Nenhum pedido em andamento.");
        }
        Pedido* pedidoAtual = gerenciadorPedidos.getPedidoAtual();
        if(pedidoAtual->getItens().empty()){
            cout << "O pedido atual nao possui itens.\n";
            return;
        }

        // Imprime os itens (lógica existente)
        for (const auto& item : pedidoAtual->getItens()) {
            cout << "Produto: " << item->getProduto()->getNome()
                 << " | Qtd: " << item->getQuantidade()
                 << " | Valor: R$ " << item->getValorTotal() << "\n";
        }
        cout << "---------------------------------\n";

        float valorTotalBruto = pedidoAtual->getValorTotalBruto();
        cout << "VALOR TOTAL BRUTO: R$ " << valorTotalBruto << endl;


        // 1. Calcula o desconto usando a estratégia de Cliente
        float descontoPorCliente = CalculadoraDesconto<DescontoPorCliente>::calcular(*pedidoAtual);
        cout << "Desconto por tipo de cliente: R$ " << descontoPorCliente << endl;

        // 2. Calcula o desconto usando a estratégia de Valor do Pedido
        float descontoPorValor = CalculadoraDesconto<DescontoPorValorPedido>::calcular(*pedidoAtual);
        cout << "Desconto por valor do pedido: R$ " << descontoPorValor << endl;

        // Exibe o maior desconto aplicável
        float maiorDesconto = std::max(descontoPorCliente, descontoPorValor);
        cout << "---------------------------------\n";
        cout << "MAIOR DESCONTO APLICAVEL: R$ " << maiorDesconto << endl;
        cout << "VALOR TOTAL LIQUIDO: R$ " << (valorTotalBruto - maiorDesconto) << endl;

    } catch (const exception& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

Endereco Menu::ui_solicitarEndereco() {
    while (true) {
        string rua, bairro, cidade, estado, cep, numero, complemento;
        cout << "\n--- CADASTRO DE ENDERECO ---\n";
        cout << "Rua: "; getline(cin, rua);
        cout << "Numero: "; getline(cin, numero);
        cout << "Complemento (opcional): "; getline(cin, complemento);
        cout << "Bairro: "; getline(cin, bairro);
        cout << "Cidade: "; getline(cin, cidade);
        cout << "Estado (sigla): "; getline(cin, estado);
        cout << "CEP (sem pontos/tracos): "; getline(cin, cep);
        try {
            return Endereco(rua, numero, complemento, bairro, cidade, estado, cep);
        } catch (const exception& e) {
            cout << "[ERRO] no endereco: " << e.what() << "\nPor favor, insira novamente.\n";
        }
    }
}

Cliente* Menu::ui_selecionarCliente() {
    cout << "\n--- SELECIONE O CLIENTE ---\n";
    const auto &clientes = gerenciadorClientes.listarTodos();
    if (clientes.empty()) {
        cout << "Nenhum cliente cadastrado.\n";
        return nullptr;
    }
    for (size_t i = 0; i < clientes.size(); ++i) {
        cout << i + 1 << ". " << clientes[i]->getNome().get() << endl;
    }
    int escolha;
    cout << "Escolha o cliente (ou 0 para cancelar): ";
    cin >> escolha;



    if (cin.fail()) {
        cin.clear();
        return nullptr;
    }

    if (escolha > 0 && escolha <= static_cast<int>(clientes.size())) {
        return gerenciadorClientes.selecionar(escolha - 1);
    }
    return nullptr;
}