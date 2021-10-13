SRCFILES = $(shell find src/ -type f -name '*.cpp')
OBJFILES = $(subst src, bin, $(patsubst %.cpp, %.o, $(SRCFILES)))

IMGUI_DIR = ./imgui
SOURCES = $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat -std=c++11
CXX = g++
IMGUIOBJS = $(shell find bin/imgui/ -type f -name '*.o')

TARGET=main.out

$(TARGET): main.cpp
$(TARGET): $(OBJFILES) 
	$(CXX) main.cpp -o $(TARGET) $(OBJFILES) $(IMGUIOBJS) -lglfw -lGL -lGLEW -lpthread -I ./include -I $(IMGUI_DIR) -I $(IMGUI_DIR)/backends

imgui: $(OBJS)
	mv *.o bin/imgui/

%.o:$(IMGUI_DIR)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/%.o: src/%.cpp include/%.hpp
	$(CXX) -c $(subst bin, src, $<) -o $@ -lglfw -lGL -lGLEW -lpthread -I ./include -I ./imgui -I imgui/backends

install:
	git submodule init
	git submodule update
	mkdir -p bin/imgui/
	make imgui

clean:
	rm $(OBJFILES)
	rm $(TARGET)
	rm -rf bin/

.PHONY: clean install
