//
//  ZegoOptionViewController.m
//  AudioLive
//
//  Created by xia on 2018/7/3.
//  Copyright © 2018 ZEGO. All rights reserved.
//

#define kTitleKey @"title"
#define kStatusKey @"status"
#define kenableKey @"enable"
#define kEventKey @"event"

#import "ZegoOptionViewController.h"

@interface ZegoOptionCell ()

@end

@implementation ZegoOptionCell

@end


@interface ZegoOptionViewController () <UITableViewDelegate, UITableViewDataSource>

@property (weak, nonatomic) IBOutlet UITableView *optionView;
@property (nonatomic, assign) ZegoMediaPlayerStatus playerStatus;

@end

@implementation ZegoOptionViewController

#pragma mark - Life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onClose:)];
    [self.view addGestureRecognizer:tapGesture];
    
    self.optionView.delegate = self;
    self.optionView.dataSource = self;
    self.optionView.layer.cornerRadius = 5.0;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Event response

- (void)onClose:(UITapGestureRecognizer *)recognizer {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)toggleMediaPlayer:(id)sender {
    UIButton *mediaPlayerButton = (UIButton *)sender;
    if ([mediaPlayerButton.currentImage isEqual: [UIImage imageNamed:@"play"]]) {
        [mediaPlayerButton setImage:[UIImage imageNamed:@"pause"] forState:UIControlStateNormal];
        if ([self.delegate respondsToSelector:@selector(onMediaPlayerStart)]) {
            [self.delegate onMediaPlayerStart];
        }
    } else {
        [mediaPlayerButton setImage:[UIImage imageNamed:@"play"] forState:UIControlStateNormal];
        if ([self.delegate respondsToSelector:@selector(onMediaPlayerStop)]) {
            [self.delegate onMediaPlayerStop];
        }
    }
}

#pragma mark - UITableViewDelegate and UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == 0) {
        return 1;
    }
    return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == 0) {
        return 44.0;
    }
    return 0.0;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    if (section == 0) {
        return NSLocalizedString(@"高级设置", nil);
    }
    return  nil;
}

- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath {
    return NO;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == 0) {
        ZegoOptionCell *cell = (ZegoOptionCell *)[tableView dequeueReusableCellWithIdentifier:@"OptionCellID" forIndexPath:indexPath];
        if (indexPath.row == 0) {
            cell.titleLabel.text = NSLocalizedString(@"媒体播放器", nil);
            if (self.playerStatus == ZegoMediaPlayerStatusPlay) {
                [cell.controlButton setImage:[UIImage imageNamed:@"pause"] forState:UIControlStateNormal];
            } else {
                [cell.controlButton setImage:[UIImage imageNamed:@"play"] forState:UIControlStateNormal];
            }
            cell.controlButton.enabled = YES;
            [cell.controlButton removeTarget:self action:NULL forControlEvents:UIControlEventTouchUpInside];
            [cell.controlButton addTarget:self action:@selector(toggleMediaPlayer:) forControlEvents:UIControlEventTouchUpInside];
        }
        
        return cell;
    } else {
        return nil;
    }
}

#pragma mark - Access method

- (ZegoMediaPlayerStatus)playerStatus {
    if ([self.delegate respondsToSelector:@selector(onGetMediaPlayerStatus)]) {
        return [self.delegate onGetMediaPlayerStatus];
    }
    return NO;
}

@end
