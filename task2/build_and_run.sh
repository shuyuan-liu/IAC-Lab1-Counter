#!/usr/bin/sh

rm -rf obj_dir
rm -f counter.vcd

verilator -Wall --cc --trace --exe counter.sv counter_tb.cpp

make -j7 -C obj_dir -f Vcounter.mk

./obj_dir/Vcounter
