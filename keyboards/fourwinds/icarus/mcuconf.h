#pragma once

#include_next <mcuconf.h>
#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLP_VALUE
#undef STM32_PLLQ_VALUE 

#define STM32_PLLM_VALUE                    16      
#define STM32_PLLN_VALUE                    192   
#define STM32_PLLP_VALUE                    2
#define STM32_PLLQ_VALUE                    4

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE