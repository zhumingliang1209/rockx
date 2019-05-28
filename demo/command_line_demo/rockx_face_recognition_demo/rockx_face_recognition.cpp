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

rockx_handle_t face_det_handle;
rockx_handle_t face_5landmarks_handle;
rockx_handle_t face_recognize_handle;

int run_face_recognize(rockx_image_t *in_image, rockx_face_feature_t *out_feature) {
    rockx_ret_t ret;

    /*************** FACE Detect ***************/
    // create rockx_face_array_t for store result
    rockx_object_array_t face_array;
    memset(&face_array, 0, sizeof(rockx_object_array_t));

    // detect face
    ret = rockx_face_detect(face_det_handle, in_image, &face_array, nullptr);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("rockx_face_detect error %d\n", ret);
        return -1;
    }

    // process result
    for (int i = 0; i < face_array.count; i++) {
        int left = face_array.object[i].box.left;
        int top = face_array.object[i].box.top;
        int right = face_array.object[i].box.right;
        int bottom = face_array.object[i].box.bottom;
        float score = face_array.object[i].score;
        printf("box=(%d %d %d %d) score=%f\n", left, top, right, bottom, score);
        // draw
        char score_str[8];
        memset(score_str, 0, 8);
        snprintf(score_str, 8, "%.3f", score);
    }

    /*************** FACE Landmark ***************/
    rockx_image_t out_img;
    out_img.width = 112;
    out_img.height = 112;
    out_img.pixel_format = ROCKX_PIXEL_FORMAT_RGB888;
    out_img.data = (uint8_t*)malloc(112*112*3*sizeof(char));
    for (int i = 0; i < face_array.count; i++) {
        rockx_face_align(face_5landmarks_handle, in_image, &face_array.object[i].box, nullptr, &out_img);
    }

    /*************** FACE Recognize ***************/
    rockx_face_recognize(face_recognize_handle, &out_img, out_feature);

    //printf("out_feature0 is %f \n",out_feature[n-1].feature[0]);
    //printf("out_feature1 is %f \n",out_feature[n-1].feature[1]);

    free(out_img.data);

    return 0;
}

int main(int argc, char** argv) {

    rockx_ret_t ret;
    struct timeval tv;

    if( argc != 3 ){
        printf("\nUsage: mser_sample <path_to_person1_image> <path_to_person2_image>\n");
        return -1;
    }
    /*************** Creat Handle ***************/
    // create a face detection handle
    ret = rockx_create(&face_det_handle, ROCKX_MODULE_FACE_DETECTION, nullptr, 0);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("init rockx module ROCKX_MODULE_FACE_DETECTION error %d\n", ret);
        return -1;
    }
    
    // create a face landmark handle
    ret = rockx_create(&face_5landmarks_handle, ROCKX_MODULE_FACE_LANDMARK_5, nullptr, 0);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("init rockx module ROCKX_MODULE_FACE_LANDMARK_68 error %d\n", ret);
        return -1;
    }

    // create a face recognize handle
    ret = rockx_create(&face_recognize_handle, ROCKX_MODULE_FACE_RECOGNIZE, nullptr, 0);
    if (ret != ROCKX_RET_SUCCESS) {
        printf("init rockx module ROCKX_MODULE_FACE_LANDMARK_68 error %d\n", ret);
        return -1;
    }

    rockx_face_feature_t out_feature1;
    rockx_face_feature_t out_feature2;

    // read image
    const char *img_path1 = argv[1];
    const char *img_path2 = argv[2];

    // read image
    rockx_image_t input_image1;
    rockx_image_read(img_path1, &input_image1, 1);

    rockx_image_t input_image2;
    rockx_image_read(img_path2, &input_image2, 1);

    run_face_recognize(&input_image1, &out_feature1);
    run_face_recognize(&input_image2, &out_feature2);

    float similarity;
    ret = rockx_face_feature_similarity(&out_feature1, &out_feature2, &similarity);
    printf("similarity is %f\n",similarity);

    //release handle
    rockx_destroy(face_det_handle);
    rockx_destroy(face_5landmarks_handle);
    rockx_destroy(face_recognize_handle);
    return 0;
}
