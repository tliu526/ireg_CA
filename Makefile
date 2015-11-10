all: first ;

first: first.cpp
	g++ -Wall -o first first.cpp 

clean:
	rm -f *.exe