#ifndef roomba_h
#define roomba_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#undef max

class Roomba
{
private:
  int rxdPin;
  int txdPin;
  int ddPin;

  SoftwareSerial link;

  char sensorbytes[10];
  //#define bumpright (sensorbytes[0] & 0x01)
  //#define bumpleft  (sensorbytes[0] & 0x02)

  void updateSensors();

public:

  Roomba(int pinRX, int pinTX, int pinDD);

  bool begin();
  void resetbaud();
  void setup();
  void loop();

  void start();
  void baud(long baudRate);
  void wakeUp();
  void reset();


  void control();
  void safe();
  void full();

  void power();
  void spot();
  void clean();
  void max();

  void drive(int velocity, int radius);
  void motors(bool mainBrush, bool vacuum, bool sideBrush);
  void leds(bool statusGreen, bool statusRed, bool spotLed, bool cleanLed, bool maxLed, bool dirtDetectLed, byte powerColor, byte powerIntensity);
  void song();
  void play(byte song);
  void sensors(byte packetCode);
  void forceSeekingDock();

  void startCleaning();
  void stopCleaning();

  void goForward(int velocity);
  void goBackward(int velocity);
  void spinLeft(int velocity);
  void spinRight(int velocity);

  void goForward();
  void goBackward();
  void spinLeft();
  void spinRight();

  void stopMoving();
};

#endif
