/*******************************************************************************
**
**      GSC-18128-1, "Core Flight Executive Version 6.7"
**
**      Copyright (c) 2006-2019 United States Government as represented by
**      the Administrator of the National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      Licensed under the Apache License, Version 2.0 (the "License");
**      you may not use this file except in compliance with the License.
**      You may obtain a copy of the License at
**
**        http://www.apache.org/licenses/LICENSE-2.0
**
**      Unless required by applicable law or agreed to in writing, software
**      distributed under the License is distributed on an "AS IS" BASIS,
**      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**      See the License for the specific language governing permissions and
**      limitations under the License.
**
** File: robot_sim.h
**
** Purpose:
**   This file is main hdr file for the ros application.
**
**
*******************************************************************************/

#ifndef _robot_sim_h_
#define _robot_sim_h_

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include "robot_sim_perfids.h"
#include "robot_sim_msgids.h"
#include "robot_sim_msg.h"

#include "ros_app_msgids.h"

/***********************************************************************/
#define ROBOT_SIM_PIPE_DEPTH 32 /* Depth of the Command Pipe for Application */

#define ROBOT_SIM_NUMBER_OF_TABLES 1 /* Number of Table(s) */

/* Define filenames of default data images for tables */
#define ROBOT_SIM_TABLE_FILE "/cf/robot_sim_tbl.tbl"

#define ROBOT_SIM_TABLE_OUT_OF_RANGE_ERR_CODE -1

#define ROBOT_SIM_TBL_ELEMENT_1_MAX 10
/************************************************************************
** Type Definitions
*************************************************************************/

/*
** Global Data
*/

typedef struct
{
    /*
    ** Command interface counters...
    */
    uint8 CmdCounter;
    uint8 ErrCounter;

    /*
    ** Housekeeping telemetry packet...
    */
    RobotSimHkTlm_t HkTlm;
    RobotSimCmd_t RobotCmd;

    /*
    ** Run Status variable used in the main processing loop
    */
    uint32 RunStatus;

    /*
    ** Operational data (not reported in housekeeping)...
    */
    CFE_SB_PipeId_t CommandPipe;
    CFE_SB_PipeId_t RosPipe;

    /*
    ** Initialization data (not reported in housekeeping)...
    */
    char   RosPipeName[CFE_MISSION_MAX_API_LEN];
    char   PipeName[CFE_MISSION_MAX_API_LEN];
    uint16 PipeDepth;

    CFE_EVS_BinFilter_t EventFilters[ROBOT_SIM_EVENT_COUNTS];
    CFE_TBL_Handle_t    TblHandles[ROBOT_SIM_NUMBER_OF_TABLES];

} RobotSimData_t;

/****************************************************************************/
/*
** Local function prototypes.
**
** Note: Except for the entry point (RobotSimMain), these
**       functions are not called from any other source module.
*/
void  RobotSimMain(void);
int32 RobotSimInit(void);
void  RobotSimProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr);
void  RobotSimProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr);
void  RobotSimProcessRosApp(CFE_SB_Buffer_t *SBBufPtr);
// void  RobotSimProcessRosApp(CFE_MSG_Message_t *MsgPtr);
int32 RobotSimReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg);
int32 RobotSimResetCounters(const RobotSimResetCountersCmd_t *Msg);
int32 RobotSimProcess(const RobotSimProcessCmd_t *Msg);
int32 RobotSimNoop(const RobotSimNoopCmd_t *Msg);
void  RobotSimHelloCmd(const RobotSimNoopCmd_t *Msg);
void  RobotSimGetCrc(const char *TableName);

int32 RobotSimTblValidationFunc(void *TblData);

bool RobotSimVerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength);


#endif /* _robot_sim_h_ */