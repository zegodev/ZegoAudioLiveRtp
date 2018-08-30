//
//  ZegoSetTableViewController.m
//  AudioLive
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoSetTableViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import <MessageUI/MessageUI.h>
#import <SafariServices/SFSafariViewController.h>
#import <SSZipArchive/SSZipArchive.h>
#import "ZegoShareLogViewController.h"

@interface ZegoSetTableViewController ()<MFMailComposeViewControllerDelegate>
@property (weak, nonatomic) IBOutlet UILabel *sdkVersion;
@property (weak, nonatomic) IBOutlet UILabel *veVersion;
@property (weak, nonatomic) IBOutlet UILabel *appVersion;

@property (weak, nonatomic) IBOutlet UISwitch *testEnvSwitch;
@property (weak, nonatomic) IBOutlet UIPickerView *appTypePicker;
@property (weak, nonatomic) IBOutlet UITextField *appIDText;
@property (weak, nonatomic) IBOutlet UITextField *appSignText;

@property (weak, nonatomic) IBOutlet UITextField *userID;
@property (weak, nonatomic) IBOutlet UITextField *userName;

@property (weak, nonatomic) IBOutlet UISwitch *manualSwitch;

@property (nonatomic, strong) UITapGestureRecognizer *tapGesture;

@property (nonatomic, strong) UIActivityIndicatorView *indicatorView;

@end

@implementation ZegoSetTableViewController

#pragma mark - Life cycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillHide:)
                                                 name:UIKeyboardWillHideNotification
                                               object:nil];
    
    [self loadAccountSettings];
    [self loadEnvironmentSettings];
    
    self.manualSwitch.on = [ZegoAudioLive enableMediaPlayer];
    
    // 发送日志邮件彩蛋
//    UITapGestureRecognizer *gesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(shareLogFile)];
//    gesture.numberOfTapsRequired = 5;
//    [self.tableView addGestureRecognizer:gesture];

}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
}

- (void)viewWillDisappear:(BOOL)animated {
    [ZegoSettings sharedInstance].userID = self.userID.text;
    [ZegoSettings sharedInstance].userName = self.userName.text;
    
    [super viewWillDisappear:animated];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIKeyboardWillHideNotification
                                                  object:nil];
}

#pragma mark - Event response

- (IBAction)toggleTestEnv:(id)sender {
    UISwitch *s = (UISwitch *)sender;
    [ZegoAudioLive setUsingTestEnv:s.on];
}

- (void)onTapTableView:(UIGestureRecognizer *)gesture
{
    [self.view endEditing:YES];
    
//    if (!self.userName.isEditing)
//        [self.view endEditing:YES];
}

- (IBAction)toggleManualSwitch:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoAudioLive setEnableMediaPlayer:s.on];
}

- (void)keyboardWillHide:(NSNotification *)notification {
    if ([ZegoAudioLive appType] == ZegoAppTypeCustom) {
        if (self.appIDText.text.length == 0 && self.appSignText.text.length == 0) {
            [ZegoAudioLive setAppType:ZegoAppTypeUDP];
            [self.appTypePicker selectRow:ZegoAppTypeUDP inComponent:0 animated:NO];
            [self loadAppID];
        } else if (self.appIDText.text.length != 0 && self.appSignText.text.length != 0) {
            NSString *strAppID = self.appIDText.text;
            uint32_t appID = (uint32_t)[strAppID longLongValue];
            [ZegoAudioLive setCustomAppID:appID sign:self.appSignText.text];
        }
    }
    
    if ([self.appIDText.text isEqualToString:@"1"]) {    // 当用户选择自定义，并且输入的 AppID 为 1 时，自动识别为 RTMP 版本且填充 AppSign
        NSString *signkey = @"0x91,0x93,0xcc,0x66,0x2a,0x1c,0x0e,0xc1,0x35,0xec,0x71,0xfb,0x07,0x19,0x4b,0x38,0x41,0xd4,0xad,0x83,0x78,0xf2,0x59,0x90,0xe0,0xa4,0x0c,0x7f,0xf4,0x28,0x41,0xf7";
        [ZegoAudioLive setCustomAppID:1 sign:signkey];
        [self.appSignText setText:signkey];
    }
    
    if (self.userName.text.length == 0) {
        [self showAlert:NSLocalizedString(@"请重新输入！", nil) message:NSLocalizedString(@"该字段不可为空", nil)];
        self.userName.text = [ZegoSettings sharedInstance].userName;
    }
}

