//
//  ZegoAudioRoomApi-Publisher.h
//  ZegoAudioRoom
//
//  Created by Strong on 2017/3/15.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import "ZegoAudioRoomApi.h"
#import "ZegoAudioRoomApiDefines.h"

@protocol ZegoAudioLivePublisherDelegate;

@interface ZegoAudioRoomApi (Publisher)

/**
 设置推流回调
 
 @param publisherDelegate Publish Delegate
 */
- (void)setAudioPublisherDelegate:(id<ZegoAudioLivePublisherDelegate>)publisherDelegate;

/**
 开始直播
 
 @return true:调用成功; false:调用失败，当前直播流已达上限,已经开播等原因
 @discussion 此函数只有在[setManualPublish:true] 时调用才有效
 @discussion 流名由SDK内部生成
 */
- (bool)startPublish;


/**
 开始直播
 
 @param streamID 直播流 ID
 @return true:调用成功; false:调用失败，当前直播流已达上限,已经开播等原因
 @discussion 此函数只有在[setManualPublish:true] 时调用才有效
 @discussion 流名由外部传入
 */
- (bool)startPublishWithStreamID:(NSString *)streamID;

/**
 停止直播
 
 @discussion 此函数只有在[setManualPublish:true] 时调用才有效
 */
- (void)stopPublish;

/**
 开启关闭麦克风
 
 @param bEnable true 打开，false 关闭。默认 false
 @return true 成功，false 失败
 @discussion 推流时可调用本 API 进行参数配置
 */
- (bool)enableMic:(bool)bEnable;

/**
 开启采集监听
 
 @param bEnable true 打开，false 关闭。默认 false
 @return true 成功，false 失败
 @discussion 推流时可调用本 API 进行参数配置。连接耳麦时设置才实际生效。开启采集监听，主播方讲话后，会听到自己的声音。
 */
- (bool)enableLoopback:(bool)bEnable;

/**
 设置采集监听音量
 
 @param volume 音量大小，取值（0, 100）。默认 100
 @discussion 推流时可调用本 API 进行参数配置
 */
- (void)setLoopbackVolume:(int)volume;

/**
 设置采集音量
 
 @param volume 音量大小，取值（0, 100）。默认 100
 @discussion SDK初始化成功后调用
 */
- (void)setCaptureVolume:(int)volume;

/**
 混音开关
 
 @param enable true 启用混音输入，false 关闭混音输入。默认 false
 @return true 成功，false 失败
 @discussion 推流开始前调用本 API 进行参数配置。主播端开启混音后，SDK 在 [ZegoAudioRoomApi (Publisher) -onAuxCallback:dataLen:sampleRate:channelCount:] 中获取混音输入数据
 */
- (bool)enableAux:(BOOL)enable;

/**
 设置混音音量
 
 @param volume 0~100，默认为 50
 */
- (void)setAuxVolume:(int)volume;

/**
 混音静音开关
 
 @param bMute true: aux 输入播放静音，false: 不静音。默认 false
 @return true 成功，false 失败
 @discussion 推流开始前调用本 API 进行参数配置
 */
- (bool)muteAux:(bool)bMute;

/**
 获取当前采集的音量
 
 @return 当前采集的音量值
 */
- (float)getCaptureSoundLevel;

/**
 是否开启离散音频包发送
 
 @param enable true 开启，此时关闭麦克风后，不会发送静音包；false 关闭，此时关闭麦克风后会发送静音包
 默认状态下，关闭麦克风后会发送静音包
 @discussion 在推流前调用，只有纯 UDP 方案才可以调用此接口
 */
- (void)enableDTX:(bool)enable;

/**
 是否开启语音活动检测

 @param enable enable true 开启; false 关闭, 默认关闭
 @discussion 在推流前调用，只有纯 UDP 方案才可以调用此接口
 */
- (void)enableVAD:(bool)enable;

/**
 设置音频码率
 
 @param bitrate 码率
 @return true 成功 false 失败
 */
- (bool)setAudioBitrate:(int)bitrate;

/**
 设置延迟模式
 
 @param mode 延迟模式，默认 ZEGOAPI_LATENCY_MODE_NORMAL
 @discussion 在推流前调用
 */
