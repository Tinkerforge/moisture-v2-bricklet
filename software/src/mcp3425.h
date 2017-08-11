/* moisture-v2-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * mcp3425.h: MCP3425 driver
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

#ifndef MCP3425_H
#define MCP3425_H

#include <stdint.h>

#include "bricklib2/hal/i2c_fifo/i2c_fifo.h"

#define MCP3425_CONF_CONVERSION_MODE_CONTINUOUS 1
#define MCP3425_CONF_CONVERSION_MODE_ONE_SHOT   0
#define MCP3425_CONF_SAMPLE_RATE_240SPS         0
#define MCP3425_CONF_SAMPLE_RATE_60SPS          1
#define MCP3425_CONF_SAMPLE_RATE_15SPS          2
#define MCP3425_CONF_GAIN_1X                    0
#define MCP3425_CONF_GAIN_2X                    1
#define MCP3425_CONF_GAIN_4X                    2
#define MCP3425_CONF_GAIN_8X                    3

typedef union {
  struct {
	uint8_t gain:2;
	uint8_t sample_rate:2;
	uint8_t conversion_mode:1;
	uint8_t channel_selection:2;
	uint8_t rdy:1;
  } bit;
  uint8_t data;
} MCP3425Configuration;

typedef struct {
	MCP3425Configuration configuration;
	I2CFifo i2c_fifo;
} MCP3425;

void mcp3425_init(MCP3425 *mcp3425);
void mcp3425_tick(MCP3425 *mcp3425);

#endif
