# ElegooTutorial

## Lesson 7 – Passive Buzzer and Happy Birthday, Imperial March, and Super Mario melody player with 3-Way Polyphony

[YouTube video](https://youtu.be/X-3AoN8Subk)

A beginner's guide to the Most Complete Starter Kit by Elegoo.  **Lesson 7 – Passive Buzzer**

Hello everyone, I'm Rick the Tech Enthusiast here with the next Lesson number 7 “Passive Buzzer”.  This is the next lesson on my Arduino UNO Series covering the Most Complete Starter Kit by Elegoo.   I try to follow the tutorial closely, without overburdening the viewer with every detail, but I will point out any changes or corrections as I find them.

As mentioned before, I purchased this Elegoo starter kit.  I’m pronouncing it El-E-Goo, I hope that’s right (I sometimes slip and say El-a-Goo).  No, Elegoo isn't sponsoring me.  I just thought it would be fun to do a video of each Lesson as I was learning the Arduino environment. 

For this video, we’ll need a few things from your Elegoo Arduino kit.  I’ll list the items below.  In this lesson we’re going to learn what a passive buzzer is and how to use them in our projects.  I step through the Elegoo provided code to explain how it makes this happen.  I also ran into some problems with what was recommended from piezo manufacturers, and other web sites, with what’s provided in the tutorial.  So I explain my findings, and restart the tutorial.  I even revise the provided sketch to include a scale that plays up and down.  For bonus material, I created a music player inspired by the Happy Birthday Melody for the Nano with 3-way Polyphony by Liss.   I use the prototype board and mini breadboard that’s included in the kit.  I did have to purchase additional passive buzzers to make this work (links below).  I quickly take you through the changes in the code and play the Happy Birthday melody in 3-Way Polyphony.  I repeated this for the Star Wars Imperial March (not Polyphony), and Super Mario theme melodies.  Sorry, I did ramble a few times.  But overall, I had a blast and maybe I’ll revisit the project in the future. 

I hope you like the Lesson, it was a lot of fun to make.

## Parts you’ll need for the basic tutorial

* Arduino UNO R3 board
* Passive Buzzer (that the one without a white sticker on it – you’ll need two more if you want to do the bonus sketch)
* One diode (5 are provided in the kit)
* One 100-ohm resistor
* Several jumpers
* Breadboard

## The Bonus Music Player parts

* Arduino UNO R3 board
* Three passive buzzers (links are provided below)
* Three 100-ohm resistors
* Three 1N4007 diode 
* 5mm Red LED
* 5mm Yellow LED
* 5mm Green LED
* Three 220-ohm resistors
* Various jumper wires
* Mini breadboard
* Elegoo prototype board

The next lesson will be **Lesson 8 – Tilt Ball Switch and the Magic 8-Ball**  

## Links

This lesson’s sketch and associated drawings can be found at [Github](https://github.com/rmorenojr/ElegooTutorial)
 
<!-- Passive Buzzers, Cylewet 10Pcs 5V 2 Terminals, Arduino (Pack of 10) on Amazon’s web site: -->
* <a target="_blank" href="https://www.amazon.com/gp/product/B01NCOXB2Q/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01NCOXB2Q&linkCode=as2&tag=rmorenojr-20&linkId=65e4660761a54140f64e954f1770006e">Cylewet 10Pcs 5V 2 Terminals Passive Electronic Alarm Buzzer Electromagnetic Beeper AC Impedance for Arduino (Pack of 10) CYT1008</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01NCOXB2Q" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
<!-- Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items) on Amazon’s web site: --> 
* <a target="_blank" href="https://www.amazon.com/gp/product/B01CZTLHGE/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B01CZTLHGE&linkCode=as2&tag=rmorenojr-20&linkId=ac3601531bad9439bc32c77b0088b741">Elegoo EL-KIT-001 UNO R3 Project Complete Starter Kit with Tutorial for Arduino (63 Items)</a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rmorenojr-20&l=am2&o=1&a=B01CZTLHGE" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />
* [Elegoo’s web site](https://www.elegoo.com/) - [Complete Starter Kit](https://www.elegoo.com/product/elegoo-uno-r3-project-complete-starter-kit/)

* [Fritzing Software](http://fritzing.org/download/)

* [Arduino Language Reference (English)](https://www.arduino.cc/reference/en/)
* [attachinterrupt](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
* [Arduino tone() function](https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/)
* [Arduino Playing tones on Multiple outputs using the tone() function](https://www.arduino.cc/en/Tutorial/ToneMultiple)

* [Tone.h library](https://github.com/bhagman/Tone)
* [An easy way to make noise with Arduino using tone()](https://www.youtube.com/watch?v=1_LMAgO14z0&t) - by Programming Electronics Academy
* Great piezo buzzer explanation [An easy way to make noise with Arduino using tone()](https://www.youtube.com/watch?v=1_LMAgO14z0&t) - Programming Electronics Academy
* [Happy Birthday Melody on Arduino Nano With 3-way Polyphony](https://www.hackster.io/liss/happy-birthday-melody-on-arduino-nano-with-3-way-polyphony-c80c31) by Liss
* [Arduino + Star Wars Imperial March (Buzzer/Piezo)](https://www.youtube.com/watch?v=83xHpj3PstI) by Profe-Electro
* [Super Mario Bros. Overworld Theme (old version)](https://pastebin.com/AKR5VL87) by Ignacio Castillo Ãlvarez
* [Overworld / Main Theme](http://www.mariopiano.com/midi-sound-file-overworld-main-theme.html) by mariopiano.com

* Music provided by Free Music Archive, by artist Jahzzar - [Jahzzar_-_12_-_Birthday_Cake](http://freemusicarchive.org/music/Jahzzar/)

This is another video for my new Arduino tutorial series. If you like the series, be sure to rate and subscribe.

Thanks for watching
