################################################################################
# Library configuration
OPENCM3_DIR		= ../libopencm3
LDSCRIPT		= stm32f3-discovery.ld

################################################################################
# Compiler arguments
LIBNAME			= opencm3_stm32f3
DEFS			= -DSTM32F3

FP_FLAGS		?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS		= -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

################################################################################
# OpenOCD specific variables
OOCD			?= openocd
OOCD_INTERFACE	?= stlink-v2
OOCD_BOARD		?= stm32f3discovery

################################################################################
# Compile all the .c files to link into the binary
CFILES=$(shell find . -name \*.c)
OBJS=$(CFILES:.c=.o)

include ../Makefile.rules
