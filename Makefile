OUT = driver
CXX = clang++
LIBSDL = -L/usr/local/lib -lSDL2
INCSDL = -I/usr/local/include/SDL2

CXXFLAGS = ${INCSDL}
LDFLAGS = ${LIBSDL}

OBJECTS = driver.o

all: $(OUT)
	ctags -R *.h *.cpp

$(OUT): $(OBJECTS)
	$(CXX) ${CXXFLAGS} -o $@ $^ ${LDFLAGS}
