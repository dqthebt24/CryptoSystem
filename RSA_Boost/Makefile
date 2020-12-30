CC=g++

EXE_FILE=rsa

INC_DIR =../source/include
SRC_DIR=../source/src

CFLAGS=-I$(INC_DIR)
OUT_DIR=.

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.o,$(SRC_FILES))

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT_DIR)/$(EXE_FILE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OUT_DIR)/*.o *~ core $(EXE_FILE)
