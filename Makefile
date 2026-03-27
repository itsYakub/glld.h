# ========

MK_ROOT	= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME	= glld

# ========

TARGET	= $(MK_ROOT)$(MK_NAME).h
GPATH	= $(MK_ROOT)gen/$(MK_NAME).py
GFLAGS	= --output=$(TARGET) \
		  --profile=core \
		  --assertion=yes 

# ========

.PHONY : all

all : gen install

.PHONY : install

install :
	mkdir -p /usr/local/include/$(MK_NAME)/
	cp -f $(TARGET) /usr/local/include/$(MK_NAME)/
	ln -nfs /usr/local/include/$(MK_NAME)/$(MK_NAME).h /usr/local/include/$(MK_NAME).h

.PHONY : remove

remove :
	rm -rf /usr/local/include/$(MK_NAME)
	rm -f /usr/local/include/$(MK_NAME).h

.PHONY : gen

gen :
	python3 $(GPATH) $(GFLAGS)

.PHONY : samples

samples :
	make -C $(MK_ROOT)samples/

# ========