- (void)setLatencyMode:(ZegoAPILatencyMode)mode;

/**
 设置推流音频声道数
 
 @param count 声道数，1 或 2，默认为 1（单声道）
 @attention 必须在调用推流前设置
 @note setLatencyMode 设置为 ZEGO_LATENCY_MODE_NORMAL, ZEGO_LATENCY_MODE_NORMAL2, ZEGO_LATENCY_MODE_LOW3 才能设置双声道
 @note 在移动端双声道通常需要配合音频前处理才能体现效果
 */
- (void)setAudioChannelCount:(int)count;

/**
 音频采集自动增益开关
 
 @param enable 是否开启，默认关闭
 @return true 成功，false 失败
 */
- (bool)enableAGC:(bool)enable;

/**
 回声消除开关
 
 @param enable true 打开 false 关闭
 @return true 成功 false 失败
 */
- (bool)enableAEC:(bool)enable;

/**
 设置回声消除模式
 
 @param mode 回声消除模式
 @discussion 建议在推流前调用设置
 */
- (void)setAECMode:(ZegoAPIAECMode)mode;

/**
 音频采集噪声抑制开关
 
 @param enable true 开启，false 关闭
 @return true 调用成功，false 调用失败
 */
- (bool)enableNoiseSuppress:(bool)enable;

/**
 更新流附加信息
 
 @param extraInfo 流附加信息, 最大为 1024 字节
 @return true 成功，false 失败
 @discussion 通常在主播方的 [ZegoAudioLivePublisherDelegate -onPublishStateUpdate:streamID:streamInfo:] 通知中，或其他需更新流附加信息的场合下调用。更新流附加信息成功后，除调用方外，同一房间内的其他人会收到 [ZegoAudioRoomDelegate -onStreamExtraInfoUpdated:roomID] 通知
 */
- (bool)updateStreamExtraInfo:(NSString *)extraInfo;

/**
 OnPublishStateUpdate回调推流失败时，可以调用此函数再次进行推流
 @return true 调用推流成功，false 调用失败
 */
- (bool)restartPublishStream;

/**
 设置音频设备模式
 
 @param mode 模式， 默认 ZEGOAPI_AUDIO_DEVICE_MODE_AUTO
 @discussion 在 Init 前调用
 */
+ (void)setAudioDeviceMode:(ZegoAPIAudioDeviceMode) mode;


/**
 设置是否开启音频流量控制

 @param enable true 开启, false 关闭
 */
- (void)enableAudioTrafficControl:(BOOL)enable;

@end

@protocol ZegoAudioLivePublisherDelegate <NSObject>

/**
 推流状态更新
 
 @param stateCode 状态码
 @param streamID 流ID
 @param info 推流信息
 */
- (void)onPublishStateUpdate:(int)stateCode streamID:(NSString *)streamID streamInfo:(NSDictionary *)info;

@optional
/**
 发布质量更新
 
 @param streamID streamID 发布流 ID
 @param quality quality 参考ZegoApiPublishQuality定义
 @discussion startPublish 后，该 API 会被多次回调。调用者可以在此回调中获取当前的视频质量数据，加以处理
 */
- (void)onPublishQualityUpdate:(NSString *)streamID quality:(ZegoApiPublishQuality)quality;

@optional

/**
 混音数据输入回调
 
 @param pData 混音数据
 @param pDataLen 缓冲区长度。实际填充长度必须为 0 或是缓冲区长度。0 代表无混音数据
 @param pSampleRate 混音数据采样率，支持16k、32k、44.1k、48k
 @param pChannelCount 混音数据声道数，支持1、2
 @discussion 用户调用该 API 将混音数据传递给 SDK。混音数据 bit depth 必须为 16
 */
- (void)onAuxCallback:(void *)pData dataLen:(int *)pDataLen sampleRate:(int *)pSampleRate channelCount:(int *)pChannelCount;

/**
 转推CDN状态信息
 @param statesInfo CDN状态信息
 @param streamID 推流的流ID
 */
- (void)onRelayCDNStateUpdate:(NSArray<ZegoAPIStreamRelayCDNInfo *> *)statesInfo streamID:(NSString*)streamID;

@end
