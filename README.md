pinoccio-photosynthesis
=======================

ndvi / photosynthesis detector on a pinoccio backpack!

based off of tech and teaching from http://publiclab.org/wiki/ndvi those folks are awesome.

![pinoccio](./animation3.gif)


this uses 2 photo sensors covered by specific color filters used in photgraphy to produce from diffused ambient light the rate of photosynthesis. the result is the NDVI which is a number based on ratio of red consumed by plants to the near IR range of light leftover.


## how?

- i take a blue and green filter over the phottocell attached to a1 which combined leave me only near ir 700nm+ , 
- subtract the value from my a1 channel from the value in my red (a0) channel to remove the near IR i left in my red
- generate the ratio and color the led =)

####photo sensors.
[![photo sensor](./photo_sensor.jpg)](https://www.sparkfun.com/products/9088)

the sparkfun photo sensor seems to get more of the near IR range than the one from adafruit. http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/LightImaging/SEN-09088.pdf
this is important.

####blue filter
![photo sensor](./blue_filter.jpg)

this is one of the components of the left "eye" adding this blue removes red but keeps as much of 700+ as possible

####green filter
![photo sensor](./green_filter.jpg)

this is the second filter for the left "eye". this removes most of the leftover blue leaving some slight light blue as noise and leaved me a good chunk of the near infrared. i should be able to find a better match.

####red filter.
![photo sensor](./red_filter.jpg)

this is the only filter on the right "eye". id ass all of the red channel and includes near ir.

