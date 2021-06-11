SRCFILES = $(shell find src/ -type f -name '*.cpp')
OBJFILES = $(subst src, bin, $(patsubst %.cpp, %.o, $(SRCFILES)))

IMGUI_DIR = ./imgui
SOURCES = $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
IMGUIOBJS = $(shell find bin/imgui/ -type f -name '*.o')
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends `sdl2-config --cflags --libs`
CXXFLAGS += -g -Wall -Wformat -lSDL2main -lSDL2 
CXX = g++

TARGET=main.out

$(TARGET): main.cpp
$(TARGET): $(OBJFILES) #$(OBJS)
	g++ main.cpp -o $(TARGET) $(OBJFILES) $(IMGUIOBJS) -lglfw -lGL -lGLEW -lpthread -I ./include -I $(IMGUI_DIR) -I $(IMGUI_DIR)/backends

%.o:$(IMGUI_DIR)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/%.o: src/%.cpp include/%.hpp
	g++ -c $(subst bin, src, $<) -o $@ -lglfw -lGL -lGLEW -lpthread -I ./include -I ./imgui -I imgui/backends


clean:
	rm $(OBJFILES)
	rm $(TARGET)

.PHONY: clean
