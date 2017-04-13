# GSM-based-GPS-tracker
Arduino Mega here acts as the centre  controlling unit which receives the input signal and provides interfaces to GPS and GSM.

GSM Module connects to the available carrier networks 

GSM sends status of device along with the location to the pre programmed number via SMS

GPS extracts the Current location from the Satellite and sends it to the Controller via Serial communication

Here Input is referenced as a Switch but this can be replaced with any signal.

Input signal can be any real time signals. It can be even 3 phase high voltage but the only thing we need is proper circuit to step down the voltage .

Whenever the signal changes its state, an SMS is triggered to the predefined number.

This SMS is embedded with google maps link with latitude and longitude extracted from GPS.

When the User clicks the link, it automatically redirects to Google Maps.

When you send a message with a predefined query ”status” it replies with the status and location.

# For more details please have a look 

[![Little red ridning hood](http://i.imgur.com/rcmjESi.png)](https://youtu.be/VPTwk3R27jY)
