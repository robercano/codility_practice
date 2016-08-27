
CXXFLAGS := -O3
TARGETS := OddOccurrencesInArray

all: $(TARGETS)
	@echo "Done!"

OddOccurrencesInArray: % : %.o
	@$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	@rm -f $(TARGETS)
	@rm -f *.o
	@echo "Done!"
