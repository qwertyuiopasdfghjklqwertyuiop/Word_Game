CC = clang
CFLAGS = -lpthread -std=c++14 -lstdc++  -Wall -lm -pedantic
TARGETDIRECTORY = ../build/
TARGET = Word_Game

all: $(TARGET)
$(TARGET):
	$(CC) $(CFLAGS) *cpp -o $(TARGETDIRECTORY)$(TARGET)

clean:
	$(RM) $(TARGETDIRECTORY)$(TARGET)
