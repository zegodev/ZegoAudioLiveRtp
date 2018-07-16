//
//  ZegoAudioRoomApi-Player.h
//  ZegoAudioRoom
//
//  Created by Strong on 2017/3/15.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import "ZegoAudioRoomApi.h"
#import "ZegoAudioRoomApiDefines.h"

@protocol ZegoAudioLivePlayerDelegate;
@protocol ZegoAudioLiveRecordDelegate;

@interface ZegoAudioRoomApi (Player)

/**
 设置播放回调
 
 @param playerDelegate player Delegate
 */
- (void)setAudioPlayerDelegate:(id<ZegoAudioLivePlayerDelegate>)playerDelegate;

/**
 （声音输出）静音开关
 
 @param bEnable true 不静音，false 静音。默认 true
 @return true 成功，false 失败
 @discussion 设置为关闭后，内置扬声器和耳机均无声音输出
 */
- (bool)enableSpeaker:(bool) bEnable;

/**
 手机内置扬声器开关
 
 @param bOn true 打开，false 关闭。默认 true
 @return true 成功，false 失败
 @discussion 设置为关闭后，扬声器无声音，耳机仍有声音输出
 */
- (bool)setBuiltInSpeakerOn:(bool)bOn;

/**
 统一设置所有拉流的播放音量
 
 @param volume 音量取值范围为(0, 100)，数值越大，音量越大。默认 100
 @return true 成功，false 失败
 @discussion 通过此 API 软件调整音量
 */
- (bool)setPlayVolume:(int)volume;

/**
 设置指定拉流的播放音量
 
 @param volume 音量取值范围为(0, 100)，数值越大，音量越大。默认 100
 @streamID  流ID. ID为空时, 统一设置所有拉流的播放音量
 @return true 成功, false 失败
 @discussion 直播时通过此 API 软件调整音量
 */
- (bool)setPlayVolume:(int)volume ofStream:(NSString *)streamID;

/**
 获取当前播放视频的音量
 
 @param streamID 播放流 ID
 @return 视频的音量值
 @discussion 直播时通过此 API 获取当前音量。音量变更也会受硬件音量键的影响。
 */
- (float)getSoundLevelOfStream:(NSString *)streamID;

/**
 音频录制开关
 
 @param enable 开启音频录制。true 开启，false 关闭。默认 false
 @return true 成功，false 失败
 @discussion 初始化 SDK 后调用。开启音频录制后，调用方需要设置音频录制回调代理对象，并通过 [ZegoLiveRoomApi (Player) -onAudioRecord:sampleRate:numOfChannels:bitDepth:type:] 获取 SDK 录制的数据。使用此接口开启音频录制，相当于调用 enableSelectedAudioRecord:(ZegoAPIAudioRecordConfig)config，且 config 中的参数默认值为：ZEGO_AUDIO_RECORD_MIX、44100、单声道。
 */
- (bool)enableAudioRecord:(BOOL)enable;

/**
 音频录制开关
 
 @warning Deprecated，请使用 enableSelectedAudioRecord:
 */
- (bool)enableSelectedAudioRecord:(unsigned int)mask sampleRate:(int)sampleRate;

/**
 音频录制开关
 
 @param config 配置信息, 参考 ZegoAPIAudioRecordConfig
 @return true 成功，false 失败
 @discussion 开启音频录制后，调用方需要设置音频录制回调代理对象，并通过 [ZegoLiveRoomApi (Player) -onAudioRecord:sampleRate:numOfChannels:bitDepth:type:] 获取 SDK 录制的数据
 */
-(bool)enableSelectedAudioRecord:(ZegoAPIAudioRecordConfig)config;

/**
 设置音频录制回调代理对象
 
 @param audioRecordDelegate 遵循 ZegoAudioLiveRecordDelegate 协议的代理对象
 @discussion 开启音频录制功能，需要设置代理对象。未设置代理对象，或对象设置错误，可能导致无法正常收到相关回调
 */
- (void)setAudioRecordDelegate:(id<ZegoAudioLiveRecordDelegate>)audioRecordDelegate;

/**
 获取 SDK 支持的最大同时播放流数
 
 @return 最大支持播放流数
 */
+ (int)getMaxPlayChannelCount;

/**
 onPlayStateUpdate返回拉流失败时，可以尝试再次拉流

 @param streamID 重新拉流流ID
 @return true 调用成功，false 调用失败
 */
- (bool)restartPlayStream:(NSString *)streamID;

@end

@protocol ZegoAudioLivePlayerDelegate <NSObject>

/**
 播放流事件
 
 @param stateCode 播放状态码
 @param stream 流信息
 */
- (void)onPlayStateUpdate:(int)stateCode stream:(ZegoAudioStream *)stream;

@optional
/**
 观看质量更新
 
 @param streamID 观看流ID
 @param quality quality 参考ZegoApiPlayQuality定义
 */
- (void)onPlayQualityUpate:(NSString *)streamID quality:(ZegoApiPlayQuality)quality;

@end

@protocol ZegoAudioLiveRecordDelegate <NSObject>

@optional
/**
 音频录制回调
 
 @param audioData SDK 录制的音频源数据
 @param sampleRate 采样率，不固定，以当前值为准
 @param numOfChannels 通道数量，单通道
 @param bitDepth 位深度，16 bit
 @param type 音源类型，参考 ZegoAPIAudioRecordMask
 @discussion 开启音频录制并设置成功代理对象后，用户调用此 API 获取 SDK 录制的音频数据。用户可自行对数据进行处理，例如：存储等。SDK 发送音频数据的周期为 20ms。存储数据时注意取 sampleRate、numOfChannels、bitDepth 参数写包头信息
 */
- (void)onAudioRecord:(NSData *)audioData sampleRate:(int)sampleRate numOfChannels:(int)numOfChannels bitDepth:(int)bitDepth type:(unsigned int)type;

/**
 音频录制回调
 
 @warning Deprecated，请使用 onAudioRecord:sampleRate:numOfChannels:bitDepth:type:
 */
- (void)onAudioRecord:(NSData *)audioData sampleRate:(int)sampleRate numOfChannels:(int)numOfChannels bitDepth:(int)bitDepth;

@end
