CXX			:= g++
CXXFLAGS	:= -std=c++14 -Wall -Wextra -Werror=vla

EXEC		:= sorcery
SRCS_DIR	:= ./src
BUILD_DIR	:= ./build
SRCS 		:= $(shell find $(SRCS_DIR) -name *.cpp)
OBJS		:= $(SRCS:$(SRCS_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

DIR_GUARD	= @mkdir -p $(@D)

$(EXEC): $(OBJS)
	$(DIR_GUARD)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(DIR_GUARD)
	$(CXX) $(CXXFLAGS) -c $< -MMD -o $@

-include $(DEPS)

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) $(EXEC)
