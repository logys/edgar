#include "dynamic_controller.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "differential.h"
#include "pwm.h"
#include "motor.h"
#include "encoder.h"
#include "tick_counter.h"

#include "esp_log.h"
static const char * tag = "Dynamic-speed";

#define STACK_SIZE 2000
#define TASK_DINAMIC_PRIORITY 2

StaticTask_t xTaskBuffer;
StackType_t xStack[STACK_SIZE];
static TaskHandle_t task_handle_dynamic;
StaticQueue_t xQueueBuffer;
QueueHandle_t queue_handle_ref;
static uint8_t queue_storage_speed[sizeof(float)];
StaticQueue_t xQueueBufferAng;
QueueHandle_t queue_handle_angular;
static uint8_t queue_storage_angular[sizeof(float)];

static void dynamicController_task(void * param);

void dynamicController_setSpeeds(float linear, float angular)
{
	xQueueSend(queue_handle_ref, &linear, 0);
}

void dynamicController_setLinear(float speed)
{
	xQueueSend(queue_handle_ref, &speed, 0);
}

void dynamicController_setAngular(float speed)
{
	xQueueSend(queue_handle_angular, &speed, 0);
}

#define FREQUENCY_PWM 1000
#define TICKS_PER_REV 213
#define CONTROLLER_PERIOD_MS 1000
#define PIN_IN1 25
#define PIN_IN2 26
#define PIN_IN3 27
#define PIN_IN4 12
#define LEFT_ENCODER_PHASEA_PIN 33
#define LEFT_ENCODER_PHASEB_PIN 32
#define RIGHT_ENCODER_PHASEA_PIN 16
#define RIGHT_ENCODER_PHASEB_PIN 17
#define WHEEL_RAD 0.035

static TickCounter left_tick;
static TickCounter right_tick;
static Pwm left_pwmIn1;
static Pwm left_pwmIn2;
static Pwm right_pwmIn1;
static Pwm right_pwmIn2;
static Encoder left_encoder;
static Encoder right_encoder;
static Motor left_motor;
static Motor right_motor;
static Wheel left_wheel;
static Wheel right_wheel;

void dynamicController_init(void)
{
	left_tick = tickCounter_create(PCNT_UNIT_0, LEFT_ENCODER_PHASEA_PIN, LEFT_ENCODER_PHASEB_PIN);
	right_tick = tickCounter_create(PCNT_UNIT_1, RIGHT_ENCODER_PHASEB_PIN, RIGHT_ENCODER_PHASEA_PIN);
	left_encoder = encoder_create(&left_tick, TICKS_PER_REV, CONTROLLER_PERIOD_MS);
	right_encoder = encoder_create(&right_tick, TICKS_PER_REV, CONTROLLER_PERIOD_MS);
	left_pwmIn1 = pwm_create(MCPWM0A, FREQUENCY_PWM, PIN_IN1);
	left_pwmIn2 = pwm_create(MCPWM0B, FREQUENCY_PWM, PIN_IN2);
	right_pwmIn1 = pwm_create(MCPWM1A, FREQUENCY_PWM, PIN_IN3);
	right_pwmIn2 = pwm_create(MCPWM1B, FREQUENCY_PWM, PIN_IN4);
	left_motor = motor_create(&left_pwmIn1, &left_pwmIn2);
	right_motor = motor_create(&right_pwmIn1, &right_pwmIn2);
	left_wheel = wheel_create(&left_motor, &left_encoder, WHEEL_RAD);
	right_wheel = wheel_create(&right_motor, &right_encoder, WHEEL_RAD);
	differential_init(&left_wheel, &right_wheel);

	queue_handle_ref = xQueueCreateStatic(
			1,
			sizeof(float),
			&(queue_storage_speed[0]),
			&xQueueBuffer
	);
	queue_handle_angular = xQueueCreateStatic(
			1,
			sizeof(float),
			&(queue_storage_angular[0]),
			&xQueueBufferAng
	);
	task_handle_dynamic = xTaskCreateStatic(
			dynamicController_task,
			"Controlador dinámico",
			STACK_SIZE,
			(void *)NULL,
			TASK_DINAMIC_PRIORITY,
			xStack,
			&xTaskBuffer
			);
	vTaskSuspend(task_handle_dynamic);
}

static void dynamicController_task(void * param)
{
	float buffer_speed = 0;
	float linear = 0;
	float angular= 0;
	while(1){
		if(pdTRUE == xQueueReceive(queue_handle_ref, &buffer_speed, 0)){
			differential_setLinearSpeed(buffer_speed);
		}
		if(pdTRUE == xQueueReceive(queue_handle_angular, &buffer_speed, 0)){
			differential_setAngularSpeed(buffer_speed);
		}
		differential_do();
		vTaskDelay(CONTROLLER_PERIOD_MS/portTICK_PERIOD_MS);
	}
}

void dynamicController_start(void)
{
	vTaskResume(task_handle_dynamic);
}

void dynamicController_stop(void)
{
	vTaskSuspend(task_handle_dynamic);
	differential_stop();
}