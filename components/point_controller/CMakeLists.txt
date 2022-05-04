idf_component_register(SRCS "point_controller.c"
			controller/src/controller.c
                    INCLUDE_DIRS "include"
		    	controller/src
		    REQUIRES
		    	dynamic_controller
		    )
