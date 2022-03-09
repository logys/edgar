idf_component_register(SRCS 	dynamic_controller.c
				differential/src/differential.c
				wheel/src/wheel.c
				motor/src/motor.c
				encoder/src/encoder.c
				pwm/src/pwm.c
				tick_counter/src/tick_counter.c
				pid/src/pid.c
                    INCLUDE_DIRS "include"
		    	differential/include
			wheel/include
			motor/include
			encoder/include
			pwm/include
			tick_counter/include
			pid/include

		    REQUIRES 
		    )
