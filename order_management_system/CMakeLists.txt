cmake_minimum_required(VERSION 3.21)
project(T2_valter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        Menu.cpp
        Produto.cpp
        Pedido.cpp
        Item.cpp
        Nome.cpp
        Endereco.cpp
        CPF.cpp
        CNPJ.cpp
        ClienteFisico.cpp
        ClienteJuridico.cpp
        GerenciadorDePedidos.cpp
        GerenciadorDeProdutos.cpp
        GerenciadorDeClientes.cpp
        TesteRapido.cpp
)

add_executable(T2_valter ${SOURCE_FILES})


if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            kernel32.lib user32.lib gdi32.lib winspool.lib
            shell32.lib ole32.lib oleaut32.lib uuid.lib
            comdlg32.lib advapi32.lib
    )
endif()