#include <Arduino.h>
#include "thruster_can.h"
#include <Servo.h>

thrusterCAN can;
HardwareSerial serial(PA10, PA9, NC, NC);

Servo thruster1;
Servo thruster2;
Servo thruster3;
Servo thruster4;
Servo thruster5;
Servo thruster6;
Servo thruster7;
Servo *thrusters[] = {&thruster1, &thruster2, &thruster3, &thruster4, &thruster5, &thruster6, &thruster7};

int PWM_signal = 1500;

int pins[] = {PA0, PA1, PA2, PA3, PA6, PA7, PB0};

int mapToPWM(int input)
{

  const int PWM_CENTER = 1500;
  const int PWM_MIN = 1350;
  const int PWM_MAX = 1650;

  if (input <= 127)
  {
    // Forward thrust (0 maps to PWM_CENTER, 127 maps to PWM_MAX)
    return PWM_CENTER + (input * (PWM_MAX - PWM_CENTER)) / 127;
  }
  else
  {
    // Reverse thrust (128 maps to PWM_CENTER, 255 maps to PWM_MIN)
    return PWM_CENTER - ((input - 128) * (PWM_CENTER - PWM_MIN)) / 127;
  }
}

void setup()
{
  serial.begin(9600);
  can.begin();
  serial.println("CAN initialized");
  for (int i = 0; i < 7; i++)
  {
    thrusters[i]->attach(pins[i]);
    thrusters[i]->writeMicroseconds(PWM_signal);
  }

  delay(3000);
}

void loop()
{
  uint8_t rxData[8];
  if (can.receive_speeds(rxData))
  {
    serial.println("Data received");
    serial.println();
    for (int i = 0; i < 7; i += 1)
    {
      serial.printf("thruster %d speed: %u\n", i, rxData[i]);
      thrusters[i]->writeMicroseconds(mapToPWM(rxData[0]));
    }

    can.transmit_heartbeat();
    serial.println("");
  }
}