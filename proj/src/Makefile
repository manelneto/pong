# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRC_DIR := .../drivers
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR := .../obj
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
