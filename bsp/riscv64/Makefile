scons := python ${SCONS}\scons.py

all:
	@$(scons)

clean:
	-rm -rf build rtthread.elf

ifeq ($(MAKECMDGOALS),qemu)
TARGET := __QEMU__
else ifeq ($(MAKECMDGOALS),nemu)
TARGET := __NEMU__
else ifeq ($(MAKECMDGOALS),nutshell)
TARGET := __NUTSHELL__
endif

rtthread.elf:
	MAKE_TARGET=$(TARGET) scons
	riscv64-unknown-elf-objdump -d rtthread.elf > build/code.txt
	riscv64-unknown-elf-objcopy -S --set-section-flags .bss=alloc,contents -O binary rtthread.elf rtthread.bin

qemu: rtthread.elf
	qemu-system-riscv64 -nographic -kernel rtthread.elf -machine virt

nemu: rtthread.elf
	$(MAKE) -C $(NEMU_HOME) ISA=riscv64 run ARGS="-b $(abspath rtthread.bin)"

nutshell: rtthread.elf
	$(MAKE) -C $(NUTSHELL_HOME) emu IMAGE="$(abspath rtthread.bin)"
