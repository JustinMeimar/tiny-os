C_SOURCES = $(wildcard kernel/*.c drivers/*.c libc/*.c cpu/*.c proc/*.c tests/*.c)
ASM_SOURCES = $(wildcard kernel/*.asm cpu/*.asm)
HEADERS = $(wildcard kernel/*.h drivers/*.h libc/*.h cpu/*.h proc/*.h tests/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o}

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
LD = /usr/local/i386elfgcc/bin/i386-elf-ld

# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Tlink.ld $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Tlink.ld $^ 

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -S -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

DUMP_DIR = dump

dump-asm: ${C_SOURCES:.c=.s}
	mv *.s $(DUMP_DIR)

%.s: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -S $< -o $@

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	find . -type f -name "*.o" -exec rm -f {} \;
	find . -type f -name "*.s" -exec rm -f {} \;