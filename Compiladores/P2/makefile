LIBS = complejo.o

Complejo: y.tab.c $(LIBS)
	g++ y.tab.c $(LIBS) -lm -w -std=c++0x -o Complex

y.tab.c: complejo.y
	byacc complejo.y

$(LIBS): complejo.cpp
	g++ complejo.cpp -c

clean:
	rm Complex $(LIBS)