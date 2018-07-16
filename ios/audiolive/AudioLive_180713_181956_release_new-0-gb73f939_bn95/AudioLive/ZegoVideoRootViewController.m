//
//  ZegoVideoRootViewController.m
//  AudioLive
//
//  Created by Strong on 2017/2/14.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import "ZegoVideoRootViewController.h"
#import "ZegoAudioLiveViewController.h"
#import "ZegoSettings.h"

#define enabledColor [UIColor colorWithRed:12/255.0 green:112/255.0 blue:255/255.0 alpha:0.8]
#define disabledColor [UIColor lightGrayColor]

@interface ZegoVideoRootViewController ()
@property (weak, nonatomic) IBOutlet UIButton *videoTalkButton;
@property (weak, nonatomic) IBOutlet UITextField *roomIdText;

@property (nonatomic, strong) UITapGestureRecognizer *tapGesture;

@end

@implementation ZegoVideoRootViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.videoTalkButton.layer.cornerRadius = 6.0;
    self.roomIdText.clearButtonMode = UITextFieldViewModeAlways;
    [self enableVideoTalk:NO];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(textFieldTextDidChange) name:UITextFieldTextDidChangeNotification object:self.roomIdText];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    NSString *title = [NSString stringWithFormat:@"AudioLive(%@)", [ZegoSettings sharedInstance].appTypeList[[ZegoAudioLive appType]]];
    self.navigationItem.title = NSLocalizedString(title, nil);
    
    // 兼容 11.2 的 Bug, 参考：https://stackoverflow.com/questions/47754472/ios-uinavigationbar-button-remains-faded-after-segue-back
    [self.navigationItem.rightBarButtonItem setEnabled:NO];
    [self.navigationItem.rightBarButtonItem setEnabled:YES];
}

- (void)enableVideoTalk:(BOOL)enable {
    if (enable) {
        self.videoTalkButton.enabled = YES;
        [self.videoTalkButton setBackgroundColor: enabledColor];
    } else {
        self.videoTalkButton.enabled = NO;
        [self.videoTalkButton setBackgroundColor: disabledColor];
    }
}

- (void)textFieldTextDidChange
{
    if(self.roomIdText.text.length > 0 ) {
        [self enableVideoTalk:YES];
    } else {
        [self enableVideoTalk:NO];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)onTapTableView:(UIGestureRecognizer *)gesture
{
    [self.view endEditing:YES];
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    if (self.tapGesture == nil)
        self.tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapTableView:)];
    
    [self.view addGestureRecognizer:self.tapGesture];
}


- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    if (text.length == 0) {
        [self enableVideoTalk:NO];
    } else {
        [self enableVideoTalk:YES];
    }

    if ([text isEqualToString:@"\n"])
    {
        [textView resignFirstResponder];
        return NO;
    }
    
    return YES;
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
    if ([segue.identifier isEqualToString:@"presentVideoTalk"])
    {
        NSCharacterSet *set = [NSCharacterSet whitespaceAndNewlineCharacterSet];
        NSString *isString = [self.roomIdText.text stringByTrimmingCharactersInSet:set];
        if (isString.length == 0) {
            [self showAlert:@"提示" message:@"房间 ID 不可为空格，请重新输入！"];
            return;
        }

        ZegoAudioLiveViewController *viewController = (ZegoAudioLiveViewController *)segue.destinationViewController;
        viewController.roomID = self.roomIdText.text;
    }
}
- (void)showAlert:(NSString *)title message:(NSString *)message {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title
                                                                             message:message
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定"
                                                      style:UIAlertActionStyleDefault
                                                    handler:^(UIAlertAction * _Nonnull action) {
                                                        
                                                    }];
    
    [alertController addAction:confirm];
    [self presentViewController:alertController animated:YES completion:nil];
}



@end
