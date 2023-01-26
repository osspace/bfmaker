ARCH = $(shell uname -s)
ifeq ($(findstring CYGWIN, $(ARCH)), CYGWIN)
	PWD_PATH = $(shell cygpath -w $(CURDIR))
else
	PWD_PATH = $(CURDIR)
endif

PROJECT_PATH = $(PWD_PATH)
LIB_PATH     = $(PROJECT_PATH)/freetype_lib
INCLUDE_PATH = $(PROJECT_PATH)/freetype/include \
			   $(PROJECT_PATH)/include
SOURCE_FILE  = $(wildcard ./source/*.cpp)
OBJ_FILE     = $(patsubst %.cpp,%.o,$(SOURCE_FILE))
SRC_PATH     = $(PROJECT_PATH)/source
FREETYPE_PATH = $(PROJECT_PATH)/freetype
FREETYPE_UNIX_PATH = $(FREETYPE_PATH)/builds/unix

# compile tools
CC  = gcc
CXX = g++
LD  = ld
AS  = as

# compile parms
INCLUDE_PARM = $(foreach d, $(INCLUDE_PATH), -I$d)
CXXFLAGS     = -std=c++17
LIB_PARM     = -lfreetype -L$(LIB_PATH)/lib

all: $(PROJECT_PATH)/freetype_lib freetyper maker parser

.ONESHELL:
SHELL := /bin/bash

$(PROJECT_PATH)/freetype_lib:
	@mkdir -p $@

freetyper:
	@echo ==============================freetype==============================
	@cd $(FREETYPE_UNIX_PATH) && ./configure --prefix=$(PROJECT_PATH)/freetype_lib
	@make install -C $(FREETYPE_PATH)/
	$(call print_done, "freetype生成成功！")
	@echo ==============================bfmaker==============================
# end of freetype

maker: $(OBJ_FILE)
	$(CXX) $(SRC_PATH)/bitmap_font_maker.o $(SRC_PATH)/bitmap_font.o $(SRC_PATH)/maker.o -o maker.out $(LIB_PARM)
	$(call print_done, "maker生成成功！")
# end of maker

parser: $(OBJ_FILE)
	$(CXX) $(SRC_PATH)/bitmap_font.o $(SRC_PATH)/parser.o -o parser.out $(LIB_PARM)
	$(call print_done, "parser生成成功！")
# end of parser	

$(OBJ_FILE):%.o:%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@ $(CXXFLAGS) $(INCLUDE_PARM)

.PHONY:clean show
clean:
	@if ls *.out &> /dev/null; then rm *.out; fi
	@if ls ./source/*.o &> /dev/null; then rm ./source/*.o; fi
	# @make clean -C $(FREETYPE_PATH)/

show:
	@echo $(SOURCE_FILE)
	@echo $(OBJ_FILE)
	@echo $(INCLUDE_PARM)


###################################################
#### shell functions
###################################################
# func: print_hint(msg)
define print_hint
	echo -e "\033[34mHint:$(1)\033[0m"
endef

# func: print_done(msg)
define print_done
	echo -e "\033[32mDone:$(1)\033[0m"
endef
