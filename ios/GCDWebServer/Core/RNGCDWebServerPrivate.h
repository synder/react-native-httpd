/*
 Copyright (c) 2012-2015, Pierre-Olivier Latour
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * The name of Pierre-Olivier Latour may not be used to endorse
 or promote products derived from this software without specific
 prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL PIERRE-OLIVIER LATOUR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <os/object.h>
#import <sys/socket.h>

/**
 *  All RNGCDWebServer headers.
 */

#import "RNGCDWebServerHTTPStatusCodes.h"
#import "RNGCDWebServerFunctions.h"

#import "RNGCDWebServer.h"
#import "RNGCDWebServerConnection.h"

#import "RNGCDWebServerDataRequest.h"
#import "RNGCDWebServerFileRequest.h"
#import "RNGCDWebServerMultiPartFormRequest.h"
#import "RNGCDWebServerURLEncodedFormRequest.h"

#import "RNGCDWebServerDataResponse.h"
#import "RNGCDWebServerErrorResponse.h"
#import "RNGCDWebServerFileResponse.h"
#import "RNGCDWebServerStreamedResponse.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  Check if a custom logging facility should be used instead.
 */

#if defined(__RNGCDWebSERVER_LOGGING_HEADER__)

#define __RNGCDWebSERVER_LOGGING_FACILITY_CUSTOM__

#import __RNGCDWebSERVER_LOGGING_HEADER__

/**
 *  Automatically detect if XLFacility is available and if so use it as a
 *  logging facility.
 */

#elif defined(__has_include) && __has_include("XLFacilityMacros.h")

#define __RNGCDWebSERVER_LOGGING_FACILITY_XLFACILITY__

#undef XLOG_TAG
#define XLOG_TAG @"RNGCDWebserver.internal"

#import "XLFacilityMacros.h"

#define GWS_LOG_DEBUG(...) XLOG_DEBUG(__VA_ARGS__)
#define GWS_LOG_VERBOSE(...) XLOG_VERBOSE(__VA_ARGS__)
#define GWS_LOG_INFO(...) XLOG_INFO(__VA_ARGS__)
#define GWS_LOG_WARNING(...) XLOG_WARNING(__VA_ARGS__)
#define GWS_LOG_ERROR(...) XLOG_ERROR(__VA_ARGS__)

#define GWS_DCHECK(__CONDITION__) XLOG_DEBUG_CHECK(__CONDITION__)
#define GWS_DNOT_REACHED() XLOG_DEBUG_UNREACHABLE()

/**
 *  If all of the above fail, then use RNGCDWebServer built-in
 *  logging facility.
 */

#else

#define __RNGCDWebSERVER_LOGGING_FACILITY_BUILTIN__

typedef NS_ENUM(int, RNGCDWebServerLoggingLevel) {
  kRNGCDWebServerLoggingLevel_Debug = 0,
  kRNGCDWebServerLoggingLevel_Verbose,
  kRNGCDWebServerLoggingLevel_Info,
  kRNGCDWebServerLoggingLevel_Warning,
  kRNGCDWebServerLoggingLevel_Error
};

extern RNGCDWebServerLoggingLevel RNGCDWebServerLogLevel;
extern void RNGCDWebServerLogMessage(RNGCDWebServerLoggingLevel level, NSString* format, ...) NS_FORMAT_FUNCTION(2, 3);

#if DEBUG
#define GWS_LOG_DEBUG(...)                                                                                                             \
  do {                                                                                                                                 \
    if (RNGCDWebServerLogLevel <= kRNGCDWebServerLoggingLevel_Debug) RNGCDWebServerLogMessage(kRNGCDWebServerLoggingLevel_Debug, __VA_ARGS__); \
  } while (0)
#else
#define GWS_LOG_DEBUG(...)
#endif
#define GWS_LOG_VERBOSE(...)                                                                                                               \
  do {                                                                                                                                     \
    if (RNGCDWebServerLogLevel <= kRNGCDWebServerLoggingLevel_Verbose) RNGCDWebServerLogMessage(kRNGCDWebServerLoggingLevel_Verbose, __VA_ARGS__); \
  } while (0)
#define GWS_LOG_INFO(...)                                                                                                            \
  do {                                                                                                                               \
    if (RNGCDWebServerLogLevel <= kRNGCDWebServerLoggingLevel_Info) RNGCDWebServerLogMessage(kRNGCDWebServerLoggingLevel_Info, __VA_ARGS__); \
  } while (0)
#define GWS_LOG_WARNING(...)                                                                                                               \
  do {                                                                                                                                     \
    if (RNGCDWebServerLogLevel <= kRNGCDWebServerLoggingLevel_Warning) RNGCDWebServerLogMessage(kRNGCDWebServerLoggingLevel_Warning, __VA_ARGS__); \
  } while (0)
