/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ballantines.avionics.autopilot.serial;

import ballantines.avionics.pipes.Pipe;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import java.io.BufferedOutputStream;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author mbuse
 */
public class SerialConnection {
  public static final int TIMEOUT = 6000;
  
  public final Pipe<Boolean> statusPipe = Pipe.newInstance("configurationForm.serverConfig");
  
  private SerialConfig config;
  
  private BufferedOutputStream output;
  private boolean connected = false;
  private Boolean status = null;
  private StringBuilder buffer = new StringBuilder();
  
  public SerialConnection(SerialConfig config) {
    this.config = config;
  }
  
  public boolean connect() {
    try {
      SerialPort serialPort = SerialPort.getCommPort(config.port);
      serialPort.setBaudRate(config.baudRate);
      serialPort.openPort();
      //LOG.info("Connecting to Arduino on port " + port);
      System.out.println("Connecting to Arduino on port " + config.port);
      serialPort.addDataListener(new SerialPortDataListener() {
        @Override
        public int getListeningEvents() {
          return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
        }

        @Override
        public void serialEvent(SerialPortEvent event) {
          if(event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
            return;
          }
          byte[] newData = new byte[serialPort.bytesAvailable()];
          serialPort.readBytes(newData, newData.length);

          String part = new String(newData);
          buffer.append(part);

          //format command string from buffer
          checkCommandBuffer();
        }
      });

      //Let's wait a little bit, otherwise the initial data connection doesn't work
      Thread.sleep(2000);
      if(serialPort.isOpen()) {
        this.output = new BufferedOutputStream(serialPort.getOutputStream());

        String command = "{connected:1}";
        output.write(command.getBytes());
        output.flush();
        connected = true;
      }
      else {
        // LOG.error("Failed to open COM port");
        System.out.println("Failed to open COM port");
        restart();
      }
    } catch (Exception e) {
      connected = false;
      //LOG.error("Failed to open port '" + port + "': " + e.toString());
      restart();
    }
    finally {
       status = connected;
       statusPipe.set(status);
    }
    return connected;
  }
  
  
  /**
   * Terminates the serial IO communication
   */
  public void shutdown() {
    connected = false;
    if(status == null || connected != status) {
      status = connected;

      statusPipe.set(status);
    }
  }

  /**
   * Executed if the serial connection fails, a restart is triggered every n seconds.
   */
  public void restart() {
    shutdown();
    //LOG.info("Terminating serial connecting, waiting for reconnect attempt...");
    System.out.println("Terminating serial connecting, waiting for reconnect attemp...");
    try {
      Thread.sleep(TIMEOUT);
      connect();
    } catch (InterruptedException e) {
      //ignore
    }
  }
  
   private void checkCommandBuffer() {
    String commands = buffer.toString();
    if(commands.contains("}") && commands.contains("{") && (commands.lastIndexOf("{") < commands.lastIndexOf("}"))) {
      buffer = new StringBuilder();
      String cmd = null;

      try {
        cmd = commands.substring(commands.lastIndexOf("{"), commands.lastIndexOf("}") + 1).trim();
        // LOG.info("Received command '" + cmd + "'");
        System.out.println("Receiving command '" + cmd + "'");
        // TODO: execute command...
      } catch (Exception e) {
        //LOG.error("Failed to parse JSON: " + e.getMessage(), e);
      }
    }
  }
}
