//
//  TsDemux.m
//  MLQX
//
//  Created by hao ke on 2023/2/9.
//

#import "TsDemux.h"













#import "m2tsextractor.h"









#include <fstream>
#include <iostream>

















@implementation TsDemux













- (void)demux:(NSString*)filePath demuxState:(nonnull DemuxSuccess)demuxSuccess{
    NSURL *temporaryDirectoryURL = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%@/",[NSHomeDirectory() stringByAppendingString:[NSString stringWithFormat:@"/Documents"]]]];
    const char    *inputFileName    =   [filePath cStringUsingEncoding:[NSString defaultCStringEncoding]];
    
    std::ifstream i(inputFileName, std::ios::binary);
    const char    *audioFileName    =   [[[temporaryDirectoryURL path] stringByAppendingString:@"/2.aac"] cStringUsingEncoding:[NSString defaultCStringEncoding]];
    
    std::ofstream a(audioFileName, std::ios::binary);
    const char    *videoFileName    =   [[[temporaryDirectoryURL path] stringByAppendingString:@"/2.265"] cStringUsingEncoding:[NSString defaultCStringEncoding]];
    
    std::ofstream v(videoFileName, std::ios::binary);
    const auto& result = m2tsext::extractVideoAudioFromM2TSSstream(i, v, a);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        demuxSuccess();
        
      
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    
    });
}










































@end
