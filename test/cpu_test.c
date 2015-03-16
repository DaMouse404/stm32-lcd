#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/rcc.h>

const clock_scale_t hsi_8mhz[CLOCK_END] = {
    {},
    {},
    { /* CLOCK_64MHz */
        .pll = RCC_CFGR_PLLMUL_PLL_IN_CLK_X11,
        .pllsrc = RCC_CFGR_PLLSRC_HSI_DIV2,
        .hpre = RCC_CFGR_HPRE_DIV_NONE,
        .ppre1 = RCC_CFGR_PPRE1_DIV_2,
        .ppre2 = RCC_CFGR_PPRE2_DIV_NONE,
        .power_save = 1,
        .flash_config = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_1WS,
        .apb1_frequency = 22000000,
        .apb2_frequency = 44000000,
    }
};


void rcc_clock_setup_hsi(const clock_scale_t *clock) {}

static void test_cpu_init() {}

int main(void)
{
	const UnitTest tests[] = {
		unit_test(test_cpu_init)
	};
	return run_tests(tests);
}
