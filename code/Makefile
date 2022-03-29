.default: all

all: main

clean:
	rm -f main *.o actual.out

main: main.o Node.o NodeList.o PathPlanner.o
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -c $^