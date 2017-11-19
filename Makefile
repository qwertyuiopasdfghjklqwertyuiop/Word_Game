CC = clang
CFLAGS = -lpthread -std=c++14 -lstdc++  -Wall -lm -pedantic
TARGETDIRECTORY = ./build/
TARGET = Word_Game

build: $(TARGETDIRECTORY)$(TARGET)
$(TARGETDIRECTORY)$(TARGET):
	$(CC) $(CFLAGS) ./src/*cpp -o $(TARGETDIRECTORY)$(TARGET)

clean:
	$(RM) $(TARGETDIRECTORY)$(TARGET)
