/ := ../
include $/commons.mk

# TODO: Compile Quell with global CFLAGS, without warnings
# Curently using lib CFLAGS

CFLAGS := -MMD -MP

CFLAGS += -std=c99
CFLAGS += -pedantic
CFLAGS += -fanalyzer
CFLAGS += -fno-builtin
CFLAGS += -fno-tree-loop-distribute-patterns
CFLAGS += -pipe

CFLAGS += -O2
CFLAGS += -march=native
CFLAGS += -mtune=native

CFLAGS += -Waggregate-return
CFLAGS += -Wall
CFLAGS += -Wdisabled-optimization
CFLAGS += -Wduplicated-branches
CFLAGS += -Wduplicated-cond
CFLAGS += -Wextra
CFLAGS += -Wformat=2
CFLAGS += -Winit-self
CFLAGS += -Winline
CFLAGS += -Wlogical-op
CFLAGS += -Wredundant-decls
CFLAGS += -Wshadow
CFLAGS += -Wsuggest-attribute=pure
CFLAGS += -Wsuggest-attribute=const
CFLAGS += -Wsuggest-attribute=format
CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
CFLAGS += -Wwrite-strings


BUILD_DIR := $/.build

LIB := $(BUILD_DIR)/libquell.a

CFLAGS += -std=c99 -pedantic
CFLAGS += -iquote .

include sourcelist.mk

vpath %.c $(VPATH)

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

.PHONY: all
all: $(LIB)

$(LIB): $(OBJ)
	@ mkdir -p $(dir $@)
	$Q $(AR) rc $@ $(OBJ)
	@ $(LOG_TIME) "AR $(C_CYAN) $@ $(C_RESET)"

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	$Q $(CC) $(CFLAGS) -o $@ -c $< || exit 1
	@ $(LOG_TIME) "CC $(C_PURPLE) $(notdir $@) $(C_RESET)"

.PHONY: clean
clean:
	@ $(RM) $(SRC:.c=.gcda)
	@ $(RM) $(SRC:.c=.gcno)
	@ $(RM) $(OBJ)
	@ $(LOG_TIME) $@

.PHONY: fclean
fclean: clean
	@ $(RM) $(LIB)

.PHONY: re
.NOTPARALLEL: re
re: fclean re

-include $(DEP)
