#include "dynamic_controller.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "differential.h"
#include "pwm.h"
#include "motor.h"
#include "encoder.h"
#include "tick_counter.h"
#include "pid.h"
#include "point_controller.h"

//#include "esp_log.h"
//static const char * tag = "Dynamic-speed";

#define STACK_SIZE 2000
#define TASK_DINAMIC_PRIORITY 2

//task structures
StaticTask_t xTaskBuffer;
StackType_t xStack[STACK_SIZE];
static TaskHandle_t task_handle_dynamic;
//queue structures
StaticQueue_t xQueueBufferSpeeds;
QueueHandle_t queue_handle_speeds;
static uint8_t queue_storage_speeds[sizeof(Speeds)];
StaticQueue_t xQueueBufferKp;
QueueHandle_t queue_handle_kp;
static uint8_t queue_storage_kp[sizeof(float)];
StaticQueue_t xQueueBufferKi;
QueueHandle_t queue_handle_ki;
static uint8_t queue_storage_ki[sizeof(float)];

#define FREQUENCY_PWM 1000
#define TICKS_PER_REV 213
#define CONTROLLER_PERIOD 0.1
#define CONTROLLER_PERIOD_MS (CONTROLLER_PERIOD*1000)
#define PIN_IN1 25
#define PIN_IN2 26
#define PIN_IN3 27
#define PIN_IN4 12
#define LEFT_ENCODER_PHASEA_PIN 33
#define LEFT_ENCODER_PHASEB_PIN 32
#define RIGHT_ENCODER_PHASEA_PIN 16
#define RIGHT_ENCODER_PHASEB_PIN 17
#define WHEEL_RAD 3.5f

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
static Pid left_pid;
static Pid right_pid;

static void init_structures(void);
static void init_queues(void);
static void dynamicController_task(void * param);
static void newCommands(void);
static void init_task(void);

void dynamicController_init(void)
{
	init_structures();
	init_queues();
	init_task();
}

static void init_structures(void)
{
	left_tick = tickCounter_create(PCNT_UNIT_0, LEFT_ENCODER_PHASEA_PIN, 
			LEFT_ENCODER_PHASEB_PIN);
	right_tick = tickCounter_create(PCNT_UNIT_1, RIGHT_ENCODER_PHASEB_PIN, 
			RIGHT_ENCODER_PHASEA_PIN);
	left_encoder = encoder_create(&left_tick, TICKS_PER_REV, CONTROLLER_PERIOD);
	right_encoder = encoder_create(&right_tick, TICKS_PER_REV, CONTROLLER_PERIOD);
	left_pwmIn1 = pwm_create(MCPWM0A, FREQUENCY_PWM, PIN_IN1);
	left_pwmIn2 = pwm_create(MCPWM0B, FREQUENCY_PWM, PIN_IN2);
	right_pwmIn1 = pwm_create(MCPWM1A, FREQUENCY_PWM, PIN_IN3);
	right_pwmIn2 = pwm_create(MCPWM1B, FREQUENCY_PWM, PIN_IN4);
	left_motor = motor_create(&left_pwmIn1, &left_pwmIn2);
	right_motor = motor_create(&right_pwmIn1, &right_pwmIn2);
	left_wheel = wheel_create(&left_motor, &left_encoder, WHEEL_RAD);
	right_wheel = wheel_create(&right_motor, &right_encoder, WHEEL_RAD);
	left_pid = pid_create();
	right_pid = pid_create();
	differential_init(&left_wheel, &right_wheel, &left_pid, &right_pid);
}

static void init_queues(void)
{
	queue_handle_speeds = xQueueCreateStatic(
			1,
			sizeof(Speeds),
			&(queue_storage_speeds[0]),
			&xQueueBufferSpeeds
	);
	queue_handle_kp = xQueueCreateStatic(
			1,
			sizeof(float),
			&(queue_storage_kp[0]),
			&xQueueBufferKp
	);
	queue_handle_ki = xQueueCreateStatic(
			1,
			sizeof(float),
			&(queue_storage_ki[0]),
			&xQueueBufferKi
	);
}

static void init_task(void)
{
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
	uint8_t point_counter = 0;
	while(1){
		newCommands();
		differential_do();
		if(point_counter == 10){
			Speeds speeds = differential_speeds();
			pointController_setSpeeds(speeds);
			point_counter = 0;
		}
		point_counter ++;
		vTaskDelay(CONTROLLER_PERIOD_MS/portTICK_PERIOD_MS);
	}
}

static void newCommands(void)
{
	Speeds buffer_speeds = {};
	if(pdTRUE == xQueueReceive(queue_handle_speeds, &buffer_speeds, 0)){
		differential_setSpeeds(buffer_speeds.linear, 
				buffer_speeds.angular);
	}
	float buffer_speed = 0;
	if(pdTRUE == xQueueReceive(queue_handle_kp, &buffer_speed, 0)){
		differential_setKp(buffer_speed);
	}
	if(pdTRUE == xQueueReceive(queue_handle_ki, &buffer_speed, 0)){
		differential_setKi(buffer_speed);
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

void dynamicController_setKp(uint8_t motor, float kp)
{
	xQueueSend(queue_handle_kp, &kp, 0);
}

void dynamicController_setKi(uint8_t motor, float ki)
{
	xQueueSend(queue_handle_ki, &ki, 0);
}

void dynamicController_setSpeeds(Speeds speeds)
{
	xQueueSend(queue_handle_speeds, &speeds, 0);
}
