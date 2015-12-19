package kolban;

import com.pi4j.component.gyroscope.honeywell.HMC5883L;
import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CFactory;

public class Main1 {
 

  public static void main(String[] args) {
    System.out.println("Running HMC5883L");
    try {
      I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
      HMC5883L hmc5883l = new HMC5883L(bus);
      hmc5883l.enable();
      while(true) {
        hmc5883l.readGyro();
        System.out.println("X=" + (short)hmc5883l.X.getRawValue() + " ,Y=" + (short)hmc5883l.Y.getRawValue() + ", Z=" + (short)hmc5883l.Z.getRawValue());
        Thread.sleep(1000);
      }
    } catch (Exception e) {
      e.printStackTrace();
    };
  }
}
