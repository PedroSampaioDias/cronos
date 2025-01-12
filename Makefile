EXEC = cronos

SRC = cronos.c

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

GREEN = \033[1;32m
BLUE = \033[1;34m
RED = \033[1;31m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
CYAN = \033[1;36m
RESET = \033[0m

ARG = $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))

all: $(EXEC)

$(EXEC): $(SRC)
	@echo "$(BLUE)🔨 Compilando o programa...$(RESET)"
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)
	@echo "$(GREEN)✅ Compilação concluída!$(RESET)"

valgrind:
	@echo "$(PURPLE)🔍 Executando Valgrind para análise de memória com argumento: $(ARG)...$(RESET)"
	valgrind --leak-check=full --track-origins=yes ./$(EXEC) $(ARG)
	@echo "$(GREEN)✅ Análise do Valgrind concluída!$(RESET)"

clean:
	@echo "$(RED)🧹 Limpando arquivos gerados...$(RESET)"
	rm -f $(EXEC) cppcheck_report.txt
	@echo "$(GREEN)✅ Limpeza concluída!$(RESET)"

help:
	@echo "$(YELLOW)💡 Comandos disponíveis no Makefile:$(RESET)"
	@echo "$(CYAN)  make$(RESET): Compila o programa."
	@echo "$(CYAN)  make clean$(RESET): Remove o executável e arquivos gerados."
	@echo "$(CYAN)  make valgrind <argumento>$(RESET): Executa análise de memória com Valgrind e passa o argumento ao programa."

%:
	@:
