//
//  ZegoVideoTalkViewController.m
//  InstantTalk
//
//  Created by Strong on 16/7/11.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoAudioLiveViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoLogTableViewController.h"
#import <AVFoundation/AVFoundation.h>
#import <ZegoAudioRoom/zego-api-mediaplayer-oc.h>
#import <ZegoAudioRoom/zego-api-sound-level-oc.h>
#import "ZegoOptionViewController.h"

#define SCREEN_WIDTH ([[UIScreen mainScreen] bounds].size.width)
#define SCREEN_HEIGHT ([[UIScreen mainScreen] bounds].size.height)
#define kStreamStateKey @"stream_state"
#define kEnableMicKey  @"enable_mic"
#define kStreamIDKey @"StreamID"
#define kMaxSoundValue 100

@interface ZegoMemberInfo()

@end

@implementation ZegoMemberInfo

@end

@interface ZegoMemberCell()

@end

@implementation ZegoMemberCell

- (void)awakeFromNib {
    [super awakeFromNib];
    [self.containerView setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"background"]]];
}

@end

@interface ZegoAudioLiveViewController () <ZegoAudioLivePublisherDelegate, ZegoAudioLivePlayerDelegate, ZegoAudioRoomDelegate, ZegoAudioIMDelegate, ZegoSoundLevelDelegate, ZegoAudioLiveEventDelegate, ZegoMediaPlayerEventDelegate, ZegoMediaPlayerVideoPlayDelegate, ZegoOptionDelegate, UICollectionViewDelegate, UICollectionViewDataSource>

@property (nonatomic, strong) NSMutableArray *logArray;
@property (nonatomic, strong) NSMutableArray *streamList;

@property (weak, nonatomic) IBOutlet UICollectionView *memberCollectionView;
@property (nonatomic, weak) IBOutlet UIButton *publishButton;   // 废弃
@property (nonatomic, weak) IBOutlet UIButton *messageButton;   // 废弃
@property (weak, nonatomic) IBOutlet UIButton *micButton;
@property (weak, nonatomic) IBOutlet UIButton *speakerButton;
@property (weak, nonatomic) IBOutlet UINavigationBar *titleBar;

@property (nonatomic, strong) NSMutableArray *memberList;   // 当前房间内用户
@property (nonatomic, assign) BOOL enableSpeaker;   // YES: 外置扬声器，NO: 内置耳机
@property (nonatomic, assign) BOOL isPublished;
@property (nonatomic, assign) int publishCount;
@property (nonatomic, assign) BOOL enableMic;
@property (nonatomic, assign) BOOL isMicStatusRefreshed;

@property (nonatomic, strong) ZegoMediaPlayer *player;  // 媒体播放器
@property (nonatomic, assign) ZegoMediaPlayerStatus playStatus;

@end

@implementation ZegoAudioLiveViewController

#pragma mark - Life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // model init
    int maxCount = [ZegoAudioRoomApi getMaxPlayChannelCount];
    self.logArray = [NSMutableArray array];
    self.streamList = [NSMutableArray arrayWithCapacity:maxCount];
    self.publishCount = 0;
    self.isMicStatusRefreshed = NO;
    self.playStatus = ZegoMediaPlayerStatusStop;
    
    // authorization
    BOOL audioAuthorization = [self checkAudioAuthorization];
    if (audioAuthorization == NO)
    {
        [self showAuthorizationAlert:NSLocalizedString(@"音频通话,访问麦克风", nil) title:NSLocalizedString(@"需要访问麦克风", nil)];
    }
    
    // view init
    if ([ZegoAudioLive manualPublish]) {
        self.publishButton.hidden = NO;
    } else {
        self.publishButton.hidden = YES;
    }
    self.titleBar.topItem.title = self.roomID;
    self.publishButton.enabled = NO;
    self.messageButton.enabled = NO;
    self.speakerButton.enabled = NO;
    self.micButton.enabled = NO;
    
    // sdk setting
    [self setupLiveKit];
    
    // 扬声器，默认从扬声器出声音
    self.enableSpeaker = YES;
    [[ZegoAudioLive api] enableAEC:YES];
    [[ZegoAudioLive api] setBuiltInSpeakerOn:self.enableSpeaker];
    
    // 麦克风
    self.enableMic = YES;
    [[ZegoAudioLive api] enableMic:self.enableMic];
    
    // 用户界面
    self.memberList = [[NSMutableArray alloc] init];
    self.memberCollectionView.delegate = self;
    self.memberCollectionView.dataSource = self;
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    layout.itemSize = CGSizeMake((SCREEN_WIDTH-21)/3, (SCREEN_WIDTH-21)/3);
    layout.sectionInset = UIEdgeInsetsMake(7, 0, 0, 0);
    layout.scrollDirection = UICollectionViewScrollDirectionVertical;
    self.memberCollectionView.collectionViewLayout = layout;
    
    // 近距离传感器
//    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sensorStateChange:) name:UIDeviceProximityStateDidChangeNotification object:nil];
    
    // 监听电话事件
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(audioSessionWasInterrupted:) name:AVAudioSessionInterruptionNotification object:nil];
    
    // 进入房间
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始加入room: %@", nil), self.roomID]];
    [[ZegoAudioLive api] loginRoom:self.roomID completionBlock:^(int errorCode) {
        if (errorCode != 0) {
            [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"加入room失败: %d", nil), errorCode]];
        } else {
            self.publishButton.enabled = YES;
            self.messageButton.enabled = YES;
            self.micButton.enabled = YES;
            self.speakerButton.enabled = YES;
            
            [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"加入room成功", nil)]];
            
            [[ZegoSoundLevel sharedInstance] startSoundLevelMonitor];
            
            ZegoMemberInfo *myself = [[ZegoMemberInfo alloc] init];
            myself.stream = [[ZegoAudioStream alloc] init];
            myself.stream.userName = [ZegoSettings sharedInstance].userName;
            myself.stream.userID = [ZegoSettings sharedInstance].userID;
            myself.networkStatus = ZegoMemberStatusConnected;
            [self.memberList addObject: myself];
            
            [self.memberCollectionView reloadData];
        }
    }];
    

}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self setIdelTimerDisable:YES];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self setIdelTimerDisable:NO];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {
    [[ZegoSoundLevel sharedInstance] stopSoundLevelMonitor];
    
    if ([UIDevice currentDevice].proximityMonitoringEnabled == YES) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:UIDeviceProximityStateDidChangeNotification object:nil];
    }
    [[UIDevice currentDevice] setProximityMonitoringEnabled:NO];
}

#pragma mark - Event response

- (IBAction)onPublishButton:(id)sender
{
    if (self.isPublished)
    {
        //停止推流
        [[ZegoAudioLive api] stopPublish];
        [self.publishButton setTitle:NSLocalizedString(@"开始推流", nil) forState:UIControlStateNormal];
        self.isPublished = NO;
        
        //删除流
        for (ZegoAudioStream *audioStream in self.streamList)
        {
            if ([audioStream.userID isEqualToString:[ZegoSettings sharedInstance].userID])
            {
                [self.streamList removeObject:audioStream];
                break;
            }
        }
    }
    else
    {
        BOOL result = [[ZegoAudioLive api] startPublish];
        if (result == NO)
        {
            [self addLogString:NSLocalizedString(@"推流失败，房间内流超过上限", nil)];
        }
        else
        {
            [self.publishButton setTitle:NSLocalizedString(@"停止通话", nil) forState:UIControlStateNormal];
            self.publishButton.enabled = NO;
        }
    }
}

- (IBAction)closeView:(id)sender
{
    [[ZegoAudioLive api] logoutRoom];
    [self.streamList removeAllObjects];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)onMessageButton:(id)sender
{
    NSString *content = [NSString stringWithFormat:@"%@ hand shake", [self getCurrentTime]];
    [[ZegoAudioLive api] sendRoomMessage:content type:ZEGO_TEXT category:ZEGO_CHAT priority:ZEGO_DEFAULT completion:^(int errorCode, NSString *roomId, unsigned long long messageId) {
        if (errorCode == 0)
            [self addLogString:@"message send success"];
    }];
}

- (IBAction)onMicButton:(id)sender {
    self.enableMic = !self.enableMic;
    if (self.enableMic) {
        [self.micButton setImage:[UIImage imageNamed:@"enable_mic"] forState:UIControlStateNormal];
    } else {
        [self.micButton setImage:[UIImage imageNamed:@"disable_mic"] forState:UIControlStateNormal];
    }
    
    [[ZegoAudioLive api] enableMic:self.enableMic];
}

