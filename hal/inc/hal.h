/*
 * hal.h
 *
 *  Created on: 21 Jun 2012
 *      Author: benedictpaten
 */

#ifndef HAL_H_
#define HAL_H_

#include "sonLib.h"
#include "cactus.h"

void makeMafFormat(stList *flowers, stKVDatabase *database, Name referenceEventName,
        FILE *fileHandle, bool showOnlySubstitutionsWithRespectToReference);

void makeHalFormat(stList *flowers, stKVDatabase *database, Name referenceEventName,
        FILE *fileHandle);

#endif /* HAL_H_ */