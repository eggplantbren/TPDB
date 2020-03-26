CXX = g++
FLAGS = -std=c++17
INCLUDE = -I . -I$(DNEST4_PATH)
OPTIM = -O2 -g
WARN = -Wall -Wextra -pedantic
ALL = $(FLAGS) $(INCLUDE) $(OPTIM) $(WARN)

default:
	$(CXX) $(ALL) -c TPDB/Example.hpp
	$(CXX) $(ALL) -c TPDB/Sampler.hpp
	$(CXX) $(ALL) -c main.cpp
	$(CXX) -L$(DNEST4_PATH)/DNest4/code -o main main.o -ldnest4 -lsqlite3
	rm -f main.o TPDB/*.gch
