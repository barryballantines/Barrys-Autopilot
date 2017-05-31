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
  
  static final String AFDS_HEADING_DEG_PROPERTY = "/autopilot/settings/heading-bug-deg";
  static final String AFDS_LATERAL_MODE_PROPERTY = "/instrumentation/afds/inputs/lateral-index";
  static final int    AFDS_LATERAL_MODE__OFF = 0;
  static final int    AFDS_LATERAL_MODE__SELECT = 1;
  static final int    AFDS_LATERAL_MODE__HOLD = 2;
  
  static final String AFDS_SPEED_KT_PROPERTY = "/autopilot/settings/target-speed-kt";
  static final String AFDS_SPEED_MACH_PROPERTY = "/autopilot/settings/target-mach";
  
  static final String AFDS_VERTICAL_SPEED_FPM_PROPERTY = "/autopilot/settings/vertical-speed-fpm";
  static final String AFDS_ALTITUDE_FT_PROPERTY = "/autopilot/settings/alt-display-ft";
  
  static final String ORIENTATION_HEADING_MAGNETIC_DEG = "/orientation/heading-magnetic-deg";
  
}
