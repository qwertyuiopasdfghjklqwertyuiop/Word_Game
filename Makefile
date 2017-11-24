CC = clang
INCLUDE = ./src/Includes/
SOURCE = ./src/*cpp
CFLAGS = -lpthread -std=c++14 -lstdc++ -Wall -lm -pedantic -I $(INCLUDE)
TARGETDIRECTORY = ./build/
TARGET = Word_Game


all: $(TARGETDIRECTORY)$(TARGET)

debug: CFLAGS += -g
debug: $(TARGETDIRECTORY)$(TARGET)

$(TARGETDIRECTORY)$(TARGET):
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGETDIRECTORY)$(TARGET)

clean:
	$(RM) $(TARGETDIRECTORY)$(TARGET)
