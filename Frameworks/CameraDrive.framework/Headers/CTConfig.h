//
//  CTConfig.h
//  CameraDrive
//
//  Created by xiaofutech on 2018/4/18.
//  Copyright © 2018年 xiaofutech. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTConfig : NSObject

#pragma mark - 常规配置项

/**
 debug开关
 开启以后，终端会输出debug日志，默认 关闭；
 */
@property (nonatomic, assign) BOOL debugEnable;

/**
 debug log block
 赋值后，内部方法会在适当时机调用，并返回关键日志
 */
@property (nonatomic, copy) void (^debugLogBlock)(NSString *log);

/**
 图像采集失败回调
 type -1：一般失败，-2：超时处理
 */
@property (nonatomic, copy) void (^captureFailedTypeBlock)(NSInteger type);

@property (nonatomic, assign) int captureMode;  // 拍摄模式：0-优先拍摄表皮层，1-优先拍摄基底层（核心版本 >= 3.1.2）；默认 0；

/**
 蓝条检测 开关
 开启以后，摄像头启动时，对 前十帧图像 执行 蓝条检测 算法，默认关闭；
 对该Block赋值即意味着开启蓝条检测，同时，对于检测到的蓝条图片，会通过Block回传
 */
@property (nonatomic, copy) void(^blueStripDetectionHandler)(UIImage *blueStripImage);

/**
 蓝条检测，类型选择，默认 0
 0：仅检测摄像头成功启动后的前十帧图像；1：对每一帧图像都进行检测（可能会影响渲染的流畅度）；
 */
@property (nonatomic, assign) NSInteger blueStripDetectionType;

/**
 热点模式，信道指定（STA模式，信道由产生WiFi信号的路由器本身决定）
 -1 随机信道，0 - 13 指定信道(不建议选择 12，13 信道)，默认随机信道；
 另：当前 Android 默认 信道9
 */
@property (nonatomic, assign) NSInteger channelSetting;

/**
 分隔字符串数组，拆分Name和BindID，默认 @[@"!@"]；
 */
@property (nonatomic, strong) NSArray *splitStrings;

/**
 蓝牙扫描时，外围设备的保活时间，默认 2s，自定义时间 >2s；
 超过保活时间即被视为该外围设备已失活，将从已扫描到的设备列表中移除；
 -1 指定，不执行 相关的保活逻辑，设备扫描到一次，将会始终存在于设备列表中；
 */
@property (nonatomic, assign) NSTimeInterval peripheralAliveTime;

/**
 StartOV788:1 延迟 500 ms 测试，默认关闭
 */
@property (nonatomic, assign) BOOL delayStartOv788Test;
/**
 StartOV788:1 延迟 500 ms 测试时间，默认 500 ms
 */
@property (nonatomic, assign) double delayStartOv788Time;

/**
 校验 图片中是否 有 蓝条
 @param image 图片数据
 @return 校验结果
 */
+ (BOOL)ExamineBlueStripImage:(UIImage *)image;

/**
 取得 CTConfig 的共享实例
 @return CTConfig 的共享实例
 */
+ (CTConfig *)SharedConfig;

/**
 销毁 CTConfig 的共享实例
 */
+ (void)DestroyedConfig;

@end
