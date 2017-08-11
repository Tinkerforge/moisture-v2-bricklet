/* moisture-v2-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * main.c: Initialization for Moisture V2 Bricklet
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdbool.h>

#include "configs/config.h"

#include "bricklib2/bootloader/bootloader.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/logging/logging.h"
#include "communication.h"
#include "mcp3425.h"

MCP3425 mcp3425;

int main(void) {
	logging_init();
	logd("Start Moisture V2 Bricklet\n\r");

	// Enable 80MHz oscillator
	XMC_GPIO_CONFIG_t oscillator_enable_pin;
	oscillator_enable_pin.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
	oscillator_enable_pin.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
	XMC_GPIO_Init(OSCILLATOR_ENABLE_PIN, &oscillator_enable_pin);

	mcp3425_init(&mcp3425);
	communication_init();

	while(true) {
		bootloader_tick();
		mcp3425_tick(&mcp3425);
//		communication_tick();
	}
}
