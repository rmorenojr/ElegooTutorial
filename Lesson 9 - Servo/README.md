# ElegooTutorial

## Lesson 9 – Servo and the Rotary Encoder

[YouTube Video](https://youtu.be/1GDnMXXSq18)

A beginner's guide to the Most Complete Starter Kit by Elegoo.  **Lesson 9 – Servo** 

Hello everyone, I'm Rick the Tech Enthusiast here with the next Lesson number 9 “Servo”.  This is the next lesson on my Arduino UNO Series covering the Most Complete Starter Kit by Elegoo.   I try to follow the tutorial closely, without overburdening the viewer with every detail, but I will point out any changes or corrections as I find them.

As mentioned before, I purchased this Elegoo starter kit.  I’m pronouncing it El-E-Goo, I hope that’s right (I sometimes slip and say El-a-Goo).  No, Elegoo isn't sponsoring me.  I just thought it would be fun to do a video of each Lesson as I was learning the Arduino environment. 

For this video, we’ll need a few things from your Elegoo Arduino kit.  I’ll list the items below.  In this lesson we’re going to learn about the servo SG90 provided in the kit and how to use them in our projects.  I step through the Elegoo provided code to explain how it makes this happen.  Then I develop a sketch to adjust the servo using a rotary encoder to find the 180 degree rotation end points in microseconds.  That way the servo can be properly setup in any future projects.  The adjustment circuit also included an OLDE and RGB LED.  I several setbacks, and discuss using interrupts, pin change interrupts and port registers to get the most out of the rotary encoder.   I hope it can be beneficial to someone with their project. 

## Parts you’ll need for the basic tutorial

* Elegoo Arduino UNO R3 board
* Servo SG90
* Three male-to-male jumpers

## The Servo Adjustment circuit parts

* Elegoo Arduino UNO R3 board
* Servo SG90
* Rotary Encoder module
* RGB LED
* OLED (purchase separately)
* Four 10K-ohm resistors
* Three 220-ohm resistors
* Two 22pF capacitors
* One 0.1 uF capacitor
* 5 female-to-male jumper wires
* 11 male-to-male jumper wires
* Various breadboard jumper wires
* Breadboard

The next lesson will be **Lesson 10 – Ultrasonic Sensor Module**  

## Links

This lesson’s sketch and associated drawings can be found at [Github](https://github.com/rmorenojr/ElegooTutorial)

<!-- LCD1602 Module with 3.3V Backlight 16x2 Character White on Blue Background by SunFounder -->
* <a target="_blank" href="https://www.amazon.com/gp/product/B071Y6JX3H/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B071Y6JX3H&linkCode=as2&tag=rmorenojr-20&linkId=81e6c312179be2b149bf6eeae0051f14">SunFounder LCD1602 Module with 3.3V Backlight for Arduino Uno R3 Mega2560 Raspberry Pi 16x2 Character White on Blue Background</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B071Y6JX3H" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
<!-- Passive Buzzers, Cylewet 10Pcs 5V 2 Terminals, Arduino (Pack of 10) on Amazon’s web site: -->
* <a target="_blank" href="https://www.amazon.com/gp/product/B01NCOXB2Q/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01NCOXB2Q&linkCode=as2&tag=rmorenojr-20&linkId=65e4660761a54140f64e954f1770006e">Cylewet 10Pcs 5V 2 Terminals Passive Electronic Alarm Buzzer Electromagnetic Beeper AC Impedance for Arduino (Pack of 10) CYT1008</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01NCOXB2Q" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
<!-- Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items) on Amazon’s web site: --> 
* <a target="_blank" href="https://www.amazon.com/gp/product/B01CZTLHGE/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01CZTLHGE&linkCode=as2&tag=rmorenojr-20&linkId=ac3601531bad9439bc32c77b0088b741">Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items)</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01CZTLHGE" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
* [Elegoo’s web site](https://www.elegoo.com/) - [Complete Starter Kit](https://www.elegoo.com/product/elegoo-uno-r3-project-complete-starter-kit/)

* [Fritzing Software](http://fritzing.org/download/)

* [Arduino Language Reference (English)](https://www.arduino.cc/reference/en/)
* [attachinterrupt](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
* [Switch Case control](https://www.arduino.cc/reference/en/language/structure/control-structure/switchcase/)
* [Pin Change Interrupt](http://playground.arduino.cc/Main/PinChangeInterrupt)
* [Port Registers](https://www.arduino.cc/en/Reference/PortManipulation)

* [How to Use a Rotary Encoder in an MCU-Based Project](https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/)
* [Efficiently Reading Quadrature with Interrupts](http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html) BY MAKEATRONICS
* [Tutorial: Using Servo Motors and Analog Inputs with the Arduino](https://www.youtube.com/watch?v=qatqVNh9uj4)
* [How Rotary Encoder Works and How To Use It with Arduino](https://www.youtube.com/watch?v=v4BbSzJ-hz4)
* [Rotary Encoder Tutorial with Arduino Code](https://www.youtube.com/watch?v=HQuLZHsGZdI)
* [Arduino UNO Tutorial 6 - Rotary Encoder](http://www.hobbytronics.co.uk/arduino-tutorial6-rotary-encoder)
* [Hands On Arduino 5A: SPI Communication](https://www.youtube.com/watch?v=Fj8IuivkQWI) BY Robert Paz
* [Interrupts](http://gammon.com.au/interrupts) BY Nick Gammon  

* Music provided by Free Music Archive, by artist Jahzzar - [Jahzzar_-_04_-_Magic_Mountain](http://freemusicarchive.org/music/Jahzzar/)

This is the ninth video on a new Arduino tutorial series. If you like the series, be sure to rate and subscribe.

Thanks for watching
