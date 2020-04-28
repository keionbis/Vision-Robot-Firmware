/*
 * Robot.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: kbisland
 */

#include "Robot.h"




Robot::Robot() {

	//Setup Robot Wifi Name
	uint8_t mac[6];
	char macStr[18] = { 0 };
	esp_wifi_get_mac(WIFI_IF_STA, mac);
	sprintf(macStr, "%02X%02X", mac[4], mac[5]);
	ssid =  "esp32" + String(macStr);

	//Set Robots ID
	ID = String(macStr);


	//Start Semaphores
	WifiSemaphore = xSemaphoreCreateCounting(1024,0); // Max 1024 before give will return fail, init at 0
	LeftColorSensorSemaphore = xSemaphoreCreateCounting(1024,0);
	RightColorSensorSemaphore = xSemaphoreCreateCounting(1024,0);
	AccelerometerSemaphore = xSemaphoreCreateCounting(1024,0);


	//Start WiFi Timers
	xWifiTimer = xTimerCreate
			( /* Just a text name, not used by the RTOS
		                     kernel. */
					"WifiTimer",
					/* The timer period in ticks, must be
		                     greater than 0. */
					200,
					/* The timers will auto-reload themselves
		                     when they expire. */
					pdTRUE,
					/* The ID is used to store a count of the
		                     number of times the timer has expired, which
		                     is initialised to 0. */
					( void * ) 0,
					/* Each timer calls the same callback when
		                     it expires. */
					handleInterrupt1
			);

	//Start Sensor Timers
	xColorSensorLeft = xTimerCreate
			( /* Just a text name, not used by the RTOS
				                     kernel. */
					"ColorSensorLeftTimer",
					/* The timer period in ticks, must be
				                     greater than 0. */
					201,
					/* The timers will auto-reload themselves
				                     when they expire. */
					pdTRUE,
					/* The ID is used to store a count of the
				                     number of times the timer has expired, which
				                     is initialised to 0. */
					( void * ) 1,
					/* Each timer calls the same callback when
				                     it expires. */
					handleInterrupt2
			);
	xColorSensorRight = xTimerCreate
			( /* Just a text name, not used by the RTOS
					                     kernel. */
					"ColorSensorRightTimer",
					/* The timer period in ticks, must be
					                     greater than 0. */
					201,
					/* The timers will auto-reload themselves
					                     when they expire. */
					pdTRUE,
					/* The ID is used to store a count of the
					                     number of times the timer has expired, which
					                     is initialised to 0. */
					( void * ) 1,
					/* Each timer calls the same callback when
					                     it expires. */
					handleInterrupt3
			);
	xAccelerometer = xTimerCreate
			( /* Just a text name, not used by the RTOS
						                     kernel. */
					"AccelerometerTimer",
					/* The timer period in ticks, must be
						                     greater than 0. */
					201,
					/* The timers will auto-reload themselves
						                     when they expire. */
					pdTRUE,
					/* The ID is used to store a count of the
						                     number of times the timer has expired, which
						                     is initialised to 0. */
					( void * ) 1,
					/* Each timer calls the same callback when
						                     it expires. */
					handleInterrupt4
			);

	//Start Sensor Tasks
	xTaskCreate(
			WifiSwitcherTask, // Task function.
			"WifiSwitcherTask", // String with name of task.
			10000, // Stack size in words.
			NULL, // Parameter passed as input of the task
			1, // Priority of the task.
			NULL); // Task handle.

	xTaskCreate(
			LeftColorSensorTask, // Task function.
			"LeftColorSensorTask", // String with name of task.
			1000, // Stack size in words.
			NULL, // Parameter passed as input of the task
			1, // Priority of the task.
			NULL); // Task handle.
	xTaskCreate(
			RightColorSensorTask, // Task function.
			"RightColorSensorTask", // String with name of task.
			1000, // Stack size in words.
			NULL, // Parameter passed as input of the task
			1, // Priority of the task.
			NULL); // Task handle.
	xTaskCreate(
			AccelerometerTask, // Task function.
			"AccelerometerTask", // String with name of task.
			1000, // Stack size in words.
			NULL, // Parameter passed as input of the task
			1, // Priority of the task.
			NULL); // Task handle.

	xTimerStart(xWifiTimer, 1000);
	xTimerStart(xColorSensorLeft, 1000);
	xTimerStart(xColorSensorRight, 1000);
	xTimerStart(xAccelerometer, 1000);



}

void Robot::startUp() {
}

int Robot::getColorSensorData(int side, int param) {
}

void Robot::setRGBLED(int ledNum, int R, int G, int B) {
}

int Robot::getRGBLED(int ledNum, int color) {
}

void Robot::setMotorPowerState(int motor, int state) {
}

int Robot::getMotorPowerState(int motor) {
}

void Robot::setBottomLED(int LED, int state) {
}

int Robot::getBottomLEDState(int LED) {
}

void Robot::setmotorVelocity(int motor, float speed) {
}

int Robot::getmotorCount(int motor) {
}

int Robot::getAccelX() {
}

int Robot::getAccelY() {
}

int Robot::getAccelZ() {
}

float Robot::getorientation() {
}
