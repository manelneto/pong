# name of the program (Minix service)
PROG=lab5

# source code files to be compiled
SRCS = lab5.c video_card.c video_gr.c keyboard.c kbc.c utils.c timer.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
