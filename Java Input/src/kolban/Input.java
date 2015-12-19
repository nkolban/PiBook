package kolban;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.PinPullResistance;
import com.pi4j.io.gpio.RaspiPin;

public class Input {

  static final GpioController gpio = GpioFactory.getInstance();

  public static void main(String[] args) {
    System.out.println("Running Input");
    try {
      GpioPinDigitalInput myInput = gpio.provisionDigitalInputPin(RaspiPin.GPIO_00);
      myInput.setPullResistance(PinPullResistance.PULL_UP);
      while (true) {
        System.out.println("Pin state is: " + myInput.getState());
        Thread.sleep(500);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
