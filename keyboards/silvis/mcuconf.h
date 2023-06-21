// Copyright 2022 Eben Quennevile (@TonehavenE)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLP_VALUE
#undef STM32_PLLQ_VALUE

#define STM32_PLLM_VALUE (STM32_HSECLK / 1000000)
#define STM32_PLLN_VALUE 192
#define STM32_PLLP_VALUE 4
#define STM32_PLLQ_VALUE 4

#undef STM32_PWM_USE_ADVANCED
#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_ADVANCED TRUE
#define STM32_PWM_USE_TIM1 TRUE
