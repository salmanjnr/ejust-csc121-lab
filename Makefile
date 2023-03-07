CXX = g++

all: build
build:
	"mkdir" -p "bin"
	$(CXX) -Wall mem.cpp -o bin/mem
grade:
	"mkdir" -p "bin"
	$(CXX) -D GRADING -Wall grade.cpp mem.cpp grade_util.cpp -o bin/grade
	bin/grade
run: build 
	bin/mem

.PHONY: clean
clean: rm *.o *.exe
