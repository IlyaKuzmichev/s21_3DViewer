CC=gcc
BUILDFLAGS=-std=c11 -Wall -Wextra -Werror
CFLAGS=$(BUILDFLAGS) -c

CMAKE_DIR=s21_3DViewer_v1.0
BUILD_DIR=build
LIB_NAME=$(CMAKE_DIR).a
ARCH_NAME=Archive_$(CMAKE_DIR)

TESTFLAGS := -lcheck -lpthread -pthread

TESTFLAGS +=
ifeq ($(shell uname -s),Linux)
	TESTFLAGS += -lm -lrt -lsubunit
endif

GCOVFLAGS = -fprofile-arcs -ftest-coverage

TESTS_SOURCES=$(addprefix tests/, test.c)
SOURCES=
OBJECTS=$(SOURCES:.c=.o)

FILES_TO_CHECK=$(shell find . -name '*.c' && find . -name '*.h' )
MAINFILE=${MAIN}

.PHONY: test rebuild clean stylecheck fmt

all: clean install open_viewer

%.o: %.c
	$(CC) $(CFLAGS) -g $^ -o $@

install: clean $(LIB_NAME)
	@mkdir $(BUILD_DIR)
	@mv $(LIB_NAME) $(CMAKE_DIR)/lib$(LIB_NAME)
	@cd $(BUILD_DIR) && cmake ../$(CMAKE_DIR)
	make -C $(BUILD_DIR)

open_calc:
	@./$(shell find build -name "$(CMAKE_DIR)")

uninstall:
	@rm -rf build

dist: clean
	cd ../ && tar cvzf $(ARCH_NAME).tgz src/

dist_remove:
	@rm -rf ../$(ARCH_NAME).tgz

dvi:
	doxygen doxconf
	@open documentation/html/index.html

dvi_remove:
	@rm -rf documentation

$(LIB_NAME): $(OBJECTS)
	ar rcs $(LIB_NAME) $^
	ranlib $(LIB_NAME)

gcov_report: test
	lcov -t test.out -o test.info -c -d . --no-external
	genhtml -o report test.info
	@open report/index.html

gcovr_report: test
	mkdir gcovr/
	gcovr --html-details gcovr/report.details.html
	@open gcovr/report.details.html

report_nohtml: test
	gcov *gcno > coverage.txt
	@open coverage.txt

test: clean test_$(LIB_NAME)
	$(CC) -g $(BUILDFLAGS) $(TESTS_SOURCES) $(GCOVFLAGS) $(TESTFLAGS) -L. $(LIB_NAME) -o test.out
	./test.out

test_$(LIB_NAME): all_functions
	ar rcs $(LIB_NAME) *.o
	ranlib $(LIB_NAME)

all_functions: $(SOURCES)
	$(CC) -g $(CFLAGS) $^ $(GCOVFLAGS)

rebuild: clean all

main: clean $(LIB_NAME)
	@[[ ! -z "$(MAINFILE)" ]] || (echo 'define MAIN env variable!' && exit 1)
	$(CC) -o main.out -g $(BUILDFLAGS) $(MAINFILE).c $(LIB_NAME)

clean: 
	@rm -rf  $(OBJECTS) build/ $(CMAKE_DIR)/lib$(LIB_NAME) 
	@rm -rf report/ gcovr/ $(LIB_NAME) *.gcda *.gcno *.gcov *.out *.info *.o coverage.txt *.dSYM

.clang-format:
	@cp ../materials/linters/.clang-format .
	
stylecheck: .clang-format
	@clang-format -n $(FILES_TO_CHECK)
	
fmt: .clang-format
	@clang-format -i $(FILES_TO_CHECK)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES_TO_CHECK)
