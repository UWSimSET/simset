#ifndef BIN_PHG_HDR
#define BIN_PHG_HDR

#include <stdio.h>
#include <string.h>

#include "SystemDependent.h"

#include "LbDebug.h"
#include "LbEnvironment.h"
#include "LbError.h"
#include "LbFile.h"
#include "LbHeader.h"
#include "LbInterface.h"
#include "LbMemory.h"
#include "LbParamFile.h"
#include "LbTypes.h"

#include "ColParams.h"
#include "ColTypes.h"
#include "Collimator.h"
#include "CylPos.h"
#include "DetParams.h"
#include "DetTypes.h"
#include "Detector.h"
#include "EmisList.h"
#include "PhgBin.h"
#include "PhgHdr.h"
#include "PhgMath.h"
#include "PhgParams.h"
#include "PhoHFile.h"
#include "PhoTrk.h"
#include "Photon.h"
#include "ProdTbl.h"
#include "SubObj.h"
#include "phg.h"

/* LOCAL CONSTANTS */
#define PHGRDHST_IsUsePHGHistory()                                            \
  LbFgIsSet (PhgOptions, LBFlag0) /* Will we use the PHG history file */
#define PHGRDHST_IsUseColHistory()                                            \
  LbFgIsSet (PhgOptions, LBFlag1) /* Will we use the Collimator history file  \
                                   */
#define PHGRDHST_IsUseDetHistory()                                            \
  LbFgIsSet (PhgOptions, LBFlag2) /* Will we use the Detector history file */

#define PHGRDHST_NumFlags 3 /* Number of flags defined */

/* LOCAL TYPES */
typedef enum
{
  Null,
  Decay,
  Photon
} EventTy;

#ifdef __cplusplus
extern "C"
{
#endif

  Boolean phgrdhstInitialize (int argc, char *argv[]);
  void phgrdhstTerminate (void);
  Boolean phgbin (int argc, char *argv[]);
  EventTy readEvent (FILE *historyFile, PHG_Decay *decayPtr,
                     PHG_DetectedPhoton *photonPtr);
  EventTy oldReadEvent (FILE *historyFile, PHG_Decay *decayPtr,
                        PHG_DetectedPhoton *photonPtr, Boolean isOldPhotons1,
                        Boolean isOldPhotons2);
  Boolean phgrdhstStandard (char *argv[]);
  Boolean phgrdhstCustom (char *argv[]);
  void phgbinProcessPhotons (PhoHFileHkTy *histHk, PHG_Decay *decayPtr,
                             PHG_TrackingPhoton *bluePhotons,
                             LbUsFourByte numBlues,
                             PHG_TrackingPhoton *pinkPhotons,
                             LbUsFourByte numPinks);

#ifdef __cplusplus
}
#endif

#endif
