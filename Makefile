#-----------------------------------#
# Makefile: Snake Game				#
#-----------------------------------#

CPP := g++ 
CPP_FG := -Wall -Werror

APP_PATH := .
INC_PATH := $(APP_PATH)/inc
SRC_PATH := $(APP_PATH)/src
BUILD_PATH := $(APP_PATH)/build
TEST_PATH := $(APP_PATH)/test

CXX_FLAGS := -std=c++11

# Target OS and raylib specific dependecies
ifeq ($(shell uname -s), Linux)
	TARGET_OS := linux
	RAYLIB := # For linux
	LIB_PATH := $(APP_PATH)/lib/linux
	BIN := SnakeGame
	MKDIR_CMD = mkdir -p
	RM_CMD    = rm -rf
	CHECK_DIR_CMD = test -d $(BUILD_PATH) && echo 1
else ifeq ($(shell uname -s), Darwin)
	TARGET_OS := macos
	RAYLIB := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib
	LIB_PATH := $(APP_PATH)/lib/macos
	BIN := SnakeGame
	MKDIR_CMD = mkdir -p
	RM_CMD    = rm -rf
	CHECK_DIR_CMD = test -d $(BUILD_PATH) && echo 1
else ifeq ($(shell uname -s), Windows_NT)
	TARGET_OS := windows
	RAYLIB := -lraylib -lopengl32 -lgdi32 -lwinmm
	LIB_PATH := $(APP_PATH)/lib/macos
	BIN := SnakeGame.exe
	MKDIR_CMD = mkdir
	RM_CMD    = rd /s /q
	CHECK_DIR_CMD = if exist $(BUILD_PATH) echo 1
endif

# raylib libraries
LIBS := $(RAYLIB) -lm

.PHONY: all all-before all-after bdir bin src

all-before:
	@echo "[INFO] Compile: start"
	@echo "[INFO] Target OS: $(TARGET_OS)"
	@echo "[INFO] Build directory configurations.."
	@$(MAKE) bdir

all-after:
	@echo "[INFO] Compile: end"

all: all-before bin all-after

bin: src
	$(CPP) $(BUILD_PATH)/*.o -o $(BUILD_PATH)/$(BIN) $(LIBS) -L$(LIB_PATH)
	@echo "==========================================="
	@echo "[INFO] BUILD: $(BUILD_PATH)/$(BIN)"
	@echo "==========================================="

src:
	@echo "[INFO] Src compiling..."
	$(CPP) $(CXX_FLAGS) -c $(SRC_PATH)/Food.cpp -o $(BUILD_PATH)/Food.o -I$(INC_PATH)
	$(CPP) $(CXX_FLAGS) -c $(SRC_PATH)/Snake.cpp -o $(BUILD_PATH)/Snake.o -I$(INC_PATH)
	$(CPP) $(CXX_FLAGS) -c $(SRC_PATH)/GamePanel.cpp -o $(BUILD_PATH)/GamePanel.o -I$(INC_PATH)
	$(CPP) $(CXX_FLAGS) -c $(SRC_PATH)/main.cpp -o $(BUILD_PATH)/Main.o -I$(INC_PATH)

bdir:
	@if [ $(shell $(CHECK_DIR_CMD)) = "1" ]; then \
		echo "[INFO] Build directory exist"; \
	else \
		echo "[INFO] Build directory does not exist. Creating it..."; \
		$(MKDIR_CMD) "$(BUILD_PATH)"; \
	fi

clean:
	@echo "[INFO] Cleaning previous build..."
	@$(RM_CMD) "$(BUILD_PATH)"
	@$(MAKE) all

