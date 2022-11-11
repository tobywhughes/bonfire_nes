BUILD_DIR=build
SRC_DIR=src

EXECUTABLE_NAME=bonfire_nes

.PHONY: all
all: $(BUILD_DIR)/$(EXECUTABLE_NAME).exe

$(BUILD_DIR)/$(EXECUTABLE_NAME).exe: $(BUILD_DIR)/main.o
	clang++ $(BUILD_DIR)/main.o -o $(BUILD_DIR)/$(EXECUTABLE_NAME).exe

$(BUILD_DIR)/main.o: main.cpp
	clang++ -c main.cpp -o $(BUILD_DIR)/main.o



.PHONY: run
run:
	$(BUILD_DIR)/$(EXECUTABLE_NAME).exe

.PHONY: install
install:
	mkdir $(BUILD_DIR)


.PHONY: clean 
clean:
	del $(BUILD_DIR)\* /s /q
