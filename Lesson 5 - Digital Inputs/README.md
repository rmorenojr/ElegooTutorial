# Lesson 5 – Digital Inputs

A beginner's guide to the Most Complete Starter Kit by Elegoo.  Lesson 5 – Digital Inputs

Video located here: https://www.youtube.com/watch?v=rbeHQ80dux8

Hello everyone, I'm Rick the Tech Enthusiast again, with the next Lesson number 5 “Digital Inputs”.  This is the next lesson on my Arduino UNO Series covering the Most Complete Starter Kit by Elegoo.   I try to follow the tutorial closely, without overburdening the viewer with every detail, but I will point out any changes or corrections as I find them.

As mentioned before, I purchased this Elegoo starter kit.  I’m pronouncing it El-E-Goo, I hope that’s right (I sometimes slip and say El-a-Goo).  No, Elegoo isn't sponsoring me.  I just thought it would be fun to do a video of each Lesson as I was learning the Arduino environment. 

For this video, we’ll need a few things from your Elegoo Arduino kit.  I’ll list the items below.  In this lesson we’re going to learn how to include digital inputs to your circuit using a couple of pushbutton switches.  I step through the Elegoo provided code to explain how it makes this happen.  Then, like before, I expand on the idea with a revised sketch.  I wanted to provide a sketch that only uses a single button to turn on and off the LED.  I also introduce the idea of debouncing the button input and how to handle it with code.  And there more.  I include yet another sketch, and this time it’s a circuit that turns on, and automatically goes to sleep when done.  The watchdog timer is included to periodically wake the board.  And a manual method in included to wake the circuit using a button and assigning to an Arduino interrupt.  All while trying to achieve a very low power, deep sleep, mode.  I got some great ideas from Kevin Darrah and Lynda.com

Of course, I’ve added Serial.begin and Serial.print statements to view and diagnose the code in the Serial Monitor.  I hope you like the Lesson, it was a lot of fun to make.

Parts you’ll need:

Arduino UNO R3 board
5mm LED
220 ohm resistor
Two pushbutton switches
Seven male-to-male wire jumpers
And the breadboard

I should also mention that Kevin Darrah has a great video for the low power, deep sleep mode for the Arduino UNO.  You should check it out.
https://www.youtube.com/watch?v=urLSDi7SD8M

The next lesson will be Lesson 6 – Active Buzzer  

Links:

<a target="_blank" href="https://www.amazon.com/gp/product/B01CZTLHGE/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01CZTLHGE&linkCode=as2&tag=rmorenojr-20&linkId=ac3601531bad9439bc32c77b0088b741">Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items)</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01CZTLHGE" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />

Elegoo’s web site:
https://www.elegoo.com/
https://www.elegoo.com/product/elegoo-uno-r3-project-complete-starter-kit/

Frtizing Software:
http://fritzing.org/download/

Language Reference (English):
https://www.arduino.cc/reference/en/
https//www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

Applied Electronics – Lynda.com
https://www.youtube.com/watch?v=QslLAPNSEFc
 
educ8s.tv
https://www.youtube.com/watch?v=jYOYgU2vlSE

Kevin Darrah - Low Power Arduino! Deep Sleep Tutorial
https://www.youtube.com/watch?v=urLSDi7SD8M

This is the sixth video on a new Arduino tutorial series. If you like the series, be sure to rate and subscribe.

Thanks for watching 
