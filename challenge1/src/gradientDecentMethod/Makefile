EXEC=main
OBJECT=main.o 
SRC=main.cpp
CXX=g++
CXXFLAGS=-std=c++20

$(EXEC): $(OBJECT)
	$(CXX) $(CXXFLAGS) $(OBJECT) -o $(EXEC)

$(OBJECT): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJECT)

clean:
	rm -f *.o $(EXEC)
