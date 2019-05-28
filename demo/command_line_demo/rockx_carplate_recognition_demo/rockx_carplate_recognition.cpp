/****************************************************************************
*
*    Copyright (c) 2017 - 2019 by Rockchip Corp.  All rights reserved.
*
*    The material in this file is confidential and contains trade secrets
*    of Rockchip Corporation. This is proprietary information owned by
*    Rockchip Corporation. No part of this work may be disclosed,
*    reproduced, copied, transmitted, or used in any way for any purpose,
*    without the express written permission of Rockchip Corporation.
*
*****************************************************************************/
#include <stdio.h>
#include <memory.h>
#include <sys/time.h>

#include "rockx.h"

int main(int argc, char** argv) {

    rockx_ret_t ret;
    rockx_handle_t car_plate_recog_handle;
    struct timeval tv;

    const char *img_path = argv[1];
   
    // create a car_plate_recog_handle handle
    ret = rockx_create(&car_plate_recog_handle, ROCKX_MODULE_CARPLATE_RECOG, nullptr, 0);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("init rockx module ROCKX_MODULE_OBJECT_DETECTION error %d\n", ret);
    }

    // read image
    rockx_image_t input_image;
    rockx_image_read(img_path, &input_image, 1);

    // create rockx_carplate_recog_result_t for store result
    rockx_carplate_recog_result_t object_array;
    memset(&object_array, 0, sizeof(rockx_carplate_recog_result_t));

    // recog lp
    ret = rockx_carplate_recognize(car_plate_recog_handle, &input_image, &object_array);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("rockx_face_detect error %d\n", ret);
        return -1;
    }

    // process result
    printf("platename code:");
    for(int i=0;i<object_array.length;i++) {
        printf("%d ", object_array.namecode[i]);
    }
    printf("\n");

    char platename[32];
    memset(platename, 0, 32);
    for(int i=0; i < object_array.length; i++) {
        strcat(platename, CARPLATE_RECOG_CODE[object_array.namecode[i]]);
    }
    printf("platename=%s\n", platename);

    // release handle
    rockx_destroy(car_plate_recog_handle);
}
