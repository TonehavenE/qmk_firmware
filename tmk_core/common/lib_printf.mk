PRINTF_PATH = $(LIB_PATH)/printf

TMK_COMMON_SRC += $(PRINTF_PATH)/printf.c
TMK_COMMON_SRC += $(COMMON_DIR)/printf.c
#TMK_COMMON_DEFS += -DPRINTF_DISABLE_SUPPORT_FLOAT
TMK_COMMON_DEFS += -DPRINTF_DISABLE_SUPPORT_EXPONENTIAL
#TMK_COMMON_DEFS += -DPRINTF_DISABLE_SUPPORT_LONG_LONG
TMK_COMMON_DEFS += -DPRINTF_DISABLE_SUPPORT_PTRDIFF_T
VPATH += $(PRINTF_PATH)
