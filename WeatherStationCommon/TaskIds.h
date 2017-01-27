/*
 * TaskIds.h
 *
 *  Created on: 21. 1. 2017
 *      Author: jindra
 */

#ifndef TASKIDS_H_
#define TASKIDS_H_

enum TaskIds {
    Si7010TempMeasure_Task = 1,
    AirPressureMeasure_Task = 2,
    Am2320TempMeasure_Task = 3,
    LightIntensityMeasure_Task = 4,
    Dht22TempMeasure_Task = 5,
    Wireless433Mhz_Task = 6,
    BackLight_Task = 7,
    DrawOnDisplay_Task = 8,
    SerialVirtButtons_Task = 9,
    NetworkTest_Task = 10,
    TimeSync_Task = 11,
    MqttLoop_Task = 12,
    MqttPublish_Task = 13,
    SmartLivingPublish_Task = 14,
    WifiWatchdog_Task = 15,
    TaskIdsEnumSize
};

#endif /* TASKIDS_H_ */
