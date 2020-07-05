/* spi - controllign 7-segment LED display with SPI and two 74HC595
 *
 * (c) 2020 David Haworth
 *
 * spi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * spi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with spi.  If not, see <http://www.gnu.org/licenses/>.
 *
 * spi is an Arduino sketch, written for an Arduino Nano
*/

/* URLs about strange problems with 74HC595
 *
 * https://forum.arduino.cc/index.php?topic=11229.0
 * https://forum.arduino.cc/index.php?topic=630186.0
 * https://electronics.stackexchange.com/questions/426608/74hc595-sinking-not-sourcing
 * https://arduino.stackexchange.com/questions/60347/74hc595-shift-register-not-working
 * https://e2e.ti.com/support/logic/f/151/t/828246?SN74HC595-Are-my-chip-is-defictive-
 *  ---> posted related query to the ti one.
 *
 * http://www.davidmpye.com/index.php/2019/01/28/fake-chips/
 *  ---> chips might be fake
*/
#include <SPI.h>

#define CLK_PIN		13
#define DATA_PIN	11
#define LATCH_PIN	10
#define DELAY_TIME	10

#define TEST_CLOCK_DISPLAY	1	/* On the clock display, bit 0 is the DP, bit 1 is a ... */

const unsigned char digit_to_7seg[16] = {	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
											0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71 };

/* setup() - standard Arduino "Init Task"
*/
void setup(void)
{
	pinMode(LATCH_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
	pinMode(DATA_PIN, OUTPUT);
	digitalWrite(LATCH_PIN, LOW);	/* Transfers on a rising edge */
	digitalWrite(CLK_PIN, LOW);		/* Transfers on a rising edge */
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
#if 0
	unsigned long t = millis();
	unsigned long t1;
	unsigned char digit[5];
	char dig = 0;
	char c1 = 0;

	digit[0] = 0;
	digit[1] = 0;
	digit[2] = 0;
	digit[3] = 0;
	digit[4] = 1;
#endif

	for (;;)
	{
#if 1
		for ( int i = 0; i < 16; i++ )
		{
			unsigned char b = ~digit_to_7seg[i];
#if TEST_CLOCK_DISPLAY
			b = (b << 1) | (((unsigned char)i) & 1);
#endif
			SPI.transfer(b);
			digitalWrite(LATCH_PIN, HIGH);
			digitalWrite(LATCH_PIN, LOW);
			delay(1000);
		}
#elif 1
		for ( int i = 0; i < 16; i++ )
		{
			unsigned char b = ~digit_to_7seg[i];
			shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, b);
			digitalWrite(LATCH_PIN, HIGH);
			digitalWrite(LATCH_PIN, LOW);
			delay(1000);
		}

#elif 1
		for ( int i = 0; i < 16; i++ )
		{
			unsigned char b = digit_to_7seg[i];
			for ( int j = 0; j < 8; j++ )
			{
				digitalWrite(DATA_PIN, ((b&0x80)==0) ? HIGH : LOW);
				digitalWrite(CLK_PIN, HIGH);
				digitalWrite(CLK_PIN, LOW);
				b = b << 1;
			}
			digitalWrite(LATCH_PIN, HIGH);
			digitalWrite(LATCH_PIN, LOW);
			delay(1000);
		}
#elif 1
		digitalWrite(DATA_PIN, HIGH);
		delay(1000);
		digitalWrite(CLK_PIN, HIGH);
		delay(1000);
		digitalWrite(CLK_PIN, LOW);
		digitalWrite(LATCH_PIN, HIGH);
		delay(1000);
		digitalWrite(LATCH_PIN, LOW);

		digitalWrite(DATA_PIN, LOW);
		delay(1000);
		digitalWrite(CLK_PIN, HIGH);
		delay(1000);
		digitalWrite(CLK_PIN, LOW);
		digitalWrite(LATCH_PIN, HIGH);
		delay(1000);
		digitalWrite(LATCH_PIN, LOW);
#else
		do
		{
			t1 = millis();
		} while ( (t1 - t) < DELAY_TIME );
		t = t1;
		delay(1000);

		dig++;
		if ( dig > 4 )	dig = 0;

		c1++;
		if ( c1 >= (1000/DELAY_TIME) )
		{
			/* Once per second
			*/
			digit[4] ^= 0x05;	/* Flip the colon */
			digit[0]++;
			if ( digit[0] > 15 )
			{
				digit[0] = 0;
				digit[1]++;
				if ( digit[1] > 15 )
				{
					digit[1] = 0;
					digit[2]++;
					if ( digit[2] > 15 )
					{
						digit[2] = 0;
						digit[3]++;
						if ( digit[3] > 15 )
						{
							digit[3] = 0;
							/* No more digits */
						}
					}
				}
			}
		}
#endif
	}
}

/* loop() - standard Arduino "Background Task"
*/
void loop(void)
{
	/* Nothing to see here */
}
