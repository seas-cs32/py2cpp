all: main clean-deps

CXX = clang++
override CXXFLAGS += -g -Wno-everything

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.cpp' -print | sed -e 's/ /\\ /g')
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

%.d: %.cpp
	@set -e; rm -f "$@"; \
	$(CXX) -MM $(CXXFLAGS) "$<" > "$@.$$$$"; \
	sed 's,\([^:]*\)\.o[ :]*,\1.o \1.d : ,g' < "$@.$$$$" > "$@"; \
	rm -f "$@.$$$$"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"

include $(DEPS)

main: main.o
	$(CXX) $(CXXFLAGS) main.o -o "$@"

main-debug: main.o
	$(CXX) $(CXXFLAGS) -O0 main.o -o "$@"

mycode: mycode.o
	$(CXX) $(CXXFLAGS) mycode.o -o "$@"

clean:
	rm -f $(OBJS) $(DEPS) main main-debug mycode

clean-deps:
	rm -f $(DEPS)