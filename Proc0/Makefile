# Proc0 Makefile.

ifndef TOP
	TOP = .
	INCLUDED = no
endif

ifeq ($(findstring $(MAKECMDGOALS),clean distclean),)
	include $(TOP)/config.mak
endif

# Цель для запуска без параметров должна быть выше остальных.
# Сборка актуальной версии.
all: config.mak proc.0.0.0

# Проверка наличия конфигурации.
config.mak:
	$(if $(wildcard $@),,@echo "Please run ./configure script." && exit 1)

# Удаление промежуточных и выходных файлов.
clean:
	git clean -xdf

# Пример сборки.
proc0: proc0.c
	gcc -O2 -Wall -g -o $@ $< -ldl

# Сборка доступных версий компилятора.
proc.0.0.0: proc.0.0.0.c
	gcc -O2 -Wall -g -o proc0$(EXE) $< -ldl
