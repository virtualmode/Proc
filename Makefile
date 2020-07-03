# Proc makefile.

DEBUG := 1

include Temp/target.makefile

# Extension $(COM) is also possible:
.PHONY: all
all: $(OUTPUT_PATH)proc$(EXE)
	@$(CP) $(OUTPUT_PATH)proc$(EXE) bin/
	@echo "Proc done." >&2

.PHONY: rebuild
rebuild: clean
	$(MAKE) all CONFIGURATION=$(CONFIGURATION) PLATFORM=$(PLATFORM) --no-print-directory

.PHONY: clean
clean:
	@cd $(OUTPUT_PATH) && $(RM) * || true
	@cd $(INTERMEDIATE_PATH) && $(RM) * || true

# End of makefile.
# Конец файла сборки.
