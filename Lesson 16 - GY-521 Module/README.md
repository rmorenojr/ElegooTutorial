# ElegooTutorial

## Lesson 16 – GY-521 Module & MPU-6050 

<!-- [[./octocat.png|alt=octocat]] -->
[![YouTube video](https://img.youtube.com/vi/T-D1KVIuvjA/0.jpg)](https://youtu.be/y5X2zwbO6e4)
[YouTube video](https://youtu.be/y5X2zwbO6e4)

GY-521-Module & MPU-6050.  Demonstrate the Elegoo sketch provided in the tutorial covering the GY-521-Module which uses a 6-axis, 6 DOF, MEMS MPU-6050.  A beginner's guide to the Most Complete Starter Kit by Elegoo.

Hello everyone, I'm Rick the Tech Enthusiast here with the next Elegoo Lesson.  This is the next lesson on my Arduino UNO Series covering the Most Complete Starter Kit by Elegoo.   I try to follow the included tutorial and will point out any changes or corrections as I find them.

As mentioned before, I purchased this Elegoo starter kit and Elegoo isn't sponsoring me.  I just thought it would be fun to do a video of each Lesson as I was learning the Arduino environment. 

We’ll need a few things from your Elegoo Arduino UNO kit.  I’ll list the items below.  In this lesson we’re going to check out the GY-521 Module.  I’ll step through the Elegoo provided tutorial and briefly explain how code makes this happen.  We’ll build and configure a simple circuit that is provided in the tutorial to demonstrate the functionality.  The sketch uses Wire.h Library and I2C to communicate to the module.  I hope you enjoy it. 

## Parts you’ll need for the tutorial

* Elegoo Arduino UNO R3 board
* GY-521 Module
* Four or five female-to-male jumper wires

The next lesson will be Lesson 17: HC-SR501 PIR Sensor

## Links

This lesson’s sketch and associated drawings can be found at [Github](https://github.com/rmorenojr/ElegooTutorial)

* [MAX7219 LED Dot Matrix Module 8 x 8 with 5pcs Dupont Line – Amazon](https://www.amazon.com/gp/product/B07775NFS1/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325)
* [DHT21 AM2301 Capacitive Digital Temperature and Humidity Sensor](https://www.amazon.com/AM2301-Capacitive-Digital-Temperature-Humidity/dp/B07543HBQ2) – amazon 
* [SODIAL(R) DHT22 AM2302 Digital Temperature and Humidity Sensor Module](https://www.amazon.com/SODIAL-Digital-Temperature-Humidity-Raspberry/dp/B0757FBWSB/ref=sr_1_19?s=industrial&ie=UTF8&qid=1520801854&sr=1-19&keywords=dht22)
* [DHT22 AM2302 Digital Temperature and Humidity Sensor Module](https://www.amazon.com/Digital-Temperature-Humidity-Arduino-Raspberry/dp/B01N6PB489/ref=sr_1_4?s=industrial&ie=UTF8&qid=1520801995&sr=1-4&keywords=dht22) - amazon 
<!-- LCD1602 Module with 3.3V Backlight 16x2 Character White on Blue Background by SunFounder -->
* <a target="_blank" href="https://www.amazon.com/gp/product/B071Y6JX3H/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B071Y6JX3H&linkCode=as2&tag=rmorenojr-20&linkId=81e6c312179be2b149bf6eeae0051f14">SunFounder LCD1602 Module with 3.3V Backlight for Arduino Uno R3 Mega2560 Raspberry Pi 16x2 Character White on Blue Background</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B071Y6JX3H" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
<!-- Passive Buzzers, Cylewet 10Pcs 5V 2 Terminals, Arduino (Pack of 10) on Amazon’s web site: -->
* <a target="_blank" href="https://www.amazon.com/gp/product/B01NCOXB2Q/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01NCOXB2Q&linkCode=as2&tag=rmorenojr-20&linkId=65e4660761a54140f64e954f1770006e">Cylewet 10Pcs 5V 2 Terminals Passive Electronic Alarm Buzzer Electromagnetic Beeper AC Impedance for Arduino (Pack of 10) CYT1008</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01NCOXB2Q" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
<!-- Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items) on Amazon’s web site: --> 
* <a target="_blank" href="https://www.amazon.com/gp/product/B01CZTLHGE/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01CZTLHGE&linkCode=as2&tag=rmorenojr-20&linkId=ac3601531bad9439bc32c77b0088b741">Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items)</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01CZTLHGE" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
* [Elegoo’s web site](https://www.elegoo.com/) - [Complete Starter Kit](https://www.elegoo.com/product/elegoo-uno-r3-project-complete-starter-kit/)

* [Fritzing Software](http://fritzing.org/download/)

* [Arduino Language Reference (English)](https://www.arduino.cc/reference/en/)
* [Wire.requestFrom()](https://www.arduino.cc/en/Reference/WireRequestFrom)
* [Wire.read()](https://www.arduino.cc/en/Reference/WireRead)
* [Wire.write()](https://www.arduino.cc/en/Reference/WireWrite)
* [Wire.beginTransmission()](https://www.arduino.cc/en/Reference/WireBeginTransmission)
* [Wire.endTransmission()](https://www.arduino.cc/en/Reference/WireEndTransmission)
* [Wire.requestFrom()](https://www.arduino.cc/en/Reference/WireRequestFrom)
* [Wire.available()](https://www.arduino.cc/en/Reference/WireAvailable)
* [TDK InvenSense MPU-6000 and MPU-6050](https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/)
* [Ep. 57 Arduino Accelerometer & Gyroscope Tutorial MPU-6050 6DOF Module by EEEnthusiast](https://www.youtube.com/watch?v=M9lZ5Qy5S2s)

* Music provided by Free Music Archive, by artist Jahzzar - [Jahzzar_-_01_-_What](http://freemusicarchive.org/music/Jahzzar/)

This is another video for my new Arduino tutorial series. If you like the series, be sure to rate and subscribe.

Thanks for watching
