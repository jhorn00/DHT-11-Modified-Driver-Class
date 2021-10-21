#include "lcd_horn.h"
#include "temp_horn.h"

int main()
{
	LCD_Thing lcd;
	lcd.writeStringToLine("DHT11 Reading...", LINE1);
	wiringPiSetup();
	std::vector<int> v = {0, 0, 0, 0, 0, 0};
	bool success = false;
	while(!success)
	{
		if(read_dht11_dat(v))
		{
			printf("%d, %d, %d, %d, %d, %d\n", v[0], v[1], v[2], v[3], v[4], v[5]);
			success = true;
		}
	}
	lcd.ClrLcd(true);
	std::string h = "Humidity: " + std::to_string(v[0]) + "." + std::to_string(v[1]) + "%";
	std::string t_c = "Temp: " + std::to_string(v[2]) + "." + std::to_string(v[3]) + "C";
	std::string t_f = "Temp: " + std::to_string(v[4]) + "." + std::to_string(v[5]) + "F";
	lcd.writeStringToLine(h, LINE1);
	lcd.writeStringToLine(t_c, LINE2);
	delay(3000);
	lcd.ClrLcd(true);
	lcd.writeStringToLine(t_f, LINE1);
	delay(3000);
	lcd.ClrLcd(true);
	delay(1000);
	lcd.ClrLcd(false);
	return 0;
}
