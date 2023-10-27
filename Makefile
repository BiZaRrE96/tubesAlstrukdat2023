CC = gcc
CFLAGS = -Wall -std=c11
SRC_DIR = src
BUILD_DIR = build
TARGET = main_program

# Daftar semua berkas sumber dalam folder src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

SRC_ADT = $(wildcard $(SRC_DIR)/*/*.h)

# Buat daftar berkas objek dari berkas sumber
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Aturan untuk kompilasi berkas sumber menjadi berkas objek
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

# Tambahkan dependensi pada semua berkas sumber dalam folder src
# Jika ada perubahan pada salah satu berkas sumber, maka target akan dijalankan ulang
$(OBJ_FILES): $(SRC_FILES) $(SRC_ADT)
