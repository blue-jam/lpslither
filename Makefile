CXX = g++
CXXFLAGS = -std=c++11
OBJS = lpslither visualizer

all: $(OBJS)

lpslither:
	$(CXX) $(CXXFLAGS) -o lpslither lpslither.cpp

visualizer:
	$(CXX) $(CXXFLAGS) -o visualizer visualizer.cpp

clean:
	$(RM) $(OBJS)
