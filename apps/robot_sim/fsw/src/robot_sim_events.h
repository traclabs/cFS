/************************************************************************
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
** File: robot_sim_events.h
**
** Purpose:
**  Define Robot Sim Events IDs
**
** Notes:
**
*************************************************************************/
#ifndef _robot_sim_events_h_
#define _robot_sim_events_h_

#define ROBOT_SIM_RESERVED_EID          0
#define ROBOT_SIM_STARTUP_INF_EID       1
#define ROBOT_SIM_COMMAND_ERR_EID       2
#define ROBOT_SIM_COMMANDNOP_INF_EID    3
#define ROBOT_SIM_COMMANDRST_INF_EID    4
#define ROBOT_SIM_INVALID_MSGID_ERR_EID 5
#define ROBOT_SIM_LEN_ERR_EID           6
#define ROBOT_SIM_PIPE_ERR_EID          7
#define ROBOT_SIM_HELLO_WORLD_INF_EID   8

#define ROBOT_SIM_EVENT_COUNTS 8

#endif /* _robot_sim_events_h_ */

/************************/
/*  End of File Comment */
/************************/