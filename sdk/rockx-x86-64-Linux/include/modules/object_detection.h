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

#ifndef _ROCKX_OBJECT_DETECTION_H
#define _ROCKX_OBJECT_DETECTION_H

#include "rockx_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Object Detection Labels Table (91 Classes)
 */
const char* const OBJECT_DETECTION_LABELS_91[91] = {
        "???", "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat", "trafficlight",
        "firehydrant", "???", "stopsign", "parkingmeter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow", "elephant",
        "bear", "zebra", "giraffe", "???", "backpack", "umbrella", "???", "???", "handbag", "tie", "suitcase", "frisbee",
        "skis", "snowboard", "sportsball", "kite", "baseballbat", "baseballglove", "skateboard", "surfboard", "tennisracket",
        "bottle", "???", "wineglass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange",
        "broccoli", "carrot", "hotdog", "pizza", "donut", "cake", "chair", "couch", "pottedplant", "bed", "???", "diningtable",
        "???", "???", "toilet", "???", "tv", "laptop", "mouse", "remote", "keyboard", "cellphone", "microwave", "oven",
        "toaster", "sink", "refrigerator", "???", "book", "clock", "vase", "scissors", "teddybear", "hairdrier", "toothbrush"
};

/**
 * @brief Object Detection Result(include Face, CarPlate, Head, Object, etc...)
 */
typedef struct rockx_object_t {
    int id;                 ///< Track id
    int cls_idx;            ///< Class index
    rockx_rect_t box;       ///< Object Region
    float score;            ///< Object confidence score
} rockx_object_t;

/**
 * @brief Object Array Result
 */
typedef struct rockx_object_array_t {
    int count;                  ///< Array Count(0 <= count < 128)
    rockx_object_t object[128]; ///< Objects
} rockx_object_array_t;

/**
 * Object Detection (91 Class)
 * @param handle [in] Handle of a created ROCKX_MODULE_OBJECT_DETECTION module(created by @ref rockx_create)
 * @param in_img [in] Input image
 * @param object_array [out] Detection Result
 * @param callback [in] Async callback function pointer
 * @return @ref rockx_ret_t
 */
rockx_ret_t rockx_object_detect(rockx_handle_t handle, rockx_image_t *in_img, rockx_object_array_t *object_array,
                              rockx_async_callback callback);

/**
 * Head Detection
 * @param handle [in] Handle of a created ROCKX_MODULE_HEAD_DETECTION module(created by @ref rockx_create)
 * @param in_img [in] Input image
 * @param object_array [out] Detection Result
 * @param callback [in] Async callback function pointer
 * @return @ref rockx_ret_t
 */
rockx_ret_t rockx_head_detect(rockx_handle_t handle, rockx_image_t *in_img, rockx_object_array_t *object_array,
                              rockx_async_callback callback);

#ifdef __cplusplus
} //extern "C"
#endif

#endif // _ROCKX_OBJECT_DETECTION_H