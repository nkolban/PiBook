wpi = require("wiring-pi");
wpi.setup("gpio");
//wpi.wiringPiSPISetup(0, 500000);
var addr = 0x12;
var val = 0x34;
var data = [(addr<<1)&0x7E, val];
var uint8Data = Uint8Array.from(data);
wpi.wiringPiSPIDataRW(0, uint8Data);
console.log("Done!");
