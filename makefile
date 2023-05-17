CC = gcc
CFLAGS = -Wall  -o3 -fPIC  #-fsanitize=address
LDFLAGS =-s -shared `pkg-config --cflags --libs gtk+-3.0` 
OBJ_DIR = obj
SRC_DIR = src

TARGET = libPureGTK.so

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)




.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
