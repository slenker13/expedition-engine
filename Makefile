CXX		  := g++
CXX_FLAGS := -Wall

BUILD		:= build
SRC		:= src
INCLUDE	:= include
LDFLAGS	:= 

LIBRARIES	:= -lSDL2 -lSDL2_image
EXECUTABLE	:= expedition


all: $(BUILD)/$(EXECUTABLE)

run: clean all
	clear
	./$(BUILD)/$(EXECUTABLE)

$(BUILD)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $(LDFLAGS) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BUILD)/*