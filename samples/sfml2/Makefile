# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

CC			= c++
CFLAGS		= -Wall -Wextra -std=c++11 -ggdb3
LFLAGS		= -lsfml-system -lsfml-window

# ========

.PHONY : all

all :
	-$(CC) $(CFLAGS) -o $(MK_ROOT)sample-legacy.out $(MK_ROOT)sample-legacy.cc $(LFLAGS)
	-$(CC) $(CFLAGS) -o $(MK_ROOT)sample-modern33.out $(MK_ROOT)sample-modern33.cc $(LFLAGS)
	-$(CC) $(CFLAGS) -o $(MK_ROOT)sample-modern46.out $(MK_ROOT)sample-modern46.cc $(LFLAGS)

.PHONY : clean

clean :
	rm -f $(MK_ROOT)sample-legacy.out
	rm -f $(MK_ROOT)sample-modern33.out
	rm -f $(MK_ROOT)sample-modern46.out
	
# ========
