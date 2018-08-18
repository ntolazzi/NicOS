GCCPARAMS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -g3
GPPPARAMS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -g3
LDPARAMS = -ffreestanding -O2 -nostdlib -lgcc
ASPARAMS =
COMPILER_PATH = compiler/bin
objects = boot.o kernel.o terminal.o stdlib.o ports.o gdt.o
VPATH = src
BUILDDIR = bin

$(BUILDDIR)/%.o: %.c
	$(COMPILER_PATH)/i686-elf-gcc $(GCCPARAMS) -o $@ -c $<

$(BUILDDIR)/%.o: %.cpp
	$(COMPILER_PATH)/i686-elf-g++ $(GPPPARAMS) -o $@ -c $<

$(BUILDDIR)/%.o: %.s
	$(COMPILER_PATH)/i686-elf-as $(ASPARAMS) -o $@ $<


clean:
	rm -rf bin

all:
	mkdir -p bin
	make bin/boot.o
	make bin/kernel.o
	make bin/stdlib.o
	make bin/terminal.o
	make bin/ports.o
	make bin/gdt.o
	make NicOS.bin


NicOS.bin:
	$(COMPILER_PATH)/i686-elf-gcc $(LDPARAMS) -T $(VPATH)/linker.ld -o $(BUILDDIR)/$@ $(addprefix $(BUILDDIR)/, $(objects))

run:
	make all
	qemu-system-i386 -kernel bin/NicOS.bin
