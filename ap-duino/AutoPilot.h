#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include <Arduino.h>
/**
 * This library encapsulates all A/P specific logic.
 * 
 * Use the following methods from the setup() function of the Arduino sketch
 *  to setup the pin configuration of the A/P
 * 
 * - setupHeading(...)
 * - setupSpeed(...)
 * - setupAltitude(...)
 * 
 * Use the following methods to set or get values either from the setup() or 
 * from the loop() functions of the Arduino sketch:
 * 
 * - setHeading()
 * - getHeading()
 * 
 * Use the following method from the loop() function of the Arduino sketch in 
 * order to update the display of the A/P hardware
 * 
 * - updateDisplay()
 * 
 * 
 */
class AutoPilot {
public:
    /**
     * Default constructor for AutoPilot class
     */
    AutoPilot();

    /**
     * Default destructor
     */
    ~AutoPilot();

    /** 
     *  setup shift register pins 
     *  
     *  @param clockPin
     *  @param latchPin
     */
    void setupShiftRegisterControl(byte clockPin, byte latchPin);

    /**
     * setup Heading display data pin
     * 
     * @param dataPin
     */
    void setupHeadingDisplayDataPin(byte dataPin);
    
    /**
     * setup method for the Heading rotary encoder
     * 
     * Both pins will be be configured as INPUT_PULLUP
     * 
     * @param pinA - the first pin of the rotary encoder, typically an interrupt
     * @param pinB - the second pin of the rotary encoder
     */
    void setupHeadingRotaryEncoder(byte pinA, byte pinB);

    /**
     * set heading for the A/P
     * 
     * calling this method does not update the heading display.
     *
     * @param hdg heading (0-359)
     */
    void setHeading(int hdg);

    /**
     * gets the heading (0-359) in degrees 
     * 
     * @return heading between 0 and 359 degrees
     */
    int getHeading();

    /**
     * Updates the displays of the A/P
     * 
     * this method should be called from the loop() method of the
     * Arduino sketch file.
     */
    void updateDisplay();
    
    /**
     * call this method on interrupt of _headingEncoderPinA
     */
    void onHeadingRotaryEncoderInterrupt();

    void testHeadingDisplay();

private:

    /** the current heading, that will be displayed the next time
     *  updateDisplay() is called.
     */
    volatile int _heading;
    
    // === PINS ===
    
    /** 
     * the Pin A of the heading rotary encoder.
     * 
     * this pin must be an interrupt pin
     */
    byte _headingEncoderPinA;

    /**
     * the Pin B of the heading rotary encoder.
     */
    byte _headingEncoderPinB;

    /**
     * heading data pin
     */
    byte _headingDisplayDataPin; 

    // --- shift register control pins ---

    byte _latchPin;
    byte _clockPin;

    
    

};

#endif
