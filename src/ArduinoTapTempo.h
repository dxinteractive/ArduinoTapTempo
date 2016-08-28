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

    // millisUntilChainReset - the current chain of taps will finish this many milliseconds after the most recent tap 
    // totalTapValues - the maximum number of most recent taps that will be averaged out to calculate the tempo

    ArduinoTapTempo(int millisUntilChainReset = 2000, int totalTapValues = 5); 

    // skipped taps are detected when a tap duration is close to double the last tap duration. 
    void setSkippedTapThresholdLow(float threshold); // This sets the lower threshold, accepts a float from 1.0 to 2.0.
    void setSkippedTapThresholdHigh(float threshold); // This sets the upper threshold, accepts a float from 2.0 to 4.0.

    void update(boolean buttonDown);
    
  private:
    int millisUntilChainReset;
    int totalTapValues;
    float skippedTapThresholdLow = 1.75;
    float skippedTapThresholdHigh = 2.75;
};

#endif
