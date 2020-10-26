

all:  bridges

bridges:		parser.o sojourner.o bridges.cpp Sojourners.h
	c++ -std=c++17   bridges.cpp parser.o sojourner.o -o bridges 

parser.o:	parser.cpp 
	c++  -c -std=c++17 parser.cpp -o $@
     
sojourner.o:	sojourner.cpp Sojourners.h
	c++ -c -std=c++17 sojourner.cpp -o $@

clean:
	$(RM) sojourner.o
	$(RM) parser.o
	$(RM) bridges


