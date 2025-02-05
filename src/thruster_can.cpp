#include "thruster_can.h"

/**
 * Starts the can bus with RX on A11 and TX on A12
 */
void thrusterCAN::begin()
{
  _can.begin(STD_ID_LEN, BR500K, PORTB_8_9_XCVR);
  _can.filterMask16Init(0, ID_A, MASK_A, ID_B, MASK_B);
}

/**
 * Checks for CAN messages, if a message with length of 7 is received,
 * updates array passed in and returns true
 */
bool thrusterCAN::receive_speeds(volatile uint8_t data[8])
{
  int len, id, fltIdx;
  len = _can.receive(id, fltIdx, data);
  return len == 7;
}

/**
 * transmits heartbeat message to SBC
 */
bool thrusterCAN::transmit_heartbeat()
{
  uint8_t txData[1] = {0x00};
  return _can.transmit(HEARTBEAT_ID, txData, 1);
}

bool thrusterCAN::transmit(int id, const void *data, int len)
{
  return _can.transmit(id, data, len);
}