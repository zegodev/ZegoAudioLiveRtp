//
//  ZegoVideoTalkViewController.h
//  InstantTalk
//
//  Created by Strong on 16/7/11.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZegoSettings.h"

typedef NS_ENUM(NSInteger, ZegoMemberNetworkStatus) {
    ZegoMemberStatusDisconnect = 0,
    ZegoMemberStatusConnecting = 1,
    ZegoMemberStatusConnected = 2,
};

typedef NS_ENUM(NSInteger, ZegoMemberSpeakingStatus) {
    ZegoMemberStatusIsSpeaking = 0,
    ZegoMemberStatusNoSpeaking = 1,
};

typedef NS_ENUM(NSInteger, ZegoMediaPlayerStatus)
{
    ZegoMediaPlayerStatusPlay = 0,
    ZegoMediaPlayerStatusStop = 1,
};


@interface ZegoMemberInfo: NSObject

@property (nonatomic) ZegoAudioStream *stream;
@property (nonatomic) ZegoAPIPlayQuality playQuality;
@property (nonatomic) ZegoAPIPublishQuality publishQuality;
@property (nonatomic) ZegoMemberSpeakingStatus speakingStatus;
@property (nonatomic) ZegoMemberNetworkStatus networkStatus;
@property (nonatomic) float soundLevel;

@end

@interface ZegoMemberCell: UICollectionViewCell

@property (weak, nonatomic) IBOutlet UIView *containerView;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *qualityLabel;
@property (weak, nonatomic) IBOutlet UIButton *statusView;
@property (weak, nonatomic) IBOutlet UIProgressView *soundView;

@end

@interface ZegoAudioLiveViewController : UIViewController

@property (nonatomic, copy) NSString *roomID;


@end
