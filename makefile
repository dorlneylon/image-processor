CC := gcc
OPT := 3
CFLAGS := -O$(OPT) -march=native -msse -msse2 -mavx2 -F dwarf -no-pie -Wall -Wextra -Wpedantic -Werror -g3 -ggdb
INCLUDES := -Iinclude
SRC_DIR := src
OUT_DIR := out

$(SRC_DIR)/sepia_asm.o:
	nasm -g -felf64 $(SRC_DIR)/sepia_asm.asm -o $@

$(OUT_DIR)/main: $(SRC_DIR)/compare.c $(SRC_DIR)/main.c $(SRC_DIR)/sepia_asm.o $(SRC_DIR)/process.c $(SRC_DIR)/sepia.c $(SRC_DIR)/image.c $(SRC_DIR)/parse.c $(SRC_DIR)/bmp_header.c $(SRC_DIR)/rotator.c $(SRC_DIR)/validator.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

all: $(OUT_DIR)/main

test: $(SRC_DIR)/compare.c $(SRC_DIR)/process.c $(SRC_DIR)/sepia.c $(SRC_DIR)/image.c $(SRC_DIR)/parse.c $(SRC_DIR)/bmp_header.c $(SRC_DIR)/rotator.c $(SRC_DIR)/validator.c 
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	./$@

clean:
	rm -rf $(SRC_DIR)/*.o $(OUT_DIR)/*.o $(OUT_DIR)/main
