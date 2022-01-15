#include "communication.h"
#include "dynamic_controller.h"

int app_main(void)
{
	communication_init();
	dynamicController_init();
	return 0;
}
