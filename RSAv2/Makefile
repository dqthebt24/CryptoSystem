# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=g++
EXE_FILE=rsa
IDIR =..
SRC_DIR=..
CFLAGS=-I$(IDIR)
ODIR=.
_OBJ = bigint.o algorithm.o RSAv2.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/rsa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(EXE_FILE)