- (IBAction)onSpeakerButton:(id)sender {
    self.enableSpeaker = !self.enableSpeaker;
    if (self.enableSpeaker) {
        [self.speakerButton setImage:[UIImage imageNamed:@"enable_speaker"] forState:UIControlStateNormal];
    } else {
        [self.speakerButton setImage:[UIImage imageNamed:@"disable_speaker"] forState:UIControlStateNormal];
    }
    
    [[ZegoAudioLive api] setBuiltInSpeakerOn:self.enableSpeaker];
}

//- (void)sensorStateChange:(NSNotification *)notification {
//
//}

- (IBAction)onAdvancedButton:(id)sender {
    UIStoryboard *sb = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    ZegoOptionViewController *controller = (ZegoOptionViewController *)[sb instantiateViewControllerWithIdentifier:@"optionControllerID"];
    controller.delegate = self;
    
    self.definesPresentationContext = YES;
    controller.modalPresentationStyle = UIModalPresentationOverCurrentContext;
    controller.view.backgroundColor = [UIColor clearColor];
    [self presentViewController:controller animated:YES completion:nil];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"logSegueIdentifier"])
    {
        UINavigationController *navigationController = [segue destinationViewController];
        ZegoLogTableViewController *logViewController = (ZegoLogTableViewController *)[navigationController.viewControllers firstObject];
        logViewController.logArray = self.logArray;
    }
}

#pragma mark - Access Method
- (void)setEnableSpeaker:(BOOL)enableSpeaker {
    if (_enableSpeaker != enableSpeaker) {
        _enableSpeaker = enableSpeaker;
        if (enableSpeaker) {
            // 开启扬声器，不启用近距离传感器
            [self enableProximityMonitor:NO];
        } else {
            // 关闭扬声器，启用近距离传感器，靠近时屏幕黑屏
            [self enableProximityMonitor:YES];
        }
    }
}

- (void)setEnableMic:(BOOL)enableMic {
    if (_enableMic != enableMic) {
        _enableMic = enableMic;
        [self updateMicStatus:enableMic];
    }
}

#pragma mark - Private method

- (void)enableProximityMonitor:(BOOL)enable {
    // 近距离传感器开启
    if (enable) {
        [[UIDevice currentDevice] setProximityMonitoringEnabled:YES];
    } else {
        [[UIDevice currentDevice] setProximityMonitoringEnabled:NO];
    }

}

- (void)setupLiveKit
{
    [[ZegoAudioLive api] setUserStateUpdate:YES];
    [[ZegoAudioLive api] setAudioRoomDelegate:self];
    [[ZegoAudioLive api] setAudioPlayerDelegate:self];
    [[ZegoAudioLive api] setAudioPublisherDelegate:self];
    [[ZegoAudioLive api] setAudioIMDelegate:self];
    [[ZegoAudioLive api] setAudioLiveEventDelegate:self];
    [[ZegoSoundLevel sharedInstance] setSoundLevelDelegate:self];
}

- (void)openSetting
{
    NSURL *settingURL = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
    if ([[UIApplication sharedApplication] canOpenURL:settingURL])
        [[UIApplication sharedApplication] openURL:settingURL];
}

- (void)showAuthorizationAlert:(NSString *)message title:(NSString *)title
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"取消", nil) style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
    }];
    UIAlertAction *settingAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"设置权限", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self openSetting];
    }];
    
    [alertController addAction:settingAction];
    [alertController addAction:cancelAction];
    
    alertController.preferredAction = settingAction;
    
    [self presentViewController:alertController animated:YES completion:nil];
}

- (NSString *)getCurrentTime
{
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"HH-mm-ss:SSS";
    return [formatter stringFromDate:[NSDate date]];
}

- (void)addLogString:(NSString *)logString
{
    if (logString.length != 0)
    {
        NSString *totalString = [NSString stringWithFormat:@"%@: %@", [self getCurrentTime], logString];
        [self.logArray insertObject:totalString atIndex:0];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:@"logUpdateNotification" object:self userInfo:nil];
    }
}

- (void)updateMicStatus:(BOOL)enableMic {
    if (enableMic) {
        for (ZegoMemberInfo *member in self.memberList) {
            if ([member.stream.userID isEqualToString:[ZegoSettings sharedInstance].userID]) {
                member.speakingStatus = ZegoMemberStatusIsSpeaking;
            }
        }
    } else {
        for (ZegoMemberInfo *member in self.memberList) {
            if ([member.stream.userID isEqualToString:[ZegoSettings sharedInstance].userID]) {
                member.speakingStatus = ZegoMemberStatusNoSpeaking;
            }
        }
    }
    
    // 通过更新 extrainfo，向其他人更新自己的状态
    NSDictionary *dict = @{kStreamStateKey: @{kEnableMicKey:[NSNumber numberWithBool:enableMic]}};
    NSString *jsonString = [self encodeDictionaryToJSON:dict];
    BOOL result = [[ZegoAudioLive api] updateStreamExtraInfo:jsonString];
    if (result) {
        NSLog(@"updateStreamExtraInfo succeed");
    } else {
        NSLog(@"updateStreamExtraInfo failed");
    }
}

- (NSString *)encodeDictionaryToJSON:(NSDictionary *)dictionary
{
    if (dictionary == nil)
        return nil;
    
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dictionary options:0 error:nil];
    if (jsonData)
    {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        return jsonString;
    }
    
    return nil;
}

- (NSDictionary *)dictionaryFromJSONString:(NSString *)jsonString {
    if (jsonString == nil) {
        return nil;
    }
    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                        options:NSJSONReadingMutableContainers
                                                          error:&error];
    if(error) {
        NSLog(@"json解析失败：%@",error);
        return nil;
    }
    return dic;
}

- (void)addNewMemberFromUserState:(ZegoUserState *)userState {
    ZegoMemberInfo *info = [[ZegoMemberInfo alloc] init];
    info.stream = [[ZegoAudioStream alloc] init];
    info.stream.userID = userState.userID;
    info.stream.userName = userState.userName;
    info.networkStatus = ZegoMemberStatusConnected;
    
    // 这种情况下，memberInfo 中缺少 streamID，后面会补全
    [self addNewMember:info];
}

- (void)addNewMemberFromStream:(ZegoAudioStream *)stream {
    ZegoMemberInfo *info = [[ZegoMemberInfo alloc] init];
    info.stream = [[ZegoAudioStream alloc] init];
    info.stream.userID = stream.userID;
    info.stream.userName = stream.userName;
    info.stream.streamID = stream.streamID;
    info.networkStatus = ZegoMemberStatusConnected;
    [self addNewMember:info];
}

- (void)addNewMember:(ZegoMemberInfo *)member {
    BOOL isUserExisted = NO;
    
    for (ZegoMemberInfo *user in self.memberList) {
        if ([user.stream.userID isEqualToString:member.stream.userID]) {
            isUserExisted = YES;
        }
        
        // 先收到 onUserUpdate，此时 member 存在，但 Info 中没有 streamID 信息，需要更新
        if (isUserExisted && user.stream.streamID == nil) {
            user.stream.streamID = member.stream.streamID;
        }
    }
    
    // member 不存在，直接添加新 member
    if (!isUserExisted) {
        [self.memberList addObject:member];
    }
}

// 根据 extrainfo 更新其他人的麦克风状态
- (void)updateMicStatusOfStream:(ZegoAudioStream *)stream {
    NSString *extraInfo = stream.extraInfo;
    if (![extraInfo length]) {
        NSLog(@"extrainfo 为空");
        return;
    }
    
    NSDictionary *dict = [self dictionaryFromJSONString:extraInfo];
    if (![dict objectForKey:kStreamStateKey] || ![dict[kStreamStateKey] objectForKey:kEnableMicKey]) {
        NSLog(@"extrainfo 字段错误: %@", dict);
        return;
    }
    
    for (ZegoMemberInfo *member in self.memberList) {
        if ([member.stream.userID isEqualToString:stream.userID]) {
            member.stream = stream;
            if ([dict[kStreamStateKey][kEnableMicKey] boolValue]) {
                member.speakingStatus = ZegoMemberStatusIsSpeaking;
            } else {
                member.speakingStatus = ZegoMemberStatusNoSpeaking;
                member.soundLevel = 0.0f;
            }
        }
    }
    [self.memberCollectionView reloadData];
}

#pragma mark - Audiosession Interrupted notification

- (void)audioSessionWasInterrupted:(NSNotification *)notification
{
    if (AVAudioSessionInterruptionTypeBegan == [notification.userInfo[AVAudioSessionInterruptionTypeKey] intValue])
    {

    }
    else if (AVAudioSessionInterruptionTypeEnded == [notification.userInfo[AVAudioSessionInterruptionTypeKey] intValue])
    {

    }
}

- (BOOL)checkAudioAuthorization
{
    AVAuthorizationStatus audioAuthStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
    if (audioAuthStatus == AVAuthorizationStatusDenied || audioAuthStatus == AVAuthorizationStatusRestricted)
        return NO;
    if (audioAuthStatus == AVAuthorizationStatusNotDetermined)
    {
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {
        }];
    }

    return YES;
}

- (void)setIdelTimerDisable:(BOOL)disable
{
    [[UIApplication sharedApplication] setIdleTimerDisabled:disable];
}

#pragma mark - ZegoOptionDelegate

- (ZegoMediaPlayerStatus)onGetMediaPlayerStatus {
    return self.playStatus;
}

- (void)onMediaPlayerStart {
    // 媒体播放器自动播放
    if (self.player == nil) {
        self.player = [[ZegoMediaPlayer alloc] initWithPlayerType: MediaPlayerTypeAux];
        [self.player setDelegate:self];
    }
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"mp3"];
    [self.player start:path Repeat:YES];
    self.playStatus = ZegoMediaPlayerStatusPlay;
}

- (void)onMediaPlayerStop {
    [self.player stop];
    self.playStatus = ZegoMediaPlayerStatusStop;
}

#pragma mark - ZegoAudioLivePublisherDelegate

- (void)onPublishStateUpdate:(int)stateCode streamID:(NSString *)streamID streamInfo:(NSDictionary *)info
{
    if (stateCode == 0)
    {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"推流成功，streamID: %@", nil), streamID]];
        
        if ([ZegoAudioLive manualPublish])
        {
            self.publishButton.enabled = YES;
            self.isPublished = YES;
        }

        ZegoAudioStream *audioStream = [ZegoAudioStream new];
        audioStream.streamID = streamID;
        audioStream.userID = [ZegoSettings sharedInstance].userID;
        audioStream.userName = [ZegoSettings sharedInstance].userName;
        [self.streamList addObject:audioStream];
        
        for (ZegoMemberInfo *member in self.memberList) {
            if ([member.stream.userID isEqualToString:[ZegoSettings sharedInstance].userID]) {
                member.stream.streamID = streamID;
                member.networkStatus = ZegoMemberStatusConnected;
                member.speakingStatus = ZegoMemberStatusIsSpeaking;
            }
        }
        [self.memberCollectionView reloadData];
        
        //清空计数器
        self.publishCount = 0;
    }
    else
    {
        for (ZegoAudioStream *playStream in self.streamList)
        {
            if ([playStream.streamID isEqualToString:streamID])
            {
                [self.streamList removeObject:(playStream)];
                break;
            }
        }
        if ([ZegoAudioLive manualPublish])
        {
            self.publishButton.enabled = YES;
            self.isPublished = NO;
            [self.publishButton setTitle:NSLocalizedString(@"开始通话", nil) forState:UIControlStateNormal];
        }
        
        for (ZegoMemberInfo *member in self.memberList) {
            if ([member.stream.userID isEqualToString:[ZegoSettings sharedInstance].userID]) {
                member.stream.streamID = streamID;
                member.networkStatus = ZegoMemberStatusDisconnect;
            }
        }
        
        [self.memberCollectionView reloadData];
        
        // 当出现推流失败，开始重试推流!
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"推流失败: %@, error:%d", nil), streamID, stateCode]];
        [self retryPublish:3.0];
    }
}

-(void)retryPublish:(float)interval {
   [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"推流失败, 重试推流", nil)]];
   //取消延时执行方法
   [NSObject cancelPreviousPerformRequestsWithTarget:self];
   //开启新的延时执行方法
   [self performSelector:@selector(retryPublishStream) withObject:@"stopRecord" afterDelay:interval];
}

