SRCFILES = $(shell find src/ -type f -name '*.cpp')
OBJFILES = $(subst src, bin, $(patsubst %.cpp, %.o, $(SRCFILES)))

TARGET=main.out

$(TARGET): main.cpp
$(TARGET): $(OBJFILES)
	g++ main.cpp -o $(TARGET) $(OBJFILES) -lglfw -lGL -lGLEW -lpthread -I ./include

bin/%.o: src/%.cpp include/%.hpp
	g++ -c $(subst bin, src, $<) -o $@ -lglfw -lGL -lGLEW -lpthread -I ./include 

#InitShader.o: InitShader.cpp
#	g++ InitShader.cpp -c -lGLEW

#App.o: App.cpp App.hpp util.hpp
#	g++ App.cpp -c

#util.o: util.hpp util.cpp
#	g++ util.cpp -c

#psys.o: psys.cpp psys.hpp
#	g++ psys.cpp -std=c++17 -c -lpthread
