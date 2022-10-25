#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char* argv[])
{
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    auto top = new Vcounter;
    auto logger = new VerilatedVcdC;
    top->trace(logger, 99);
    logger->open("counter.vcd");

    if (vbdOpen() != 1) {
        return -1;
    }
    vbdHeader("Lab 1: Counter");

    top->clk = 0;
    top->rst = 1;
    top->en = 0;

    for (int cycle = 0; cycle < 300; cycle++) {
        top->rst = cycle <= 1;
        top->en = vbdFlag();

        for (int i = 0; i < 2; i++) {
            logger->dump(2 * cycle + i);
            top->clk = !top->clk;
            top->eval();
        }

        vbdHex(4, (int)(top->count >> 12) & 0xF);
        vbdHex(3, (int)(top->count >> 8) & 0xF);
        vbdHex(2, (int)(top->count >> 4) & 0xF);
        vbdHex(1, (int)(top->count) & 0xF);
        vbdCycle(cycle + 1);

        if (Verilated::gotFinish()) {
            return 0;
        }
    }

    vbdClose();
    logger->close();
    return 0;
}

