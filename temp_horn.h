#pragma once
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#define MAXTIMINGS	85
#define DHTPIN		7

bool read_dht11_dat(vector<int>& dht11_dat)
{
	if (dht11_dat.size() != 5) {
		printf("DHT-11 Error: Invalid container size\n");
		return;
	}
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;
	float	f;

	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	pinMode(DHTPIN, OUTPUT);
	digitalWrite(DHTPIN, LOW);
	delay(18);
	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(40);
	pinMode(DHTPIN, INPUT);

	for (i = 0; i < MAXTIMINGS; i++)
	{
		counter = 0;
		while (digitalRead(DHTPIN) == laststate)
		{
			counter++;
			delayMicroseconds(1);
			if (counter == 255)
			{
				break;
			}
		}
		laststate = digitalRead(DHTPIN);

		if (counter == 255)
			break;

		if ((i >= 4) && (i % 2 == 0))
		{
			dht11_dat[j / 8] <<= 1;
			if (counter > 50)
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}

	if ((j >= 40) &&
		(dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)))
	{
		f = dht11_dat[2] * 9. / 5. + 32;
		printf("Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
			dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f);
		dht11_dat[4] = f;
		//success
		return true;
	}
	else {
		printf("Data not good, skip\n");
		dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
		//failure
		return false;
	}
}
