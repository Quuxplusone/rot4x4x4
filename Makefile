CXXFLAGS = -std=c++14 -O3 -W -Wall -Werror -pedantic
CXXFLAGS += ${EXTRA_CXXFLAGS}

test_rotations: test_rotations.cc rotations.h
	$(CXX) $(CXXFLAGS) test_rotations.cc -o $@

rotations.h: generate_rotations.py
	./generate_rotations.py > rotations.h
