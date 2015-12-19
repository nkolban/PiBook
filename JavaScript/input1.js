var wpi = require('wiring-pi');

wpi.setup('wpi');

var pin = 0;

wpi.pinMode(pin, wpi.INPUT);

var value = 1;

setInterval(function() {
  var value = wpi.digitalRead(pin);
  console.log("value is " + value);
}, 500);