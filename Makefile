CC=gcc
P = -pedantic
FLAGS=-Wall -Werror -Wextra -std=c11 $(P)
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
GCOV_REPORT_DIR = gcov_report
LIBS=libtetris.a -lncurses

SOURCES=$(wildcard gui/cli/*.c) tetris.c
OBJECTS = $(addprefix out/, $(notdir $(SOURCES:%.c=%.o)))

SOURCES_LIBRARY = $(wildcard brick_game/tetris/*.c) 
OBJECTS_LIBRARY=$(addprefix out/, $(notdir $(SOURCES_LIBRARY:%.c=%.o)))

TEST_SRC = $(wildcard tests/*.c) $(wildcard matrix_functions/*.c)
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

#all: s21_matrix.a test gcov_report
install: libtetris.a $(OBJECTS)
	@touch data.txt
	$(CC) $(FLAGS) $(OBJECTS) $(LIBS) -o tetris.out
	@rm -f out/*.o

uninstall:
	@rm -f data.txt tetris.out

dvi:
	@mkdir docs
	@doxygen -g Doxyfile
	@echo "PROJECT_NAME = \"Tetris\"" > Doxyfile
	@echo "OUTPUT_DIRECTORY = docs" >> Doxyfile
	@echo "GENERATE_HTML = YES" >> Doxyfile
	@echo "GENERATE_LATEX = NO" >> Doxyfile
	@echo "INPUT = tetris.c tetris.h ./gui/cli" >> Doxyfile
	@doxygen Doxyfile 

libtetris.a: $(OBJECTS_LIBRARY)
	@ar rcs $@ $^

# libtest_tetris.a: $(TEST_OBJ)
# 	ar rcs $@ $^

out/%.o: brick_game/tetris/%.c
	$(CC) $(FLAGS) -c $< -o $@

out/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

out/%.o: gui/cli/%.c
	$(CC) $(FLAGS) -c $< -o $@	

clean:
	@rm -f *.a out/*.o *.out Doxyfile
	@rm -r docs

# %.o.test: %.c
# 	$(CC) $(FLAGS) $(GCOV_FLAGS) -c $< -o $@

# test: clean test_s21_matrix.a
# 	$(CC) $(FLAGS) $(GCOV_FLAGS) $(TEST_OBJ) test_s21_matrix.a -o $@ $(LFLAGS)
# 	./$@

# gcov_report: test
# 	lcov --capture --directory . --output-file coverage.info --rc lcov_branch_coverage=1
# 	genhtml coverage.info --output-directory $(GCOV_REPORT_DIR) --branch-coverage

# 	$(OPEN) $(GCOV_REPORT_DIR)/index.html


# clean:
# 	rm -f *.o *.a test *.gcda *.gcno *.gcov coverage.info matrix_functions/*.gcno matrix_functions/*.gcda tests/*.gcno tests/*.gcda
# 	rm -rf $(GCOV_REPORT_DIR) matrix_functions/*.o tests/*.o
# 	rm -rf $(GCOV_REPORT_DIR) matrix_functions/*.o.test tests/*.o.test

clang:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i tests/* matrix_functions/* *.h
	rm -rf .clang-format
