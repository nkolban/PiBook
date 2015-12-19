package kolban;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.RaspiPin;

public class Main1 {

  static final GpioController gpio = GpioFactory.getInstance();

  public static void main(String[] args) {
    System.out.println("Running Blinky");
    try {
      GpioPinDigitalOutput myLed = gpio.provisionDigitalOutputPin(RaspiPin.GPIO_00);
      boolean value = true;
      while (true) {
        myLed.setState(value);
        Thread.sleep(500);
        value = !value;
      }
    } catch (Exception e) {
      e.printStackTrace();
    };
  }
}
