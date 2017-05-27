/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot.flightgear;

/**
 *
 * @author mbuse
 */
public interface AutopilotProperties {
  
  static final String HEADING_DEG_PROPERTY = "/autopilot/settings/heading-bug-deg";
  
  static final String SPEED_KT_PROPERTY = "/autopilot/settings/target-speed-kt";
  static final String SPEED_MACH_PROPERTY = "/autopilot/settings/target-mach";
  
  static final String VERTICAL_SPEED_FPM_PROPERTY = "/autopilot/settings/vertical-speed-fpm";
  
  static final String ALTITUDE_FT_PROPERTY = "/autopilot/settings/alt-display-ft";
  
}
