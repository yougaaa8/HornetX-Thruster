#pragma once

#include "eXoCAN.h"

// constants
const static int HEARTBEAT_ID = 0x30;
const static int ID_A = 0;
const static int MASK_A = 0x7ff;
const static int ID_B = 0x000;
const static int MASK_B = 0x0ff;

class thrusterCAN
{
private:
  eXoCAN _can;

public:
  void begin();
  bool receive_speeds(volatile uint8_t data[8]);
  bool transmit_heartbeat();
  bool transmit(int id, const void *data, int len);
};