# knockify
Door knock sensor that sends push notification to your cellphone and computer

## Requirements
* 1x ESP-8266
* 1x Piezosensor
* 1x 1M ohms resistor (may vary depending on your piezo)

## Setup push notifications
* Install pushbullet on your mobile device or computer
* From http://www.pushbullet.com/
    * Create a new Access Token from your account settings
* From http://www.pushingbox.com/ 
    * Create a new pushbullet service and enter your access token
    * Set the Title as "Door Detector"
    * Set the message as $message_parameter$
    * From your virtual scenarios, copy the DeviceID

## Setup the ESP-8266
* Add your DeviceID
* Set your wifi SSID
* Set your wifi Password

## References
* https://www.geekstips.com/android-push-notifications-esp8266-arduino-tutorial/
