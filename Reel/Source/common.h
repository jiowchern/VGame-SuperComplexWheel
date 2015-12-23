#ifndef DEF_INCLUDE_COMMON_H
#define DEF_INCLUDE_COMMON_H


#define NAMESPACE_NATIVE_BEGIN namespace VGame  { namespace Native { 
#define NAMESPACE_NATIVE_END } }

typedef  unsigned       char UBYTE ;
typedef                 char SBYTE ;
typedef  unsigned short int  UWORD ;
typedef           short int  SWORD ;
typedef  unsigned       long ULONG ;
typedef                 long SLONG ;
typedef  unsigned long  long DLONG ;
typedef           long  long LLONG ;

#define __STDC_CONSTANT_MACROS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#include <windows.h>

#include "rtc3021.h"
#include "key.h"
#include "rand.h"
#include "game.h"
#include "buffer.h"
#include "lamp.h"
#include "meter.h"
#include "ssr.h"
#include "password.h"
#include "adjustvalue.h"
#include "io.h"
#include "flashrom.h"

#include "memory.h"
#include "g1_define.h"
#include "master.h"
#include "slave.h"
#include "record.h"
#include "macro.h"
#include "recsys.h"
#include "chance.h"
#include "gameassign.h"
#include "gamecheck.h"
#include "reel.h"
#include "scroll.h"
#include "wupchance.h"

namespace VGame
{
	namespace Native
	{
		namespace Dump
		{
			class WheelDumper;
		}
	}
}

#endif