EXEC=main
OBJECT=main.o 
SRC=gradientMethod.cpp

$(EXEC): $(OBJECT)
	g++ $(OBJECT) -o $(EXEC)

$(OBJECT): $(SRC)
	g++ $(SRC) -o $(OBJECT) -c

clear:
	rm *.o $(EXEC)