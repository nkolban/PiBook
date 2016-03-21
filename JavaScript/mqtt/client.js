var mqtt = require("mqtt");
var client = mqtt.connect("mqtt://pc9100");
client.on('connect', function() {
  console.log("Connected ... now publishing");
  client.publish("greeting", "Hello from JavaScript");
  client.end();
});
