/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot;

import ballantines.avionics.autopilot.flightgear.FlightgearAutopilot;
import ballantines.avionics.autopilot.serial.SerialConfig;
import ballantines.avionics.autopilot.serial.SerialConnection;
import ballantines.avionics.autopilot.synch.SynchronizationService;
import ballantines.avionics.flightgear.connect.HttpPropertyServiceImpl;
import ballantines.avionics.flightgear.connect.PropertyService;
import ballantines.avionics.flightgear.connect.ServerConfig;
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
    
    ServerConfig config = new ServerConfig("localhost", 5500);
    PropertyService propertyService = new HttpPropertyServiceImpl(config);
    
    FlightgearAutopilot autopilot = new FlightgearAutopilot(propertyService);
    SynchronizationService synchro = new SynchronizationService(autopilot);
    
    synchro.serialInputPipe.connectTo(serial.commandPipe);
    
    
    serial.connect();
  }
  
}