- (void)retryPublishStream {
    if (self.publishCount <= 10) {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始第 %d 次重试推流",nil), self.publishCount + 1]];
        [[ZegoAudioLive api] restartPublishStream];
        self.publishCount++;
        
        for (ZegoMemberInfo *member in self.memberList) {
            if ([member.stream.userID isEqualToString:[ZegoSettings sharedInstance].userID]) {
                member.networkStatus = ZegoMemberStatusConnecting;
            }
        }
    } else {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"重试推流全部失败，放弃治疗",nil)]];
    }
}

- (void)onPublishQualityUpdate:(NSString *)streamID quality:(ZegoApiPublishQuality)quality
{
    NSLog(@"onPublishQualityUpdate, streamID: %@, quality: %d, audiobiterate: %fkb", streamID, quality.quality, quality.akbps);
    for (ZegoMemberInfo *member in self.memberList) {
        if ([member.stream.streamID isEqualToString:streamID]) {
            member.publishQuality = quality;
        }
    }
    [self.memberCollectionView reloadData];
}

#pragma mark - ZegoAudioLivePlayerDelegate
- (void)onPlayStateUpdate:(int)stateCode stream:(ZegoAudioStream *)stream
{
    if (stateCode == 0) {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"拉流成功，streamID: %@，userName: %@，userID: %@", nil), stream.streamID, stream.userName, stream.userID]];
        [self addNewMemberFromStream:stream];
        [self updateMicStatusOfStream:stream];
    } else {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"拉流失败，streamID: %@，userName: %@，userID: %@，error: %d", nil), stream.streamID, stream.userName, stream.userID, stateCode]];
        
        for (ZegoMemberInfo *member in self.memberList) {
            if ([member.stream.userID isEqualToString:stream.userID]) {
                member.stream = stream;
                member.networkStatus = ZegoMemberStatusDisconnect;
            }
        }
    }
    
    [self.memberCollectionView reloadData];
}

- (void)onPlayQualityUpate:(NSString *)streamID quality:(ZegoApiPlayQuality)quality
{
    NSLog(@"onPlayQualityUpate, streamID: %@, quality: %d, audiobiterate: %fkb", streamID, quality.quality, quality.akbps);
    for (ZegoMemberInfo *member in self.memberList) {
        if ([member.stream.streamID isEqualToString:streamID]) {
            member.playQuality = quality;
        }
    }
    [self.memberCollectionView reloadData];
}

#pragma mark - ZegoAudioLiveEventDelegate
- (void)zego_onAudioLiveEvent:(ZegoAudioLiveEvent)event info:(NSDictionary<NSString*, NSString*>*)info {
    if(![info objectForKey:kStreamIDKey]) {
        NSLog(@"zego_onAudioLiveEvent, streamID is null");
        return;
    }
    
    [self addLogString:[NSString stringWithFormat:@"zego_onAudioLiveEvent, streamID: %@, event:%lu", [info objectForKey:kStreamIDKey], (unsigned long)event]];
    for (ZegoMemberInfo *member in self.memberList) {
        if ([member.stream.streamID isEqualToString:[info objectForKey:kStreamIDKey]]) {
            switch (event) {
                case Audio_Play_TempDisconnected:
                    member.networkStatus = ZegoMemberStatusDisconnect;
                    break;
                case Audio_Play_BeginRetry:
                    member.networkStatus = ZegoMemberStatusConnecting;
                    break;
                case Audio_Play_RetrySuccess:
                    member.networkStatus = ZegoMemberStatusConnected;
                    break;
                case Audio_Publish_TempDisconnected:
                    member.networkStatus = ZegoMemberStatusDisconnect;
                    break;
                case Audio_Publish_BeginRetry:
                    member.networkStatus = ZegoMemberStatusConnecting;
                    break;
                case Audio_Publish_RetrySuccess:
                    member.networkStatus = ZegoMemberStatusConnected;
                    break;
            }
        }
    }
    [self.memberCollectionView reloadData];
}

#pragma mark - ZegoAudioRoomDelegate

- (void)onDisconnect:(int)errorCode roomID:(NSString *)roomID
{
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"连接房间失败 %d", nil), errorCode]];
    for (ZegoMemberInfo *info in self.memberList) {
        info.networkStatus = ZegoMemberStatusDisconnect;
    }
    [self.memberCollectionView reloadData];
}

