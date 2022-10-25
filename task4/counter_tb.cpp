#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char* argv[])
{
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    auto top = new Vtop;
    auto logger = new VerilatedVcdC;
    top->trace(logger, 99);
    logger->open("counter.vcd");

    if (vbdOpen() != 1) {
        return -1;
    }
    vbdHeader("Lab 1: Counter");

    top->clk = 0;
    top->rst = 1;
    top->en = 1;

    for (int cycle = 0; cycle < 1000; cycle++) {
        top->rst = cycle <= 1;

        for (int i = 0; i < 2; i++) {
            logger->dump(2 * cycle + i);
            top->clk = !top->clk;
            top->eval();
        }

        vbdHex(1, top->bcd & 0xF);
        vbdHex(2, (top->bcd >> 4) & 0xF);
        vbdHex(3, (top->bcd >> 8) & 0xF);
        vbdHex(4, (top->bcd >> 12) & 0xF);
        vbdCycle(cycle + 1);

        if (Verilated::gotFinish()) {
            return 0;
        }
    }

    vbdClose();
    logger->close();
    return 0;
}

