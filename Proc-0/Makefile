# Proc-0 makefile.

#DEBUG := 1
TARGET_ENTRY := main

include ../Temp/target.makefile

.PHONY: all
all: $(OUTPUT_PATH)proc$(EXE)
	@echo "Proc-0 done." >&2

.PHONY: rebuild
rebuild: clean
	$(MAKE) all

.PHONY: clean
clean:
	@cd $(OUTPUT_PATH) && $(RM) * || true
	@cd $(INTERMEDIATE_PATH) && $(RM) * || true

# End of makefile.
# Конец файла сборки.
