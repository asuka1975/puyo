puyo: main.o Field.o FieldControl.o
        g++ -o puyo main.o Field.o FieldControl.o -lncurses

main.o: main.cpp
        g++ -c main.cpp

Field.o: Field.cpp
        g++ -c Field.cpp

FieldControl.o: FieldControl.cpp
        g++ -c FieldControl.cpp