CC = gcc
TARGET = hw2
OBJECTS = hw2.c

$(TARGET) : $(OBJECTS)
	$(CC) -g -o $@ $(OBJECTS)

clean:
	rm $(OBJECTS) $(TARGET)