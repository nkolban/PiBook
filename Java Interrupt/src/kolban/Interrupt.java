package kolban;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.PinPullResistance;
import com.pi4j.io.gpio.RaspiPin;
import com.pi4j.io.gpio.event.GpioPinDigitalStateChangeEvent;
import com.pi4j.io.gpio.event.GpioPinListenerDigital;

public class Interrupt {

  static final GpioController gpio = GpioFactory.getInstance();

  public static void main(String[] args) {
    System.out.println("Running Interrupt");
    try {
      GpioPinDigitalInput myInput = gpio.provisionDigitalInputPin(RaspiPin.GPIO_00);
      myInput.setPullResistance(PinPullResistance.PULL_UP);
      myInput.addListener(new GpioPinListenerDigital() {

        @Override
        public void handleGpioPinDigitalStateChangeEvent(GpioPinDigitalStateChangeEvent changeEvent) {
          System.out.println("The pin changed state to: " + changeEvent.getState());
        }
      });
      while (true) {
        Thread.sleep(50000);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
