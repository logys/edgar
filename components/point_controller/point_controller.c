#include "point_controller.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "point.h"
#include "math.h"
#include "dynamic_controller.h"
#include "speeds.h"

#define STACK_SIZE 2000
#define TASK_DYNAMIC_PRIORITY 3
#define SAMPLE_TIME 100

static StaticTask_t xTaskBuffer;
static StackType_t xStack[STACK_SIZE];
static TaskHandle_t task_handle_point;

static StaticQueue_t xQueueBufferPoint;
static QueueHandle_t queue_handle_point;
static uint8_t queue_storage_point[sizeof(struct Point)];

static StaticQueue_t xQueueBufferSpeeds;
static QueueHandle_t queue_handle_speeds;
static uint8_t queue_storage_speeds[sizeof(struct Point)];

static Point reference_ = {};
static Point position_ = {};

static void pointController_task(void * param);
static void task_init(void);
static void queues_init(void);

void pointController_init(void)
{
	queues_init();
	task_init();
}

/* Se utilizan dos queue's, una para almacenar puntos indicados por un 
 * módulo externo y otra para guardar la velocidades medidas y calculadas
 * por el controlador interno
 */
static void queues_init(void)
{
	queue_handle_point = xQueueCreateStatic(
			1,
			sizeof(Point),
			&(queue_storage_point[0]),
			&xQueueBufferPoint
			);

	queue_handle_speeds = xQueueCreateStatic(
			1,
			sizeof(Point),
			&(queue_storage_speeds[0]),
			&xQueueBufferSpeeds
			);
}

static void task_init(void)
{
	task_handle_point = xTaskCreateStatic(
			pointController_task,
			"Controlador puntos",
			STACK_SIZE,
			(void *)NULL,
			TASK_DYNAMIC_PRIORITY,
			xStack,
			&xTaskBuffer
			);
	vTaskSuspend(task_handle_point);
}


static void checkNewPoints(void);

#define KW 1
#define KV 1
float phi_position_ = 0;
Point speeds_ = {};

static void pointController_task(void * param)
{
	while(1){
		checkNewPoints();
		float phi_ref = atan2(
				reference_.y - position_.y,
				reference_.x - position_.x
				);
		//calculate errors
		float xerror = reference_.x - position_.x;
		float yerror = reference_.y - position_.y;
		float phierror = phi_ref - phi_position_;
		//Control
		Speeds speeds = {};
		speeds.linear = KW*phierror;
		speeds.angular = KV*sqrt(pow(xerror, 2) + pow(yerror, 2));
		//limit speeds TODO
		//Send speeds TODO
		dynamicController_setSpeeds(speeds);
		//wait speeds TODO
		Point buffer;
		if( pdTRUE == xQueueReceive(queue_handle_speeds, 
					&buffer, portMAX_DELAY))
			speeds_ = buffer;
		//Compute position TODO
	}
}

static void checkNewPoints(void)
{
	Point buffer;
	if( pdTRUE == xQueueReceive(queue_handle_point, &buffer, 0 )){
		reference_ = buffer;
	}
}

void pointController_enable(void)
{
	vTaskResume(task_handle_point);
}

void pointController_setPoint(Point point)
{ 
	xQueueSend(queue_handle_point, &point, 0);
}

void pointController_disable(void)
{
	//TODO
}
