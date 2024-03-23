all: main_P1.out

run_P1: main_P1.cpp
	./main_P1.out

%.o: %.cpp
	g++ -c $<

%.out: %.o
	g++ $^ -o $@

clean:
	rm -f *.out *.o