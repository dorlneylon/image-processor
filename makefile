CC := gcc
OPT := 3
CFLAGS := -O$(OPT) -march=native -g -F dwarf -no-pie
INCLUDES := -Iinclude
SRC_DIR := src
OUT_DIR := out


# $(OUT_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# # $(SRC_DIR)/sepia.asm:

# $(SRC_DIR)/sepia_inner.o: $(SRC_DIR)/sepia_inner.asm
# 	nasm -f elf64 -o $@ $^

$(OUT_DIR)/main: $(SRC_DIR)/main.c $(SRC_DIR)/process.c $(SRC_DIR)/sepia.c $(SRC_DIR)/image.c $(SRC_DIR)/parse.c $(SRC_DIR)/bmp_header.c $(SRC_DIR)/rotator.c $(SRC_DIR)/validator.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

all: $(OUT_DIR)/main

test: $(SRC_DIR)/compare.c $(SRC_DIR)/process.c $(SRC_DIR)/sepia.c $(SRC_DIR)/image.c $(SRC_DIR)/parse.c $(SRC_DIR)/bmp_header.c $(SRC_DIR)/rotator.c $(SRC_DIR)/validator.c 
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	./$@

clean:
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/main



