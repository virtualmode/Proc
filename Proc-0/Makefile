# Proc-0 makefile.
# Временный файл сборки, используемый только в Proc-0 процессоре.
# После реализации первой версии, будет использована новая система сборки.

DEBUG := 1

TARGET_PCH_CPP_HEADER := Temp/Dependency.h
TARGET_PCH_CPP_SOURCE := Temp/Dependency.cpp

include ../Temp/target.makefile

.PHONY: all
all: $(OUTPUT_PATH)proc$(EXE)
	@echo "Proc-0 done." >&2

.PHONY: rebuild
rebuild: clean
	$(MAKE) all

.PHONY: clean
clean:
	@cd $(OUTPUT_PATH).. && $(RM) * || true
	@cd $(INTERMEDIATE_PATH).. && $(RM) * || true
	@echo "Proc-0 clean succeeded." >&2

# End of makefile.
# Конец файла сборки.
