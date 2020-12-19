CC=g++

EXE_FILE=rsa

UTEST_FILE=unittest
UTEST_DIR=../source/unittest/tests

INC_DIR =../source/include
SRC_DIR=../source/src

CFLAGS=-I$(INC_DIR)
OUT_DIR=.

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.o,$(SRC_FILES))

CXXFLAGS = -g -Wall -Werror

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT_DIR)/$(EXE_FILE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean_all clean_unittest clean

clean:
	rm -f $(OUT_DIR)/*.o *~ core $(EXE_FILE)
clean_unittest:
	rm $(UTEST_FILE)

clean_all: clean clean_unittest

.PHONY: unittest

unittest:
	$(CC) -c $(SRC_DIR)/*.cpp $(CFLAGS)
	rm -f RSA.o
	$(CC) -c $(UTEST_DIR)/*.cpp $(CFLAGS) -I../source/unittest
	$(CC) -o $(UTEST_FILE) *.o -lgtest -lpthread


