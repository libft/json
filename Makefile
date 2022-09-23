Q3 := $(if $(filter 3,$(V) $(VERBOSE)),,@)
Q2 := $(if $(filter 2 3,$(V) $(VERBOSE)),,@)
Q1 := $(if $(filter 1 2 3,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 3,$(V) $(VERBOSE)),,--no-print-directory) $(if $(filter 1,$(NO_ADDITIONAL_J)),,-j $(shell sh src/build/script/nproc.sh) NO_ADDITIONAL_J=1)

export V

all: test
clean:
	$(Q2)rm -rf tmp
	$(Q2)$(MAKE) -C src clean
	$(Q2)$(MAKE) -C test clean
	$(Q2)find src \( -type f \( -name compile_commands.json -o -name "*.part.json" -o -name "*.exe" \) -o -type d -name .cache \) -delete
	$(Q2)find src -type d -empty -delete
	$(Q2)find src -type d -name test | xargs -L1 -I {} $(MAKE) -C {} clean
	@printf "\033[0m"
fclean:
	$(Q2)rm -f compile_commands.json .vscode/launch.json .vscode/tasks.json
	$(Q2)$(MAKE) -C src fclean
	$(Q2)$(MAKE) -C test fclean
	$(Q2)find src \( -type f \( -name compile_commands.json -o -name "*.part.json" -o -name "*.exe" \) -o -type d -name .cache \) -delete
	$(Q2)find src -type d -empty -delete
	$(Q2)find src -type d -name test | xargs -L1 -I {} $(MAKE) -C {} fclean
	@printf "\033[0m"
re:
	$(Q3)$(MAKE) fclean
	$(Q3)$(MAKE) all
test:
	$(Q2)find src -type d -name test | sort | xargs -L1 $(MAKE) -C
	@echo "Some test might need manual review"
.PHONY: all clean fclean re refresh test publish publish_without_test

.PHONY: pre_dev
pre_dev:
	$(Q2)find src -type d -name test | xargs -L1 -I {} $(MAKE) -C {} dev
.PHONY: compile_commands.json
compile_commands.json: pre_dev
	$(Q2)$(MAKE) -C src -k PROFILE=debug TARGET=development all bonus ; (printf "[" && find src/.cache -name "*.development.debug.o.compile_commands.part.json" | xargs cat && printf "]") > $@
.PHONY: .vscode/launch.json
.vscode/launch.json: pre_dev
	$(Q2)(cat template/launch.json.before.txt && find src -name launch.part.json | xargs cat && cat template/launch.json.after.txt) > $@
.PHONY: .vscode/tasks.json
.vscode/tasks.json: pre_dev
	$(Q2)(cat template/tasks.json.before.txt && find src -name tasks.part.json | xargs cat && cat template/tasks.json.after.txt) > $@
.PHONY: dev
dev: compile_commands.json .vscode/launch.json .vscode/tasks.json

.PHONY: run
run:
	$(Q3)$(MAKE) -C src .cache/minishell.production.release.exe
	$(Q1)src/.cache/minishell.production.release.exe
