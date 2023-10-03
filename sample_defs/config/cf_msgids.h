/************************************************************************
 * NASA Docket No. GSC-18,447-1, and identified as “CFS CFDP (CF)
 * Application version 3.0.0”
 *
 * Copyright (c) 2019 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * @file
 *  The CF Application Message IDs header file
 */

#ifndef CF_MSGIDS_H
#define CF_MSGIDS_H

/**
 * \defgroup cfscfcmdmid CFS CFDP Command Message IDs
 * \{
 */

#define CF_CMD_MID     (0x18B3) /**< \brief Message ID for commands */
#define CF_SEND_HK_MID (0x18B4) /**< \brief Message ID to request housekeeping telemetry */
#define CF_WAKE_UP_MID (0x18B5) /**< \brief Message ID for waking up the processing cycle */

/**\}*/

/**
 * \defgroup cfscftlmmid CFS CFDP Telemetry Message IDs
 * \{
 */

#define CF_HK_TLM_MID  (0x08B0) /**< \brief Message ID for housekeeping telemetry */
#define CF_EOT_TLM_MID (0x08B3) /**< \brief Message ID for end of transaction telemetry */

/**\}*/

/**
 * \defgroup cfscftlmmid CFS CFDP PDUMessage IDs (originally set in default cf_def_config.c table only)
 * \{
 */

// CFDP Entity IDs (see below for channel MID mappings)
#define CF_ROSGSW_EID 1
#define CF_ROSFSW_EID 2
#define CF_FSW_EID    25

// CH0: ROSGSW to FSW
#define CF_CH0_IN_MID  0x18c8 // ROSGSW to FSW
#define CF_CH0_OUT_MID 0x08c2 // FSW to ROSGSW

// CH1: FSW to ROSFSW
#define CF_CH1_IN_MID  0x18c9 // ROSFSW to FSW
#define CF_CH1_OUT_MID 0x08c3 // FSW to ROSFSW

// CH2: ROSFSW to ROSGSW (FSW is a pass-through only)
#define CF_CH2_IN_MID  0x18ca  // ROSGSW to ROSFSW
#define CF_CH2_OUT_MID 0x08c4  // ROSFSW to ROSGSW

/**\}*/

#endif /* !CF_MSGIDS_H */
