#!/bin/bash
basepath=$(cd `dirname $0`; pwd)
#echo ${basepath}
cd ${basepath}

scons

riscv64-linux-gnu-objdump -d rtthread.elf > rtthread.txt
