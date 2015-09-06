# Server-Sent Events / EventSource Demo

This demonstrates how to use EventSource with PHP or Arduino Event Generators.

Here's a small explanation and a video demo of the scripts:  
https://www.claudiuscoenen.de/2015/09/generating-server-sent-events-on-arduino/


## Arduino

Use an *Arduino Ethernet* or the Ethernet Shield with any other Arduino board.
Add Something to pins 5, 6 or A0. Enter a free IP in the `.ino` file on which
your Arduino will be available.

Alter the IP in `index.html` to match your Arduino's IP.


## PHP

Change the script in `index.html` to point to `source.php` - the code is already
there, you just need to remove a comment.

Run `php -S 0.0.0.0:8000` in this directory, this will create a simple webserver.


## EventSource Resources

* [W3C Specification](http://www.w3.org/TR/eventsource/)
* [Can I Use](http://caniuse.com/#feat=eventsource) hint: in 2015, everything but IE/Edge is fair game.
* [HTML5Rocks Tutorial](www.html5rocks.com/en/tutorials/eventsource/basics/)
