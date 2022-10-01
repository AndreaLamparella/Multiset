main: main.o element_not_found.o
	g++ -std=c++0x  -o main main.o element_not_found.o

main.o: main.cpp multiset.h element_not_found.h
	g++ -c main.cpp element_not_found.cpp

	
		
.PHONY: clean

clean:
	rm -f *.exe *.o main