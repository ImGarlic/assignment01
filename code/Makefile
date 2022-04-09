.default: all

all: assign1

clean:
	rm -f assign1 *.o actual.out

assign1: main.o Node.o NodeList.o PathPlanner.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^