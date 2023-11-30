CC = g++
CFLAGS = -std=c++11 -Wall

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
TARGET_DIR = target

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
INCLUDES = $(addprefix -I./,$(shell find $(INCLUDE_DIR) -type d))
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
TARGET = -o $(TARGET_DIR)/wisp
LIBS = -lssl -lcrypto

all:
	@echo -n "Making:\t"
	@echo -n "cleaning outputs -> "
	@make clean >/dev/null
	@echo -n "generating objects -> "
	@make objects >/dev/null
	@echo -n "building target -> "
	@$(CC) $(CFLAGS) $(TARGET) $(INCLUDES) $(OBJS) $(LIBS)
	@echo "finish!"

objects:
	@for source_file in $(SRCS); do \
			object_file="$(OBJ_DIR)/$$(basename $$source_file .cpp).o"; \
    	  	$(CC) $(CFLAGS) $(INCLUDES) -c -o $$object_file $$source_file $(LIBS); \
    	done

clean:
	@rm -rf $(OBJ_DIR) $(TARGET_DIR)
	@mkdir -p ./$(OBJ_DIR)
	@mkdir -p ./$(TARGET_DIR)



