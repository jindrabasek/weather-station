/*
 * SerialVirtButtonsTask.cpp
 *
 *  Created on: 14. 2. 2016
 *      Author: jindra
 */

#include "SerialVirtButtonsTask.h"

#include <ApplicationMonitor.h>
#include <Arduino.h>
#include <ButtonHandler.h>
#include <Debouncer.h>
#include <HardwareSerial.h>
#include <Logger.h>
#include <mem_eval.h>
#include <PciManagerLock.h>
#include <stdbool.h>
#include <stdint.h>
#include <TaskIds.h>
#include <WString.h>
#include <Logger.h>
#include <Wire.h>

#include "../net/Network.h"
#include "../ProgramState.h"
#include "Buttons.h"

extern ProgramState *state;

SerialVirtButtonsTask::SerialVirtButtonsTask(unsigned long periodMs) :
        Task(periodMs, true, SerialVirtButtons_Task) {
    pinMode(DO_RESET_PIN, OUTPUT);
}

void SerialVirtButtonsTask::doReset() {
    Logger.log(LOGGER_LEVEL_INFO, F("Device will reboot."));
    delay(RESET_DELAY);
    digitalWrite(DO_RESET_PIN, HIGH);
}

void SerialVirtButtonsTask::printMemoryUsage() {

    uint8_t *largest_begin, *largest_end;
    uint16_t largest_size;

    Logger.println(F("--- Memory Usage ---"));

    MemoryEval::AnalyzeMemory(&largest_begin, &largest_size, Logger);
    largest_end = largest_begin + largest_size;

    Logger.printTimeAndLevel(LOGGER_LEVEL_INFO);
    Logger.print(F("Unused memory: 0x"));

    Logger.print((uint16_t) largest_begin >> 8, 16);
    Logger.print((uint16_t) largest_begin & 0xFF, 16);
    Logger.print(F(" - 0x"));
    Logger.print((uint16_t) largest_end >> 8, 16);
    Logger.print((uint16_t) largest_end & 0xFF, 16);
    Logger.print(F(" ("));
    Logger.print(largest_size);
    Logger.println(F(" Bytes)"));

    Logger.println(F("--- End of Memory Usage ---"));
}

void SerialVirtButtonsTask::run() {
    // check if new serial input is available
    if (Serial.available()) {
        // read one char from input buffer
        char input = Serial.read();
        LOG_INFO1(F("Key received: "), input);

        {
            PciManagerLock lock;
            switch (input) {
                case UP_CHAR:
                    state->getButtons()[WeatherStation::Buttons::UP].getHandler()
                            ->onPressed();
                    break;
                case DOWN_CHAR:
                    state->getButtons()[WeatherStation::Buttons::DOWN]
                            .getHandler()->onPressed();
                    break;
                    /*case LEFT_CHAR:
                     state->getButtons()[WeatherStation::Buttons::LEFT].getHandler()->onPressed();
                     break;
                     case RIGHT_CHAR:
                     state->getButtons()[WeatherStation::Buttons::RIGHT].getHandler()->onPressed();
                     break;*/
                case BACKLIGHT_CHAR:
                    state->getButtons()[WeatherStation::Buttons::BACKLIGHT]
                            .getHandler()->onPressed();
                    break;
                case ENTER_CHAR:
                    state->getButtons()[WeatherStation::Buttons::ENTER]
                            .getHandler()->onPressed();
                    break;
                case ESC_CHAR:
                    state->getButtons()[WeatherStation::Buttons::ESC].getHandler()
                            ->onPressed();
                    break;
                case RESET_CHAR:
                    doReset();
                    break;
                case LOG_DUMP_CHAR:
                    Logger.dumpLog();
                    break;
                case LIST_NETWORKS_CHAR:
                    ApplicationMonitor.DisableWatchdog();
                    Network::listNetworks();
                    ApplicationMonitor.EnableWatchdog(
                            Watchdog::CApplicationMonitor::Timeout_8s);
                    break;
                case NETWORK_STATUS_CHAR:
                    Network::status();
                    break;
                case PRINT_MEMORY_USAGE_CHAR:
                    ApplicationMonitor.DisableWatchdog();
                    printMemoryUsage();
                    ApplicationMonitor.EnableWatchdog(
                            Watchdog::CApplicationMonitor::Timeout_8s);
                    break;
                case DO_INFINITE_LOOP_CHAR:
                	LOG_INFO(F("Testing watch dog."));
                    while (true) {
                        // nothing
                    }
                    break;
                case ENABLE_WATCHDOG_CHAR:
                	LOG_INFO(F("Watch dog enabled."));
                    ApplicationMonitor.EnableWatchdog(Watchdog::CApplicationMonitor::Timeout_8s);
                    break;
                case DISABLE_WATCHDOG_CHAR:
                	LOG_INFO(F("Watch dog disabled."));
                    ApplicationMonitor.DisableWatchdog();
                    break;
                case WIRE_DISABLE_ENABLE_CHAR:
                	LOG_INFO(F("Restarting wire."));
                	Wire.end();
                	Wire.begin();
                	LOG_INFO(F("Wire restarted."));
                	break;
                default:
                    break;
            }
        }
    }
}
