CC      = g++
LIBS    = -lncurses
OBJS    = main.o Field.o FieldControl.o PuyoArrayActive.o PuyoArrayStack.o PuyoGenerator.o
TARGET  = puyo

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f *.o *~

.c.o:
	$(CC) -c $*.c