//
//  ZegoSettings.m
//  LiveDemo3
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoSettings.h"

#include <string>

NSString *kZegoDemoUserIDKey            = @"userid";
NSString *kZegoDemoUserNameKey          = @"username";

@implementation ZegoSettings
{
    NSString *_userID;
    NSString *_userName;
}

+ (instancetype)sharedInstance {
    static ZegoSettings *s_instance = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        s_instance = [self new];
    });
    
    return s_instance;
}

- (instancetype)init {
    self = [super init];
    if (self)
    {
        _appTypeList = @[NSLocalizedString(@"国内版", nil),
                         NSLocalizedString(@"国际版", nil),
                         NSLocalizedString(@"自定义", nil)];
    }
    
    return self;
}

- (NSString *)userID {
    if (_userID.length == 0) {
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        NSString *userID = [ud stringForKey:kZegoDemoUserIDKey];
        if (userID.length > 0) {
            _userID = userID;
        } else {
            srand((unsigned)time(0));
            _userID = [NSString stringWithFormat:@"%u", (unsigned)rand()];
            [ud setObject:_userID forKey:kZegoDemoUserIDKey];
        }
    }
    
    return _userID;
}

- (void)setUserID:(NSString *)userID {
    if ([_userID isEqualToString:userID]) {
        return;
    }
    
    if (userID.length > 0) {
        _userID = userID;
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        [ud setObject:_userID forKey:kZegoDemoUserIDKey];
        
        [ZegoAudioLive releaseApi];
    }
}

- (void)cleanLocalUser
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults removeObjectForKey:kZegoDemoUserIDKey];
    [userDefaults removeObjectForKey:kZegoDemoUserNameKey];
    
    _userID = nil;
    _userName = nil;
}

- (NSString *)userName {
    if (_userName.length == 0) {
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        NSString *userName = [ud stringForKey:kZegoDemoUserNameKey];
        if (userName.length > 0) {
            _userName = userName;
        } else {
            srand((unsigned)time(0));
#if TARGET_OS_SIMULATOR
            _userName = [NSString stringWithFormat:@"simulator-%u", (unsigned)rand()];
#else
            _userName = [NSString stringWithFormat:@"iphone-%u", (unsigned)rand()];
#endif
            [ud setObject:_userName forKey:kZegoDemoUserNameKey];
        }
    }
    
    return _userName;
}


- (void)setUserName:(NSString *)userName {
    if ([_userName isEqualToString:userName]) {
        return;
    }
    
    if (userName.length > 0) {
        _userName = userName;
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        [ud setObject:_userName forKey:kZegoDemoUserNameKey];
        
        [ZegoAudioLive releaseApi];
    }
}

- (BOOL)isDeviceiOS7
{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 8.0)
        return YES;
    
    return NO;
}

@end
