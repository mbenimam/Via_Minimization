EXEC= VisuNetlist tests_elementaires test_echeancier test_arbre test_graph test_crossings

CFLAGS= -Wall -g
SRC_PATH = src
SRC_EXT = c
BUILD_PATH = build

BIN_PATH = $(BUILD_PATH)/bin


SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
EXEC_BIN = $(EXEC:%=$(BIN_PATH)/%)

NETLIB = build/netlib/netlib.a

DEPS = $(OBJECTS:.o=.d)

INCLUDES = -I src/netlib/include



all: dirs netlib $(EXEC_BIN)


.PHONY: check dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

.PHONY: clean
check: all
	./build/bin/test_crossings

clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)


# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CC) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

$(BIN_PATH)/%: $(BUILD_PATH)/%.o 
	@echo "Linking: $@, $<"
	$(CC) $^ $(NETLIB) -o $@

netlib:
	@echo "Entered netlib"
	$(MAKE) -C $(SRC_PATH)/netlib	

