/**
 * Copyright (c) 2016 Motorola.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __STM32_HAL_MOD_H
#define __STM32_HAL_MOD_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <greybus.h>
#include <stm32_mod_device.h>

#define getreg32(a)         (*(volatile uint32_t *)(a))

typedef enum
{
  PIN_RESET = 0,
  PIN_SET
} PinState;

enum slave_pwrctrl_mode {
    SLAVE_PWRCTRL_POWER_ON          = 0x01,
    SLAVE_PWRCTRL_POWER_OFF         = 0x02,
    SLAVE_PWRCTRL_POWER_FLASH_MODE  = 0x03,
};

extern bool mods_is_spi_csn(uint16_t pin);
extern void mods_rfr_set(PinState pstate);
extern PinState mods_rfr_get(void);
extern void mods_wake_n_set(PinState pstate);
extern PinState mods_wake_n_get(void);
extern void mods_muc_int_set(PinState pstate);
extern PinState mods_muc_int_get(void);
extern void SPI_NSS_INT_CTRL_Config(void);

extern void mods_gpio_clk_enable(void);
extern void device_gpio_init(void);
extern PinState mods_force_flash_get(void);
extern void mod_dev_base_spi_reset(void);
/* Is the mod currently attached to a base? */
extern bool mod_dev_is_attached(void);

/* from main.c */
extern void SystemClock_Config(void);
extern void MX_SPI_Init(void);
extern void MX_USART_UART_Init(void);
extern void MX_GPIO_Init(void);
extern void MX_DMA_Init(void);
extern int get_chip_uid(uint64_t *uid_high, uint64_t *uid_low);

/* flashing */
#define FLASHMODE_FLAG_PAGE     (FLASH_BASE + FLASH_SIZE - FLASH_PAGE_SIZE)

void ErasePage(uint32_t pageAddress);
int flash_erase(uint32_t start_addr, uint32_t size);
int program_flash_data(uint32_t start, uint32_t size, uint8_t *data);
int program_flash_lock(void);
int program_flash_unlock(void);
int program_flash_dword(const uint64_t *dword);
uint32_t mod_get_tftf_addr(void);

#endif /* __STM32_HAL_MOD_H */