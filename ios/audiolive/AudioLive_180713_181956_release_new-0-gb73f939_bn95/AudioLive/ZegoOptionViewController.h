//
//  ZegoOptionViewController.h
//  AudioLive
//
//  Created by xia on 2018/7/3.
//  Copyright © 2018 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZegoAudioLiveViewController.h"

@protocol ZegoOptionDelegate <NSObject>

- (ZegoMediaPlayerStatus)onGetMediaPlayerStatus;
- (void)onMediaPlayerStart;
- (void)onMediaPlayerStop;
@end

@interface ZegoOptionCell: UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UIButton *controlButton;

@end

@interface ZegoOptionViewController : UIViewController

@property (nonatomic, weak) id<ZegoOptionDelegate> delegate;

@end
