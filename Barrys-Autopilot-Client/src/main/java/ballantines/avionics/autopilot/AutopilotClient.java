/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot;

import ballantines.avionics.autopilot.serial.SerialConfig;
import ballantines.avionics.autopilot.serial.SerialConnection;
import ballantines.avionics.pipes.Pipe;

/**
 *
 * @author mbuse
 */
public class AutopilotClient {
  
  public static void main(String... args) {
    SerialConfig serialCfg = new SerialConfig();
    serialCfg.port = "COM3";
    serialCfg.baudRate = 9600;
    SerialConnection serial = new SerialConnection(serialCfg);
    serial.statusPipe.addListener((Pipe<Boolean> model) ->   {
      System.out.println("Status: " + model.get());
    });
    serial.connect();
  }
  
}