#define GWS_LOG_ERROR(...)                                                                                                             \
  do {                                                                                                                                 \
    if (RNGCDWebServerLogLevel <= kRNGCDWebServerLoggingLevel_Error) RNGCDWebServerLogMessage(kRNGCDWebServerLoggingLevel_Error, __VA_ARGS__); \
  } while (0)

#endif

/**
 *  Consistency check macros used when building Debug only.
 */

#if !defined(GWS_DCHECK) || !defined(GWS_DNOT_REACHED)

#if DEBUG

#define GWS_DCHECK(__CONDITION__) \
  do {                            \
    if (!(__CONDITION__)) {       \
      abort();                    \
    }                             \
  } while (0)
#define GWS_DNOT_REACHED() abort()

#else

#define GWS_DCHECK(__CONDITION__)
#define GWS_DNOT_REACHED()

#endif

#endif

/**
 *  RNGCDWebServer internal constants and APIs.
 */

#define kRNGCDWebServerDefaultMimeType @"application/octet-stream"
#define kRNGCDWebServerErrorDomain @"RNGCDWebServerErrorDomain"

static inline BOOL RNGCDWebServerIsValidByteRange(NSRange range) {
  return ((range.location != NSUIntegerMax) || (range.length > 0));
}

static inline NSError* RNGCDWebServerMakePosixError(int code) {
  return [NSError errorWithDomain:NSPOSIXErrorDomain code:code userInfo:@{NSLocalizedDescriptionKey : (NSString*)[NSString stringWithUTF8String:strerror(code)]}];
}

extern void RNGCDWebServerInitializeFunctions();
extern NSString* _Nullable RNGCDWebServerNormalizeHeaderValue(NSString* _Nullable value);
extern NSString* _Nullable RNGCDWebServerTruncateHeaderValue(NSString* _Nullable value);
extern NSString* _Nullable RNGCDWebServerExtractHeaderValueParameter(NSString* _Nullable value, NSString* attribute);
extern NSStringEncoding RNGCDWebServerStringEncodingFromCharset(NSString* charset);
extern BOOL RNGCDWebServerIsTextContentType(NSString* type);
extern NSString* RNGCDWebServerDescribeData(NSData* data, NSString* contentType);
extern NSString* RNGCDWebServerComputeMD5Digest(NSString* format, ...) NS_FORMAT_FUNCTION(1, 2);
extern NSString* RNGCDWebServerStringFromSockAddr(const struct sockaddr* addr, BOOL includeService);

@interface RNGCDWebServerConnection ()
- (instancetype)initWithServer:(RNGCDWebServer*)server localAddress:(NSData*)localAddress remoteAddress:(NSData*)remoteAddress socket:(CFSocketNativeHandle)socket;
@end

@interface RNGCDWebServer ()
@property(nonatomic, readonly) NSMutableArray* handlers;
@property(nonatomic, readonly, nullable) NSString* serverName;
@property(nonatomic, readonly, nullable) NSString* authenticationRealm;
@property(nonatomic, readonly, nullable) NSMutableDictionary* authenticationBasicAccounts;
@property(nonatomic, readonly, nullable) NSMutableDictionary* authenticationDigestAccounts;
@property(nonatomic, readonly) BOOL shouldAutomaticallyMapHEADToGET;
@property(nonatomic, readonly) dispatch_queue_priority_t dispatchQueuePriority;
- (void)willStartConnection:(RNGCDWebServerConnection*)connection;
- (void)didEndConnection:(RNGCDWebServerConnection*)connection;
@end

@interface RNGCDWebServerHandler : NSObject
@property(nonatomic, readonly) RNGCDWebServerMatchBlock matchBlock;
@property(nonatomic, readonly) RNGCDWebServerAsyncProcessBlock asyncProcessBlock;
@end

@interface RNGCDWebServerRequest ()
@property(nonatomic, readonly) BOOL usesChunkedTransferEncoding;
@property(nonatomic) NSData* localAddressData;
@property(nonatomic) NSData* remoteAddressData;
- (void)prepareForWriting;
- (BOOL)performOpen:(NSError**)error;
- (BOOL)performWriteData:(NSData*)data error:(NSError**)error;
- (BOOL)performClose:(NSError**)error;
- (void)setAttribute:(nullable id)attribute forKey:(NSString*)key;
@end

@interface RNGCDWebServerResponse ()
@property(nonatomic, readonly) NSDictionary* additionalHeaders;
@property(nonatomic, readonly) BOOL usesChunkedTransferEncoding;
- (void)prepareForReading;
- (BOOL)performOpen:(NSError**)error;
- (void)performReadDataWithCompletion:(RNGCDWebServerBodyReaderCompletionBlock)block;
- (void)performClose;
@end

NS_ASSUME_NONNULL_END
