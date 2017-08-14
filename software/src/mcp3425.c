/* moisture-v2-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * mcp3425.c: MCP3425 driver
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

#include "mcp3425.h"

#include "configs/config_mcp3425.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/hal/i2c_fifo/i2c_fifo.h"

#include "bricklib2/logging/logging.h"

void mcp3425_init(MCP3425 *mcp3425) {
	mcp3425->i2c_fifo.baudrate         = MCP3425_I2C_BAUDRATE;
	mcp3425->i2c_fifo.address          = MCP3425_I2C_ADDRESS;
	mcp3425->i2c_fifo.i2c              = MCP3425_I2C;

	mcp3425->i2c_fifo.scl_port         = MCP3425_SCL_PORT;
	mcp3425->i2c_fifo.scl_pin          = MCP3425_SCL_PIN;
	mcp3425->i2c_fifo.scl_mode         = MCP3425_SCL_PIN_MODE;
	mcp3425->i2c_fifo.scl_input        = MCP3425_SCL_INPUT;
	mcp3425->i2c_fifo.scl_source       = MCP3425_SCL_SOURCE;
	mcp3425->i2c_fifo.scl_fifo_size    = MCP3425_SCL_FIFO_SIZE;
	mcp3425->i2c_fifo.scl_fifo_pointer = MCP3425_SCL_FIFO_POINTER;

	mcp3425->i2c_fifo.sda_port         = MCP3425_SDA_PORT;
	mcp3425->i2c_fifo.sda_pin          = MCP3425_SDA_PIN;
	mcp3425->i2c_fifo.sda_mode         = MCP3425_SDA_PIN_MODE;
	mcp3425->i2c_fifo.sda_input        = MCP3425_SDA_INPUT;
	mcp3425->i2c_fifo.sda_source       = MCP3425_SDA_SOURCE;
	mcp3425->i2c_fifo.sda_fifo_size    = MCP3425_SDA_FIFO_SIZE;
	mcp3425->i2c_fifo.sda_fifo_pointer = MCP3425_SDA_FIFO_POINTER;

	i2c_fifo_init(&mcp3425->i2c_fifo);

	mcp3425->configuration.bit.rdy               = 0;
	mcp3425->configuration.bit.channel_selection = 0;
	mcp3425->configuration.bit.conversion_mode   = MCP3425_CONF_CONVERSION_MODE_CONTINUOUS;
	mcp3425->configuration.bit.sample_rate       = MCP3425_CONF_SAMPLE_RATE_15SPS;
	mcp3425->configuration.bit.gain              = MCP3425_CONF_GAIN_8X;

	system_timer_sleep_ms(100);

	logd("MCP3425 config: %d\n\r", mcp3425->configuration.data);
	i2c_fifo_write_direct(&mcp3425->i2c_fifo, 1, &mcp3425->configuration.data, true);
}

void mcp3425_tick(MCP3425 *mcp3425) {
	I2CFifoState state = i2c_fifo_next_state(&mcp3425->i2c_fifo);

	if(state & I2C_FIFO_STATE_ERROR) {
		loge("MCP3425 I2C error: %d\n\r", state);
		mcp3425_init(mcp3425);
		return;
	}

	switch(state) {
		case I2C_FIFO_STATE_READ_DIRECT_READY: {
			uint8_t buffer[16];
			uint8_t length = i2c_fifo_read_fifo(&mcp3425->i2c_fifo, buffer, 16);
			if(length != 3) {
				loge("MCP3425 I2C unexpected read length : %d\n\r", length);
				mcp3425_init(mcp3425);
				break;
			}

			int16_t value = (buffer[0] << 8) | buffer[1];
			logd("value: %d\n\r", value);

		} __attribute__((fallthrough));
		case I2C_FIFO_STATE_WRITE_DIRECT_READY:
		case I2C_FIFO_STATE_IDLE: {
			i2c_fifo_read_direct(&mcp3425->i2c_fifo, 3);
			break;
		}

		default: {
			if(state & I2C_FIFO_STATE_READY) {
				loge("MCP3425 I2C unrecognized ready state : %d\n\r", state);
				mcp3425_init(mcp3425);
			}
			return;
		}
	}
}
