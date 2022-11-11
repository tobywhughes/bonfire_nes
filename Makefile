EXECUTABLE_NAME := bonfire_nes

BUILD_DIR := build
SRC_DIR := src

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIR))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

.PHONY: all
all: $(BUILD_DIR)/$(EXECUTABLE_NAME)

$(BUILD_DIR)/$(EXECUTABLE_NAME): $(OBJS)
	clang++ $(OBJS) -o $(BUILD_DIR)/$(EXECUTABLE_NAME)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	clang++ $(CPPFLAGS) -c $< -o $@



.PHONY: run
run:
	$(BUILD_DIR)/$(EXECUTABLE_NAME)


.PHONY: clean 
clean:
	rm -r -f $(BUILD_DIR)/*


-include $(DEPS)