CC = g++
CFALGS = -c
TARGET = main
SFML = -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) main.o -o plot $(SFML)

$(TARGET).o: $(TARGET).cpp
	$(CC) $(CFALGS) main.cpp

clean:
	rm main.o plot
