ARCH = $(shell uname -s)
ifeq ($(findstring CYGWIN, $(ARCH)), CYGWIN)
	PWD_PATH = $(shell cygpath -w $(CURDIR))
else
	PWD_PATH = $(CURDIR)
endif

PROJECT_PATH = $(PWD_PATH)
LIB_PATH     = $(PROJECT_PATH)
INCLUDE_PATH = $(PROJECT_PATH)/freetype/include \
			   $(PROJECT_PATH)/include
SOURCE_FILE  = $(wildcard ./source/*.cpp)
OBJ_FILE     = $(patsubst %.cpp,%.o,$(SOURCE_FILE))
SRC_PATH     = $(PROJECT_PATH)/source

# compile tools
CC  = gcc
CXX = g++
LD  = ld
AS  = as

# compile parms
INCLUDE_PARM = $(foreach d, $(INCLUDE_PATH), -I$d)
CXXFLAGS     = -std=c++17
LIB_PARM     = -lfreetype
LIB_PATH     = -L$(PROJECT_PATH)/lib

all: maker parser

test: $(OBJ_FILE)
	$(CXX) $(SRC_PATH)/test.o $(SRC_PATH)/bitmap_font_maker.o $(SRC_PATH)/bitmap_font.o -o test.exe $(LIB_PARM) $(LIB_PATH)

maker: $(OBJ_FILE)
	$(CXX) $(SRC_PATH)/bitmap_font_maker.o $(SRC_PATH)/bitmap_font.o $(SRC_PATH)/maker.o -o maker.exe $(LIB_PARM) $(LIB_PATH)

parser: $(OBJ_FILE)
	$(CXX) $(SRC_PATH)/bitmap_font.o $(SRC_PATH)/parser.o -o parser.exe $(LIB_PARM) $(LIB_PATH)
	
$(OBJ_FILE):%.o:%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@ $(CXXFLAGS) $(INCLUDE_PARM)

.PHONY:clean
clean:
	@if ls *.exe &> /dev/null; then rm *.exe; fi
	@if ls ./source/*.o &> /dev/null; then rm ./source/*.o; fi

show:
	@echo $(SOURCE_FILE)
	@echo $(OBJ_FILE)
	@echo $(INCLUDE_PARM)
