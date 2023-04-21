#-----------------------------------#
# Makefile: Snake Game				#
#-----------------------------------#

CPP			= g++ 
CPP_FG		= -Wall -Werror

BIN			= SnakeGame.exe
APP_PATH	= .
INC_PATH	= $(APP_PATH)/inc
SRC_PATH	= $(APP_PATH)/src
LIB_PATH	= $(APP_PATH)/lib
BUILD_PATH	= $(APP_PATH)/build
TEST_PATH	= $(APP_PATH)/test

# raylib libraries
RAYLIB		= -lraylib -lopengl32 -lgdi32 -lwinmm
LIBS		= $(RAYLIB) -lm

.PHONY: all all-before all-after

start_msg:
	echo "Compilation Started.."

end_msg:
	echo "Compilation Complete."

all: all-before start_msg $(BIN) end_msg all-after

cMain:
	$(CPP) -c $(SRC_PATH)/main.cpp -o $(BUILD_PATH)/Main.o -I$(INC_PATH) -L$(LIB_PATH) $(LIBS)

#source builder will initiate the recipes for the specific targets
source_builder: cMain

$(BIN): source_builder
	$(CPP) $(BUILD_PATH)/*.o -o $(BUILD_PATH)/$(BIN) $(LIBS) -L$(LIB_PATH)


