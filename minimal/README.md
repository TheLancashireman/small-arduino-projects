# minimal

An arduino sketch that gets rid of the arduino timer interrupt and therefore
kills millis() and micros() and related functions.

## Why?

Why would anyone want to do that? One reason would be to use the timers running at full speed
so that the PWM outputs can be used to create analogue signals more easily. The low-pass
filtering won't introduce audible effects like portamento when the output is used to drive a
VCO, for example.

## Explanation

In the Arduino library, the main() function calls init(), initVariant(), optionally USBDevice.attach(),
setup() and then enters an endless loop that calls loop() and optionally serialEventRun().

initVariant() is an empty function in main.cpp. It's declared "weak" so I guess it can be provided
as an optional extra for some hardware types.

USBDevice.attach() is only called if USBCON is defined, so this is possibly only for controllers with
USB hardware.

serialEventRun() appears to be unused anywhere. It might be something that the sketch can supply.

During the build process, the whole Arduino infrastructure is compiled and placed in a library. However,
your sketch (and any other .cpp files in the same directory) get compiled and passed to the linker
on the command line. This means that functions in your own files take precedence over functions in
the library.

So if the sketch contains the main(), the standard Arduino main() function is left out and you
don't need to provide setup() and loop(). However, tne initialisation done by init() and
initVariant() doesn't happen.

Don't be tempted to call the Arduino init() though, because that will pull in the entire wiring.c file
and with it the interrupt handler for timer0 overflow. If you disable the timer0 overflow interrupt the
handler never gets called, so having it present just wastes space, and you might not be able to provide
your own.

So you need to provide your own function that re-implements the parts of the Arduino init() that you need.
It's best to call your function init() rather than (say) my_init(). That way, if your sketch inadvertently
calls millis() or some related function you get a linker error because init() is defined twice.

This sketch does exactly that. It doesn't need any of the initialisation done in the standard
wiring.c implementation of init, so it doesn't do it. However, the Serial functions need to have
interrupts enabled - so we do that directly in main().

There's a copy of wiring.c from Arduino 1.6.8 here for reference. It's called wiring.c.reference to prevent
the build process from finding and compiling it.

## Disclaimer

I use the command-line build environment. If you use the GUI IDE you might have different experiences.

