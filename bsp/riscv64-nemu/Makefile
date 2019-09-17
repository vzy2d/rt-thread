scons := python ${SCONS}\scons.py

all:
	@$(scons)

clean:
	-rm -rf build

run:
	scons
	riscv64-unknown-elf-objdump -d rtthread.elf > build/code.txt
	riscv64-unknown-elf-objcopy --adjust-vma +0x100000 -S --set-section-flags .bss=alloc,contents -O binary rtthread.elf rtthread.bin
	$(MAKE) -C $(NEMU_HOME) ISA=riscv64 run ARGS="-b $(abspath rtthread.bin)"
