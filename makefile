INCDIRS:=/Users/dmielke/Documents/oopl/trees/googletest/googletest/include
LIBDIRS:=/Users/dmielke/Documents/oopl/trees/googletest/googletest/make

FILES :=                                \
    .travis.yml                         \
    dijkstra-tests/EID-RunDreamoon.in   \
    dijkstra-tests/EID-RunDreamoon.out  \
    dijkstra-tests/EID-TestDreamoon.c++ \
    dijkstra-tests/EID-TestDreamoon.out \
    Dreamoon.c++                        \
    Dreamoon.h                          \
    Dreamoon.log                        \
    html                                \
    RunDreamoon.c++                     \
    RunDreamoon.in                      \
    RunDreamoon.out                     \
    TestDreamoon.c++                    \
    TestDreamoon.out                    \
    DreamoonBundle.c++

# Call gcc and gcov differently on Darwin
ifeq ($(shell uname), Darwin)
  CXX      := g++
  GCOV     := gcov
  VALGRIND := echo Valgrind not available on Darwin
else
  CXX      := g++-4.8
  GCOV     := gcov-4.8
  VALGRIND := valgrind
endif

CXXFLAGS   := -pedantic -std=c++11 -Wall -I$(INCDIRS)
LDFLAGS    := -lgtest -lgtest_main -pthread -L$(LIBDIRS)
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunDreamoon
	rm -f RunDreamoon.tmp
	rm -f TestDreamoon
	rm -f TestDreamoon.tmp
	rm -f DreamoonBundle

config:
	git config -l

bundle:
	cat Dreamoon.h Dreamoon.c++ RunDreamoon.c++ | sed -e "s/#include \"Dreamoon.h\"//g" > DreamoonBundle.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) DreamoonBundle.c++ -o DreamoonBundle

scrub:
	make  clean
	rm -f  Dreamoon.log
	rm -rf dijkstra-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunDreamoon.tmp TestDreamoon.tmp

RunDreamoon: Dreamoon.h Dreamoon.c++ RunDreamoon.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Dreamoon.c++ RunDreamoon.c++ -o RunDreamoon

RunDreamoon.tmp: RunDreamoon
	./RunDreamoon < RunDreamoon.in > RunDreamoon.tmp
	diff RunDreamoon.tmp RunDreamoon.out

TestDreamoon: Dreamoon.h Dreamoon.c++ TestDreamoon.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Dreamoon.c++ TestDreamoon.c++ -o TestDreamoon $(LDFLAGS)

TestDreamoon.tmp: TestDreamoon
	./TestDreamoon                                                     >  TestDreamoon.tmp 2>&1
	$(VALGRIND) ./TestDreamoon                                         >> TestDreamoon.tmp
	$(GCOV) -b Dreamoon.c++     | grep -A 5 "File 'Dreamoon.c++'"     >> TestDreamoon.tmp
	$(GCOV) -b TestDreamoon.c++ | grep -A 5 "File 'TestDreamoon.c++'" >> TestDreamoon.tmp
	cat TestDreamoon.tmp
