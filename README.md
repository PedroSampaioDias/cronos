
# Cronos - SNTP

  

## Ambiente de Desenvolvimento 🛠️📚💡

- **Sistema Operacional:** Ubuntu 22.0

- **Compilador:** GCC (GNU Compiler Collection)

- **Editor de Texto:** VSCode

- **Ferramentas:**

	- **Makefile:** Automatiza o processo de compilação e gerenciamento de dependências. O Makefile utilizado neste projeto inclui: 🚀📂🔄

	- **Cppcheck:** Ferramenta para análise estática de código, usada para detectar erros comuns e possíveis problemas em códigos em C/C++. 🧐🖥️✔️

	- **Valgrind:** Ferramenta para identificação de vazamentos de memória e erros relacionados à alocação dinâmica de memória. 🔍⚙️♻️

## Como Construir a Aplicação 🏗️⚡💾

1. Certifique-se de ter o compilador GCC instalado. Caso não esteja instalado, utilize o comando: 🔽📥🛠️
	```bash
	sudo apt install build-essential
	```
2. No terminal, navegue até o diretório onde o código e o Makefile estão localizados. 📂📜💻

Execute o comando:
```bash
make
```
Isso irá gerar um executável chamado `cronos`. ✅🔧🏁

## Como Executar a Aplicação ▶️🖥️📡
Após a compilação, execute o programa passando o endereço IP de um servidor SNTP como argumento: 🌐📥📊
```bash
./cronos <IP_DO_SERVIDOR_SNTP>
```
Substitua `<IP_DO_SERVIDOR_SNTP>` pelo endereço IPv4 do servidor que você deseja consultar. 💡📌🌟

Exemplo de uso:
```bash
./cronos 200.160.7.186
```
## Instruções de Uso 📖✨🔧
O programa suporta os seguintes comandos e funcionalidades, que podem ser executados via terminal com o **Makefile** ⚙️💻✅

**Compilação do programa:**
```bash
make
```
Compila o código-fonte e gera o executável `cronos`.

**Limpeza de arquivos gerados:**
```bash
make clean
```
Remove o executável e os arquivos gerados durante a compilação.

**Análise de memória:**
```bash
make valgrind <IP_DO_SERVIDOR_SNTP>
```
Executa o Valgrind para análise de uso de memória, utilizando o executável gerado. 🔍🧠✔️

### Principais mensagens exibidas 💬🖥️🔍

**Sucesso:**
```bash
Data/hora: Qui Mar 28 23:11:16 2019
```
**Erro de resposta do servidor:**
```bash
Data/hora: não foi possível contactar servidor
```
**Uso incorreto:**
```bash
Uso: ./cronos <IP do servidor SNTP>
```
**Endereço IP inválido:**
```bash
Erro ao configurar o endereço IP: endereço inválido "<IP_DO_SERVIDOR_SNTP>"
```
### Limitações Conhecidas 🚧🌐📋

A aplicação atualmente **suporta apenas endereços IPv4**. ⚠️🌍📜
