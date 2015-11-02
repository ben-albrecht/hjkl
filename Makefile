OUT = driver
CXX = clang++

LIB = -L/usr/local/lib
LIBSDL = -lSDL2
LIBIMG = -lSDL2_image

INCSDL = -I/usr/local/include/SDL2

CXXFLAGS = ${INCSDL}
LDFLAGS = ${LIB} ${LIBSDL} ${LIBIMG}

OBJECTS = driver.o

all: $(OUT)
	ctags -R *.h *.cpp

$(OUT): $(OBJECTS)
	$(CXX) ${CXXFLAGS} -o $@ $^ ${LDFLAGS}