#pragma mark - Private method

- (void)loadAccountSettings {
    NSUInteger userIDInteger = [[ZegoSettings sharedInstance].userID integerValue];
    if (userIDInteger == 0)
    {
        [[ZegoSettings sharedInstance] cleanLocalUser];
    }
    
    self.userID.text = [ZegoSettings sharedInstance].userID;
    self.userName.text = [ZegoSettings sharedInstance].userName;
    
    self.userName.clearButtonMode = UITextFieldViewModeWhileEditing;
    
    self.appVersion.text = [NSString stringWithFormat:@"App: %@", [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]];
    self.sdkVersion.text = [NSString stringWithFormat:@"SDK: %@", [ZegoAudioRoomApi version]];
    self.veVersion.text = [NSString stringWithFormat:@"VE: %@", [ZegoAudioRoomApi version2]];
}

- (void)loadEnvironmentSettings {
    self.testEnvSwitch.on = [ZegoAudioLive usingTestEnv];
    [self.appTypePicker selectRow:[ZegoAudioLive appType] inComponent:0 animated:NO];
    
    [self loadAppID];
}

- (void)loadAppID {
    ZegoAppType type = [ZegoAudioLive appType];
    
    // 导航栏标题随设置变化
    NSString *title = [NSString stringWithFormat:@"ZEGO(%@)", [ZegoSettings sharedInstance].appTypeList[type]];
    self.navigationItem.title =  NSLocalizedString(title, nil);
    
    // 自定义的 APPID 来源于用户输入
    uint32_t appID = [ZegoAudioLive appID];
    NSData *appSign = [ZegoAudioLive zegoAppSignFromServer];
    if (type == ZegoAppTypeCustom) {
        NSString *appSignString = [ZegoAudioLive customAppSign];
        
        if (appID && appSign) {
            self.appIDText.enabled = YES;
            [self.appIDText setText:[NSString stringWithFormat:@"%u", appID]];
            
            self.appSignText.enabled = YES;
            [self.appSignText setText:appSignString];
        } else {
            NSIndexPath *indexPath = [NSIndexPath indexPathForRow:0 inSection:1];
            [self.tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionTop animated:NO];
            
            self.appIDText.enabled = YES;
            [self.appIDText setText:@""];
            self.appIDText.placeholder = NSLocalizedString(@"请输入 AppID", nil);
            self.appIDText.clearButtonMode = UITextFieldViewModeWhileEditing;
            self.appIDText.keyboardType = UIKeyboardTypeDefault;
            self.appIDText.returnKeyType = UIReturnKeyDone;
            [self.appIDText becomeFirstResponder];
            
            self.appSignText.placeholder = NSLocalizedString(@"请输入 AppSign", nil);
            self.appSignText.clearButtonMode = UITextFieldViewModeWhileEditing;
            self.appSignText.keyboardType = UIKeyboardTypeASCIICapable;
            self.appSignText.returnKeyType = UIReturnKeyDone;
            self.appSignText.enabled = YES;
            [self.appSignText setText:@""];
        }
    } else {
        // 其他类型的 APPID 从本地加载
        [self.appIDText resignFirstResponder];
        [self.appSignText setText:@""];
        self.appSignText.placeholder = NSLocalizedString(@"AppSign 已设置", nil);
        self.appSignText.enabled = NO;
        
        self.appIDText.enabled = NO;
        [self.appIDText setText:[NSString stringWithFormat:@"%u", appID]];
    }
}

