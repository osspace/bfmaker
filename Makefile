ARCH = $(shell uname -s)
ifeq ($(findstring CYGWIN, $(ARCH)), CYGWIN)
	PWD_PATH = $(shell cygpath -w $(CURDIR))
else
	PWD_PATH = $(CURDIR)
endif

LIB_PATH     = $(PWD_PATH)/freetype_lib
INCLUDE_PATH = $(PWD_PATH)/freetype/include \
			   $(PWD_PATH)/include
SOURCE_FILE  = $(wildcard ./source/*.cpp)
OBJ_FILE     = $(patsubst %.cpp,%.o,$(SOURCE_FILE))
SRC_PATH     = $(PWD_PATH)/source
FREETYPE_PATH = $(PWD_PATH)/freetype

# compile tools
CC  = gcc
CXX = g++
LD  = ld
AS  = as

# compile parms
INCLUDE_PARM = $(foreach d, $(INCLUDE_PATH), -I$d)
CXXFLAGS     = -std=c++17
LIB_PARM     = -lfreetype -L$(LIB_PATH)/lib

all: $(PWD_PATH)/freetype_lib freetyper maker parser

.ONESHELL:
SHELL := /bin/bash

$(PWD_PATH)/freetype_lib:
	@mkdir -p $@

freetyper:
	@echo ==============================freetype==============================
	cd $(FREETYPE_PATH) && ./configure --prefix=$(PWD_PATH)/freetype_lib --disable-shared --enable-static
	make -C $(FREETYPE_PATH)/
	cd $(FREETYPE_PATH) && make install
	$(call print_done, "freetype生成成功！")
	@echo ==============================bfmaker==============================
# end of freetype

maker: $(OBJ_FILE)
	$(CXX) $(SRC_PATH)/bitmap_font_maker.o $(SRC_PATH)/bitmap_font.o $(SRC_PATH)/maker.o -o maker $(LIB_PARM)
	$(call print_done, "maker生成成功！")
# end of maker

parser: $(OBJ_FILE)
	$(CXX) $(SRC_PATH)/bitmap_font.o $(SRC_PATH)/parser.o -o parser $(LIB_PARM)
	$(call print_done, "parser生成成功！")
# end of parser	

$(OBJ_FILE):%.o:%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@ $(CXXFLAGS) $(INCLUDE_PARM)

.PHONY:clean
clean:
	@if ls *.out &> /dev/null; then rm *.out; fi
	@if ls ./source/*.o &> /dev/null; then rm ./source/*.o; fi
	@cd $(FREETYPE_PATH) && make clean

###################################################
#### shell functions
###################################################
# func: print_hint(msg)
define print_hint
	@echo -e "\033[34mHint:$(1)\033[0m"
endef

# func: print_done(msg)
define print_done
	@echo -e "\033[32mDone:$(1)\033[0m"
endef
