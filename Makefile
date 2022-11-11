BUILD_DIR=build
SRC_DIR=src

EXECUTABLE_NAME=bonfire_nes

.PHONY: all
all: $(BUILD_DIR)/$(EXECUTABLE_NAME)

$(BUILD_DIR)/$(EXECUTABLE_NAME): $(BUILD_DIR)/main.o
	clang++ $(BUILD_DIR)/main.o -o $(BUILD_DIR)/$(EXECUTABLE_NAME)

$(BUILD_DIR)/main.o: main.cpp
	clang++ -c main.cpp -o $(BUILD_DIR)/main.o



.PHONY: run
run:
	$(BUILD_DIR)/$(EXECUTABLE_NAME)

.PHONY: install
install:
	mkdir -p $(BUILD_DIR)


.PHONY: clean 
clean:
	rm -r -f $(BUILD_DIR)/*
