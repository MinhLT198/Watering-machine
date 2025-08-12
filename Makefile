# Tên file thực thi
TARGET = my_program

# Thư mục gốc chứa mã nguồn
SRC_DIR = .

# Thư mục chứa các file .c của các component
# Học viên chỉ cần thêm tên thư mục component mới vào danh sách này
COMPONENTS = Actuators Buttons Sensors Config Types Watering_logic Notifier

# Thư mục App chứa main.c
APP_DIR = App

# Thư mục để chứa các file .o và file thực thi
BUILD_DIR = build

# Cờ biên dịch và liên kết
CC = gcc
# Tự động tạo cờ -I cho các component
COMPONENT_INCLUDE_PATHS = $(foreach comp,$(COMPONENTS),-I$(SRC_DIR)/$(comp))
CFLAGS = -Wall -I$(SRC_DIR)/$(APP_DIR) $(COMPONENT_INCLUDE_PATHS)
LDFLAGS =

# Tìm tất cả các file .c trong các thư mục component và thư mục App
COMPONENT_SRC = $(foreach comp,$(COMPONENTS),$(wildcard $(SRC_DIR)/$(comp)/*.c))
APP_SRC = $(wildcard $(SRC_DIR)/$(APP_DIR)/*.c)
SRC_FILES = $(COMPONENT_SRC) $(APP_SRC)

# Tạo danh sách các file .o tương ứng
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Mục tiêu mặc định
.PHONY: all
all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)

# Quy tắc biên dịch file .c thành file .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc liên kết các file .o thành file thực thi
$(BUILD_DIR)/$(TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

# Tạo thư mục build nếu chưa tồn tại
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Mục tiêu dọn dẹp các file đã biên dịch
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Mục tiêu chạy chương trình
.PHONY: run
run: all
	./$(BUILD_DIR)/$(TARGET)