CC=g++
CFLAGS=-I .
OUTPUT=rsa
BUILD_DIR=Debug
SRC_DIR=./
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
BUILD_DIR=Debug
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))


$(BUILD_DIR)/$(OUTPUT):$(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(OUTPUT)