- (void)showUploadAlertView
{
    NSString *message = [NSString stringWithFormat:NSLocalizedString(@"日志上传成功", nil)];
    //    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 8.0)
    {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"" message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alertView show];
    }
}

- (void)showAlert:(NSString *)title message:(NSString *)message {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title
                                                                   message:message
                                                            preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:NSLocalizedString(@"确定", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self dismissViewControllerAnimated:YES completion:nil];
    }];
    
    [alert addAction:confirm];
    [self presentViewController:alert animated:NO completion:nil];
}

- (void)shareLogFile {
    [self performSegueWithIdentifier:@"uploadLogIdentifier" sender:nil];
}

- (void)sendEmail {
    if ([MFMailComposeViewController canSendMail]) {
        MFMailComposeViewController *mailCompose = [[MFMailComposeViewController alloc] init];
        [mailCompose setMailComposeDelegate:self];
        
        // 主体
        NSDate *date = [NSDate date]; //date: 2016-07-07 08:00:04 UTC
        NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
        [formatter setDateFormat:@"YYYYMMddHHmmss"];
        NSString *dateString = [formatter stringFromDate:date]; //dateString: 20160707160333
        
        NSString *subject = [NSString stringWithFormat:@"%d-%@-%@", [ZegoAudioLive appID], [ZegoSettings sharedInstance].userID, dateString];
        [mailCompose setSubject:[NSString stringWithFormat:@"手动发送日志提醒【%@】", subject]];
        
        // 收件人
        [mailCompose setToRecipients:@[@"zegosdklog@zego.im"]];
        
        // 正文
        NSString *mailContent = @"手动发送日志邮件";
        [mailCompose setMessageBody:mailContent isHTML:NO];
        
        // 附件
        [mailCompose addAttachmentData:[self zipArchiveWithFiles] mimeType:@"application/zip" fileName:@"zegoavlog.zip"];
        
        [self presentViewController:mailCompose animated:YES completion:nil];
        
        // 清理环境，删除当次的 zip 文件
        NSString *zipPath = [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingString:@"/ZegoLogs/zegoavlog.zip"];
        NSError *error;
        [[NSFileManager defaultManager] removeItemAtPath:zipPath error:&error];
        if (error) {
            NSLog(@"删除日志 zip 文件失败");
        }
    } else {
        [self showAlert:NSLocalizedString(@"无法发送邮件", nil) message:NSLocalizedString(@"请先在手机的 [设置>邮件] 中添加可使用账户并开启邮件服务", nil)];
    }
}

- (NSData *)zipArchiveWithFiles {
    NSString *cachesPath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject];
    NSString *zegologs = [cachesPath stringByAppendingString:@"/ZegoLogs"];
    
    // 获取 Library/Caches/ZegoLogs 目录下的所有文件
    NSFileManager *manager = [NSFileManager defaultManager];
    NSArray *files = [manager subpathsAtPath:zegologs];
    
    NSMutableArray *logFiles = [NSMutableArray arrayWithCapacity:1];
    [files enumerateObjectsUsingBlock:^(NSString *obj, NSUInteger idx, BOOL * stop) {
        // 取出 ZegoLogs 下的 txt 日志文件
        if ([obj hasSuffix:@".txt"]) {
            NSString *logFile = [NSString stringWithFormat:@"%@/%@", zegologs, obj];
            [logFiles addObject:logFile];
        }
    }];
    
    // 压缩文件
    NSString *zipPath = [zegologs stringByAppendingPathComponent:@"/zegoavlog.zip"];
    BOOL zipSuccess = [SSZipArchive createZipFileAtPath:zipPath withFilesAtPaths:logFiles];
    
    if (zipSuccess) {
        NSData *data = [[NSData alloc] initWithContentsOfFile:zipPath];
        if (data) {
            return data;
        }
    } else {
        [self showAlert:NSLocalizedString(@"无法发送邮件", nil) message:NSLocalizedString(@"日志文件压缩失败", nil)];
    }
    
    return nil;
}


