/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot.flightgear;

import ballantines.avionics.flightgear.connect.PropertyService;

/**
 *
 * @author mbuse
 */
public class FlightgearAutopilot {
  
  private PropertyService fgPropertyService;
  
  public void setHeadingDeg(int hdg) {
    fgPropertyService.writeProperty(AutopilotProperties.HEADING_DEG_PROPERTY, hdg);
  }
  
}
