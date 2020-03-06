# 目标
TARGET :=out
#build 目录
BUILD_DIR=build

CC :=gcc-7

SZ :=size
# 头文件目录
INCDIRS:=\
mem \
fatfs \
disk_simu
# 源文件目录
SRCDIRS:=\
mem \
fatfs \
disk_simu \
./

#全局弘定义 
DEFS :=\
-DDEBUG \

INCLUDE:= $(patsubst %, -I%, $(INCDIRS))

CFILES:=$(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
# 库
LIBS:=\
# -lpthread

# 标志
CFLAGS:=\
-g \
-m32 \
# -fno-stack-protector

OBJECTS:=$(addprefix $(BUILD_DIR)/,$(notdir $(CFILES:.c=.o)))

.PHONLYS:clean
.PHONLYS:all


VPATH:=$(SRCDIRS)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) $(DEFS) -c  $(CFLAGS) $<  $(INCLUDE) -o $@

$(TARGET):$(OBJECTS)
	$(CC) $(OBJECTS) $(DEFS) $(CFLAGS) -o $@ $(LIBS)

$(BUILD_DIR):
	mkdir $@

clean:
# echo CFILES=$(CFILES)
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)



