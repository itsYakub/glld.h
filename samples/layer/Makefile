# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

CFLAGS	= -Wall -Wextra -Werror -ggdb3
LFLAGS	= -lSDL3

# ========

.PHONY : all

all :
	-cc  $(CFLAGS) -o $(MK_ROOT)sample-c.out   $(MK_ROOT)sample.c   $(LFLAGS)
	-c++ $(CFLAGS) -o $(MK_ROOT)sample-cpp.out $(MK_ROOT)sample.cpp $(LFLAGS)

.PHONY : clean

clean :
	rm -f $(MK_ROOT)sample-c.out
	rm -f $(MK_ROOT)sample-cpp.out
	
# ========
