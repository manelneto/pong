# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/drivers
.PATH: ${.CURDIR}/game

# source code files to be compiled
SRCS = proj.c kbc.c keyboard.c mouse.c timer.c utils.c video_gr.c ball.c game.c wall.c sprite.c menu.c button.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ -O2

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
