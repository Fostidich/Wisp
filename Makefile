CC = g++ -std=c++17 -Wall

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
TARGET_DIR = target

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
INCLUDES = $(addprefix -I./,$(shell find $(INCLUDE_DIR) -type d))
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
TARGET = -o $(TARGET_DIR)/wisp
LIBS = -lssl -lcrypto

.PHONY: all
all:
	@echo "[---] Cleaning outputs"
	@make clean >/dev/null
	@echo "[#--] Generating objects"
	@make objects >/dev/null
	@echo "[##-] Building target"
	@$(CC) $(TARGET) $(INCLUDES) $(OBJS) $(LIBS)
	@echo "[###] Finish"

.PHONY: objects
objects:
	@for source_file in $(SRCS); \
 	do object_file="$(OBJ_DIR)/$$(basename $$source_file .cpp).o"; \
 	$(CC) $(INCLUDES) -c -o $$object_file $$source_file $(LIBS); \
	done

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) $(TARGET_DIR)
	@mkdir -p ./$(OBJ_DIR)
	@mkdir -p ./$(TARGET_DIR)
