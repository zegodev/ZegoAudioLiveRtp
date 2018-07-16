//
//  ZegoSettings.h
//  LiveDemo3
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZegoAVKitManager.h"

@interface ZegoSettings : NSObject

+ (instancetype)sharedInstance;

@property (nonatomic, copy) NSString *userID;
@property (nonatomic, copy) NSString *userName;

@property (nonatomic, readonly) NSArray *appTypeList;

- (void)cleanLocalUser;

- (BOOL)isDeviceiOS7;

@end
