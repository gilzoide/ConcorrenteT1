objs = main.o matriz.o resolvedor.o
CXXFLAGS = -Wall -g -O3 -std=c++11
LINKS = -lpthread
CXX = g++

all : $(objs)
	$(CXX) -o $(BUILD)/$(exe) $(foreach f, $(objs), $(BUILD)/$f) $(CXXFLAGS) $(LINKS)

%.o : %.cpp
	$(CXX) -o $(BUILD)/$@ -c $< $(CXXFLAGS)

clean :
	$(RM) *~ *.o $(exe)
