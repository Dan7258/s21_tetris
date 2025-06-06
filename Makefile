CC=gcc
P = -pedantic
FLAGS=-Wall -Werror -Wextra -std=c11 $(P)
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
GCOV_REPORT_DIR = gcov_report
LIBS=libtetris.a -lncurses
LIBS_TEST= libtetris_test.a -lncurses
PROJECT_NAME=tetris
VERSION=1.2

GAMEDIR=game

INSTALL_PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

SOURCES=$(wildcard gui/cli/*.c) tetris.c
OBJECTS = $(addprefix out/, $(notdir $(SOURCES:%.c=%.o)))

SOURCES_LIBRARY = $(wildcard brick_game/tetris/*.c)
OBJECTS_LIBRARY=$(addprefix out/, $(notdir $(SOURCES_LIBRARY:%.c=%.o)))

TEST_SRC = $(wildcard tests/*.c) $(wildcard brick_game/tetris/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o.test)



ifeq ($(shell uname), Darwin)
	LFLAGS = -lcheck
else ifeq ($(shell uname), Linux)
	LFLAGS = -lcheck -pthread -lm -lsubunit
endif
ifeq ($(shell uname), Windows_NT)
	OPEN = start
else
	OPEN = open
endif

all: install play

install: tetris
	@mkdir -p $(GAMEDIR)
	@cp tetris $(GAMEDIR)/
	@rm -f *.a out/*.o tetris

uninstall:
	@rm -f $(GAMEDIR)/tetris $(GAMEDIR)/data.txt

dvi:
	@mkdir -p docs
	@doxygen -g Doxyfile
	@echo "PROJECT_NAME = \"Tetris\"" > Doxyfile
	@echo "OUTPUT_DIRECTORY = docs" >> Doxyfile
	@echo "GENERATE_HTML = YES" >> Doxyfile
	@echo "GENERATE_LATEX = NO" >> Doxyfile
	@echo "INPUT = tetris.c tetris.h ./gui/cli ./brick_game/tetris" >> Doxyfile
	@doxygen Doxyfile 

dist:
	tar czf $(PROJECT_NAME)-$(VERSION).tar.gz \
	tetris.c tetris.h \
	brick_game/ \
	gui/ \
	Makefile \

tetris: out libtetris.a $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(LIBS) -o $@
	@rm -f out/*.o
	
play:
	./$(GAMEDIR)/tetris

out:
	@mkdir -p out

libtetris.a: $(OBJECTS_LIBRARY)
	@ar rcs $@ $^

libtetris_test.a: $(TEST_OBJ)
	ar rcs $@ $^

out/%.o: brick_game/tetris/%.c
	$(CC) $(FLAGS) -c $< -o $@

out/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

out/%.o: gui/cli/%.c
	$(CC) $(FLAGS) -c $< -o $@	

clean:
	@rm -f *.a *.out Doxyfile data.txt tetris 
	@rm -rf out $(GAMEDIR) docs
	@rm -f *.o *.a test *.gcda *.gcno *.gcov coverage.info brick_game/tetris/*.gcno brick_game/tetris/*.gcda tests/*.gcno tests/*.gcda gui/cli/*.gcno gui/cli/*.gcda
	@rm -rf $(GCOV_REPORT_DIR) brick_game/tetris/*.o.test gui/cli/*.o.test tests/*.o.test *.o.test
	@test -d docs && rm -r docs || true

%.o.test: %.c
	$(CC) $(FLAGS) $(GCOV_FLAGS) -c $< -o $@

test: clean libtetris_test.a
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(TEST_OBJ) $(LIBS_TEST) -o $@ $(LFLAGS)
	./$@

gcov_report: clean test
	lcov --capture --directory . --output-file coverage.info --rc lcov_branch_coverage=1
	genhtml coverage.info --output-directory $(GCOV_REPORT_DIR) --branch-coverage

	$(OPEN) $(GCOV_REPORT_DIR)/index.html

clang:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i tests/* brick_game/tetris/* *.h *.c gui/cli/*
	rm -rf .clang-format
