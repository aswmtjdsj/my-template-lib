asmly:
	g++ -g -Wall -O2 --std=c++0x big_integer.cpp -S
base:
	g++ -g -Wall -O2 --std=c++0x big_integer.cpp -o big_integer
	./big_integer
	# g++ -g -Wall -O2 --std=c++0x matrix.cpp -o matrix 
	# ./matrix
comp:
	g++ -g -Wall -O2 --std=c++0x big_integer.cpp -o big_integer
	time -p ./big_integer < big.in > test.out
	time -p python big_test.py < big.in > big.out
prof:
	g++ -pg -g -Wall -O2 --std=c++0x big_integer.cpp -o big_integer
	time -p ./big_integer < big.in > test.out
	gprof big_integer gmon.out > prof.out