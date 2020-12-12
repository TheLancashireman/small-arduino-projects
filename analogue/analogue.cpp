/* analogue-synth - a midi interface for an analogue synthiesiser
 *
 * (c) 2020 David Haworth
 *
 *	This file is part of analogue.
 *
 *	analogue is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	analogue is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with analogue.  If not, see <http://www.gnu.org/licenses/>.
 * modular is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
*/
#include <Arduino.h>
#include "timestamp.h"

extern void init(void);

static void setup_t0(void);
static void setup_t1(void);

int main(void)
{
	init();
	setup_t0();
	setup_t1();
	sei();

	Serial.begin(115200);
	Serial.println("Hello world!");

	Serial.print("TCCR0A = ");
	Serial.println(TCCR0A);
	Serial.print("TCNT0 = ");
	Serial.println(TCNT0);
	Serial.print("TCNT0 = ");
	Serial.println(TCNT0);
	Serial.print("TCNT1 = ");
	Serial.println(TCNT1);
	Serial.print("sizeof(unsigned) = ");
	Serial.println(sizeof(unsigned));
	Serial.print("sizeof(unsigned long) = ");
	Serial.println(sizeof(unsigned long));
	Serial.print("sizeof(unsigned long long) = ");
	Serial.println(sizeof(unsigned long long));

	for (;;)
	{
		tick_delay(MICROS_TO_TICKS(250000));
		OCR0A = 0xe0;
		tick_delay(MICROS_TO_TICKS(250000));
		OCR0A = 0x20;
		OCR0B = 0xe0;
		tick_delay(MICROS_TO_TICKS(250000));
		OCR0A = 0xe0;
		tick_delay(MICROS_TO_TICKS(250000));
		OCR0A = 0x20;
		OCR0B = 0x20;
	}
}

static void setup_t0(void)
{
	GTCCR = 0;
	TCCR0A = 0xa3;				/* Fast PWM, non-inverting on outputs A and B */
	TCCR0B = 0x01;				/* Enable counter, prescaler = 1; WGM02 = 0 */
	TIMSK0 = 0;					/* Disable all the interrupts */
	TCNT0 = 0;
	OCR0A = 0x80;				/* 50% duty cycle */
	OCR0B = 0x40;				/* 25% duty cycle */
	TIFR0 = 0x07;				/* Clear all pending interrupts */

	DDRD |= (1<<5) | (1<<6);	/* Set PD5/OC0B and PD6/OC0A to output */
}

static void setup_t1(void)
{
	TCCR1A = 0;					/* Normal port operation */
	TCCR1B = 0x01;				/* Enable counter, prescaler = 1; WGM12/3 = 0 */
	TCCR1C = 0;					/* Probably not needed */
	TIMSK1 = 0;					/* Disable all the interrupts */
	TCNT1 = 0;
	TIFR1 = 0x27;				/* Clear all pending interrupts */
}
