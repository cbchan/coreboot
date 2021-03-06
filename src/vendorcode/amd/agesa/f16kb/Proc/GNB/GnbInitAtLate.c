/* $NoKeywords:$ */
/**
 * @file
 *
 * GNB late init interface
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 85198 $   @e \$Date: 2013-01-03 13:49:32 -0600 (Thu, 03 Jan 2013) $
 *
 */
/*
*****************************************************************************
*
 * Copyright (c) 2008 - 2013, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ***************************************************************************
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "AGESA.h"
#include  "Ids.h"
#include  "Gnb.h"
#include  "OptionGnb.h"
#include  "GnbLibFeatures.h"
#include  "Filecode.h"
#define FILECODE PROC_GNB_GNBINITATLATE_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern  OPTION_GNB_CONFIGURATION  GnbLateFeatureTable[];
extern  BUILD_OPT_CFG             UserOptions;
extern  GNB_BUILD_OPTIONS         GnbBuildOptions;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
GnbInitDataStructAtLateDef (
  IN OUT   GNB_LATE_CONFIGURATION   *GnbLateConfigPtr,
  IN       AMD_LATE_PARAMS          *LateParamsPtr
  );

AGESA_STATUS
GnbInitAtLate (
  IN OUT   AMD_LATE_PARAMS         *LateParamsPtr
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Default constructor of GNB configuration at Late
 *
 *
 *
 * @param[in] GnbLateConfigPtr    Pointer to gnb Late configuration params.
 * @param[in] LateParamsPtr       Pointer to Late configuration params.
 */
VOID
GnbInitDataStructAtLateDef (
  IN OUT   GNB_LATE_CONFIGURATION   *GnbLateConfigPtr,
  IN       AMD_LATE_PARAMS          *LateParamsPtr
  )
{
  UINT32            Property;

  Property = TABLE_PROPERTY_DEFAULT;
  Property |= GnbBuildOptions.CfgBapmSupport ? TABLE_PROPERTY_BAPM : 0;

  IDS_OPTION_HOOK (IDS_GNB_PROPERTY, &Property,
      (AMD_CONFIG_PARAMS *)&LateParamsPtr->StdHeader);

  GnbLateConfigPtr->DockedTdpHeadroom = FALSE;
  if ((Property & TABLE_PROPERTY_BAPM) && UserOptions.CfgDockedTdpHeadroom) {
    GnbLateConfigPtr->DockedTdpHeadroom = TRUE;
  }

}

/*----------------------------------------------------------------------------------------*/
/**
 * Init GNB at Late post
 *
 *
 *
 * @param[in,out] LateParamsPtr    Pointer to late configuration params.
 * @retval                         Initialization status.
 */

AGESA_STATUS
GnbInitAtLate (
  IN OUT   AMD_LATE_PARAMS         *LateParamsPtr
  )
{
  AGESA_STATUS  Status;
  Status = GnbLibDispatchFeatures (&GnbLateFeatureTable[0], &LateParamsPtr->StdHeader);
  return  Status;
}
