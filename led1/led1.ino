/* led1 - a two-colour LED project
 *
 * (c) 2020 David Haworth
 *
 * led1 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * led1 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with led1.  If not, see <http://www.gnu.org/licenses/>.
 *
 * led1 is an Arduino sketch, written for an Arduino Nano
*/

/* MODE = 0 - 2-colour switching
 * MODE = 1 - 2-colour fading
 * MODE = 2 - 3-colour fading
 * MODE = 3 - 3-colour individual switching
 * MODE = 4 - cross-fading
*/
#define MODE		4

/* Pin numbers
*/
#define LED_1	2
#define LED_2	3
#define LED_3	4

void fade_up(int pin);
void fade_down(int pin);
void fade_up_down(int up_pin, int down_pin);
void udelay(unsigned us);

/* setup() - standard Arduino "Init Task"
*/
void setup(void)
{
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	digitalWrite(LED_1, LOW);
	digitalWrite(LED_2, LOW);
	digitalWrite(LED_3, LOW);

	for (;;)
	{
#if MODE==0
		/* Switch colour every second */
		delay(1000);
		digitalWrite(LED_1, HIGH);
		delay(1000);
		digitalWrite(LED_2, HIGH);
		delay(1000);
		digitalWrite(LED_1, LOW);
		delay(1000);
		digitalWrite(LED_2, LOW);
#elif MODE==1
		/* Gradually ramp colour intensity up and down. Approx 10 secs for each fade. */
		fade_up(LED_1);
		fade_up(LED_2);
		fade_down(LED_1);
		fade_down(LED_2);
#elif MODE==2
		/* Gradually ramp colour intensity up and down. Approx 10 secs for each fade. Gray code! */
		delay(1000);
		fade_up(LED_1);
		delay(1000);
		fade_up(LED_2);
		delay(1000);
		fade_down(LED_1);
		delay(1000);
		fade_up(LED_3);
		delay(1000);
		fade_up(LED_1);
		delay(1000);
		fade_down(LED_2);
		delay(1000);
		fade_down(LED_1);
		delay(1000);
		fade_down(LED_3);
#elif MODE==3
		/* Switch colour every second */
		digitalWrite(LED_1, HIGH);
		delay(1000);
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_2, HIGH);
		delay(1000);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_3, HIGH);
		delay(1000);
		digitalWrite(LED_3, LOW);
#elif MODE==4
		/* Gradually ramp colour intensity up and down simultaneously. Approx 10 secs for each fade. */
		delay(1000);
		fade_up_down(LED_2, LED_1);
		delay(1000);
		fade_up_down(LED_3, LED_2);
		delay(1000);
		fade_up_down(LED_1, LED_3);
#else
#error "Unknown mode"
		delay(1000);
		digitalWrite(LED_3, LOW);
#endif
	}
}

/* loop() - standard Arduino "Background Task"
*/
void loop(void)
{
	/* Nothing to see here */
}

void fade_up(int pin)
{
	for (unsigned i = 100; i < 10000; i += 100 )
	{
		for ( int j = 0; j < 10; j++ )
		{
			digitalWrite(pin, HIGH);
			udelay(i);
			digitalWrite(pin, LOW);
			udelay(10000 - i);
		}
	}
	digitalWrite(pin, HIGH);
}

void fade_down(int pin)
{
	for (unsigned i = 100; i < 10000; i += 100 )
	{
		for ( int j = 0; j < 10; j++ )
		{
			digitalWrite(pin, LOW);
			udelay(i);
			digitalWrite(pin, HIGH);
			udelay(10000 - i);
		}
	}
	digitalWrite(pin, LOW);
}

void fade_up_down(int up_pin, int down_pin)
{
	for (unsigned i = 100; i < 10000; i += 100 )
	{
		for ( int j = 0; j < 10; j++ )
		{
			digitalWrite(up_pin, HIGH);
			digitalWrite(down_pin, LOW);
			udelay(i);
			digitalWrite(up_pin, LOW);
			digitalWrite(down_pin, HIGH);
			udelay(10000 - i);
		}
	}
	digitalWrite(up_pin, HIGH);
	digitalWrite(down_pin, LOW);
}

void udelay(unsigned us)
{
	unsigned long start = micros();

	while ( (micros() - start) < us )	/* Overflow/underflow doesn't matter */
	{
		/* Twiddle thumbs */
	}
}
