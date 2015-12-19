package kolban;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalMultipurpose;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.Pin;
import com.pi4j.io.gpio.PinMode;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;

public class Main1 {
  private final Pin CLK_NUM = RaspiPin.GPIO_00;
  private final Pin DIO_NUM = RaspiPin.GPIO_02;
  private final Pin CS_NUM = RaspiPin.GPIO_03;
  
  private GpioPinDigitalOutput CLK;
  private GpioPinDigitalOutput CS;
  GpioPinDigitalMultipurpose DIO;
  
  final GpioController gpio = GpioFactory.getInstance();
  
  public int getValue() {
    try {
      DIO.setMode(PinMode.DIGITAL_OUTPUT);
      CLK.setState(PinState.LOW);
      CS.setState(PinState.LOW);
      
      DIO.setState(PinState.HIGH); // Start Bit
      Thread.sleep(10);
      CLK.setState(PinState.HIGH);
      Thread.sleep(10);
      CLK.setState(PinState.LOW);
      Thread.sleep(10);
      
      DIO.setState(PinState.HIGH); // SGL
      CLK.setState(PinState.HIGH);
      Thread.sleep(10);
      CLK.setState(PinState.LOW);
      Thread.sleep(10);
      
      DIO.setState(PinState.LOW); // Choose channel 0
      CLK.setState(PinState.HIGH);
      Thread.sleep(10);
      DIO.setMode(PinMode.DIGITAL_INPUT);
      CLK.setState(PinState.LOW);
      Thread.sleep(10);
      
      CLK.setState(PinState.HIGH); // Skip a clock
      Thread.sleep(10);
      CLK.setState(PinState.LOW);
      Thread.sleep(10);
      
      int value = 0;
      for (int i=0; i<8; i++) {
        CLK.setState(PinState.HIGH);
        int bit = DIO.getState().getValue();
        value = value << 1 | bit;
        Thread.sleep(10);
        CLK.setState(PinState.LOW);
        Thread.sleep(10);
      }
      CS.setState(PinState.HIGH);
      
      return value;
      
    } catch (Exception e) {
      e.printStackTrace();
    };
    return 0;
  }

  public void run() {
    CLK = gpio.provisionDigitalOutputPin(CLK_NUM);
    CS = gpio.provisionDigitalOutputPin(CS_NUM);
    DIO = gpio.provisionDigitalMultipurposePin(DIO_NUM, PinMode.DIGITAL_OUTPUT);
    while(true) {
      int value = getValue();
      System.out.println("Value = " + value);
      try {
        Thread.sleep(1000);
      } catch(Exception e) {
        e.printStackTrace();
      }
    }
  }
  
  public static void main(String[] args) {
    System.out.println("Running ADC0832");
    new Main1().run();
  }  
}
