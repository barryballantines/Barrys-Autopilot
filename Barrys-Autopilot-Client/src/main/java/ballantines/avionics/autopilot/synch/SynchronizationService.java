/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot.synch;

import ballantines.avionics.autopilot.flightgear.FlightgearAutopilot;
import ballantines.avionics.autopilot.serial.SerialCommand;
import ballantines.avionics.pipes.Pipe;
import ballantines.avionics.pipes.PipeUpdateListener;

/**
 *
 * @author mbuse
 */
public class SynchronizationService implements PipeUpdateListener {
  
  public Pipe<Object> flightGearInputPipe = Pipe.newInstance("synchronizationService.flightgear.in");
  public Pipe<Object> flightGearOutputPipe = Pipe.newInstance("sychronizationService.flightgear.out");
  public Pipe<SerialCommand> serialInputPipe = Pipe.newInstance("synchronizationServer.serial.in");
  public Pipe<Object> serialOutputPipe = Pipe.newInstance("synchronizationService.serial.out");

  private FlightgearAutopilot fgAutopilot;

  public SynchronizationService(FlightgearAutopilot fgAutopilot) {
    this.fgAutopilot = fgAutopilot;
  }
  
  @Override
  public void pipeUpdated(Pipe pipe) {
    if (pipe == serialInputPipe) {
      SerialCommand cmd = serialInputPipe.get();
      if ("hdg".equals(cmd.getKey())) {
        fgAutopilot.setHeadingDeg(cmd.getValue());
      }
    }
  }
  
  
  
}
