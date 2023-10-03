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
 *  The CF Application default configuration table
 */
#include "cfe.h"
#include "cfe_tbl_filedef.h"
#include "cf_tbldefs.h"
#include "cf_msgids.h"

CF_ConfigTable_t CF_config_table = {
    10,    /* ticks_per_second */
    16384, /* max number of bytes per wakeup to calculate r2 recv file crc */
    CF_FSW_EID,    /* local entity id */
    {      /* channel configuration for CF_NUM_CHANNELS */
     {
         /* channel 0 */
         5,      /* max number of outgoing messages per wakeup */
         5,      /* max number of rx messages per wakeup */
         3,      /* ack timer */
         3,      /* nak timer */
         30,     /* inactivity timer */
         4,      /* ack limit */
         4,      /* nak limit */
         CF_CH0_IN_MID,  /* input message id */
         CF_CH0_OUT_MID, /* output message id */
         16,     /* input pipe depth */
         {       /* polling directory configuration for CF_MAX_POLLING_DIR_PER_CHAN */
          {
              /* polling directory 0 */
              5,               /* interval seconds */
              25,              /* priority */
              CF_CFDP_CLASS_2, /* class to send */
              CF_ROSGSW_EID,              /* destination entity id */
              "/cf/poll_dir",  /* source directory */
              "./poll_dir",    /* destination directory */
              0                /* polling directory enable flag (1 = enabled) */
          },
          {
              0 /* zero fill unused polling directory slots */
          }},
         "", /* throttle sem, empty string means no throttle */
         1,  /* dequeue enable flag (1 = enabled) */
     },
     {
         /* channel 1 */
         5,      /* max number of outgoing messages per wakeup */
         5,      /* max number of rx messages per wakeup */
         3,      /* ack timer */
         3,      /* nak timer */
         30,     /* inactivity timer */
         4,      /* ack limit */
         4,      /* nak limit */
         CF_CH1_IN_MID,  /* input message id */
         CF_CH1_OUT_MID, /* output message id */
         16,     /* input pipe depth */
         {       /* polling directory configuration for CF_MAX_POOLING_DIR_PER_CHAN */
          {
              0 /* zero fill unused polling directory slots */
          }},
         "", /* throttle sem, empty string means no throttle */
         1   /* dequeue enable flag (1 = enabled) */
     }},
    480,       /* outgoing_file_chunk_size */
    "/cf/tmp", /* temporary file directory */
};
CFE_TBL_FILEDEF(CF_config_table, CF.config_table, CF config table, cf_def_config.tbl)