#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (indexPath.section == 1)
    {
        if (indexPath.row == 0) {
            [ZegoAudioRoomApi uploadLog];
            [self showUploadAlertView];
        } else {
            [self shareLogFile];
        }
    }
    else if (indexPath.section == [self.tableView numberOfSections] - 1)
    {
        SFSafariViewController *safariViewController = [[SFSafariViewController alloc] initWithURL:[NSURL URLWithString:@"https://www.zego.im"]];
        [self presentViewController:safariViewController animated:YES completion:nil];
    }
}

- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSInteger sectionCount = [self.tableView numberOfSections];
    if (sectionCount >= 2 && indexPath.section == sectionCount - 1)
        return YES;
    
    if (indexPath.section == 1 && (indexPath.row == 0 || indexPath.row == 1))
        return YES;
    return NO;
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
//    [self.view endEditing:YES];
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (textField.text.length != 0) {
        [textField resignFirstResponder];
        return YES;
    } else {
        [self showAlert:NSLocalizedString(@"请重新输入！", nil) message:NSLocalizedString(@"该字段不可为空", nil)];
        [textField becomeFirstResponder];
        return NO;
    }
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    if (textField == self.appSignText) {
        self.appSignText.placeholder = NSLocalizedString(@"请输入 AppSign", nil);
    }

    if (self.tapGesture == nil)
        self.tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapTableView:)];
    
    [self.tableView addGestureRecognizer:self.tapGesture];
}

#pragma mark - UIPickerViewDelegate, UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    if (pickerView == self.appTypePicker) {
        return [ZegoSettings sharedInstance].appTypeList.count;
    } else {
        return 0;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
    if (pickerView == self.appTypePicker) {
        if (row >= [ZegoSettings sharedInstance].appTypeList.count) {
            return ;
        }
        
        NSLog(@"%s: %@", __func__, [ZegoSettings sharedInstance].appTypeList[row]);
        
        [ZegoAudioLive setAppType:(ZegoAppType)row];
        [self loadAppID];
    }
    
    return;
}

//返回当前行的内容,此处是将数组中数值添加到滚动的那个显示栏上
- (NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    if (pickerView == self.appTypePicker) {
        if (row >= [ZegoSettings sharedInstance].appTypeList.count) {
            return @"ERROR";
        }
        
        return [[ZegoSettings sharedInstance].appTypeList objectAtIndex:row];
    }
    return nil;
}

#pragma mark - MFMailComposeViewControllerDelegate

- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error {
    switch (result) {
        case MFMailComposeResultCancelled:
            [controller dismissViewControllerAnimated:YES completion:nil];
            break;
        case MFMailComposeResultSaved:
            [controller dismissViewControllerAnimated:YES completion:nil];
            break;
        case MFMailComposeResultSent:
        {
            NSLog(@"日志邮件发送成功");
            
            // 弹框提示
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"日志邮件发送成功", nil)
                                                                           message:nil
                                                                    preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                [controller dismissViewControllerAnimated:YES completion:nil];
            }];
            
            [alert addAction:confirm];
            
            [controller presentViewController:alert animated:NO completion:nil];
            
        }
            break;
        case MFMailComposeResultFailed:
        {
            NSLog(@"日志邮件发送失败");
            // 弹框提示
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"日志邮件发送失败", nil)
                                                                           message:NSLocalizedString(@"请稍后重试", nil)
                                                                    preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *confirm = [UIAlertAction actionWithTitle:NSLocalizedString(@"确定", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                [controller dismissViewControllerAnimated:YES completion:nil];
            }];
            
            [alert addAction:confirm];
            
            [controller presentViewController:alert animated:NO completion:nil];
        }
            break;
    }
}


@end
