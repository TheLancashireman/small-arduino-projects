# analogue

An arduino sketch that drives one or more analogue outputs

This sketch builds on the "minimal" sketch.

## Caveat

To allow the PWM outputs to generate analogue levels with very little ripple (and whose
ripple is above normal hearing range), the timers are clocked at full speed. This means
that the normal Arduino timing functions like millis(), micros() and delay() aren't
available. If you adapt the sketch and attempt to use Arduino timing, you should get a linker
error.
