
LESSONS_FILES=$(shell \ls *.cpp)
LESSONS_TARGETS=$(LESSONS_FILES:.cpp=)

CXXFLAGS := -O3

all: $(LESSONS_TARGETS)
	@echo "Done!"

%: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	@rm -f $(LESSONS_TARGETS)
	@echo "Done!"
