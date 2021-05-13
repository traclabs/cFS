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

    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp();

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


    // CFE_SB_Buffer_t *RosSBNPtr;
    CFE_SB_Buffer_t *RosCmdPtr;

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
        // status = CFE_SB_ReceiveBuffer(&SBBufPtr, RobotSimData.CommandPipe, CFE_SB_POLL); //CFE_SB_PEND_FOREVER


        /*
        ** Performance Log Entry Stamp
        */
        // CFE_ES_PerfLogEntry(ROBOT_SIM_PERF_ID);

        // if (status == CFE_SUCCESS)
        // {
        //     RobotSimProcessCommandPacket(SBBufPtr);
        // }
        // else
        // {
        //     // CFE_EVS_SendEvent(ROBOT_SIM_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
        //     //                   "Robot Sim: SB Pipe Read Error, App Will Exit");

        //     // RobotSimData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        // }
     

        // // adding to test the new SBN pipe
        // /*
        // ** Get command execution counters...
        // */
        // RobotSimData.RosHk.ErrCounter = RobotSimData.ErrCounter;
        // RobotSimData.RosHk.CmdCounter      = RobotSimData.CmdCounter;

        // /*
        // ** Send housekeeping telemetry packet...
        // */
        // CFE_SB_TimeStampMsg(&RobotSimData.RosHk.TlmHeader.Msg);
        // CFE_SB_TransmitMsg(&RobotSimData.RosHk.TlmHeader.Msg, true);

        // status = CFE_SB_ReceiveBuffer(&RosSBNPtr, RobotSimData.RobotSimPipe_1, CFE_SB_POLL);
        // if (status == CFE_SUCCESS)
        // {
        //     RobotSimProcessSBN(RosSBNPtr);
        // }
        // else if (status == CFE_SB_TIME_OUT)
        // {
        //     printf("\nWE TIMED OUT WAITING\n");
        // }
        // else
        // {
        //     printf("\nbad msg 0x%08lX\n", (unsigned long)status);
        //     CFE_EVS_SendEvent(ROBOT_SIM_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
        //                       "Robot Sim: SB Pipe Read Error, App Will Exit");

        //     RobotSimData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        // }


        // 5/12 adding to test the new SBN command pipe
        /*
        ** Send cmd packet...
        theirs:
        CFE_MSG_CommandHeader_t CmdMsg;
        CFE_MSG_Init((CFE_MSG_Message_t *)&CmdMsg, CFE_SB_SUB_RPT_CTRL_MID, sizeof(CmdMsg));
        CFE_MSG_SetFcnCode((CFE_MSG_Message_t *)&CmdMsg, CFE_SB_ENABLE_SUB_REPORTING_CC);
        CFE_MSG_Init(&RobotSimData.SbnCmd.CmdHeader.Msg, ROBOT_SIM_SBN_CMD_ID, sizeof(RobotSimData.SbnCmd));
        */

        // printf("\nBIG TEST\n");
        // CFE_MSG_CommandHeader_t cmd;
        // CFE_MSG_Message_t      *msgptr  = &cmd.Msg;
        // CFE_MSG_FcnCode_t       val  = 0x11;
        // CFE_MSG_FcnCode_t       actual  = 0x7F;

        // CFE_MSG_SetType(msgptr, CFE_MSG_Type_Cmd);
        // CFE_MSG_SetHasSecondaryHeader(msgptr, true);

        // int32 test = CFE_MSG_SetFcnCode(msgptr, val);
        // if (test == CFE_SUCCESS)
        // {
        //     printf("good test\n");

        //     int32 getter = CFE_MSG_GetFcnCode(msgptr, &actual);

        //     if (getter == CFE_SUCCESS)
        //         printf("\tyayy we got it == %d\n", actual);
        //     else if (getter == CFE_MSG_BAD_ARGUMENT)
        //         printf("bad getter: bad argument\n");
        //     else // CFE_MSG_WRONG_MSG_TYPE)
        //         printf("bad getter: wrong msg type\n");
        // }
        // else if (test == CFE_MSG_BAD_ARGUMENT)
        //     printf("bad test: bad argument\n");
        // else // CFE_MSG_WRONG_MSG_TYPE)
        //     printf("bad test: wrong msg type\n");

        // CFE_MSG_Type_t type;
        // CFE_MSG_GetType(&RobotSimData.SbnCmd.CmdHeader.Msg, &type);
        // if (type == CFE_MSG_Type_Tlm)
        //     printf("TYPE IS TLM\n");
        // else if (type == CFE_MSG_Type_Cmd)
        //     printf("TYPE IS\n");
        // else //CFE_MSG_Type_Invalid
        //     printf("INVALID\n");

        // printf("looking to see if our class msg has 2nd header\n");
        // bool has = false;
        // CFE_MSG_GetHasSecondaryHeader(&RobotSimData.SbnCmd.CmdHeader.Msg, &has);
        // if (has)
        // {
        //     printf("WE HAVE A 2ND HEADER\n");
        // }
        // else
        // {
        //     printf("no 2nd header\n");
        //     if (CFE_MSG_SetHasSecondaryHeader(&RobotSimData.SbnCmd.CmdHeader.Msg, true) != CFE_SUCCESS)
        //         printf("FAILED TO SET 2ND HEADER\n");
        // }
        
        // CFE_MSG_FcnCode_t cmd_code = 0x11;

        // // CFE_MSG_CommandHeader_t CmdMsg;
        // // CFE_MSG_Init(&CmdMsg.Msg, ROBOT_SIM_SBN_CMD_ID, sizeof(CmdMsg));
        // // int32 set = CFE_MSG_SetFcnCode(&CmdMsg.Msg, cmd_code);        
        
        // int32 set = CFE_MSG_SetFcnCode(&RobotSimData.SbnCmd.CmdHeader.Msg, cmd_code);
        // if (set != CFE_SUCCESS)
        // {
        //     if (set == CFE_MSG_BAD_ARGUMENT)
        //         printf("CAN'T SET CMD: bad argument\n");
        //     else if (set == CFE_MSG_WRONG_MSG_TYPE)
        //         printf("CAN'T SET CMD: wrong msg type\n");
        //     else
        //         printf("CAN'T SET CMD: ?\n");
        // }
        // else
        // {
        //     printf("we finally set the fcn code, now sending on sbn...\n");
        //     // CFE_SB_TransmitMsg(&RobotSimData.HkTlm.TlmHeader.Msg, true);

        printf("\n");

        CFE_MSG_FcnCode_t test_code = 0x0;
        int32 get = CFE_MSG_GetFcnCode(&RobotSimData.SbnCmd.CmdHeader.Msg, &test_code);
        if (get != CFE_SUCCESS)
        {
            if (get == CFE_MSG_BAD_ARGUMENT)
                printf("RobotSimMain() -- CAN'T GET CMD: bad argument\n");
            else if (get == CFE_MSG_WRONG_MSG_TYPE)
                printf("RobotSimMain() -- CAN'T GET CMD: wrong msg type\n");
            else
                printf("RobotSimMain() -- CAN'T GET CMD: ?\n");
        }
        else
        {
            printf("RobotSimMain() -- WE HAVE TEST CMD CODE VAL: %d\n", test_code);
        }

        printf("RobotSimMain() -- going to transmit msg now\n");

        int32 ret = CFE_SB_TransmitMsg(&RobotSimData.SbnCmd.CmdHeader.Msg, true);
        if (ret != CFE_SUCCESS)
        {
            printf("RobotSimMain() -- COULDN'T TRANSMIT MSG\n");
            CFE_EVS_SendEvent(ROBOT_SIM_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "Robot Sim: SB Pipe Read Error, App Will Exit");

            RobotSimData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }

        status = CFE_SB_ReceiveBuffer(&RosCmdPtr, RobotSimData.RosSbnPipe, CFE_SB_PEND_FOREVER);
        if (status == CFE_SUCCESS)
        {
            RobotSimProcessCmd(RosCmdPtr);
        }
        else if (status == CFE_SB_TIME_OUT)
        {
            printf("RobotSimMain() -- WE TIMED OUT WAITING FOR CMD\n");
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
        // }
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

    printf("\nHEY WE'RE INITing THE ROBOT SIM APP\n");

    /*
    ** Initialize housekeeping packet (clear user data area).
    */
    CFE_MSG_Init(&RobotSimData.HkTlm.TlmHeader.Msg, ROBOT_SIM_HK_TLM_MID, sizeof(RobotSimData.HkTlm));
    
    CFE_MSG_Init(&RobotSimData.RosHk.TlmHeader.Msg, ROBOT_SIM_CMDID_1, sizeof(RobotSimData.RosHk));

    CFE_MSG_Init(&RobotSimData.SbnCmd.CmdHeader.Msg, ROBOT_SIM_SBN_CMD_ID, sizeof(RobotSimData.SbnCmd));

    printf("looking to see if our class msg has 2nd header\n");
    bool has = false;
    CFE_MSG_GetHasSecondaryHeader(&RobotSimData.SbnCmd.CmdHeader.Msg, &has);
    if (has)
    {
        printf("WE HAVE A 2ND HEADER\n");
    }
    else
    {
        printf("no 2nd header\n");
        if (CFE_MSG_SetHasSecondaryHeader(&RobotSimData.SbnCmd.CmdHeader.Msg, true) != CFE_SUCCESS)
            printf("FAILED TO SET 2ND HEADER\n");
    }
    
    CFE_MSG_FcnCode_t cmd_code = 0x11;
    int32 set = CFE_MSG_SetFcnCode(&RobotSimData.SbnCmd.CmdHeader.Msg, cmd_code);
    if (set != CFE_SUCCESS)
    {
        if (set == CFE_MSG_BAD_ARGUMENT)
            printf("CAN'T SET CMD: bad argument\n");
        else if (set == CFE_MSG_WRONG_MSG_TYPE)
            printf("CAN'T SET CMD: wrong msg type\n");
        else
            printf("CAN'T SET CMD: ?\n");
    }


    CFE_MSG_FcnCode_t test_code = 0x0;
    int32 get = CFE_MSG_GetFcnCode(&RobotSimData.SbnCmd.CmdHeader.Msg, &test_code);
    if (get != CFE_SUCCESS)
    {
        if (get == CFE_MSG_BAD_ARGUMENT)
            printf("CAN'T GET CMD: bad argument\n");
        else if (get == CFE_MSG_WRONG_MSG_TYPE)
            printf("CAN'T GET CMD: wrong msg type\n");
        else
            printf("CAN'T GET CMD: ?\n");
    }
    else
    {
        printf("WE FINALLY GOT THE CODE: %d\n", test_code);
    }

    printf("\njust created all of the msgs\n");

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
    ** 5/11 new pipe testing
    */
    strncpy(RobotSimData.RosName, "ROBOT_SIM_SBN_PIPE", sizeof(RobotSimData.RosName));
    RobotSimData.RosName[sizeof(RobotSimData.RosName) - 1] = 0;

    status = CFE_SB_CreatePipe(&RobotSimData.RobotSimPipe_1, RobotSimData.PipeDepth, RobotSimData.RosName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error creating ROS pipe, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    // printf("\nwe just created a NEW SBN pipe!\n");

    // status = CFE_SB_SubscribeEx(ROBOT_SIM_CMDID_1, RobotSimData.RobotSimPipe_1, CFE_SB_DEFAULT_QOS, ROBOT_SIM_CMDID_1_LIMIT);
    status = CFE_SB_Subscribe(ROBOT_SIM_CMDID_1, RobotSimData.RobotSimPipe_1);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error Subscribing to NEW PIPE request, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }
    // printf("\nwe just created a NEW SBN subEx pipe!\n");



    /*
    ** 5/12 new COMMAND MSG pipe testing
    */
    strncpy(RobotSimData.RosCmdName, "ROBOT_SIM_SBN_CMD", sizeof(RobotSimData.RosCmdName));
    RobotSimData.RosCmdName[sizeof(RobotSimData.RosCmdName) - 1] = 0;

    status = CFE_SB_CreatePipe(&RobotSimData.RosSbnPipe, RobotSimData.PipeDepth, RobotSimData.RosCmdName);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error creating ROS SBN pipe, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    printf("\nwe just created a NEW SBN COMMAND MSG TYPE pipe!\n");

    status = CFE_SB_Subscribe(ROBOT_SIM_SBN_CMD_ID, RobotSimData.RosSbnPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Robot Sim: Error Subscribing to NEW PIPE request, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }
    printf("\nwe just subscribed to the SBN CMD pipe!\n");

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


void RobotSimProcessCmd(CFE_SB_Buffer_t *SBBufPtr)
{
    printf("\nRobotSimProcessCmd() -- robot sim is processing a cmd....\n");

    // CFE_MSG_Message_t *MsgPtr = &SBBufPtr->Msg;

    CFE_MSG_Type_t type = CFE_MSG_Type_Invalid;
    CFE_MSG_GetType(&SBBufPtr->Msg, &type);
    if (type == CFE_MSG_Type_Tlm)
        printf("RobotSimProcessCmd() -- type is TLM\n");
    else if (type == CFE_MSG_Type_Cmd)
        printf("RobotSimProcessCmd() -- type is CMD\n");
    else //CFE_MSG_Type_Invalid
        printf("RobotSimProcessCmd() -- INVALID\n");

    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    // printf("looking for function code? %d\n", SBBufPtr->Msg->Sec.FunctionCode);

    printf("RobotSimProcessCmd() -- we're processing the cmd with msg ID: %d\n", (unsigned int)CFE_SB_MsgIdToValue(MsgId));

    bool has = false;
    CFE_MSG_GetHasSecondaryHeader(&SBBufPtr->Msg, &has);
    if (has)
    {
        printf("RobotSimProcessCmd() -- WE HAVE A 2ND HEADER\n");
    }
    else
    {
        printf("RobotSimProcessCmd() -- no 2nd header\n");
        if (CFE_MSG_SetHasSecondaryHeader(&SBBufPtr->Msg, true) != CFE_SUCCESS)
            printf("RobotSimProcessCmd() -- FAILED TO SET 2ND HEADER\n");
    }

    // printf("getting function code? %d\n", SBBufPtr->Msg->Sec.FunctionCode);

    CFE_MSG_FcnCode_t CommandCode = 0;
    int32 ret = CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

    if (ret == CFE_SUCCESS)
        printf("RobotSimProcessCmd() -- we're processing the cmd: %d\n", CommandCode);
    else if (ret == CFE_MSG_BAD_ARGUMENT)
        printf("RobotSimProcessCmd() -- we have a bad msg argument\n");
    else
        printf("RobotSimProcessCmd() -- we have a wrong msg type!!\n");

    return;

} /* End RobotSimProcessCommandPacket */


void RobotSimProcessSBN(CFE_SB_Buffer_t *SBBufPtr)
{
    printf("\nrobot sim is processing telem....\n");

    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    printf("we're processing the telem with msg ID: %d\n", (unsigned int)CFE_SB_MsgIdToValue(MsgId));

    return;

} /* End RobotSimProcessCommandPacket */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* RobotSimProcessGroundCommand() -- robot sim ground commands                */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void RobotSimProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_MSG_FcnCode_t CommandCode = 0;

    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);
    printf("we're getting a ground command?\n");
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
    printf("housekeeping...\n");
    /*
    ** Get command execution counters...
    */
    RobotSimData.HkTlm.Payload.CommandErrorCounter = RobotSimData.ErrCounter;
    RobotSimData.HkTlm.Payload.CommandCounter      = RobotSimData.CmdCounter;

    /*
    ** Send housekeeping telemetry packet...
    */
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

    // CFE_EVS_SendEvent(ROBOT_SIM_HELLO_WORLD_INF_EID, CFE_EVS_EventType_INFORMATION, "robot sim: Hello, ros! %s",
    //                   ROBOT_SIM_VERSION);

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