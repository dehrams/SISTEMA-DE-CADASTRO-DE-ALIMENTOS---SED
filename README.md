SISTEMA DE CADASTRO DE ALIMENTOS
SOBRE O PROJETO
O Sistema de Cadastro de Alimentos é um programa desenvolvido em linguagem C para realizar o cadastro e o gerenciamento de informações de alimentos. A aplicação funciona por meio de um menu no terminal e permite registrar, consultar, remover e visualizar os alimentos cadastrados.
Os dados são armazenados localmente no arquivo cadastro.txt, permitindo que os registros sejam recuperados quando o programa for iniciado novamente.
FUNCIONALIDADES
Cadastrar alimento Registra um alimento com nome, código, quantidade, data de validade e peso ou volume.
Pesquisar alimento Localiza um registro por meio do código do alimento.
Remover alimento Permite localizar um alimento e removê-lo após confirmação.
Gerar relatório Apresenta a quantidade total de alimentos cadastrados e exibe os dados de cada registro.
Salvar e carregar dados Grava os registros no arquivo cadastro.txt e carrega os dados salvos na inicialização do programa.
DADOS SOLICITADOS NO CADASTRO
Nome: nome do alimento. Não pode ficar vazio.
Código: código alfanumérico com exatamente 6 caracteres. Letras minúsculas são convertidas para maiúsculas.
Quantidade: número inteiro entre 1 e 120.
Validade: data no formato DD/MM/AAAA, com verificação dos dias de cada mês e de anos bissextos.
Peso/volume: valor numérico maior ou igual a 1, informado em gramas ou litros.
O sistema impede o cadastro de dois alimentos com o mesmo código.
TECNOLOGIAS E BIBLIOTECAS
Linguagem de programação: C.
stdio.h: entrada e saída de dados e manipulação de arquivos.
stdlib.h: conversões numéricas e funções utilitárias.
string.h: manipulação de textos.
ctype.h: verificação e conversão de caracteres.
locale.h: configuração de localização.
Armazenamento: arquivo de texto (cadastro.txt).
Não é necessário instalar bibliotecas externas para compilar o código.
REQUISITOS PARA EXECUÇÃO
Computador com compilador C instalado, como o GCC.
Terminal ou prompt de comando para executar o programa.
Sistema operacional Windows recomendado, pois o código utiliza comandos de terminal específicos do Windows para limpar a tela e configurar a página de código.
COMO COMPILAR E EXECUTAR
Salve o código-fonte com o nome main.c e abra o terminal na pasta em que o arquivo está localizado.
No Windows, utilizando GCC/MinGW, compile com:
    gcc main.c -o sistema_alimentos.exe
Em seguida, execute com:
    .\\sistema_alimentos.exe
Se estiver utilizando outro compilador ou ambiente de desenvolvimento, siga o procedimento correspondente para compilar um programa em C.
COMO UTILIZAR
Ao iniciar, o programa carrega os registros existentes em cadastro.txt, caso esse arquivo esteja disponível, e apresenta o menu principal:
    1. Cadastrar alimento 2. Pesquisar alimento 3. Remover alimento 4. Relatório 5. Sair
Digite o número da opção desejada e siga as instruções exibidas no terminal.
Para cadastrar, informe os dados solicitados respeitando os formatos e limites apresentados.
Para pesquisar ou remover, informe o código de seis caracteres do alimento.
Para remover um registro, confirme a operação quando solicitado.
Para consultar os registros, selecione a opção de relatório.
Para encerrar, selecione a opção de saída e confirme. O programa salva os dados antes de finalizar.
ARMAZENAMENTO DOS DADOS
O arquivo cadastro.txt é criado ou atualizado pelo próprio programa na pasta de execução. Ele contém os registros cadastrados e é utilizado para recuperar as informações em execuções futuras.
Mantenha o arquivo cadastro.txt na mesma pasta em que o programa é executado. Se ele não existir, o sistema inicia sem registros cadastrados. Como os dados são armazenados em um arquivo de texto local, recomenda-se manter cópias de segurança desse arquivo.
LIMITAÇÕES DA VERSÃO ATUAL
Esta versão realiza o cadastro, a pesquisa, a remoção e a emissão de relatório de alimentos. A aplicação possui interface textual no terminal e utiliza um arquivo de texto local para persistência dos dados. Não utiliza banco de dados nem interface gráfica.
AUTORIA
Projeto acadêmico desenvolvido no contexto do curso de Tecnologia em Análise e Desenvolvimento de Sistemas (TADS).
Integrantes: Amanda de Sousa Afonso, Debora Emilly Ramos Rabelo e Ifeanyi Robert Ohaji
Instituição: IFSP Campinas - Curso: Analise e Desenvolvimento de Sistemas Ano: 2026
