/* infrared - decoding IR remote control handsets
 *
 * (c) 2020 David Haworth
 *
 * infrared is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * infrared is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with infrared.  If not, see <http://www.gnu.org/licenses/>.
 *
 * infrared is an Arduino sketch, written for an Arduino Nano
*/
#include <IRremote.h>

#define IR_PIN	7
IRrecv irrecv(IR_PIN);

/* setup() - standard Arduino "Init Task"
*/
void setup(void)
{
	decode_results results;
	char *typ;

	Serial.begin(115200);

	irrecv.enableIRIn();
	irrecv.blink13(true);

	for (;;)
	{
		if (irrecv.decode(&results))
		{
			switch (results.decode_type)
			{
			case NEC:			Serial.println("NEC");			break;
			case SONY:			Serial.println("SONY");			break;
			case RC5:			Serial.println("RC5");			break;
			case RC6:			Serial.println("RC6");			break;
			case DISH:			Serial.println("DISH");			break;
			case SHARP:			Serial.println("SHARP");		break;
			case JVC:			Serial.println("JVC");			break;
			case SANYO:			Serial.println("SANYO");		break;
			case MITSUBISHI:	Serial.println("MITSUBISHI");	break;
			case SAMSUNG:		Serial.println("SAMSUNG");		break;
			case LG:			Serial.println("LG");			break;
			case WHYNTER:		Serial.println("WHYNTER");		break;
			case AIWA_RC_T501:	Serial.println("AIWA_RC_T501");	break;
			case PANASONIC:		Serial.println("PANASONIC");	break;
			case DENON:			Serial.println("DENON");		break;
			default:			Serial.println("UNKNOWN");		break;
			}

        	Serial.println(results.value, HEX);
        	irrecv.resume();
		}
	}
}

/* loop() - standard Arduino "Background Task"
*/
void loop(void)
{
	/* Nothing to see here */
}

