CC = gcc
CFLAGS = -g -O3 -mtune=znver2 -march=znver2 -funroll-loops 

TARGET = oplib
OBJS = oplib.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS)
