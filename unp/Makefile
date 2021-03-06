#############################################################################
#
# Generic Makefile for C/C++ Program
#
# Author:  yun63<thewardsthe@mail.com>
#
#############################################################################

## 头文件搜索路径 
INCPATH = -I. -I$(GTEST_DIR)/include  -I./protobuf/include

## 源代码目录
SRCDIRS = src 

## 生成目标目录
OBJ_DIR = object.dir

## 可执行程序目录
BIN = bin

## GTest测试框架目录
GTEST_DIR = ./3rd/gtest-1.7.0
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h 
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

export LD_LIBRARY_PATH+=:./protobuf/lib/

## 可执行文件名称
TARGETS = 

## 源文件类型
SRCEXTS = .c .cc .cpp .c++ .cxx 
## 头文件类型
HDREXTS = .h .hh .hpp .h++ .hxx 

CPPFLAGS += -isystem $(GTEST_DIR)/include

## C/C++编译器编译选项
CFLAGS   += -g #-Wall -Wextra
CXXFLAGS += -g #-Wall -Wextra

## 自定义编译选项
MYCFLAGS = #-DENCODING_UTF8 -DCHARSET_SHOW_GBK 

## 指定C/C++编译器
CC = gcc
CXX = g++

SOURCES := $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*, $(SRCEXTS))))
HEADERS := $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*, $(HDREXTS))))

#$(warning $(SOURCES))
#$(warning $(HEADERS))

SRC_CXX := $(filter-out %.c,$(SOURCES))
OBJECTS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))

PROTO_INC := $(patsubst %.proto, %.pb.h,  $(wildcard base/pb/*.proto))
PROTO_CXX := $(patsubst %.proto, %.pb.cc, $(wildcard base/pb/*.proto))
PROTO_OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(PROTO_CXX))))


## 系统库文件
LIBS = -lpthread -lz -lm

## 第三方库文件
MYLIBS = -L/usr/lib -lpthread \
		 -L/usr/lib -lm \
		 -L/lib -L/usr/local/lib 

COMPILE_C := $(CC) $(CFLAGS) $(MYCFLAGS) $(INCPATH) -c
COMPILE_CXX := $(CXX) $(CXXFLAGS) $(MYCFLAGS) $(INCPATH) -c

ifeq ($(SRC_CXX),)
	LINK = $(CC) $(CFLAGS) $(LDFLAGS) $(MYCFLAGS)
else
	LINK = $(CXX) $(CXXFLAGS) $(LDFLAGSk) $(MYCFLAGS)
endif

ifeq (DEBUG, 1)
	CFLAGS = -g3 -DDEBUG
	CXXFLAGS = -g3 -DDEBUG
else
	CFLAGS = -O3 -DNDEBUG
	CXXFLAGS = -O3 -DNDEBUG
endif

.PHONY: clean show

.SUFFIXES:

all: pb $(TARGETS)

## 生成所有(.o)文件规则.
#----------------------------------------
$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(@D)
	@echo "\033[1;32mCOMPILING \033[0m"
	$(COMPILE_C) $< -o $@

$(OBJ_DIR)/%.o:%.cc
	@mkdir -p $(@D)
	@echo "\033[1;32mCOMPILING \033[0m"
	$(COMPILE_CXX) $< -o $@

$(OBJ_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	@echo "\033[1;32mCOMPILING \033[0m"
	$(COMPILE_CXX) $< -o $@

$(OBJ_DIR)/%.o:%.c++
	@mkdir -p $(@D)
	@echo "\033[1;32mCOMPILING \033[0m"
	$(COMPILE_CXX) $< -o $@

$(OBJ_DIR)/%.o:%.cxx
	@mkdir -p $(@D)
	@echo "\033[1;32mCOMPILING \033[0m"
	$(COMPILE_CXX) $< -o $@

%.o:%.c
	@echo "\033[1;32mCOMPILING \033[0m"
	$(COMPILE_C) $< -o $@

%.o:%.cpp
	@echo "\033[1;32mCOMPILING \033[0m"
	$(COMPILE_CXX) $< -o $@

%.o:%.cc
	@echo "\033[1;32mCOMPILING \033[0m"
	$(COMPILE_CXX) $< -o $@


%.pb.cc: %.proto
	./protobuf/bin/protoc -I=base/pb/ --cpp_out=base/pb/ $<

libgtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^
	@mv $@ ./lib

libgtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
	@mv $@ ./lib

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc
	

## 生成目标
#-------------------------------------
pb : $(PROTO_CXX)

cloud : test_main.o $(PROTO_OBJS) $(OBJECTS) 
	@$(LINK) -o $@ $^ $(MYLIBS) $(LIBS)
	@echo "\033[1;35mLINKING $@ \033[0m"

add_person: add_person.o $(PROTO_OBJS) $(OBJECTS)
	@$(LINK) -o $@ $^ $(MYLIBS) $(LIBS)
	@echo "\033[1;35mLINKING $@ \033[0m"

list_people : list_people.o $(PROTO_OBJS) $(OBJECTS)
	@$(LINK) -o $@ $^ $(MYLIBS) $(LIBS)
	@echo "\033[1;35mLINKING $@ \033[0m"


install:
	mv -f $(TARGETS) $(BIN)

clean:
	-rm -f $(PROTO_INC) $(PROTO_CXX)
	-rm -f *.o
	-rm -f *~ core *.core
	-rm -rf $(OBJ_DIR) 
	-rm -f $(TARGETS) 
	-rm -f $(BIN)/*

#############################################################################
