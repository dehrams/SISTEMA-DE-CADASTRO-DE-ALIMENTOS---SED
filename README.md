#  SISTEMA DE CADASTRO DE ALIMENTOS - SED

<p align="center">
  <strong>Sistema de gerenciamento e cadastro de alimentos desenvolvido em linguagem C.</strong>
</p>

---

## 📌 SOBRE O PROJETO

O Sistema de Cadastro de Alimentos é um programa desenvolvido em linguagem C para realizar o cadastro e o gerenciamento de informações de alimentos.

A aplicação funciona por meio de um menu interativo no terminal e permite registrar, consultar, remover e visualizar os alimentos cadastrados.

Os dados são armazenados localmente no arquivo `cadastro.txt`, permitindo que os registros sejam recuperados quando o programa for iniciado novamente.

## ⚙️ FUNCIONALIDADES

O sistema possui as seguintes funcionalidades:

1. **Cadastrar alimento:** registra um alimento com nome, código, quantidade, data de validade e peso ou volume.
2. **Pesquisar alimento:** localiza um registro por meio do código do alimento.
3. **Remover alimento:** permite localizar um alimento e removê-lo após confirmação.
4. **Gerar relatório:** apresenta a quantidade total de alimentos cadastrados e exibe os dados de cada registro.
5. **Salvar e carregar dados:** grava os registros no arquivo `cadastro.txt` e carrega os dados salvos na inicialização do programa.

## 📝 DADOS SOLICITADOS NO CADASTRO

Durante o cadastro, o sistema solicita as seguintes informações:

| Campo | Descrição |
|---|---|
| **Nome** | Nome do alimento. Não pode ficar vazio. |
| **Código** | Código alfanumérico com exatamente 6 caracteres. Letras minúsculas são convertidas para maiúsculas. |
| **Quantidade** | Número inteiro entre 1 e 120. |
| **Validade** | Data no formato DD/MM/AAAA, com verificação dos dias de cada mês e de anos bissextos. |
| **Peso/Volume** | Valor numérico maior ou igual a 1, informado em gramas ou litros. |

> ⚠️ O sistema impede o cadastro de dois alimentos com o mesmo código.

## 💻 TECNOLOGIAS E BIBLIOTECAS

- **Linguagem de programação:** C.
- **stdio.h:** entrada e saída de dados e manipulação de arquivos.
- **stdlib.h:** conversões numéricas e funções utilitárias.
- **string.h:** manipulação de textos.
- **ctype.h:** verificação e conversão de caracteres.
- **locale.h:** configuração de localização.
- **Armazenamento:** arquivo de texto (`cadastro.txt`).

Não é necessário instalar bibliotecas externas para compilar o código.

## 📋 REQUISITOS PARA EXECUÇÃO

- Computador com compilador C instalado, como o GCC.
- Terminal ou prompt de comando para executar o programa.
- Sistema operacional Windows recomendado, pois o código utiliza comandos de terminal específicos do Windows para limpar a tela e configurar a página de código.

## 🚀 COMO COMPILAR E EXECUTAR

**1. Salvar o código-fonte**

Salve o código-fonte com o nome `main.c` e abra o terminal na pasta em que o arquivo está localizado.

**2. Compilar o programa**

No Windows, utilizando GCC/MinGW, execute:

```bash
gcc main.c -o sistema_alimentos.exe
```

**3. Executar o programa**

Após a compilação, execute:

```bash
.\sistema_alimentos.exe
```

Se estiver utilizando outro compilador ou ambiente de desenvolvimento, siga o procedimento correspondente para compilar um programa em C.

## 🎮 COMO UTILIZAR

Ao iniciar, o programa carrega os registros existentes em `cadastro.txt`, caso esse arquivo esteja disponível, e apresenta o menu principal:

```text
1. Cadastrar alimento
2. Pesquisar alimento
3. Remover alimento
4. Relatório
5. Sair
```

Digite o número da opção desejada e siga as instruções exibidas no terminal.

- **Cadastrar:** informe os dados solicitados respeitando os formatos e limites apresentados.
- **Pesquisar ou remover:** informe o código de seis caracteres do alimento.
- **Remover registro:** confirme a operação quando solicitado.
- **Consultar registros:** selecione a opção de relatório.
- **Encerrar:** selecione a opção de saída e confirme. O programa salva os dados antes de finalizar.

## 📁 ARMAZENAMENTO DOS DADOS

O arquivo `cadastro.txt` é criado ou atualizado pelo próprio programa na pasta de execução. Ele contém os registros cadastrados e é utilizado para recuperar as informações em execuções futuras.

**Importante:**
- Mantenha o arquivo `cadastro.txt` na mesma pasta em que o programa é executado.
- Se o arquivo não existir, o sistema inicia sem registros cadastrados.
- Como os dados são armazenados em um arquivo de texto local, recomenda-se manter cópias de segurança desse arquivo.

## ⚠️ LIMITAÇÕES DA VERSÃO ATUAL

Esta versão realiza o cadastro, a pesquisa, a remoção e a emissão de relatório de alimentos.

A aplicação possui interface textual no terminal e utiliza um arquivo de texto local para persistência dos dados. Não utiliza banco de dados nem interface gráfica.

## 👥 AUTORIA

Projeto acadêmico desenvolvido no contexto do curso de **Tecnologia em Análise e Desenvolvimento de Sistemas (TADS)**.

**Integrantes:**
- Amanda de Sousa Afonso
- Debora Emilly Ramos Rabelo
- Ifeanyi Robert Ohaji

**Instituição:** IFSP Campinas

**Curso:** Análise e Desenvolvimento de Sistemas

**Ano:** 2026
