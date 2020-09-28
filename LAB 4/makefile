all:
	g++ -std=c++11 test_main.cpp
	g++ -std=c++11 myStack_corey33p.hpp
	g++ -std=c++11 myInfixPostfix.hpp
test:
	./a.out Instance_Files/instance1.txt output1.txt
	./a.out Instance_Files/instance2.txt output2.txt
	./a.out Instance_Files/instance3.txt output3.txt
	./a.out Instance_Files/instance4.txt output4.txt
	./a.out Instance_Files/instance5.txt output5.txt
	./a.out Instance_Files/instance6.txt output6.txt
	./a.out Instance_Files/instance7.txt output7.txt
	./a.out Instance_Files/instance8.txt output8.txt
	./a.out Instance_Files/instance9.txt output9.txt
	./a.out Instance_Files/instance10.txt output10.txt
	diff output1.txt Output_Files/output1.txt -w
	diff output2.txt Output_Files/output2.txt -w
	diff output3.txt Output_Files/output3.txt -w
	diff output4.txt Output_Files/output4.txt -w
	diff output5.txt Output_Files/output5.txt -w
	diff output6.txt Output_Files/output6.txt -w
	diff output7.txt Output_Files/output7.txt -w
	diff output8.txt Output_Files/output8.txt -w
	diff output9.txt Output_Files/output9.txt -w
	diff output10.txt Output_Files/output10.txt -w

clean:
	rm -rf *.o *~ L04 *.gch
