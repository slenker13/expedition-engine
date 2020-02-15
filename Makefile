CXX		  := g++
CXX_FLAGS := -Wall

BUILD	:= build
OBJ		:= $(BUILD)/obj
SRC		:= src
INCLUDE	:= include
SRC_FILES	:= $(wildcard $(SRC)/*.cpp)
OBJ_FILES	:= $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRC_FILES))

LIBRARY	:= libexpedition.a


$(BUILD)/$(LIBRARY): $(OBJ_FILES)
	ar rcs $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c -o $@ $<

$(OBJ):
	mkdir -p $@

.PHONY: clean
clean:
	-rm -rf $(OBJ)
	-rm $(BUILD)/*