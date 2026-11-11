#ifndef PRINT_HEADER
#define PRINT_HEADER


#include <stdio.h>
#include <string.h>

#include "SystemDependent.h"

#include "LbTypes.h"
#include "LbError.h"
#include "LbDebug.h"
#include "LbEnvironment.h"
#include "LbFile.h"
#include "LbMemory.h"
#include "LbInterface.h"
#include "LbParamFile.h"
#include "LbHeader.h"

#include "Photon.h"
#include "PhgParams.h"
#include "ColTypes.h"
#include "ColParams.h"
#include "DetTypes.h"
#include "DetParams.h"
#include "CylPos.h"
#include "PhgMath.h"
#include "PhoHFile.h"
#include "ProdTbl.h"
#include "PhoTrk.h"
#include "SubObj.h"
#include "EmisList.h"
#include "Collimator.h"
#include "Detector.h"
#include "PhgHdr.h"
#include "phg.h"
#include "PhgBin.h"


#ifdef __cplusplus
extern "C" {
#endif

Boolean         PrintHeader(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

#endif
