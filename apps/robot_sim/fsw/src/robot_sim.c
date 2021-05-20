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
** File: robot_sim.c
**
** Purpose:
**   This file contains the source code for the ros App.
**
*******************************************************************************/

/*
** Include Files:
*/
#include "robot_sim_events.h"
#include "robot_sim_version.h"
#include "robot_sim.h"
#include "robot_sim_table.h"

#include <string.h>

/*
** global data
*/
RobotSimData_t RobotSimData;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/* RobotSimMain() -- Application entry point and main process loop         */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void RobotSimMain(void)
{
    int32            status;
    // CFE_SB_Buffer_t *SBBufPtr;
    CFE_SB_Buffer_t *RosAppBufPtr;
    // CFE_MSG_Message_t *MsgPtr    = 0;

    /*
    ** Register the app with Executive services
    */
    // CFE_ES_RegisterApp();

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(ROBOT_SIM_PERF_ID);

    /*
    ** Perform application specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = RobotSimInit();

    if (status != CFE_SUCCESS)
    {
        RobotSimData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** ros Runloop
    */
    while (CFE_ES_RunLoop(&RobotSimData.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(ROBOT_SIM_PERF_ID);

        /* Pend on receipt of command packet */
        // status = CFE_SB_ReceiveBuffer(&SBBufPtr, RobotSimData.CommandPipe, CFE_SB_PEND_FOREVER); //CFE_SB_POLL CFE_SB_PEND_FOREVER


        /*
        ** Send payload...
        */
        // starting to send the changning joint states
        // using random values 0-9 for now because that's easy to asciify for wireshark
        // RobotSimData.HkTlm.Payload.str[0] = 'H';
        // RobotSimData.HkTlm.Payload.str[1] = 'i';
        // RobotSimData.HkTlm.Payload.str[2] = '!';
        // for (uint8 i = 0; i < ROBOT_SIM_DOF; ++i)
        // {
        //     // RobotSimData.HkTlm.Payload.joint_state[i].position = (float)rand()/(float)(RAND_MAX/1.57);
        //     // printf("RobotSimInit() -- randomized joint state[%d]: %g\n", i, RobotSimData.HkTlm.Payload.joint_state[i].position);
        //     RobotSimData.HkTlm.Payload.joint_state[i].position = rand()%9 + '0';
        //     printf("RobotSimInit() -- randomized joint state[%d] to %c\n", i, RobotSimData.HkTlm.Payload.joint_state[i].position);
        // }

        // CFE_SB_TimeStampMsg(&RobotSimData.HkTlm.TlmHeader.Msg);
        // CFE_SB_TransmitMsg(&RobotSimData.HkTlm.TlmHeader.Msg, true);

        /*
        ** Performance Log Entry Stamp
        */
        // CFE_ES_PerfLogEntry(ROBOT_SIM_PERF_ID);

        // commented out for now, should add this back in later as it handles commands and telemetry
        // if (status == CFE_SUCCESS)
        // {
        //     RobotSimProcessCommandPacket(SBBufPtr);
        // }
        // else
        // {
        //     CFE_EVS_SendEvent(ROBOT_SIM_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
        //                       "Robot Sim: SB Pipe Read Error, App Will Exit");

        //     RobotSimData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        // }


        // wait for a new message from the ROS APP        
        printf("\n");
        status = CFE_SB_ReceiveBuffer(&RosAppBufPtr, RobotSimData.CommandPipe, CFE_SB_PEND_FOREVER); //CFE_SB_POLL CFE_SB_PEND_FOREVER
        // status = CFE_SB_ReceiveBuffer((CFE_SB_Buffer_t **)&MsgPtr, RobotSimData.RosPipe, CFE_SB_PEND_FOREVER); //CFE_SB_POLL CFE_SB_PEND_FOREVER
        if (status == CFE_SUCCESS)
        {
            printf("RobotSimMain() -- received msg\n");
            RobotSimProcessRosApp(RosAppBufPtr);
            // RobotSimProcessRosApp(MsgPtr);
        }
        else if (status == CFE_SB_TIME_OUT)
        {
            printf("RobotSimMain() -- timed out!\n");
        }
        else
        {
            if (status == CFE_SB_BAD_ARGUMENT)
                printf("RobotSimMain() -- buff received bad arg!!\n");
            else if (status == CFE_SB_PIPE_RD_ERR)
                printf("RobotSimMain() -- buff received pipe read error!!\n");
            else // CFE_SB_NO_MESSAGE
                printf("RobotSimMain() -- received NO (bad) msg \n"); //0x%08lX\n", (unsigned long)status);
            // CFE_EVS_SendEvent(ROBOT_SIM_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
            //                   "Robot Sim: SB Pipe Read Error, App Will Exit");

            // RobotSimData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(ROBOT_SIM_PERF_ID);

    CFE_ES_ExitApp(RobotSimData.RunStatus);

} /* End of RobotSimMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* RobotSimInit() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 RobotSimInit(void)
{
    int32 status;

    RobotSimData.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app command execution counters
    */
    RobotSimData.CmdCounter = 0;
    RobotSimData.ErrCounter = 0;

    /*
    ** Initialize app configuration data
    */
    RobotSimData.PipeDepth = ROBOT_SIM_PIPE_DEPTH;

    strncpy(RobotSimData.PipeName, "ROBOT_SIM_CMD_PIPE", sizeof(RobotSimData.PipeName));
    RobotSimData.PipeName[sizeof(RobotSimData.PipeName) - 1] = 0;

    /*
    ** Initialize event filter table...
    */
    RobotSimData.EventFilters[0].EventID = ROBOT_SIM_STARTUP_INF_EID;
    RobotSimData.EventFilters[0].Mask    = 0x0000;
    RobotSimData.EventFilters[1].EventID = ROBOT_SIM_COMMAND_ERR_EID;
    RobotSimData.EventFilters[1].Mask    = 0x0000;
    RobotSimData.EventFilters[2].EventID = ROBOT_SIM_COMMANDNOP_INF_EID;
    RobotSimData.EventFilters[2].Mask    = 0x0000;
    RobotSimData.EventFilters[3].EventID = ROBOT_SIM_COMMANDRST_INF_EID;
    RobotSimData.EventFilters[3].Mask    = 0x0000;
    RobotSimData.EventFilters[4].EventID = ROBOT_SIM_INVALID_MSGID_ERR_EID;
    RobotSimData.EventFilters[4].Mask    = 0x0000;
    RobotSimData.EventFilters[5].EventID = ROBOT_SIM_LEN_ERR_EID;
    RobotSimData.EventFilters[5].Mask    = 0x0000;
    RobotSimData.EventFilters[6].EventID = ROBOT_SIM_PIPE_ERR_EID;
    RobotSimData.EventFilters[6].Mask    = 0x0000;
    RobotSimData.EventFilters[7].EventID = ROBOT_SIM_HELLO_WORLD_INF_EID;
    RobotSimData.EventFilters[7].Mask    = 0x0000;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(RobotSimData.EventFilters, ROBOT_SIM_EVENT_COUNTS, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error Registering Events, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Initialize housekeeping packet (clear user data area).
    */
    CFE_MSG_Init(&RobotSimData.HkTlm.TlmHeader.Msg, ROBOT_SIM_HK_TLM_MID, sizeof(RobotSimData.HkTlm));

    // init the joint states
    for (uint8 i = 0; i < ROBOT_SIM_DOF; ++i)
    {
        RobotSimJoint_t jnt;
        // jnt.index = i;
        // jnt.position = 0.0;
        jnt.index = i + '0';
        jnt.position = '0';
        RobotSimData.HkTlm.Payload.joint_state[i] = jnt;
        // printf("RobotSimInit() -- creating joint: %d out of %d with position: %g\n", i+1, ROBOT_SIM_DOF, jnt.position);
    }

    // CFE_MSG_Init(&RobotSimData.RobotCmd.CmdHeader.Msg, ROBOT_SIM_MSG_CMD_MID, sizeof(RobotSimData.RobotCmd));

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&RobotSimData.CommandPipe, RobotSimData.PipeDepth, RobotSimData.PipeName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error creating pipe, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to Housekeeping request commands
    */
    status = CFE_SB_Subscribe(ROBOT_SIM_SEND_HK_MID, RobotSimData.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error Subscribing to HK request, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to ground command packets
    */
    status = CFE_SB_Subscribe(ROBOT_SIM_CMD_MID, RobotSimData.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error Subscribing to Command, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }

    /*
    ** Register Table(s)
    */
    status = CFE_TBL_Register(&RobotSimData.TblHandles[0], "RobotSimTable", sizeof(RobotSimTable_t),
                              CFE_TBL_OPT_DEFAULT, RobotSimTblValidationFunc);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error Registering Table, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }
    else
    {
        status = CFE_TBL_Load(RobotSimData.TblHandles[0], CFE_TBL_SRC_FILE, ROBOT_SIM_TABLE_FILE);
    }

    CFE_EVS_SendEvent(ROBOT_SIM_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION, "Robot Sim Initialized.%s",
                      ROBOT_SIM_VERSION_STRING);

    /*
    ** create a pipe to get msg in from other cpu
    */
    // strncpy(RobotSimData.RosPipeName, "ROBOT_SIM_ROS_PIPE", sizeof(RobotSimData.RosPipeName));
    // RobotSimData.RosPipeName[sizeof(RobotSimData.RosPipeName) - 1] = 0;

    /*
    ** Create ROS message pipe.
    */
    // status = CFE_SB_CreatePipe(&RobotSimData.RosPipe, RobotSimData.PipeDepth, RobotSimData.RosPipeName);
    // if (status != CFE_SUCCESS)
    // {
    //     CFE_ES_WriteToSysLog("Robot Sim: Error creating ROS pipe, RC = 0x%08lX\n", (unsigned long)status);
    //     return (status);
    // }

    /*
    ** Subscribe to ros app commands
    */
    status = CFE_SB_Subscribe(0x1896, RobotSimData.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error Subscribing to ROS APP messages, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    return (CFE_SUCCESS);

} /* End of RobotSimInit() */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  RobotSimProcessCommandPacket                                    */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the ros    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void RobotSimProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    switch (MsgId)
    {
        case ROBOT_SIM_CMD_MID:
            RobotSimProcessGroundCommand(SBBufPtr);
            break;

        case ROBOT_SIM_SEND_HK_MID:
            RobotSimReportHousekeeping((CFE_MSG_CommandHeader_t *)SBBufPtr);
            break;

        default:
            CFE_EVS_SendEvent(ROBOT_SIM_INVALID_MSGID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "robot sim: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }

    return;

} /* End RobotSimProcessCommandPacket */


void RobotSimProcessRosApp(CFE_SB_Buffer_t *SBBufPtr)
{
    printf("\nRobotSimProcessRosApp() -- robot sim is processing a buffer....\n");
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);
    printf("RobotSimProcessRosApp() -- we're processing the cmd from MID: 0x%04x\n", CFE_SB_MsgIdToValue(MsgId));

    CFE_MSG_Type_t type = CFE_MSG_Type_Invalid;
    CFE_MSG_GetType(&SBBufPtr->Msg, &type);
    if (type == CFE_MSG_Type_Tlm)
    {
        printf("RobotSimProcessRosApp() -- type is TLM\n");
    }
    else if (type == CFE_MSG_Type_Cmd)
    {
        printf("RobotSimProcessRosApp() -- type is CMD\n");

        bool has = false;
        CFE_MSG_GetHasSecondaryHeader(&SBBufPtr->Msg, &has);
        if (has)
        {
            printf("RobotSimProcessRosApp() -- there is a 2nd header\n");
        }
        else
        {
            printf("RobotSimProcessRosApp() -- no 2nd header\n");
            // if it gets here it doesn't really matter if we add a 2nd header because the value will be 0
            // CFE_MSG_SetHasSecondaryHeader((CFE_MSG_Message_t *)&CmdMsg, true);
        }

        CFE_MSG_FcnCode_t CommandCode = 0;
        int32 ret = CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

        if (ret == CFE_SUCCESS)
            printf("RobotSimProcessRosApp() -- we're processing the cmd: %d\n", CommandCode);
        else if (ret == CFE_MSG_BAD_ARGUMENT)
            printf("RobotSimProcessRosApp() -- we have a bad msg argument\n");
        else
            printf("RobotSimProcessRosApp() -- we have a wrong msg type!!\n");

    }
    else
    {
        printf("RobotSimProcessRosApp() -- INVALID type\n");
    }


    return;
}

// void RobotSimProcessRosApp(CFE_MSG_Message_t *MsgPtr)
// {
//     printf("\nRobotSimProcessRosApp() -- robot sim is processing a msg....\n");

//     CFE_SB_MsgId_t    MsgId   = 0;
//     CFE_MSG_FcnCode_t FcnCode = 0;

//     if (CFE_MSG_GetMsgId(MsgPtr, &MsgId) != CFE_SUCCESS)
//     {
//         return;
//     }

//     printf("RobotSimProcessRosApp() -- we're processing the cmd from MID: 0x%04x\n", CFE_SB_MsgIdToValue(MsgId));

//     int32 ret = CFE_MSG_GetFcnCode((CFE_MSG_CommandHeader_t *)MsgPtr, &FcnCode);
//     if (ret != CFE_SUCCESS)
//     {
//         if (ret == CFE_MSG_BAD_ARGUMENT)
//             printf("RobotSimProcessRosApp() -- bad msg argument\n");
//         else
//             printf("RobotSimProcessRosApp() -- wrong msg type!!\n");
//     }
//     else
//     {
//         printf("RobotSimProcessRosApp() -- we're processing the cmd: %d\n", FcnCode);
//     }


//     return;

// } /* End RobotSimProcessCommandPacket */



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* RobotSimProcessGroundCommand() -- robot sim ground commands                */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void RobotSimProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_MSG_FcnCode_t CommandCode = 0;

    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);
    printf("RobotSimProcessGroundCommand() -- we're getting a ground command...\n");
    /*
    ** Process "known" ros app ground commands
    */
    switch (CommandCode)
    {
        case ROBOT_SIM_NOOP_CC:
            if (RobotSimVerifyCmdLength(&SBBufPtr->Msg, sizeof(RobotSimNoopCmd_t)))
            {
                RobotSimNoop((RobotSimNoopCmd_t *)SBBufPtr);
            }

            break;

        case ROBOT_SIM_RESET_COUNTERS_CC:
            if (RobotSimVerifyCmdLength(&SBBufPtr->Msg, sizeof(RobotSimResetCountersCmd_t)))
            {
                RobotSimResetCounters((RobotSimResetCountersCmd_t *)SBBufPtr);
            }

            break;

        case ROBOT_SIM_PROCESS_CC:
            if (RobotSimVerifyCmdLength(&SBBufPtr->Msg, sizeof(RobotSimProcessCmd_t)))
            {
                RobotSimProcess((RobotSimProcessCmd_t *)SBBufPtr);
            }

            break;

        case ROBOT_SIM_HELLO_WORLD_CC:
            if (RobotSimVerifyCmdLength(&SBBufPtr->Msg, sizeof(RobotSimResetCountersCmd_t)))
            {
                RobotSimHelloCmd((RobotSimNoopCmd_t *)SBBufPtr);
            }

            break;

        /* default case already found during FC vs length test */
        default:
            CFE_EVS_SendEvent(ROBOT_SIM_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR,
                              "Invalid ground command code: CC = %d", CommandCode);
            break;
    }


    return;

} /* End of RobotSimProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  RobotSimReportHousekeeping                                          */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 RobotSimReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg)
{
    int i;
    
    printf("RobotSimReportHousekeeping() -- sending joint states as part of housekeeping...\n");
    
    /*
    ** Get command execution counters...
    */
    RobotSimData.HkTlm.Payload.CommandErrorCounter = RobotSimData.ErrCounter;
    RobotSimData.HkTlm.Payload.CommandCounter      = RobotSimData.CmdCounter;

    /*
    ** Send housekeeping telemetry packet...
    */
    // RobotSimData.HkTlm.Payload.str[0] = 'H';
    // RobotSimData.HkTlm.Payload.str[1] = 'i';
    // RobotSimData.HkTlm.Payload.str[2] = '!';
    // for (uint8 i = 0; i < ROBOT_SIM_DOF; ++i)
    // {
    //     // RobotSimData.HkTlm.Payload.joint_state[i].position = (float)rand()/(float)(RAND_MAX/1.57);
    //     RobotSimData.HkTlm.Payload.joint_state[i].position = ((uint8)rand()/(uint8)(RAND_MAX/9)) + '0';
    //     printf("RobotSimInit() -- randomized joint state[%d]", i);//: %c\n", i, RobotSimData.HkTlm.Payload.joint_state[i].position);
    // }
    
    CFE_SB_TimeStampMsg(&RobotSimData.HkTlm.TlmHeader.Msg);
    CFE_SB_TransmitMsg(&RobotSimData.HkTlm.TlmHeader.Msg, true);

    /*
    ** Manage any pending table loads, validations, etc.
    */
    for (i = 0; i < ROBOT_SIM_NUMBER_OF_TABLES; i++)
    {
        CFE_TBL_Manage(RobotSimData.TblHandles[i]);
    }

    return CFE_SUCCESS;

} /* End of RobotSimReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* RobotSimNoop -- ROS NOOP commands                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 RobotSimNoop(const RobotSimNoopCmd_t *Msg)
{

    RobotSimData.CmdCounter++;

    CFE_EVS_SendEvent(ROBOT_SIM_COMMANDNOP_INF_EID, CFE_EVS_EventType_INFORMATION, "robot sim: NOOP command %s",
                      ROBOT_SIM_VERSION);

    return CFE_SUCCESS;

} /* End of RobotSimNoop */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* RobotHelloCmd -- ros NOOP commands                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void RobotSimHelloCmd(const RobotSimNoopCmd_t *Msg)
{
    RobotSimData.CmdCounter++;

    CFE_EVS_SendEvent(ROBOT_SIM_HELLO_WORLD_INF_EID, CFE_EVS_EventType_INFORMATION, "robot sim: Hello, ros! %s",
                      ROBOT_SIM_VERSION);

} /* End of RobotHelloCmd */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  RobotSimResetCounters                                               */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 RobotSimResetCounters(const RobotSimResetCountersCmd_t *Msg)
{

    RobotSimData.CmdCounter = 0;
    RobotSimData.ErrCounter = 0;

    CFE_EVS_SendEvent(ROBOT_SIM_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION, "robot sim: RESET command");

    return CFE_SUCCESS;

} /* End of RobotSimResetCounters() */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* RobotSimVerifyCmdLength() -- Verify command packet length                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool RobotSimVerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength)
{
    bool              result       = true;
    size_t            ActualLength = 0;
    CFE_SB_MsgId_t    MsgId        = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_FcnCode_t FcnCode      = 0;

    printf("RobotSimVerifyCmdLength() --\n");

    CFE_MSG_GetSize(MsgPtr, &ActualLength);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_MSG_GetMsgId(MsgPtr, &MsgId);
        CFE_MSG_GetFcnCode(MsgPtr, &FcnCode);

        CFE_EVS_SendEvent(ROBOT_SIM_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)FcnCode, (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        RobotSimData.ErrCounter++;
    }

    return (result);

} /* End of RobotSimVerifyCmdLength() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* RobotSimGetCrc -- Output CRC                                     */
/*                                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void RobotSimGetCrc(const char *TableName)
{
    int32          status;
    uint32         Crc;
    CFE_TBL_Info_t TblInfoPtr;

    printf("RobotSimGetCrc() -- \n");

    status = CFE_TBL_GetInfo(&TblInfoPtr, TableName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error Getting Table Info");
    }
    else
    {
        Crc = TblInfoPtr.Crc;
        CFE_ES_WriteToSysLog("Robot Sim: CRC: 0x%08lX\n\n", (unsigned long)Crc);
    }

    return;

} /* End of RobotSimGetCrc */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* RobotSimTblValidationFunc -- Verify contents of First Table      */
/* buffer contents                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 RobotSimTblValidationFunc(void *TblData)
{
    int32               ReturnCode = CFE_SUCCESS;
    RobotSimTable_t *TblDataPtr = (RobotSimTable_t *)TblData;

    printf("RobotSimTblValidationFunc() -- validating a table\n");

    /*
    ** Ros Table Validation
    */
    if (TblDataPtr->Int1 > ROBOT_SIM_TBL_ELEMENT_1_MAX)
    {
        /* First element is out of range, return an appropriate error code */
        ReturnCode = ROBOT_SIM_TABLE_OUT_OF_RANGE_ERR_CODE;
    }

    return ReturnCode;

} /* End of RobotSimTBLValidationFunc() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  RobotSimProcess                                                     */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function Process Ground Station Command                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
int32 RobotSimProcess(const RobotSimProcessCmd_t *Msg)
{
    int32               status;
    RobotSimTable_t *TblPtr;
    const char *        TableName = "RobotSim.RobotSimTable";

    /* Ros Use of Table */

    printf("RobotSimProcess() --\n");

    status = CFE_TBL_GetAddress((void *)&TblPtr, RobotSimData.TblHandles[0]);

    if (status < CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Fail to get table address: 0x%08lx", (unsigned long)status);
        return status;
    }

    CFE_ES_WriteToSysLog("Robot Sim: Table Value 1: %d  Value 2: %d", TblPtr->Int1, TblPtr->Int2);

    RobotSimGetCrc(TableName);

    status = CFE_TBL_ReleaseAddress(RobotSimData.TblHandles[0]);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Fail to release table address: 0x%08lx", (unsigned long)status);
        return status;
    }

    return CFE_SUCCESS;

} /* End of RobotSimProcessCC */