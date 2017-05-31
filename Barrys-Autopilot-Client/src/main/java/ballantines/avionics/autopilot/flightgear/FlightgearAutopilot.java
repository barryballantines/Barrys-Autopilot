/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot.flightgear;

import ballantines.avionics.flightgear.connect.PropertyService;
import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author mbuse
 */
public class FlightgearAutopilot implements AutopilotProperties {
  
  private PropertyService flightgear;
  
  public FlightgearAutopilot(PropertyService service) {
    this.flightgear = service;
  }
  
  public void setHeadingDeg(int hdg) {
    flightgear.writeProperty(AFDS_HEADING_DEG_PROPERTY, hdg);
  }
  
  public void toggleHeadingHold() {
    int lateralMode = flightgear.readProperty(AFDS_LATERAL_MODE_PROPERTY);
    if (lateralMode==AFDS_LATERAL_MODE__HOLD) {
      flightgear.writeProperty(AFDS_LATERAL_MODE_PROPERTY, AFDS_LATERAL_MODE__OFF);
    }
    else {
      double heading = (double) flightgear.readProperty(AutopilotProperties.ORIENTATION_HEADING_MAGNETIC_DEG);
      Map<String,Object> props = new HashMap<>();
      props.put(AFDS_HEADING_DEG_PROPERTY, heading);
      props.put(AFDS_LATERAL_MODE_PROPERTY, AFDS_LATERAL_MODE__HOLD);
      flightgear.writeProperties(props);
    }
  }
  
  public void toggleHeadingSelect() {
    int lateralMode = flightgear.readProperty(AFDS_LATERAL_MODE_PROPERTY);
    if (lateralMode==AFDS_LATERAL_MODE__SELECT) {
      flightgear.writeProperty(AFDS_LATERAL_MODE_PROPERTY, AFDS_LATERAL_MODE__OFF);
    }
    else {
      flightgear.writeProperty(AFDS_LATERAL_MODE_PROPERTY, AFDS_LATERAL_MODE__SELECT);
    }
  }
}
