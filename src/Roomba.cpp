#include <Roomba.h>

Roomba::Roomba(int pinRX, int pinTX, int pinDD) : link(pinRX, pinTX)
{
  rxdPin = pinRX;
  txdPin = pinTX;
  ddPin = pinDD;
}

void Roomba::resetbaud() {
	pinMode(ddPin, OUTPUT);
  link.begin(19200);
	wakeUp();
	start();
  baud(115200);
}


void Roomba::setup() {
	pinMode(ddPin, OUTPUT);
  link.begin(115200);
	wakeUp();
	start();
	control();
}

void Roomba::loop()
{
  updateSensors();
}

void Roomba::wakeUp()
{
	digitalWrite(ddPin, HIGH);
	delay(100);
	digitalWrite(ddPin, LOW);
	delay(500);
	digitalWrite(ddPin, HIGH);
	delay(100);
}

void Roomba::reset()
{
	digitalWrite(ddPin, LOW);
	delay(500);
	digitalWrite(ddPin, HIGH);
	delay(100);
}

void Roomba::start()
{
	link.write((byte)128);
	delay(100);
}

void Roomba::baud(long baudRate)
{
	link.write((byte)129); // Baud

	if(baudRate == 300) {
		link.write((byte)(byte)0);
	} else if(baudRate == 600) {
		link.write((byte)1);
	} else if(baudRate == 1200) {
		link.write((byte)2);
	} else if(baudRate == 2400) {
		link.write((byte)3);
	} else if(baudRate == 4800) {
		link.write((byte)4);
	} else if(baudRate == 9600) {
		link.write((byte)5);
	} else if(baudRate == 14400) {
		link.write((byte)6);
	} else if(baudRate == 19200) {
		link.write((byte)7);
	} else if(baudRate == 28800) {
		link.write((byte)8);
	} else if(baudRate == 38400) {
		link.write((byte)9);
	} else if(baudRate == 57600) {
		link.write((byte)10);
	} else if(baudRate == 115200) {
		link.write((byte)11);
	}
}

void Roomba::control()
{
	link.write((byte)130);
	delay(100);
}

void Roomba::safe()
{
	link.write((byte)131);
  delay(100);
}


void Roomba::full()
{
	link.write((byte)132);
	delay(100);
}

void Roomba::power()
{
	link.write((byte)133);
	delay(100);
}

void Roomba::spot()
{
	link.write((byte)134);
	delay(100);
}

void Roomba::clean()
{
	link.write((byte)135);
	delay(100);
}

void Roomba::max()
{
	link.write((byte)136);
	delay(100);
}

void Roomba::drive(int velocity, int radius)
{
	if (velocity >= 2000)
	velocity = 2000;
	if (velocity <= -2000)
	velocity = -2000;
	if (radius >= 500)
	radius = 500;
	if (radius <= -500)
	radius = -500;
	if (radius == 0 && velocity!= 0)
	radius = 32768;

	byte v_byte_high;
	byte v_byte_low;
	byte r_byte_high;
	byte r_byte_low;

	v_byte_low = velocity & 0xFF;
	v_byte_high = velocity >> 8;

	r_byte_low = radius & 0xFF;
	r_byte_high = radius >> 8;

	link.write((byte)137);
	link.write((byte)v_byte_high);
	link.write((byte)v_byte_low);
	link.write((byte)r_byte_high);
	link.write((byte)r_byte_low);
}

void Roomba::motors(bool mainBrush, bool vacuum, bool sideBrush)
{
	byte data = 0x00;
	data |= mainBrush && 0x04;
	data |= vacuum && 0x02;
	data |= sideBrush && 0x01;

	link.write((byte)138);
	link.write((byte)data);
	delay(100);
}

void Roomba::leds(bool statusGreen, bool statusRed, bool spotLed, bool cleanLed, bool maxLed, bool dirtDetectLed, byte powerColor, byte powerIntensity)
{
	byte ledBits = 0x00;
	ledBits |= (statusGreen ? 0x20 : 0x00);
	ledBits |= (statusRed ? 0x10 : 0x00);
	ledBits |= (spotLed ? 0x08 : 0x00);
	ledBits |= (cleanLed ? 0x04 : 0x00);
	ledBits |= (maxLed ? 0x02 : 0x00);
	ledBits |= (dirtDetectLed ? 0x01 : 0x00);

  link.write((byte)139);
	link.write((byte)ledBits);
	link.write((byte)powerColor);
	link.write((byte)powerIntensity);
	delay(100);
}

void Roomba::song()
{
	link.write((byte)140);
	link.write((byte)1);
	link.write((byte)12);
}

void Roomba::play(byte song)
{
	link.write((byte)141);
	link.write((byte)song);
	delay(100);
}

void Roomba::sensors(byte packetCode)
{
	link.write((byte)142);
	link.write((byte)packetCode);
	delay(100);
}

void Roomba::forceSeekingDock()
{
	link.write((byte)143);
	delay(100);
}

void Roomba::startCleaning()
{
	link.write((byte)138);
	link.write((byte)0x07);
}

void Roomba::stopCleaning()
{
	link.write((byte)138);
	link.write((byte)(byte)0x00);
}

void Roomba::goForward(int velocity)
{
  drive(abs(velocity), 0);
}

void Roomba::goBackward(int velocity)
{
  drive(-abs(velocity), 0);
}

void Roomba::spinLeft(int velocity)
{
  drive(abs(velocity), 1);
}

void Roomba::spinRight(int velocity)
{
  drive(abs(velocity), -1);
}

void Roomba::goForward()
{
	link.write((byte)137);
	link.write((byte)0x00);
	link.write((byte)0xC8);
	link.write((byte)0x80);
	link.write((byte)0x00);
}

void Roomba::goBackward()
{
	link.write((byte)137);
	link.write((byte)0xFF);
	link.write((byte)0x38);
	link.write((byte)0x80);
	link.write((byte)0x00);
}

void Roomba::spinLeft()
{
	link.write((byte)137);
	link.write((byte)0x00);
	link.write((byte)0xC8);
	link.write((byte)0x00);
	link.write((byte)0x01);
}

void Roomba::spinRight()
{
	link.write((byte)137);
	link.write((byte)0x00);
	link.write((byte)0xC8);
	link.write((byte)0xff);
	link.write((byte)0xff);
}

void Roomba::stopMoving()
{
	link.write((byte)137);
	link.write((byte)0x00);
	link.write((byte)0x00);
	link.write((byte)0x00);
	link.write((byte)0x00);
}

void Roomba::updateSensors()
{
	link.write((byte)142);
	link.write((byte)2);  // sensor packet 1, 10 bytes
	delay(100); // wait for sensors
	char i = 0;
	while(link.available()) {
		char c = link.read();
		if( c==-1 ) {
			/*
			for( int i=0; i<5; i ++ ) {   // say we had an error via the LED
				digitalWrite(ledPin, HIGH);
				delay(50);
				digitalWrite(ledPin, LOW);
				delay(50);
			}*/
		}
		sensorbytes[i++] = c;
	}
}
