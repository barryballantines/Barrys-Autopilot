/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot.serial;

import java.util.Objects;

/**
 *
 * @author mbuse
 */
public class SerialCommand {
  private String key;
  private int value;
  private long timestamp;

  public SerialCommand(String key, int value) {
    this.key = key;
    this.value = value;
    this.timestamp = System.currentTimeMillis();
  }
  
  public String getKey() {
    return key;
  }

  public int getValue() {
    return value;
  }

  public long getTimestamp() {
    return timestamp;
  }

  @Override
  public int hashCode() {
    int hash = 3;
    hash = 31 * hash + Objects.hashCode(this.key);
    hash = 31 * hash + this.value;
    return hash;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj) {
      return true;
    }
    if (obj == null) {
      return false;
    }
    if (getClass() != obj.getClass()) {
      return false;
    }
    final SerialCommand other = (SerialCommand) obj;
    if (this.value != other.value) {
      return false;
    }
    if (!Objects.equals(this.key, other.key)) {
      return false;
    }
    return true;
  }

  @Override
  public String toString() {
    return "{"+key+ ":" + value + "}";
  }
  
  
  
  
  
}
