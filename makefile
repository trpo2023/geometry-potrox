APP_NAME = geometry_app 
LIB_STATIC = geometry
LIB_DIR = libgeometry
LIB_TEST_DIR = thirdparty

CFLAGS = -Wall -Werror
CPPFLAGS = -Isrc -MP -MMD

OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = test
TEST_NAME = maintest

TEST_TARGET = $(OBJ_DIR)/$(TEST_NAME)

APP_PATH = $(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_DIR)/$(LIB_STATIC).a

APP_SOURCES = $(shell find $(SRC_DIR)/$(LIB_STATIC) -name '*.c')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_DIR) -name '*.c')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)
$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	gcc $(CFLAGS) $(CPPFLAGS) $^ -o $@ -lm

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

	
test: $(TEST_TARGET)
	$(BIN_DIR)/$(TEST_NAME)

$(TEST_TARGET): $(OBJ_DIR)/$(TEST_DIR)/main.o $(OBJ_DIR)/$(TEST_DIR)/test.o
	gcc -I $(SRC_DIR)/libgeometry -I $(LIB_TEST_DIR) $^ $(LIB_PATH) -o $(BIN_DIR)/$(TEST_NAME) -lm

$(OBJ_DIR)/$(TEST_DIR)/main.o: $(TEST_DIR)/main.c
	gcc $(CFLAGS) $(CPPFLAGS) -I $(LIB_TEST_DIR) -c $< -o $@

$(OBJ_DIR)/$(TEST_DIR)/test.o: $(TEST_DIR)/test.c
	gcc $(CFLAGS) $(CPPFLAGS) -I $(SRC_DIR)/libgeometry -I $(LIB_TEST_DIR) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
