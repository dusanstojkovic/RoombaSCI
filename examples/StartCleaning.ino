#include <Roomba.h>

Roomba roomba(5,6,7);

void setup()
{
  roomba.setup();

  roomba.startCleaning();
}

void loop()
{
  roomba.loop();
}
