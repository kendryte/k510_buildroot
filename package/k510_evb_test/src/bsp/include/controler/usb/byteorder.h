/**********************************************************************
 * Copyright (C) 2014 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * byteorder.h
 * File contains Endian handling
 ***********************************************************************/

#ifndef BYTEORDER_H
#define BYTEORDER_H

#define CPU_LITTLE_ENDIAN

#ifdef CPU_LITTLE_ENDIAN
#include "little_endian.h"
#else
#include "big_endian.h"
#endif

#endif // BYTEORDER_H

