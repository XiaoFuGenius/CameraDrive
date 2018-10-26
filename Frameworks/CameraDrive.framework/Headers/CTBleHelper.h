//
//  CTBleHelper.h
//  CameraTool
//
//  Created by xiaofutech on 2016/12/27.
//  Copyright © 2016年 xiaofutech. All rights reserved.
//

//CT_Device_BleDisconnect
//CT_Device_BatteryUpdate
//CT_Device_Scan
#import <Foundation/Foundation.h>

#define 	OTA_CONNECT_OK                      0x01
#define 	OTA_CONNECT_ERROR                   0x02
#define 	OTA_CMD_IND_FW_INFO                 0x03
#define 	OTA_CMD_IND_FW_DATA                 0x04
#define 	OTA_CMD_REQ_VERIFY_FW               0x05
#define 	OTA_CMD_REQ_EXEC_FW                 0x06
#define 	OTA_RSP_SUCCESS                     0x07
#define 	OTA_RSP_PKT_CHECKSUM_ERROR			0x08
#define 	OTA_RSP_PKT_LEN_ERROR				0x09
#define 	OTA_RSP_DEVICE_NOT_SUPPORT_OTA		0x0A
#define 	OTA_RSP_FW_SIZE_ERROR				0x0B
#define 	OTA_RSP_FW_VERIFY_ERROR				0x0C
#define 	OTA_RSP_PROGRESS                    0x0D
#define 	OTA_DISCONNECT                      0x0E
#define 	OTA_OK                              0x0F

#define CORE_OTA_AP                                 0x01
#define CORE_OTA_SEND_UPDATE                        0x02
#define CORE_OTA_SOCKET_LINSTEN                     0x03
#define CORE_OTA_SOCKET_ACCPET                      0x04
#define CORE_OTA_SOCKET_SEND_LENGTH                 0x05
#define CORE_OTA_SOCKET_SEND_DATA                   0x06
#define CORE_OTA_SOCKET_SEND_PROGRESS               0x07
#define CORE_OTA_DATA_CRC                           0x08
#define CORE_OTA_DATA_UPDATE                        0x09
#define CORE_OTA_OK                                 0x0a
#define CORE_OTA_ERROR_AP                           0x0b
#define CORE_OTA_ERROR_SEND_UPDATE                  0x0c
#define CORE_OTA_ERROR_SOCKET_LINSTEN               0x0d
#define CORE_OTA_ERROR_SOCKET_ACCPET_TIMEOUT        0x0e
#define CORE_OTA_ERROR_SOCKET_DISCONNECT            0x0f
#define CORE_OTA_ERROR_DATA_CRC                     0x10
#define CORE_OTA_ERROR_DATA_UPDATE                  0x11

#pragma mark - CTDevice
@interface CTDevice : NSObject
@property (nonatomic, strong) NSDate *aliveDate;
@property (nonatomic, strong) NSString *Name;
@property (nonatomic, strong) NSString *BindID;
@property (nonatomic, strong) NSNumber *RSSI;
@end

#pragma mark - CTBleHelper

enum CTBleRequestEnum:int {CTBleRequestOK=1,CTBleRequestError=2};

@interface CTBleHelper : UIViewController

#pragma mark >>> 初始化 <<<

/**
 初始化核心命令助手类 CTBleHelper
 */
+ (void)HelperInit;

#pragma mark >>> 设备扫描相关 <<<

/**
 开始扫描
 */
+ (void)StartScan;

/**
 停止扫描
 */
+ (void)StopScan;

/**
 重新扫描，等同于 StartScan
 */
+ (void)FlushScan;

#pragma mark >>> 蓝牙连接相关 <<<

/**
 通过BindID与设备的蓝牙建立连接
 @Block 完成回调
 */
+ (void)Connect:(NSString *)bindID Completion:(void (^)(BOOL status))Block;

/**
 通过Name与设备的蓝牙建立连接
 @Block 完成回调
 */
+ (void)ConnectByName:(NSString *)Name Completion:(void (^)(BOOL status))Block;

/**
 当前与设备蓝牙的连接状态
 */
+ (int)ConnectStatus;

/**
 断开蓝牙连接，命令执行完成后会将当前线程挂起2秒
 */
+ (void)Close;

