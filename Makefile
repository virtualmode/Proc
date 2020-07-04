# Proc solution makefile.

# Do not create output and intermediate directories:
TARGET_PATHS :=

include Temp/target.makefile

usage:
	@echo " " >&2
	@echo "Proc solution" >&2
	@echo " " >&2
	@echo "Usage:" >&2
	@echo "	make all       # Builds all projects." >&2
	@echo "	make rebuild   # Rebuilds all targets." >&2
	@echo "	make clean     # Removes all output and intermediate results." >&2
	@echo "	make install   # Installation target stub." >&2
	@echo "	make uninstall # Uninstallation stub." >&2
	@echo " " >&2

# Solution projects:
.PHONY: all
all:
	@cd Proc-0 && $(MAKE) all && $(CP) $(OUTPUT_PATH)proc$(EXE) ../bin/
	@echo && echo "Ready." >&2

# Rebuild all targets:
.PHONY: rebuild
rebuild: clean
	$(MAKE) all

# Clean solution:
.PHONY: clean
clean:
	@cd $(OUTPUT_PATH) && $(RM) * || true
	@cd $(INTERMEDIATE_PATH) && $(RM) * || true

# Installation target stub:
.PHONY: install
install:
	@echo "Installation target isn't implemented." >&2

# Uninstall target stub:
.PHONY: uninstall
uninstall:
	@echo "Uninstall target isn't implemented." >&2

# End of makefile.
# Конец файла сборки.
