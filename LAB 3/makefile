L03: test_main.o
	g++ -std=c++11 -g -Wall test_main.o -o a.out

test_main.o: test_main.cpp
	g++ -std=c++11 -g -Wall -c test_main.cpp myStack.hpp myQueue.hpp

clean:
	rm -rf *.o *~ L03 *.gch