- (void)onStreamUpdated:(ZegoAudioStreamType)type stream:(ZegoAudioStream *)stream
{
    if (type == ZEGO_AUDIO_STREAM_ADD) {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"新增流:%@", nil), stream.streamID]];
        [self addNewMemberFromStream:stream];
        [self updateMicStatusOfStream:stream];
    } else {
        for (ZegoAudioStream *playStream in self.streamList) {
            if ([playStream.streamID isEqualToString:stream.streamID]) {
                [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"删除流:%@", nil), stream.streamID]];
                [self.streamList removeObject:playStream];
                break;
            }
        }
    }
}

- (void)onUserUpdate:(NSArray<ZegoUserState *> *)userList updateType:(ZegoUserUpdateType)type
{
    if (type == ZEGO_UPDATE_TOTAL) {
        [self addLogString:NSLocalizedString(@"用户列表已全量更新", nil)];
    } else if (type == ZEGO_UPDATE_INCREASE) {
        [self addLogString:NSLocalizedString(@"用户列表增量更新", nil)];
    }
    
    for (ZegoUserState *userState in userList) {
        if (userState.updateFlag == ZEGO_USER_ADD) {
            [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"%@ 用户进入房间", nil), userState.userID]];
            [self addNewMemberFromUserState:userState];
        } else if (userState.updateFlag == ZEGO_USER_DELETE) {
            [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"%@ 用户离开房间", nil), userState.userID]];
            for (NSInteger i = self.memberList.count - 1; i > 0; i--) {
                ZegoMemberInfo *user = self.memberList[i];
                if([user.stream.userID isEqualToString:userState.userID]) {
                    [self.memberList removeObjectAtIndex:i];
                    [self.memberCollectionView reloadData];
                }
            }
        }
    }
}

- (void)onRecvAudioRoomMessage:(NSString *)roomId messageList:(NSArray<ZegoRoomMessage *> *)messageList
{
    for (ZegoRoomMessage *message in messageList)
    {
        [self addLogString:[NSString stringWithFormat:@"%@ said: %@", message.fromUserId, message.content]];
    }
}

- (void)onStreamExtraInfoUpdated:(NSArray<ZegoAudioStream *> *)streamList roomID:(NSString *)roomID {
    if (![roomID isEqualToString:self.roomID]) {
        NSLog(@"%@", [NSString stringWithFormat:@"roomID（%@）与 roomID（%@）不匹配，忽略", roomID, self.roomID]);
        return;
    }
    
    for (ZegoMemberInfo *info in self.memberList) {
        for (ZegoAudioStream *stream in streamList) {
            if ([info.stream.userID isEqualToString:stream.userID]) {
                NSString *extraInfo = stream.extraInfo;
                NSDictionary *dict = [self dictionaryFromJSONString:extraInfo];
                
                if (![dict objectForKey:kStreamStateKey] || ![dict[kStreamStateKey] objectForKey:kEnableMicKey]) {
                    NSLog(@"流（%@）的 extrainfo 字段错误: %@", stream.streamID, dict);
                    return;
                }
                
                if ([dict[kStreamStateKey][kEnableMicKey] boolValue]) {
                    info.speakingStatus = ZegoMemberStatusIsSpeaking;
                } else {
                    info.speakingStatus = ZegoMemberStatusNoSpeaking;
                    info.soundLevel = 0.0f;
                }
            }
        }
    }
    [self.memberCollectionView reloadData];
}

