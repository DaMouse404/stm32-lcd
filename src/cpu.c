#include <libopencm3/stm32/rcc.h>

#include "cpu.h"

void cpu_init(void)
{
	rcc_clock_setup_hsi(&hsi_8mhz[CLOCK_64MHZ]);
}
