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
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 *
 * @author mbuse
 */
public class SynchronizationService implements PipeUpdateListener {
  private final static Logger LOG = LoggerFactory.getLogger(SynchronizationService.class);
  
  public Pipe<Object> flightGearInputPipe = Pipe.newInstance("synchronizationService.flightgear.in", this);
  public Pipe<Object> flightGearOutputPipe = Pipe.newInstance("sychronizationService.flightgear.out", this);
  public Pipe<SerialCommand> serialInputPipe = Pipe.newInstance("synchronizationServer.serial.in", this);
  public Pipe<Object> serialOutputPipe = Pipe.newInstance("synchronizationService.serial.out", this);

  private FlightgearAutopilot fgAutopilot;

  public SynchronizationService(FlightgearAutopilot fgAutopilot) {
    this.fgAutopilot = fgAutopilot;
  }
  
  @Override
  public void pipeUpdated(Pipe pipe) {
    LOG.debug(pipe.toString());
    if (pipe == serialInputPipe) {
      SerialCommand cmd = serialInputPipe.get();
      if (cmd!=null) {
        if ("hdg".equals(cmd.getKey())) {
          fgAutopilot.setHeadingDeg(cmd.getValue());
        }
        else if ("hdgSelectPressed".equals(cmd.getKey())) {
          fgAutopilot.toggleHeadingSelect();
        }
        else if ("hdgHoldPressed".equals(cmd.getKey())) {
          fgAutopilot.toggleHeadingHold();
        }
      }
    }
  }
  
  
  
}
