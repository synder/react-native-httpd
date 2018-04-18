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

#import "RNGCDWebServerRequest.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  The RNGCDWebServerMultiPart class is an abstract class that wraps the content
 *  of a part.
 */
@interface RNGCDWebServerMultiPart : NSObject

/**
 *  Returns the control name retrieved from the part headers.
 */
@property(nonatomic, readonly) NSString* controlName;

/**
 *  Returns the content type retrieved from the part headers or "text/plain"
 *  if not available (per HTTP specifications).
 */
@property(nonatomic, readonly) NSString* contentType;

/**
 *  Returns the MIME type component of the content type for the part.
 */
@property(nonatomic, readonly) NSString* mimeType;

@end

/**
 *  The RNGCDWebServerMultiPartArgument subclass of RNGCDWebServerMultiPart wraps
 *  the content of a part as data in memory.
 */
@interface RNGCDWebServerMultiPartArgument : RNGCDWebServerMultiPart

/**
 *  Returns the data for the part.
 */
@property(nonatomic, readonly) NSData* data;

/**
 *  Returns the data for the part interpreted as text. If the content
 *  type of the part is not a text one, or if an error occurs, nil is returned.
 *
 *  The text encoding used to interpret the data is extracted from the
 *  "Content-Type" header or defaults to UTF-8.
 */
@property(nonatomic, readonly, nullable) NSString* string;

@end

/**
 *  The RNGCDWebServerMultiPartFile subclass of RNGCDWebServerMultiPart wraps
 *  the content of a part as a file on disk.
 */
@interface RNGCDWebServerMultiPartFile : RNGCDWebServerMultiPart

/**
 *  Returns the file name retrieved from the part headers.
 */
@property(nonatomic, readonly) NSString* fileName;

/**
 *  Returns the path to the temporary file containing the part data.
 *
 *  @warning This temporary file will be automatically deleted when the
 *  RNGCDWebServerMultiPartFile is deallocated. If you want to preserve this file,
 *  you must move it to a different location beforehand.
 */
@property(nonatomic, readonly) NSString* temporaryPath;

@end

/**
 *  The RNGCDWebServerMultiPartFormRequest subclass of RNGCDWebServerRequest
 *  parses the body of the HTTP request as a multipart encoded form.
 */
@interface RNGCDWebServerMultiPartFormRequest : RNGCDWebServerRequest

/**
 *  Returns the argument parts from the multipart encoded form as
 *  name / RNGCDWebServerMultiPartArgument pairs.
 */
@property(nonatomic, readonly) NSArray* arguments;

/**
 *  Returns the files parts from the multipart encoded form as
 *  name / RNGCDWebServerMultiPartFile pairs.
 */
@property(nonatomic, readonly) NSArray* files;

/**
 *  Returns the MIME type for multipart encoded forms
 *  i.e. "multipart/form-data".
 */
+ (NSString*)mimeType;

/**
 *  Returns the first argument for a given control name or nil if not found.
 */
- (nullable RNGCDWebServerMultiPartArgument*)firstArgumentForControlName:(NSString*)name;

/**
 *  Returns the first file for a given control name or nil if not found.
 */
- (nullable RNGCDWebServerMultiPartFile*)firstFileForControlName:(NSString*)name;

@end

NS_ASSUME_NONNULL_END
