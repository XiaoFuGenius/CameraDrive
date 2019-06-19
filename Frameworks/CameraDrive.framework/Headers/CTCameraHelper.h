//
//  CTCameraHelper.h
//  CameraTool
//
//  Created by xiaofutech on 2016/12/30.
//  Copyright © 2016年 xiaofutech. All rights reserved.
//

#import <Foundation/Foundation.h>

#define RECORD_VIDEO_START                              0x01
#define RECORD_VIDEO_STOP                               0x02
#define RECORD_VIDEO_START_ERROR                        0x03
#define RECORD_VIDEO_STOP_ERROR                         0x04
#define RECORD_VIDEO_FILE_ERROR                         0x05

@interface CTCameraHelper : NSObject

/**
 关闭，关于 摄像头启动、拍摄 的超时控制
 */
+ (void)TimeoutControlDisabled:(BOOL)disabled;

#pragma mark >>> 基础设定相关 <<<

/**
 设置 图像 加载视图
 @param view 视图
 @param isRetroflexion 图像是否 镜像显示
 @param handler 摄像头启动结果回调
 */
+ (void)SetCameraView:(UIView *)view Retroflexion:(BOOL)isRetroflexion
  CameraActiveHandler:(void (^)(BOOL status))handler;

/**
 移除之前设置的View 释放内存
 */
+ (void)DestroyedCameraView;

/**
 设置 图像 长宽，默认 1280*720 （16:9）
 */
+ (void)SetWidth:(int)width Height:(int)height;

/**
 设置码率 默认600，码率会影响图像清晰度
 */
+ (void)SetBitrate:(int)bitrate;

#pragma mark >>> 摄像头开启、关闭 <<<

/**
 此时是否可以启动摄像头
 @return YES 可以启动，NO 需要 延迟1秒 再次执行判定；
 */
+ (BOOL)StartIsAvailable;

/**
 开启摄像头
 @param ip 设备路由ip地址
 @param port 端口号，默认 1000
 */
+ (void)Start:(NSString*)ip Port:(int)port;

/** 
 关闭摄像头 会挂起当前线程1秒
 */
+ (void)Stop;

#pragma mark >>> 拍照相关 <<<

/**
 设备固件版本低于1.2.2时，需要采用本方法
 拍摄一张照片
 */
+ (void)Capture:(NSString *)pathName Completion:(void (^)(BOOL status))Block;

/**
 拍摄2张照片，设备固件版本需要不小于1.2.2
 @param rgbPathName 真皮层 图片地址
 @param plPathName 表皮层 图片地址
 */
+ (void)CaptureNew:(NSString *)rgbPathName PLPathName:(NSString*)plPathName
        Completion:(void (^)(BOOL status))Block;

#pragma mark >>> 高级设定相关 <<<

/**
 切换图像的真表皮显示
 @param mode 0 表皮，1 真皮
 */
+ (void)SetLedMode:(int)mode;

/**
 未成功激活摄像头时，触发原因是否为 蓝条检测
 @return 蓝条检测 反馈
 */
+ (BOOL)IsBlueStripConfirmed;

/**
 取得 CameraHelper 的共享实例
 @return CameraHelper 的共享实例
 */
+ (CTCameraHelper *)SharedCameraHelper;

@end