/**
 仅用于等待设备返回确认命令，此方法不会发出任何命令
 @Block 收到设备返回的确认命令后，执行完成回调
 */
+ (void)Bind:(void (^)(BOOL isOK,enum CTBleRequestEnum status))Block;

#pragma mark >>> WiFi连接相关 <<<

/**
 发送命令，控制设备 开启/关闭 主控芯片
 @status 0 关闭，1 开启
 @Block 命令完成回调
 */
+ (void)StartOV788:(int)status Completion:(void (^)(BOOL isOK, enum CTBleRequestEnum status))Block;

/**
 获取设备当前的WiFi连接状态
 */
+ (void)WIFIStatus:(void (^)(int type, NSString* SSID, NSString* password,
                             NSString* IP, enum CTBleRequestEnum status))Block;

/**
 发送命令使设备创建 热点
 */
+ (void)AP:(void (^)(NSString* SSID, NSString* password, enum CTBleRequestEnum status))Block;

/**
 确认连接公共wifi
 wifiStatus：-2:旧版本，未搜索到ssid, -1:密码错误, 0:请求失败或超时, 1:成功
 */
+ (void)STA:(NSString*)SSID Password:(NSString*)password
 Completion:(void (^)(NSString* IP, int wifiStatus, enum CTBleRequestEnum status))Block;

#pragma mark >>> 电量信息、mac地址信息、蓝牙/核心 固件版本信息 <<<

/**
 取得设备 电量 信息
 */
+ (void)Battery:(void (^)(BOOL isCharge,int electric,enum CTBleRequestEnum status))Block;

/**
 取得设备 MAC 信息
 */
+ (void)MAC:(void (^)(NSString* mac,enum CTBleRequestEnum status))Block;

/**
 取得设备 蓝牙、内核 固件版本信息
 备注：会启动主控芯片
 */
+ (void)Version:(void (^)(NSString* Ble,NSString* Core,enum CTBleRequestEnum status))Block;

#pragma mark >>> 蓝牙、核心 固件升级相关 <<<

/**
 蓝牙固件升级，升级期间，会多次调用 response
 @response 升级进度回调
 */
+ (void)UpdateBLE:(NSData*)firmware Response:(void (^)(int status, int value))response;

/**
 核心固件升级，升级期间，会多次调用 response
 @response 升级进度回调
 */
+ (void)UpdateCore:(NSData*)firmware Response:(void (^)(int status, int value))response;

#pragma mark >>> 新增 <<<
/**
 验证测试仪是否能够搜索到该ssid - 2018.3.12，场景：5G网络判断
 版本要求：蓝牙 1.0.11  固件 1.2.7，低于版本要求，会直接返回验证失败.
 @param ssid 手机当前链接的wifi名称
 @param Block 验证结果回调
 */
+ (void)STA_VerifiedSSID:(NSString*)ssid
              Completion:(void (^)(BOOL success, int status, NSString *msg))Block;

/**
 关机
 */
+ (void)Shutdown;

/**
 获取是否需要校准
 @param completion -2：未知状态码，-1：请求失败，0：不需要校准，1：需要校准，2：已校准
 注：版本要求，Ble 2.1.0 & Core 3.1.0
 */
+ (void)CalibrationStatusCheck:(void (^)(int status, NSString *msg))completion;

/**
 图像校准
 @param command 校准命令 1：校准(ave>250)，2：校准(ave<=250)，3：清除(回滚)
 @param completion 完成回调
 注：版本要求，Ble 2.1.0 & Core 3.1.0
 */
+ (void)CalibrationImageWithCommand:(int)command
                         Completion:(void (^)(BOOL success, NSString *msg))completion;

/**
 RestartNVDS
一键恢复 校准配置文件
 注：版本要求，Ble 2.1.0 & Core 3.1.0
 */
+ (void)CalibrationRestartNVDS:(void (^)(BOOL success, NSString *msg))completion;

/**
 有线模式 设置
 @param command 设置命令，-2：混合模式（新设备），-1：混合模式（旧设备），1：有线模式（旧设备），2：有线模式（新设备）
 @param completion 完成回调
 注：版本要求，Ble 2.1.0 & Core 3.1.0
 */
+ (void)SetWiredModeCommand:(int)command Completion:(void (^)(BOOL success, NSString *msg))completion;

@end
