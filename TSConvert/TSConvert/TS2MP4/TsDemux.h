//
//  TsDemux.h
//  MLQX
//
//  Created by hao ke on 2023/2/9.
//

#import <Foundation/Foundation.h>





typedef void(^DemuxSuccess)(void);
NS_ASSUME_NONNULL_BEGIN

@interface TsDemux : NSObject

- (void)demux:(NSString*)filePath demuxState:(DemuxSuccess)demuxSuccess;
@property (nonatomic,copy)DemuxSuccess  demuxSuccess;
@end

NS_ASSUME_NONNULL_END
