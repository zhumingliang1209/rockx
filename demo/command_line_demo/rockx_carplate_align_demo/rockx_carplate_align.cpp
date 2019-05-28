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
#include <stdlib.h>

#include "rockx.h"

int main(int argc, char** argv) {

    rockx_ret_t ret;
    const char *img_path = argv[1];
    struct timeval tv;

    // read image
    rockx_image_t input_image;
    rockx_image_read(img_path, &input_image, 1);

    /*************** rockx_carplate_fmapping ***************/
    rockx_handle_t plate_det_handle;
    rockx_handle_t carplate_fmapping_handle;
    // create a plate detection handle
    ret = rockx_create(&plate_det_handle, ROCKX_MODULE_CARPLATE_DETECTION, nullptr, 0);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("init rockx module ROCKX_MODULE_CARPLATE_DETECTION error %d\n", ret);
    }

    // create a carplate_fmapping_ handle
    ret = rockx_create(&carplate_fmapping_handle, ROCKX_MODULE_CARPLATE_ALIGN, nullptr, 0);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("init rockx module ROCKX_MODULE_CARPLATE_ALIGN error %d\n", ret);
    }
    rockx_object_array_t plate_array;
    memset(&plate_array, 0, sizeof(rockx_object_array_t));

    // detect plate
    ret = rockx_carplate_detect(plate_det_handle, &input_image, &plate_array, nullptr);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("rockx_carplate_detect error %d\n", ret);
        return -1;
    }

    for (int i = 0; i < plate_array.count; i++) {

        // create rockx_carplate_align_result_t for store result
        rockx_carplate_align_result_t aligned_outarray;
        memset(&aligned_outarray, 0, sizeof(rockx_carplate_align_result_t));

        aligned_outarray.aligned_image.data = (uint8_t *) malloc(40 * 160 * 3);

        printf("(%d %d %d %d) %f\n", plate_array.object[i].box.left, plate_array.object[i].box.top,
                plate_array.object[i].box.right, plate_array.object[i].box.bottom, plate_array.object[i].score);

        // carplate_fmapping_
        ret = rockx_carplate_align(carplate_fmapping_handle, &input_image,&plate_array.object[i],&aligned_outarray);
        if (ret != ROCKX_RET_SUCCESS) {
            printf("rockx_carplate_align error %d\n", ret);
            return -1;
        }

        // process result
        aligned_outarray.aligned_image;
        // save image
        rockx_image_write("./refined_img.jpg", &(aligned_outarray.aligned_image));
        rockx_image_release(&(aligned_outarray.aligned_image));
    }

    // release handle
    rockx_destroy(carplate_fmapping_handle);
}
