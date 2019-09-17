scons := python ${SCONS}\scons.py

all:
	@$(scons)

clean:
	-rm -rf build

run:
	scons
	riscv64-unknown-elf-objdump -d rtthread.elf > build/code.txt
	qemu-system-riscv64 -nographic -kernel rtthread.elf -machine virt
