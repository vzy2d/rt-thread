scons := python ${SCONS}\scons.py

all:
	@$(scons)

clean:
	-rm -rf build

nemu_run:
	scons
	riscv64-unknown-elf-objdump -d rtthread.elf > build/code.txt
	riscv64-unknown-elf-objcopy -S --set-section-flags .bss=alloc,contents -O binary rtthread.elf rtthread.bin
	$(MAKE) -C $(NEMU_HOME) ISA=riscv64 run ARGS="-b $(abspath rtthread.bin)"

run:
	scons
	riscv64-unknown-elf-objdump -d rtthread.elf > build/code.txt
	riscv64-unknown-elf-objcopy -S --set-section-flags .bss=alloc,contents -O binary rtthread.elf rtthread.bin
	$(MAKE) -C $(NOOP_HOME) emu IMAGE="$(abspath rtthread.bin)"


# usage:
# noop_run