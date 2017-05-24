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
     *  @param clearPin
     *  @param outputEnablePin
     */
    void setupShiftRegisterControl(byte clockPin, byte latchPin, byte clearPin, byte outputEnablePin);

    // === HEADING === 
    
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
     * setup method for Heading activate push button
     * 
     * Pin will be configured as INPUT_PULLUP
     */
    void setupHeadingModeActivateBtn(byte hdgModeActivatePin);

    /**
     * setup method for Heading Hold push button
     * 
     * Pin will be INPUT_PULLUP
     */
    void setupHeadingHoldBtn(byte hdgHoldBtnPin);

    /**
     * setup method for Heading Mode LED
     * Pin will be OUTPUT
     */
    void setupHeadingModeLED(byte hdgModeLEDPin);

    /**
     * set heading for the A/P
     * 
     * calling this method does not update the heading display.
     *
     * @param hdg heading (0-359)
     */
    void setHeading(int hdg);

    /** 
     *  set heading mode active
     */
    void setHeadingModeActive(boolean active);

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


    // === SERIAL COMMUNICATION ===

    void sendChanges();
    void onSerialEvent();

private:

    /** the current heading, that will be displayed the next time
     *  updateDisplay() is called.
     */
    volatile int _heading;
    boolean _headingDirty = false;

    
    boolean _headingModeActive = false;
    boolean _headingModeActiveDirty = false;
    
    String _commandInput = "";

    // === SERIAL COMM ===
    
    void executeCommand();
    void sendCommand(const char * name, const long value);

    
    // === PINS ===

    // --- HEADING ---
    
    byte _headingEncoderPinA;
    byte _headingEncoderPinB;
    byte _headingDisplayDataPin; 
    byte _headingModeActivatePin;
    byte _headingHoldBtnPin;
    byte _headingModeLEDPin;

    // --- shift register control pins ---

    byte _shiftRegLatchPin;
    byte _shiftRegClockPin;
    byte _shiftRegOutputEnablePin;
    byte _shiftRegClearPin;
};

// HELPER FUNCTIONS...

// segment byte order: a b c d e f g DP
const byte DIGIT_TO_BYTES[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B00000000, // SPACE
  B00000010, // -
  B00000001, // .
};

/** this helper function translates a digit into a byte
 *  to be used for displaying the digit on a 7 segment led display
 */
byte digitToByte(int digit);

/**
 * translates an unsigned integer into an array of bytes to be used 
 * for a display of 7 segment led displays
 * 
 * The integer 345 will be translated into the array
 * { digitToByte(0), digitToByte(0), digitToByte(3), digitToByte(4), digitToByte(5) }
 * 
 * @param input the input value in the range of 0 - 99999 (higher numbers will result in "-----")
 * @param output the byte array of length 5, used to hold the result
 */
void translateUnsignedIntToByteArray(unsigned int input, byte output[5]);

#endif
