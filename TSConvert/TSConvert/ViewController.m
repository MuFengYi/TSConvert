//
//  ViewController.m
//  TSConvert
//
//  Created by hao ke on 2023/2/15.
//

#import "ViewController.h"
#import "TS2MP4/TsDemux.h"
#import "mp4mux.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    NSURL *tsFileURL = [NSURL URLWithString:[[NSBundle mainBundle] pathForResource:@"REC20230214-041329-2551" ofType:@"ts"]];
    
    
    [[TsDemux new] demux:[tsFileURL path] demuxState:^{
        NSURL *temporaryDirectoryURL = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%@/",[NSHomeDirectory() stringByAppendingString:[NSString stringWithFormat:@"/Documents/"]]]];


        assemble_elementary_streams((char *)[[[temporaryDirectoryURL path] stringByAppendingString:@"2.265"] UTF8String], (char *)[[[temporaryDirectoryURL path] stringByAppendingString:@"2.aac"] UTF8String], (char *)[[[temporaryDirectoryURL path] stringByAppendingString:@"haha.mp4"] UTF8String], 30);
    }];
}


@end
