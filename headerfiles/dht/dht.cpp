#include "dht.h"

#define TIMEOUT 10000




int dht::read11(uint8_t pin)
{
	int rv = read(pin);
	if (rv != 0) return rv;

	
	humidity    = bits[0];
	temperature = bits[2];  
	
	uint8_t sum = bits[0] + bits[2]; 
	if (bits[4] != sum) return -1;

	return 0;
}


int dht::read22(uint8_t pin)
{
	
	int rv = read(pin);
	if (rv != 0) return rv;

	
	humidity    = word(bits[0], bits[1]) * 0.1;

	int sign = 1;
	if (bits[2] & 0x80) 
	{
		bits[2] = bits[2] & 0x7F;
		sign = -1;
	}
	temperature = sign * word(bits[2], bits[3]) * 0.1;



	uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
	if (bits[4] != sum) return -1;

	return 0;
}


int dht::read(uint8_t pin)
{
	
	uint8_t cnt = 7;
	uint8_t idx = 0;

	
	for (int i=0; i< 5; i++) bits[i] = 0;

	
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(20);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	pinMode(pin, INPUT);

	
	unsigned int loopCnt = TIMEOUT;
	while(digitalRead(pin) == LOW)
		if (loopCnt-- == 0) return -2;

	loopCnt = TIMEOUT;
	while(digitalRead(pin) == HIGH)
		if (loopCnt-- == 0) return -2;

	
	for (int i=0; i<40; i++)
	{
		loopCnt = TIMEOUT;
		while(digitalRead(pin) == LOW)
			if (loopCnt-- == 0) return -2;

		unsigned long t = micros();

		loopCnt = TIMEOUT;
		while(digitalRead(pin) == HIGH)
			if (loopCnt-- == 0) return -2;

		if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
		if (cnt == 0)  
		{
			cnt = 7;   
			idx++;      
		}
		else cnt--;
	}

	return 0;
}

