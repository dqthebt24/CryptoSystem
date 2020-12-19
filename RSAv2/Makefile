CC=g++
EXE_FILE=rsa
UNITTEST_FILE=unittest
UNITTEST_DIR=../unittest
IDIR =..
SRC_DIR=..
CFLAGS=-I$(IDIR)
ODIR=.
_OBJ = bigint.o algorithm.o RSAv2.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CXXFLAGS = -g -Wall -Werror

$(ODIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/rsa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean_all clean_unittest clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXE_FILE)
clean_unittest:
	rm $(UNITTEST_FILE)

clean_all: clean clean_unittest

.PHONY: unittest

unittest:
	$(CC) -c $(SRC_DIR)/*.cpp
	rm -f RSAv2.o
	$(CC) -c $(UNITTEST_DIR)/*.cpp
	$(CC) -o $(UNITTEST_FILE) *.o -lgtest -lpthread

