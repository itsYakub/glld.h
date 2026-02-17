# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=c99 -ggdb3
LFLAGS		= -lSDL3

# ========

.PHONY : all

all :
	-$(CC) $(CFLAGS) -o $(MK_ROOT)sample-legacy.out $(MK_ROOT)sample-legacy.c $(LFLAGS)
	-$(CC) $(CFLAGS) -o $(MK_ROOT)sample-modern33.out $(MK_ROOT)sample-modern33.c $(LFLAGS)
	-$(CC) $(CFLAGS) -o $(MK_ROOT)sample-modern46.out $(MK_ROOT)sample-modern46.c $(LFLAGS)

.PHONY : clean

clean :
	rm -f $(MK_ROOT)sample-legacy.out
	rm -f $(MK_ROOT)sample-modern33.out
	rm -f $(MK_ROOT)sample-modern46.out
	
# ========
