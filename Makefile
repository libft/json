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
	$(Q2)make -C assets/leak_test all
	$(Q2)make -C src PROFILE=debug TARGET=development .cache/libft.development.debug.a
	$(Q2)make -C src PROFILE=debug TARGET=development SANITIZER=undefined .cache/libft.development.debug.undefined.a || echo "[WARNING] Failed to build debug/development/undefined" 1>&2
	$(Q2)make -C src PROFILE=debug TARGET=development SANITIZER=address .cache/libft.development.debug.address.a || echo "[WARNING] Failed to build debug/development/address" 1>&2
	$(Q2)make -C src PROFILE=debug TARGET=development SANITIZER=memory .cache/libft.development.debug.memory.a || echo "[WARNING] Failed to build debug/development/memory" 1>&2
	$(Q2)make -C src PROFILE=debug TARGET=development SANITIZER=leak .cache/libft.development.debug.leak.a || echo "[WARNING] Failed to build debug/development/leak" 1>&2
	$(Q2)make -C src PROFILE=debug TARGET=production .cache/libft.production.debug.a
	$(Q2)make -C src PROFILE=debug TARGET=production SANITIZER=undefined .cache/libft.production.debug.undefined.a || echo "[WARNING] Failed to build debug/development/undefined" 1>&2
	$(Q2)make -C src PROFILE=debug TARGET=production SANITIZER=address .cache/libft.production.debug.address.a || echo "[WARNING] Failed to build debug/development/address" 1>&2
	$(Q2)make -C src PROFILE=debug TARGET=production SANITIZER=memory .cache/libft.production.debug.memory.a || echo "[WARNING] Failed to build debug/development/memory" 1>&2
	$(Q2)make -C src PROFILE=debug TARGET=production SANITIZER=leak .cache/libft.production.debug.leak.a || echo "[WARNING] Failed to build debug/development/leak" 1>&2
	$(Q2)make -C src PROFILE=release TARGET=development .cache/libft.development.release.a
	$(Q2)make -C src PROFILE=release TARGET=development SANITIZER=undefined .cache/libft.development.release.undefined.a || echo "[WARNING] Failed to build release/development/undefined" 1>&2
	$(Q2)make -C src PROFILE=release TARGET=development SANITIZER=address .cache/libft.development.release.address.a || echo "[WARNING] Failed to build release/development/address" 1>&2
	$(Q2)make -C src PROFILE=release TARGET=development SANITIZER=memory .cache/libft.development.release.memory.a || echo "[WARNING] Failed to build release/development/memory" 1>&2
	$(Q2)make -C src PROFILE=release TARGET=development SANITIZER=leak .cache/libft.development.release.leak.a || echo "[WARNING] Failed to build release/development/leak" 1>&2
	$(Q2)make -C src PROFILE=release TARGET=production .cache/libft.production.release.a
	$(Q2)make -C src PROFILE=release TARGET=production SANITIZER=undefined .cache/libft.production.release.undefined.a || echo "[WARNING] Failed to build release/development/undefined" 1>&2
	$(Q2)make -C src PROFILE=release TARGET=production SANITIZER=address .cache/libft.production.release.address.a || echo "[WARNING] Failed to build release/development/address" 1>&2
	$(Q2)make -C src PROFILE=release TARGET=production SANITIZER=memory .cache/libft.production.release.memory.a || echo "[WARNING] Failed to build release/development/memory" 1>&2
	$(Q2)make -C src PROFILE=release TARGET=production SANITIZER=leak .cache/libft.production.release.leak.a || echo "[WARNING] Failed to build release/development/leak" 1>&2
	$(Q2)make -C test PROFILE=debug TARGET=development
	$(Q2)[ ! -f src/.cache/libft.development.debug.undefined.a ] || make -C test PROFILE=debug TARGET=development SANITIZER=undefined
	$(Q2)[ ! -f src/.cache/libft.development.debug.address.a ] || make -C test PROFILE=debug TARGET=development SANITIZER=address
	$(Q2)[ ! -f src/.cache/libft.development.debug.memory.a ] || make -C test PROFILE=debug TARGET=development SANITIZER=memory
	$(Q2)[ ! -f src/.cache/libft.development.debug.leak.a ] || make -C test PROFILE=debug TARGET=development SANITIZER=leak
	$(Q2)make -C test PROFILE=debug TARGET=production
	$(Q2)[ ! -f src/.cache/libft.production.debug.undefined.a ] || make -C test PROFILE=debug TARGET=production SANITIZER=undefined
	$(Q2)[ ! -f src/.cache/libft.production.debug.address.a ] || make -C test PROFILE=debug TARGET=production SANITIZER=address
	$(Q2)[ ! -f src/.cache/libft.production.debug.memory.a ] || make -C test PROFILE=debug TARGET=production SANITIZER=memory
	$(Q2)[ ! -f src/.cache/libft.production.debug.leak.a ] || make -C test PROFILE=debug TARGET=production SANITIZER=leak
	$(Q2)make -C test PROFILE=release TARGET=development
	$(Q2)[ ! -f src/.cache/libft.development.release.undefined.a ] || make -C test PROFILE=release TARGET=development SANITIZER=undefined
	$(Q2)[ ! -f src/.cache/libft.development.release.address.a ] || make -C test PROFILE=release TARGET=development SANITIZER=address
	$(Q2)[ ! -f src/.cache/libft.development.release.memory.a ] || make -C test PROFILE=release TARGET=development SANITIZER=memory
	$(Q2)[ ! -f src/.cache/libft.development.release.leak.a ] || make -C test PROFILE=release TARGET=development SANITIZER=leak
	$(Q2)make -C test PROFILE=release TARGET=production
	$(Q2)[ ! -f src/.cache/libft.production.release.undefined.a ] || make -C test PROFILE=release TARGET=production SANITIZER=undefined
	$(Q2)[ ! -f src/.cache/libft.production.release.address.a ] || make -C test PROFILE=release TARGET=production SANITIZER=address
	$(Q2)[ ! -f src/.cache/libft.production.release.memory.a ] || make -C test PROFILE=release TARGET=production SANITIZER=memory
	$(Q2)[ ! -f src/.cache/libft.production.release.leak.a ] || make -C test PROFILE=release TARGET=production SANITIZER=leak
	@echo "Some test might need manual review"
.PHONY: all clean fclean re refresh test publish publish_without_test

.PHONY: pre_dev
pre_dev:
	$(Q2)find src -type d -name test | xargs -L1 -I {} $(MAKE) -C {} dev
	$(Q2)$(MAKE) -C test build PROFILE=debug TARGET=development
.PHONY: compile_commands.json
compile_commands.json: pre_dev
	$(Q2)$(MAKE) -C src -k PROFILE=debug TARGET=development all bonus ; (echo "[" && find src/.cache -name "*.development.debug.o.compile_commands.part.json" | xargs cat && find test -name "*.development.debug.o.compile_commands.part.json" | xargs cat && echo "]") > $@
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
