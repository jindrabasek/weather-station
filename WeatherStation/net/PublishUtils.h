/*
 * PublishUtils.h
 *
 *  Created on: 7. 1. 2017
 *      Author: jindra
 */

#ifndef PUBLISHUTILS_H_
#define PUBLISHUTILS_H_

#include <Print.h>
#include <stddef.h>
#include <stdint.h>

class PublishUtils {
public:
    PublishUtils(const PublishUtils& that) = delete;
    void operator=(const PublishUtils& that) = delete;

    static bool getAssetId(char* buffer, uint8_t valueId, const char * const * const assetIds, size_t maxSize);
    static void formatTime(Print & out, unsigned long timeStamp);
    static size_t numberOfDigits(double value, uint16_t floatDigits);
    static size_t numberOfDigits(long value);
};

#endif /* PUBLISHUTILS_H_ */
