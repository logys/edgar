#include "communication.h"
#include "dynamic_controller.h"
#include "point_controller.h"

int app_main(void)
{
	communication_init();
	dynamicController_init();
	pointController_init();
	return 0;
}
