#import <React/RCTBridgeModule.h>

// RNGCDWebServer: https://github.com/swisspol/RNGCDWebServer
#import "RNGCDWebServer.h"

@interface FPStaticServer : NSObject <RCTBridgeModule> {
    RNGCDWebServer* _webServer;
}

    @property(nonatomic, retain) NSString *localPath;
    @property(nonatomic, retain) NSString *url;

    @property (nonatomic, retain) NSString* www_root;
    @property (nonatomic, retain) NSNumber* port;
    @property (assign) BOOL localhost_only;
    @property (assign) BOOL keep_alive;

@end
  
