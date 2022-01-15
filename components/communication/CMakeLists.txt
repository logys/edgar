idf_component_register(SRCS 	communication.c
				ble.c
				gatt_svr.c
				scli.c
				misc.c
                    INCLUDE_DIRS "include"
		    REQUIRES 	nvs_flash
		    		console
				dynamic_controller
		    		bt)