#pragma mark - UICollectionViewDataSource

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.memberList.count;
}

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    ZegoMemberCell *cell = (ZegoMemberCell*)[collectionView dequeueReusableCellWithReuseIdentifier:@"MemberCellID" forIndexPath:indexPath];
    
    if (indexPath.item > self.memberList.count) {
        return cell;
    }
    
    ZegoMemberInfo *memberInfo = self.memberList[indexPath.item];
    if (memberInfo.stream.userName.length > 0) {
        if ([memberInfo.stream.userID isEqualToString:[ZegoSettings sharedInstance].userID]) {
            NSString *rawString = [NSString stringWithFormat:@"%@（自己）", memberInfo.stream.userName];
            NSDictionary *attr = @{NSForegroundColorAttributeName: [UIColor yellowColor]};
            NSMutableAttributedString *attrString = [[NSMutableAttributedString alloc] initWithString:rawString attributes:attr];
            cell.nameLabel.attributedText = attrString;
        } else {
            cell.nameLabel.text = memberInfo.stream.userName;
        }
    }
    
    if ([memberInfo.stream.userID isEqualToString:[ZegoSettings sharedInstance].userID]) {
        // 推流质量展示
        cell.qualityLabel.text = [NSString stringWithFormat:@"延时：%dms\n丢包率：%.1f%%", memberInfo.publishQuality.rtt, memberInfo.publishQuality.pktLostRate / 256.0 * 100];
    } else {
        // 拉流质量展示
        cell.qualityLabel.text = [NSString stringWithFormat:@"延时：%dms\n丢包率：%.1f%%\n卡顿率：%.1f次/min", memberInfo.playQuality.rtt, memberInfo.playQuality.pktLostRate / 256.0 * 100, memberInfo.playQuality.audioBreakRate];
    }
    
    [cell.soundView setProgress:memberInfo.soundLevel animated:NO];
    
    if (memberInfo.networkStatus == ZegoMemberStatusConnected) {
        switch (memberInfo.speakingStatus) {
            case ZegoMemberStatusIsSpeaking:
                cell.soundView.hidden = NO;
                [cell.statusView setBackgroundImage:[UIImage imageNamed:@"is_speaking"] forState:UIControlStateNormal];
                break;
            case ZegoMemberStatusNoSpeaking:
                cell.soundView.hidden = YES;
                [cell.statusView setBackgroundImage:[UIImage imageNamed:@"no_speaking"] forState:UIControlStateNormal];
                break;
        }
    } else if (memberInfo.networkStatus == ZegoMemberStatusConnecting) {
        cell.soundView.hidden = YES;
        [cell.statusView setBackgroundImage:[UIImage imageNamed:@"connecting"] forState:UIControlStateNormal];
    } else if (memberInfo.networkStatus == ZegoMemberStatusDisconnect) {
        cell.soundView.hidden = YES;
        [cell.statusView setBackgroundImage:[UIImage imageNamed:@"disconnect"] forState:UIControlStateNormal];
    }
    
    return cell;
}

#pragma mark - ZegoSoundLevelUpdateDelegate

- (void)onSoundLevelUpdate:(NSArray<ZegoSoundLevelInfo *> *)soundLevels {
    for (ZegoMemberInfo *info in self.memberList) {
        NSLog(@"member stream: %@ ", info.stream.streamID);
        for (ZegoSoundLevelInfo *levelInfo in soundLevels) {
            NSLog(@"soundlevel stream: %@ ", levelInfo.streamID);
//            NSLog(@"stream: %@, soundLevel: %.3f", levelInfo.streamID, info.soundLevel);
            if ([info.stream.streamID isEqualToString:levelInfo.streamID]) {
                info.soundLevel = levelInfo.soundLevel / kMaxSoundValue;
            }
        }
    }
    [self.memberCollectionView reloadData];
}

- (void)onCaptureSoundLevelUpdate:(ZegoSoundLevelInfo *)captureSoundLevel {
    if (self.enableMic) {
        for (ZegoMemberInfo *info in self.memberList) {
            // 打开扬声器，且推流状态正常时，才需要展示音量
            if ([info.stream.streamID isEqualToString:captureSoundLevel.streamID] && info.speakingStatus ==ZegoMemberStatusIsSpeaking) {
                info.soundLevel = captureSoundLevel.soundLevel / kMaxSoundValue;
            }
        }
    } else {
        // 用户关闭麦克风，采集音量依然存在，但不展示自己的音量值。并且展示麦克风关闭
        for (ZegoMemberInfo *info in self.memberList) {
            if ([info.stream.streamID isEqualToString:captureSoundLevel.streamID]) {
                info.soundLevel = 0.0f;
                info.speakingStatus = ZegoMemberStatusNoSpeaking;
            }
        }
    }
    [self.memberCollectionView reloadData];
}

# pragma mark - ZegoMediaPlayerEventDelegate

- (void)onPlayStart {
    [self addLogString:@"media player onPlayStart"];
    self.playStatus = ZegoMediaPlayerStatusPlay;
}

- (void)onPlayError:(int)code {
    [self addLogString:[NSString stringWithFormat:@"media player onPlayError: %d", code]];
    self.playStatus = ZegoMediaPlayerStatusStop;
}

- (void)onPlayEnd {
    [self addLogString:@"media player onPlayEnd"];
    self.playStatus = ZegoMediaPlayerStatusStop;
}

@end
