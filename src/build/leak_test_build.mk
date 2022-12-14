include $(BASE_PATH)/build/common.mk

ifeq ($(WITH_COVERAGE),1)
CC := $(PATH_TO_LLVM_BIN)/clang
CPPFLAGS := -I$(BASE_PATH)/../assets/leak_test/include $(addprefix -I$(BASE_PATH),$(shell xargs < $(INCS_FILE))) -DLLVM_BUILD_INSTRUMENTED_COVERAGE=On
CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic $(CPPFLAGS) $(COMMON_FLAGS) -g3 -fprofile-instr-generate -fcoverage-mapping
LDFLAGS := $(COMMON_FLAGS) -fprofile-instr-generate
else
CPPFLAGS := -I$(BASE_PATH)/../assets/leak_test/include $(addprefix -I$(BASE_PATH),$(shell xargs < $(INCS_FILE)))
CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic $(CPPFLAGS) $(COMMON_FLAGS) -g3
LDFLAGS := $(COMMON_FLAGS)
endif

$(BASE_PATH)/../assets/leak_test/libft_leak_test.address.a:
	$(Q2)$(MAKE) -C $(@D) $(@F)

%.o:
	$(Q2)$(CC) -MMD -MJ $@.compile_commands.part.json $(CFLAGS) -o $@ -x c -c $<
%.a:
	$(Q2)$(AR) $(ARFLAGS) $@ $^
%.exe: $(BASE_PATH)/../assets/leak_test/libft_leak_test.address.a
	$(Q2)$(CC) $(LDFLAGS) -o $@ $^

Makefile: deps.mk
	$(Q3)touch $@
deps.mk: $(DEPS_FILE)
	$(Q2)cat $^ | sh $(BASE_PATH)/build/script/srcs_to_deps.sh test.exe > $@

-include deps.mk $(shell find . -type f -name "*.d")
