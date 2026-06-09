#include "Menu.h"
#include "TesteRapido.h"


//descomente a proxima linha pra rodar os testes, ou comente para usar o menu normal.
#define EXECUTAR_TESTES

int main() {

#ifdef EXECUTAR_TESTES
    // Se a macro estiver definido, o código entra no modo de teste
    Menu menuParaTeste;
    TesteRapido testes(menuParaTeste);
    testes.executarTestes();
#else
    // senao, executa o programa normalmente
    Menu sistema;
    sistema.executar();
#endif

    return 0;
}