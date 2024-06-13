CC := gcc

CFLAGS += -pedantic
CFLAGS += -Wp,-U_FORTIFY_SOURCE
CFLAGS += -Wformat=2

CFLAGS += -MMD -MP
CFLAGS += -fanalyzer
CFLAGS += -fno-builtin
CFLAGS += -pipe

CFLAGS += -O2 -march=native -mtune=native

CFLAGS += -Wall
CFLAGS += -Wcast-qual
CFLAGS += -Wconversion
CFLAGS += -Wdisabled-optimization
CFLAGS += -Wduplicated-branches
CFLAGS += -Wduplicated-cond
CFLAGS += -Werror=return-type
CFLAGS += -Wextra
CFLAGS += -Winit-self
CFLAGS += -Winline
CFLAGS += -Wlogical-op
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wredundant-decls
CFLAGS += -Wshadow
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wsuggest-attribute=pure
CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
CFLAGS += -Wwrite-strings
CFLAGS += -Wstrict-aliasing=0

CFLAGS += -g

.POSIX:
.SUFFIXES: .d

# ↓ `touch .fast` to force multi-threading
ifneq ($(shell find . -name ".fast"),)
    MAKEFLAGS += -j
endif

V ?= 0
ifneq ($(V),0)
  Q :=
else
  Q := @
endif

RM ?= rm -f
AR ?= ar

ifneq ($(shell command -v tput),)
  ifneq ($(shell tput colors),0)

mk-color = \e[$(strip $1)m

C_BEGIN := \033[A
C_RESET := $(call mk-color, 00)

C_RED := $(call mk-color, 31)
C_GREEN := $(call mk-color, 32)
C_YELLOW := $(call mk-color, 33)
C_BLUE := $(call mk-color, 34)
C_PURPLE := $(call mk-color, 35)
C_CYAN := $(call mk-color, 36)

  endif
endif

NOW = $(shell date +%s%3N)
STIME := $(call NOW)
TIME_NS = $(shell expr $(call NOW) - $(STIME))
TIME_MS = $(shell expr $(call TIME_NS))

BOXIFY = "[$(C_BLUE)$(1)$(C_RESET)] $(2)"

ifneq ($(shell command -v printf),)
  LOG_TIME = printf $(call BOXIFY, %6s , %b\n) "$(call TIME_MS)"
else
  LOG_TIME = echo -e $(call BOXIFY, $(call TIME_MS) ,)
endif
