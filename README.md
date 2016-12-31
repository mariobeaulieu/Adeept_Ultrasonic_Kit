This is a repository containing improved exercices for the
Adeept Ultrasonic Kit used with the Raspberry Pi.

The improvements I did are extra features on the python versions,
and I have implemented pthreads on the C versions in order to
turn off the feature (sound, LED, or other) at the end of the
run.

To compile C versions on the Raspberry Pi:
 - Go to the directory containing the C code
 - gcc nameOfTheFile.c -l wiringPi -l pthread -o nameOfTheFile

Of course, the wiringPi must have been previously configured
(see git clone git://git.drogon.net/wiringPi )
