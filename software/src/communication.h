/* moisture-v2-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define MOISTURE_V2_THRESHOLD_OPTION_OFF 'x'
#define MOISTURE_V2_THRESHOLD_OPTION_OUTSIDE 'o'
#define MOISTURE_V2_THRESHOLD_OPTION_INSIDE 'i'
#define MOISTURE_V2_THRESHOLD_OPTION_SMALLER '<'
#define MOISTURE_V2_THRESHOLD_OPTION_GREATER '>'

// Function and callback IDs and structs
#define FID_GET_MOISTURE 1
#define FID_SET_MOISTURE_CALLBACK_CONFIGURATION 2
#define FID_GET_MOISTURE_CALLBACK_CONFIGURATION 3

#define FID_CALLBACK_MOISTURE 4



// Function prototypes


// Callbacks
bool handle_moisture_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 1
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_moisture_callback, \


#endif
