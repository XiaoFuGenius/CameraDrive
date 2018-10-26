//
//  CTBluetoothHelper.h
//  CameraDrive
//
//  Created by xiaofutech on 2018/4/19.
//  Copyright © 2018年 xiaofutech. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol CTBluetoothHelperDelegate <NSObject>
- (void)CTBluetoothHelperDelegateDidUpdateState:(BOOL)state;
@end

@interface CTBluetoothHelper : UIViewController

/**
 取得CTBluetoothHelper的共享实例
 @return CTBluetoothHelper的共享实例
 */
+ (CTBluetoothHelper *)SharedBleHelper;

/**
 取得蓝牙的当前状态 (PoweredOn | !PoweredOn)
 @return 蓝牙的当前状态
 */
@property(nonatomic, assign, readonly) BOOL state;

/**
 添加一个观察者
 @observer 观察者对象
 */
+ (void)AddObserver:(id<CTBluetoothHelperDelegate>)observer;

/**
 移除一个观察者
 @observer 观察者对象
 */
+ (void)RemoveObserver:(id<CTBluetoothHelperDelegate>)observer;

@end
