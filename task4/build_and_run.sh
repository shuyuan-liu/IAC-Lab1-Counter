#!/usr/bin/sh

rm -rf obj_dir
rm -f counter.vcd

verilator --cc --trace --exe top.sv counter.sv bin2bcd.sv counter_tb.cpp

make -j7 -C obj_dir -f Vtop.mk

./obj_dir/Vtop
