CC = gcc
CFLAGS = -lm

TARGET = pj14

SRC = pj14.c

all: $(TARGET)

${TARGET}: ${SRC}
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean: 
	rm -f $(TARGET)