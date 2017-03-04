# Analyzing weather station signal


This is my very first RTL-SDR project. I watched some cool videos about what can be done with RTL-SDR dongle and decided to buy one and try it out. Only after I installed and tested it, I realized that father has weather station, which gets data over the air from reciever, installed in the back of the house. Time to start analyzing :)

First, what weather station this is, what frequency does it use? I found out that it's Alecto v1 weather station and that it works on 433 MHz. This is commonly used frequency in Europe for home automation and similar systems. At the begining I just wanted to find out how it works. During googling I found out that one can actually record the signal and play it back! For this you need transmitter on 433 MZh, for which you can use HackRF or Yardstick One or something similar. Or you can use Arduino with cheap 433 MHz transmitter, that you can buy for few Euros. Way to go!

Enjoy!
