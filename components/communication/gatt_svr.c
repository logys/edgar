/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "bleprph.h"

/**
 * The vendor specific security test service consists of two characteristics:
 *     o random-number-generator: generates a random 32-bit number each time
 *       it is read.  This characteristic can only be read over an encrypted
 *       connection.
 *     o static-value: a single-byte characteristic that can always be read,
 *       but can only be written over an encrypted connection.
 */

/* 5c3a659e-897e-45e1-b016-007107c96d00 */
static const ble_uuid128_t gatt_service_edgar =
    BLE_UUID128_INIT(0xf7, 0x00, 0xc9, 0x07, 0x71, 0x00, 0x16, 0xb0,
                     0xe1, 0x45, 0x7e, 0x89, 0x9e, 0x65, 0x3a, 0xb0);

/* 5c3a659e-897e-45e1-b016-007107c96d10 */
static const ble_uuid128_t gatt_char_commands =
    BLE_UUID128_INIT(0xf7, 0x10, 0xc9, 0x07, 0x71, 0x00, 0x16, 0xb0,
                     0xe1, 0x45, 0x7e, 0x89, 0x9e, 0x65, 0x3a, 0xb0);

static int handleCommands(uint16_t conn_handle, uint16_t attr_handle,
                             struct ble_gatt_access_ctxt *ctxt,
                             void *arg);

static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    	{
		/* Edgar service */
		.type = BLE_GATT_SVC_TYPE_PRIMARY,
		.uuid = &gatt_service_edgar.u,
		.characteristics = (struct ble_gatt_chr_def[])
		{
			{
				.uuid = &gatt_char_commands.u,
				.access_cb = handleCommands,
				.flags = BLE_GATT_CHR_F_WRITE
			}, {
				0, /* No more chars */
			}
		}
    	}, {
		0, /* No more services. */
    	},
};

#include "dynamic_controller.h"
#include <string.h>

#define START 0
#define STOP 1
#define LINEAL 3
#define ANGULAR 4
#define KPL 5
#define KPR 6
#define KPI 7

static int handleCommands(uint16_t conn_handle, uint16_t attr_handle,
                             struct ble_gatt_access_ctxt *ctxt,
                             void *arg)
{
	uint8_t command[8];
	uint16_t length;
	ble_hs_mbuf_to_flat(ctxt->om, &command, 8, &length);
	uint8_t command_value = command[0];
	float data = *(float *)(command+1);
	switch(command_value){
		case START:
			MODLOG_DFLT(INFO, "Arrancando motores\n");
			dynamicController_start();
			break;
		case STOP:
			MODLOG_DFLT(INFO, "Deteniendo motores\n");
			dynamicController_stop();
			break;
		case LINEAL:
			dynamicController_setLinear(data);
			break;
		case ANGULAR:
			dynamicController_setAngular(data);
			break;
		case KPL:
			dynamicController_setKp(KPL, data);
			break;
		case KPR:
			dynamicController_setKp(KPR, data);
			break;
		case KPI:
			dynamicController_setKi(KPR, data);
			break;
	}
	return 0;
}

int gatt_svr_init(void)
{
    int rc;

    ble_gatts_reset();
    ble_svc_gap_init();
    ble_svc_gatt_init();

    rc = ble_gatts_count_cfg(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    rc = ble_gatts_add_svcs(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    return 0;
}
