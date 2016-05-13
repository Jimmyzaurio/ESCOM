LIBS = complejo.o symbol.o

Complejo: y.tab.c $(LIBS)
	g++ y.tab.c $(LIBS) -std=c++0x

y.tab.c: complejo.y
	byacc complejo.y

$(LIBS): complejo.cpp symbol.cpp
	g++ complejo.cpp symbol.cpp -c 

clean:
	rm y.tab.c $(LIBS)
