# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

.PHONY : all

all :
	make all -C $(MK_ROOT)null/
	make all -C $(MK_ROOT)glfw3/
	make all -C $(MK_ROOT)sdl3/
	make all -C $(MK_ROOT)sfml2/
	make all -C $(MK_ROOT)sfml3/
	make all -C $(MK_ROOT)window.h/

.PHONY : clean

clean :
	make clean -C $(MK_ROOT)null/
	make clean -C $(MK_ROOT)glfw3/
	make clean -C $(MK_ROOT)sdl3/
	make clean -C $(MK_ROOT)sfml2/
	make clean -C $(MK_ROOT)sfml3/
	make clean -C $(MK_ROOT)window.h/
	
# ========
