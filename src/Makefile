PROJECT_NAME=BrickGame
CC=gcc
CPP=g++
GCOV=--coverage
NCURSES=-lncurses
CFLAGS=-Wall -Werror -Wextra
STANDART=-std=c++17
ADD_LIB=-lm
GTEST=-lgtest

FRONTEND_CLI=gui/cli
FRONTEND_DESKTOP=gui/desktop
BACKEND_TETRIS=brick_game/tetris
BACKEND_SNAKE=brick_game/snake
MODEL_SNAKE=$(BACKEND_SNAKE)/model
CONTROLLER_SNAKE=$(BACKEND_SNAKE)/controller
TEST_DIR=unit_tests

OS=$(shell uname -s)

ifeq ($(OS), Linux)
	LEAK_CHECK=valgrind --tool=memcheck --leak-check=yes
	OPEN_CMD=xdg-open
else ifeq ($(OS), Darwin)
	LEAK_CHECK=leaks -atExit --
	OPEN_CMD=open
endif

all: clean install

install: clean cli desktop

cli: libtetris.a libsnake.a
	mkdir build
	$(CC) $(CFLAGS) -c $(FRONTEND_CLI)/*.c $(NCURSES)
	$(CPP) $(STANDART) $(CFLAGS) -c $(FRONTEND_CLI)/*.cpp $(NCURSES)
	cd build && $(CPP) $(STANDART) $(CFLAGS) -o $(PROJECT_NAME)_cli ../*.o $(NCURSES) -L./.. -lsnake -ltetris
	rm -rf *.o *.a

desktop:
	rm -rf desk
	mkdir desk
	cd desk && qmake ../gui/desktop
	cd desk && make
	mv desk/BrickGame_desktop build
	rm -rf desk

libsnake.a:
	$(CPP) $(STANDART) $(CFLAGS) -c $(MODEL_SNAKE)/*.cpp $(CONTROLLER_SNAKE)/*.cpp
	ar rc libsnake.a *.o
	rm -rf *.o

libtetris.a:
	$(CC) $(CFLAGS) -c $(BACKEND_TETRIS)/*.c
	ar rc libtetris.a *.o
	rm -rf *.o

unistall:
	rm -rf build

dvi: clean
	cd dvi && latex description.tex
	cd dvi && rm -rf description.log description.aux
	cd dvi && dvipdf description.dvi

dist: install
	tar -cvzf $(PROJECT_NAME).tgz build
	rm -rf build

test: clean
	$(CPP) $(CFLAGS) $(STANDART) $(MODEL_SNAKE)/*.cpp $(CONTROLLER_SNAKE)/*.cpp $(TEST_DIR)/*.cpp -o snake_tests $(ADD_LIB) $(GTEST)
	./snake_tests

gcov_report: clean
	$(CPP) $(CFLAGS) $(STANDART) $(MODEL_SNAKE)/*.cpp $(CONTROLLER_SNAKE)/*.cpp $(TEST_DIR)/*.cpp -o snake_tests $(ADD_LIB) $(GTEST) $(GCOV)
	./snake_tests
	lcov -c -d . --no-external -o snake_gcov.info
	genhtml -o report snake_gcov.info
	chmod 777 report/*
	rm *.gcda *.gcno
	$(OPEN_CMD) ./report/index.html

leaks: clean 
	$(CPP) $(CFLAGS) $(STANDART) $(MODEL_SNAKE)/*.cpp $(CONTROLLER_SNAKE)/*.cpp $(TEST_DIR)/*.cpp -o snake_tests $(ADD_LIB) $(GTEST)
	$(LEAK_CHECK) ./snake_tests

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i \
	$(BACKEND_TETRIS)/*.c \
	$(BACKEND_TETRIS)/inc/*.h \
	$(BACKEND_SNAKE)/model/* \
	$(BACKEND_SNAKE)/controller/* \
	$(FRONTEND_CLI)/*.* \
	$(FRONTEND_DESKTOP)/*.cpp \
	$(FRONTEND_DESKTOP)/*.h \
	unit_tests/*.*
	rm -rf .clang-format

clean:
	@rm -rf \
	build \
	report \
	$(PROJECT_NAME).tgz \
	*.txt *.o *.a *.info \
	dvi/*.pdf \
	dvi/*.aux \
	dvi/*.log \
	dvi/*.dvi \
	snake_tests

# qt:
# 	/opt/Qt/Tools/QtCreator/bin/qtcreator