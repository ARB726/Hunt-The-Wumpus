# This is a very fancy makefile. Don't touch it. It works like magic, even if
# you add more .cpp files and .hpp files to this project. It also
# auto-generates dependency lists as a side effect of compilation, so you'll
# basically never need to run `make clean`. The `clean` target is still there
# in case you want to use it, though.

CXX = g++ -g
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d
EXE = wumpus

SRC_DIR = .
SRC = $(shell find $(SRC_DIR) -regex ".*\.cpp")

OBJ_DIR = .obj
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

DEP_DIR = .deps
DEP = $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRC))

$(EXE): $(OBJ)
	$(CXX) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEP_DIR)/%.d $(OBJ_DIR)/%.o.sentinel $(DEP_DIR)/%.d.sentinel
	$(CXX) $(DEP_FLAGS) -I . -c -o $@ $<

$(OBJ_DIR)/%.sentinel:
	@mkdir -p ${@D}
	@touch $@

$(DEP_DIR)/%.sentinel:
	@mkdir -p ${@D}
	@touch $@

$(DEP):

include $(wildcard $(DEP))

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR) $(EXE)

.PHONY: clean
