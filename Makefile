CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/ 

exec: bin/exec
tests: bin/tests

bin/exec: src/driver.cc includes/application.hpp includes/player.hpp includes/deck.hpp src/application.cc src/player.cc src/deck.cc
	${CXX} ${CXX_FLAGS} src/driver.cc src/application.cc src/player.cc src/deck.cc -o bin/exec

bin/tests: tests/tests.cc includes/application.hpp includes/player.hpp includes/deck.hpp src/application.cc src/player.cc src/deck.cc
	${CXX} ${CXX_FLAGS} tests/tests.cc src/application.cc src/player.cc src/deck.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*