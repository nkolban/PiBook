var adc0832 = require("adc0832");
adc0832.init();

setInterval(function() {
  console.log("Value: " + adc0832.getValue());
}, 1000);
