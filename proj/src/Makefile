# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}
.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/game
.PATH: ${.CURDIR}/imgs
.PATH: ${.CURDIR}/event_handler

# source code files to be compiled
SRCS = proj.c utils.c device_utils.c video_card.c keyboard.c mouse.c timer.c rtc.c kbd_event_handler.c mouse_event_handler.c timer_event_handler.c int_manager.c tetromino.c game_state.c draw_graphics.c logic.c leaderboard.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>>