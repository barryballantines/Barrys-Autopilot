/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot;

import ballantines.avionics.autopilot.serial.SerialConfig;
import ballantines.avionics.autopilot.serial.SerialConnection;
import ballantines.avionics.pipes.Pipe;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 *
 * @author mbuse
 */
public class AutopilotClient {
  private final static Logger LOG = LoggerFactory.getLogger(AutopilotClient.class);
  
  public static void main(String... args) {
    SerialConfig serialCfg = new SerialConfig();
    serialCfg.port = "COM3";
    serialCfg.baudRate = 9600;
    SerialConnection serial = new SerialConnection(serialCfg);
    serial.statusPipe.addListener((Pipe<Boolean> model) ->   {
      LOG.info("Status: " + model.get());
    });
    serial.connect();
  }
  
}
