
SOURCES := lesson3.cpp

OBJS := $(SOURCES:.cpp=.o)

CXXFLAGS := -O3

TARGET := lesson3

all: $(TARGET)
	@echo "Done!"

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $^

%.cpp.o:
	@$(CXX) $(CXXFLAGS) -c $<

clean:
	@rm -f $(TARGET)
	@rm -f *.o
	@echo "Done!"
