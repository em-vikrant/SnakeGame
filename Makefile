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
uname = $(shell uname)

ifeq ($(uname), Linux)
	TARGET_OS := linux
	RAYLIB := # For linux
	LIB_PATH := $(APP_PATH)/lib/linux
	BIN := SnakeGame
endif

ifeq ($(uname), Darwin)
	TARGET_OS := macos
	RAYLIB := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib
	LIB_PATH := $(APP_PATH)/lib/macos
	BIN := SnakeGame
endif

ifeq ($(uname), Windows_NT)
	TARGET_OS := windows
	RAYLIB := -lraylib -lopengl32 -lgdi32 -lwinmm
	LIB_PATH := $(APP_PATH)/lib/macos
	BIN := SnakeGame.exe
endif

# raylib libraries
LIBS := $(RAYLIB) -lm

.PHONY: all all-before all-after bin src

all-before:
	@echo "[INFO] Compile: start"
	@echo "Target OS: $(TARGET_OS)"

all-after:
	@echo "[INFO] Compile: end"

all: all-before bin all-after

bin: src
	@echo "$(BIN) compiling..."
	$(CPP) $(BUILD_PATH)/*.o -o $(BUILD_PATH)/$(BIN) $(LIBS) -L$(LIB_PATH)
	@echo "[INFO] BUILD: $(BUILD_PATH)/$(BIN)"

src:
	@echo "src compiling"
	$(CPP) $(CXX_FLAGS) -c $(SRC_PATH)/Food.cpp -o $(BUILD_PATH)/Food.o -I$(INC_PATH)
	$(CPP) $(CXX_FLAGS) -c $(SRC_PATH)/Snake.cpp -o $(BUILD_PATH)/Snake.o -I$(INC_PATH)
	$(CPP) $(CXX_FLAGS) -c $(SRC_PATH)/GamePanel.cpp -o $(BUILD_PATH)/GamePanel.o -I$(INC_PATH)
	$(CPP) $(CXX_FLAGS) -c $(SRC_PATH)/main.cpp -o $(BUILD_PATH)/Main.o -I$(INC_PATH)

