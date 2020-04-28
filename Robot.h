/*
 * Robot.h
 *
 *  Created on: Apr 27, 2020
 *      Author: kbisland
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <Preferences.h>
#include <WiFi.h>
#include <esp_wifi.h>
class Robot {
public:
	Robot();
	virtual ~Robot();

	void startUp();

	int getColorSensorData(int side, int param);


	void setRGBLED(int ledNum, int R,int G, int B);
	int getRGBLED(int ledNum, int color);

	void setMotorPowerState(int motor, int state);
	int getMotorPowerState(int motor);

	void setBottomLED(int LED, int state);
	int getBottomLEDState(int LED);

	void setmotorVelocity(int motor, float speed);
	int getmotorCount(int motor);

	int getAccelX();
	int getAccelY();
	int getAccelZ();

	float getorientation();

	void SelfUpdate();

private:

	String ssid;
	const char *password = "12345678";
	String ID;

	float Accel[3];
	float orientation = 0;
	uint8_t RGBLeds[6][3];
	uint8_t motorStates[3];
	uint8_t bottomLedStates[3];
	uint32_t WheelSteps[2];
	uint16_t RGBWSensors[2][6];
	uint8_t wifiSwitchState = 0;




	SemaphoreHandle_t WifiSemaphore;
	SemaphoreHandle_t LeftColorSensorSemaphore;
	SemaphoreHandle_t RightColorSensorSemaphore;
	SemaphoreHandle_t AccelerometerSemaphore;

	int nTasks=4;
	TimerHandle_t xWifiTimer;
	TimerHandle_t xColorSensorLeft;
	TimerHandle_t xColorSensorRight;
	TimerHandle_t xAccelerometer;

	void handleInterrupt1(TimerHandle_t xTimer) {
		xSemaphoreGiveFromISR(WifiSemaphore, NULL);
		// can't use Serial in interrupt
		// Serial.println("Motion detected isr 1");

	}

	void handleInterrupt2(TimerHandle_t xTimer) {
		xSemaphoreGiveFromISR(LeftColorSensorSemaphore, NULL);
		//Serial.println("Motion detected isr 2");

	}
	void handleInterrupt3(TimerHandle_t xTimer) {
		xSemaphoreGiveFromISR(RightColorSensorSemaphore, NULL);
		//Serial.println("Motion detected isr 2");

	}
	void handleInterrupt4(TimerHandle_t xTimer) {
		xSemaphoreGiveFromISR(AccelerometerSemaphore, NULL);
		//Serial.println("Motion detected isr 2");

	}


	void LeftColorSensorTask( void * parameter )
	{
		/* Block for 1 second */
		const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
		while( true) {

			if(xSemaphoreTake(LeftColorSensorSemaphore, xDelay) && xSemaphoreTake(RightColorSensorSemaphore, xDelay)&& xSemaphoreTake(AccelerometerSemaphore, xDelay)){

			}
		}
		vTaskDelete( NULL );

	}

	void RightColorSensorTask( void * parameter)
	{
		/* Block for 1 second */
		const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
		while(true){
			if(xSemaphoreTake(LeftColorSensorSemaphore, xDelay)&&xSemaphoreTake(RightColorSensorSemaphore, xDelay)&& xSemaphoreTake(AccelerometerSemaphore, xDelay)){

			}
		}
		vTaskDelete( NULL );

	}

	void AccelerometerTask( void * parameter)
	{
		/* Block for 1 second */
		const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
		while(true){
			if(xSemaphoreTake(LeftColorSensorSemaphore, xDelay)&&xSemaphoreTake(RightColorSensorSemaphore, xDelay)&& xSemaphoreTake(AccelerometerSemaphore, xDelay)){

			}
		}
		vTaskDelete( NULL );

	}
	void WifiSwitcherTask( void * parameter)
	{
		/* Block for 1 second */
		const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
		while(true){
			if(xSemaphoreTake(WifiSemaphore, xDelay)){

			}
		}
		vTaskDelete( NULL );

	}
};

#endif /* ROBOT_H_ */
