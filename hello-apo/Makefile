# Makefile to buidl example for different ISA targets
# Select architecture by ARCH parameter
#   native, x86, riscv, riscv64, mips, arm, aarch64

# Specify source files of the program
SOURCES = hello-apo.c

# Specify base name of the executable - architecture
TARGET_BASE = hello-apo

# The actual target filename is unique for each architecture
TARGET_EXE = $(TARGET_BASE)-$(ARCH)

all: default

.PHONY : all default build run dump clean

ARCH_SUPPORTED = native x86 riscv riscv64 mips arm aarch64

ifneq ($(MAKECMDGOALS),clean)
ifeq ($(filter $(ARCH_SUPPORTED),$(ARCH)),)
  $(error ARCH parameter has to be set accepted: x86, riscv, riscv64, mips and arm)
endif
endif

# setting specific for riscv build for native build
SOURCES-native +=
LOADLIBES-native +=
CC-native = gcc
OBJDUMP-native = objdump
ARCHFLAGS-native += -ggdb
RUN-native =

# setting specific for riscv build for native build
SOURCES-x86 +=
LOADLIBES-x86 +=
CC-x86 = x86_64-linux-gnu-gcc
OBJDUMP-x86 = x86_64-linux-gnu-objdump
ARCHFLAGS-native += -static  -ggdb
RUN-x86 = qemu-x86_64-static

# setting specific for riscv build for QtRvSim simulator and or RISC-V Linux 32-bit run
SOURCES-riscv += sys-qtrvsim/qtrvsim_sys_stub.c sys-qtrvsim/crt0local.S
LOADLIBES-riscv += -lc -lgcc
CC-riscv = riscv64-unknown-elf-gcc
OBJDUMP-riscv = riscv64-unknown-elf-objdump
ARCHFLAGS-riscv += -mabi=ilp32 -march=rv32im -fno-lto -nostartfiles -nostdlib -static -ggdb
RUN-riscv = qemu-riscv32-static

# setting specific for riscv64 build for QtRvSim simulator and or RISC-V Linux 64-bit run
SOURCES-riscv64 += sys-qtrvsim/qtrvsim_sys_stub.c sys-qtrvsim/crt0local.S
LOADLIBES-riscv64 += -lc -lgcc
CC-riscv64 = riscv64-unknown-elf-gcc
OBJDUMP-riscv64 = riscv64-unknown-elf-objdump
ARCHFLAGS-riscv64 += -mabi=lp64 -march=rv64imac -fno-lto -nostartfiles -nostdlib -static -ggdb
RUN-riscv64 = qemu-riscv64-static

# setting specific for riscv64 build for QtMips simulator and or MIPS Linux run
SOURCES-mips += sys-qtmips/qtmips_sys_stub.c sys-qtmips/crt0local.S
LOADLIBES-mips += -lc -lgcc
CC-mips = mips-elf-gcc
OBJDUMP-mips = mips-elf-objdump
ARCHFLAGS-mips += -march=mips32 -fno-lto -nostartfiles -nostdlib -static -ggdb
RUN-mips = qemu-mips-static

# setting specific for ARM 32-bit build
SOURCES-arm +=
LOADLIBES-arm +=
CC-arm = arm-linux-gnueabihf-gcc
OBJDUMP-arm = arm-linux-gnueabihf-objdump
ARCHFLAGS-arm += -static -ggdb
RUN-arm = qemu-arm-static

# setting specific for ARM 64-bit build
SOURCES-aarch64 +=
LOADLIBES-aarch64 +=
CC-aarch64 = aarch64-linux-gnu-gcc
OBJDUMP-aarch64 = aarch64-linux-gnu-objdump
ARCHFLAGS-aarch64 += -static -ggdb
RUN-aarch64 = qemu-aarch64-static

define compile_one_src
src := $(1)
arch := $(2)
obj := $$(basename $$(notdir $$(src)))-$$(arch).o
$$(obj) : $$(src)
	$$(CC-$$(arch)) $$(ARCHFLAGS-$$(arch)) -c $$< -o $$@
OBJS-$$(arch) := $$(OBJS-$$(arch)) $$(obj)
#$$(warning $$(src) $$(obj) $$(arch) $$(OBJS-$$(arch)))
endef

$(foreach srci, $(SOURCES) $(SOURCES-$(ARCH)),$(eval $(call compile_one_src, $(srci), $(ARCH))))

$(TARGET_EXE) : $(OBJS-$(ARCH))
	$(CC-$(ARCH)) -o $@ $^ $(ARCHFLAGS-$(ARCH)) $(LOADLIBES-$(ARCH))

build : $(TARGET_EXE)

run : $(TARGET_EXE)
	$(RUN-$(ARCH)) ./$<

dump: $(TARGET_EXE)
	$(OBJDUMP-$(ARCH)) --source $< > $<.dump
	cat $<.dump

clean :
	rm -f $(OBJS-$(ARCH)) $(foreach arch,$(ARCH_SUPPORTED),$(TARGET_BASE)-$(arch)) *.o *.dump

default : build