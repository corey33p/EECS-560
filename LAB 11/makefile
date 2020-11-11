L11: test_main.o
	g++ -std=c++11 -g -Wall test_main.o -o a.out

test_main.o: test_main.cpp
	# g++ -std=c++11 -g -Wall -c test_main.cpp myGraph.hpp
	g++ -std=c++11 -g -Wall -c test_main.cpp myGraph_corey33p.hpp

clean:
	rm -rf *.o *~ L11 *.gch

test:
	# ./a.out Instance_Files/instance155.txt > output155.txt
	# valgrind ./a.out Instance_Files/instance155.txt
	# ./a.out Instance_Files/instance155.txt
	# ./a.out Instance_Files/instance1.txt
	# ./a.out dataout.txt > outputx1.txt
	# ./a.out dataout.txt > outputy1.txt 0 1
	# ./a.out dataout.txt > outputz1.txt 1 0
	# diff outputzout.txt outputyout.txt -w -s
	# diff outputx1.txt outputz1.txt -w -s
	# diff outputy1.txt outputz1.txt -w -s
	# valgrind --leak-check=full ./a.out Instance_Files/instance1.txt
	# valgrind ./a.out Instance_Files/instance1.txt > output1.txt
	# valgrind ./a.out Instance_Files/instance3.txt > output3.txt
	# time ./a.out Instance_Files/instance4.txt
	# valgrind ./a.out Instance_Files/instance5.txt output5.txt
	# valgrind ./a.out Instance_Files/instance7.txt > output7.txt
	# valgrind ./a.out Instance_Files/instance8.txt > output8.txt
	time ./a.out Instance_Files/instance1.txt > output1.txt
	time ./a.out Instance_Files/instance2.txt > output2.txt
	# time ./a.out Instance_Files/instance3.txt > output3.txt
	# time ./a.out Instance_Files/instance4.txt > output4.txt
	# time ./a.out Instance_Files/instance5.txt > output5.txt
	# time ./a.out Instance_Files/instance6.txt > output6.txt
	# time ./a.out Instance_Files/instance7.txt > output7.txt
	# time ./a.out Instance_Files/instance8.txt > output8.txt
	# time ./a.out Instance_Files/instance9.txt > output9.txt
	# time ./a.out Instance_Files/instance10.txt > output10.txt
	diff output1.txt Output_Files/output1.txt -w -s
	diff output2.txt Output_Files/output2.txt -w -s
	# diff output3.txt Output_Files/output3.txt -w -s
	# diff output4.txt Output_Files/output4.txt -w -s
	# diff output5.txt Output_Files/output5.txt -w -s
	# diff output6.txt Output_Files/output6.txt -w -s
	# diff output7.txt Output_Files/output7.txt -w -s
	# diff output8.txt Output_Files/output8.txt -w -s
	# diff output9.txt Output_Files/output9.txt -w -s
	# diff output10.txt Output_Files/output10.txt -w -s
	# diff outputz.txt outputy.txt -w -s