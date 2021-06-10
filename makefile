
TARGET=main.out

$(TARGET): main.cpp App.hpp
$(TARGET): psys.o
	g++ main.cpp -lglfw -lGL -lGLEW -o $(TARGET) psys.o -lpthread

#InitShader.o: InitShader.cpp
#	g++ InitShader.cpp -c -lGLEW

psys.o: psys.cpp psys.hpp
	g++ psys.cpp -std=c++17 -c -lpthread
