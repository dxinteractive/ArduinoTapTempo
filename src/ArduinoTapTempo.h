/*
 * ArduinoTapTempo.h
 * An Arduino library that times consecutive button presses to calculate Beats Per Minute. Corrects for missed beats and can reset phase with single taps. *
 * Copyright (c) 2016 Damien Clarke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.  
 */
 
#ifndef ARDUINO_TAP_TEMPO_H
#define ARDUINO_TAP_TEMPO_H

#include <Arduino.h>

class ArduinoTapTempo
{
  public:
    static const int MAX_TAP_VALUES = 10;

    bool onBeat(); // returns true if a beat has occured since the last update(), not accurate enough for timing in music but useful for LEDs or other indicators
    bool isChainActive(); // returns true if the current tap chain is still accepting new taps to fine tune the tempo
    bool isChainActive(unsigned long ms); // returns true if the current tap chain is still accepting new taps to fine tune the tempo
    float getBPM(); // returns the number of beats per minute
    float beatProgress(); // returns a float from 0.0 to 1.0 indicating the percent through the current beat
    void resetTapChain(); // resets the current chain of taps and sets the start of the bar to the current time
    void resetTapChain(unsigned long ms); // resets the current chain of taps and sets the start of the bar to the current time

    inline unsigned long getBeatLength() { return beatLengthMS; } // returns the length of the beat in milliseconds
    inline unsigned long getLastTapTime() { return lastTapMS; } // returns the time of the last tap in milliseconds since the program started

    void update(bool buttonDown); // call this each time you read your button state, accepts a boolean indicating if the button is down

    // getters and setters

    // skipped taps are detected when a tap duration is close to double the last tap duration. 
    void setSkippedTapThresholdLow(float threshold); // This sets the lower threshold, accepts a float from 1.0 to 2.0.
    void setSkippedTapThresholdHigh(float threshold); // This sets the upper threshold, accepts a float from 2.0 to 4.0.
    inline void setMillisUntilChainReset(unsigned long ms) { millisUntilChainReset = ms; } // The current chain of taps will finish this many milliseconds after the most recent tap 
    void setBeatsUntilChainReset(int beats); // The current chain of taps will finish this many beats after the most recent tap, accepts an int grater than 1 
    void setTotalTapValues(int total); // Sets the maximum number of most recent taps that will be averaged out to calculate the tempo, accepts int from 2 to MAX_TAP_VALUES
    
  private:
    // config
    unsigned long millisUntilChainReset = 2000;
    int beatsUntilChainReset = 4;
    int totalTapValues = 5;
    float skippedTapThresholdLow = 1.75;
    float skippedTapThresholdHigh = 2.75;

    // button state
    bool buttonDownOld = false;

    // timing
    unsigned long millisSinceReset = 0;
    unsigned long millisSinceResetOld = 0;
    unsigned long beatLengthMS = 500;
    unsigned long lastResetMS = millis();
    
    // taps
    unsigned long lastTapMS = 0;
    unsigned long tapDurations[ArduinoTapTempo::MAX_TAP_VALUES];
    int tapDurationIndex = 0;
    int tapsInChain = 0;
    bool lastTapSkipped = false;

    // private methods
    void tap(unsigned long ms);
    void addTapToChain(unsigned long ms);
    unsigned long getAverageTapDuration();
};

#endif
