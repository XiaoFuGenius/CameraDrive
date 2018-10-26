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
 取得CTConfig的共享实例
 @return CTConfig的共享实例
 */
+ (CTConfig *)SharedConfig;

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

@end
