// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from bitcoin_like_wallet.djinni

#import "RCTCoreLGBitcoinLikeOperation.h"


@implementation RCTCoreLGBitcoinLikeOperation
//Export module
RCT_EXPORT_MODULE(RCTCoreLGBitcoinLikeOperation)

@synthesize bridge = _bridge;

-(instancetype)init
{
    self = [super init];
    //Init Objc implementation
    if(self)
    {
        self.objcImplementations = [[NSMutableDictionary alloc] init];
    }
    return self;
}

+ (BOOL)requiresMainQueueSetup
{
    return NO;
}
RCT_REMAP_METHOD(release, release:(NSDictionary *)currentInstance withResolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject)
{
    if (!currentInstance[@"uid"] || !currentInstance[@"type"])
    {
        reject(@"impl_call_error", @"Error while calling RCTCoreLGBitcoinLikeOperation::release, first argument should be an instance of LGBitcoinLikeOperation", nil);
    }
    [self.objcImplementations removeObjectForKey:currentInstance[@"uid"]];
    resolve(@(YES));
}
RCT_REMAP_METHOD(log, logWithResolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject)
{
    NSMutableArray *uuids = [[NSMutableArray alloc] init];
    for (id key in self.objcImplementations)
    {
        [uuids addObject:key];
    }
    NSDictionary *result = @{@"value" : uuids};
    resolve(result);
}
RCT_REMAP_METHOD(flush, flushWithResolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject)
{
    [self.objcImplementations removeAllObjects];
    resolve(@(YES));
}

/**
 *Get operation's transaction
 *@return BitcoinLikeTransaction object
 */
RCT_REMAP_METHOD(getTransaction,getTransaction:(NSDictionary *)currentInstance WithResolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject) {
    if (!currentInstance[@"uid"] || !currentInstance[@"type"])
    {
        reject(@"impl_call_error", @"Error while calling RCTCoreLGBitcoinLikeOperation::getTransaction, first argument should be an instance of LGBitcoinLikeOperation", nil);
    }
    LGBitcoinLikeOperation *currentInstanceObj = [self.objcImplementations objectForKey:currentInstance[@"uid"]];
    if (!currentInstanceObj)
    {
        NSString *error = [NSString stringWithFormat:@"Error while calling LGBitcoinLikeOperation::getTransaction, instance of uid %@ not found", currentInstance[@"uid"]];
        reject(@"impl_call_error", error, nil);
    }
    LGBitcoinLikeTransaction * objcResult = [currentInstanceObj getTransaction];

    NSString *uuid = [[NSUUID UUID] UUIDString];
    RCTCoreLGBitcoinLikeTransaction *rctImpl_objcResult = (RCTCoreLGBitcoinLikeTransaction *)[self.bridge moduleForName:@"CoreLGBitcoinLikeTransaction"];
    [rctImpl_objcResult.objcImplementations setObject:objcResult forKey:uuid];
    NSDictionary *result = @{@"type" : @"CoreLGBitcoinLikeTransaction", @"uid" : uuid };

    if(result)
    {
        resolve(result);
    }
    else
    {
        reject(@"impl_call_error", @"Error while calling LGBitcoinLikeOperation::getTransaction", nil);
    }

}
@end