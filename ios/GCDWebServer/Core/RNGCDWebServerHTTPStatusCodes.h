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

// http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
// http://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml

#import <Foundation/Foundation.h>

/**
 *  Convenience constants for "informational" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, RNGCDWebServerInformationalHTTPStatusCode) {
  kRNGCDWebServerHTTPStatusCode_Continue = 100,
  kRNGCDWebServerHTTPStatusCode_SwitchingProtocols = 101,
  kRNGCDWebServerHTTPStatusCode_Processing = 102
};

/**
 *  Convenience constants for "successful" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, RNGCDWebServerSuccessfulHTTPStatusCode) {
  kRNGCDWebServerHTTPStatusCode_OK = 200,
  kRNGCDWebServerHTTPStatusCode_Created = 201,
  kRNGCDWebServerHTTPStatusCode_Accepted = 202,
  kRNGCDWebServerHTTPStatusCode_NonAuthoritativeInformation = 203,
  kRNGCDWebServerHTTPStatusCode_NoContent = 204,
  kRNGCDWebServerHTTPStatusCode_ResetContent = 205,
  kRNGCDWebServerHTTPStatusCode_PartialContent = 206,
  kRNGCDWebServerHTTPStatusCode_MultiStatus = 207,
  kRNGCDWebServerHTTPStatusCode_AlreadyReported = 208
};

/**
 *  Convenience constants for "redirection" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, RNGCDWebServerRedirectionHTTPStatusCode) {
  kRNGCDWebServerHTTPStatusCode_MultipleChoices = 300,
  kRNGCDWebServerHTTPStatusCode_MovedPermanently = 301,
  kRNGCDWebServerHTTPStatusCode_Found = 302,
  kRNGCDWebServerHTTPStatusCode_SeeOther = 303,
  kRNGCDWebServerHTTPStatusCode_NotModified = 304,
  kRNGCDWebServerHTTPStatusCode_UseProxy = 305,
  kRNGCDWebServerHTTPStatusCode_TemporaryRedirect = 307,
  kRNGCDWebServerHTTPStatusCode_PermanentRedirect = 308
};

/**
 *  Convenience constants for "client error" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, RNGCDWebServerClientErrorHTTPStatusCode) {
  kRNGCDWebServerHTTPStatusCode_BadRequest = 400,
  kRNGCDWebServerHTTPStatusCode_Unauthorized = 401,
  kRNGCDWebServerHTTPStatusCode_PaymentRequired = 402,
  kRNGCDWebServerHTTPStatusCode_Forbidden = 403,
  kRNGCDWebServerHTTPStatusCode_NotFound = 404,
  kRNGCDWebServerHTTPStatusCode_MethodNotAllowed = 405,
  kRNGCDWebServerHTTPStatusCode_NotAcceptable = 406,
  kRNGCDWebServerHTTPStatusCode_ProxyAuthenticationRequired = 407,
  kRNGCDWebServerHTTPStatusCode_RequestTimeout = 408,
  kRNGCDWebServerHTTPStatusCode_Conflict = 409,
  kRNGCDWebServerHTTPStatusCode_Gone = 410,
  kRNGCDWebServerHTTPStatusCode_LengthRequired = 411,
  kRNGCDWebServerHTTPStatusCode_PreconditionFailed = 412,
  kRNGCDWebServerHTTPStatusCode_RequestEntityTooLarge = 413,
  kRNGCDWebServerHTTPStatusCode_RequestURITooLong = 414,
  kRNGCDWebServerHTTPStatusCode_UnsupportedMediaType = 415,
  kRNGCDWebServerHTTPStatusCode_RequestedRangeNotSatisfiable = 416,
  kRNGCDWebServerHTTPStatusCode_ExpectationFailed = 417,
  kRNGCDWebServerHTTPStatusCode_UnprocessableEntity = 422,
  kRNGCDWebServerHTTPStatusCode_Locked = 423,
  kRNGCDWebServerHTTPStatusCode_FailedDependency = 424,
  kRNGCDWebServerHTTPStatusCode_UpgradeRequired = 426,
  kRNGCDWebServerHTTPStatusCode_PreconditionRequired = 428,
  kRNGCDWebServerHTTPStatusCode_TooManyRequests = 429,
  kRNGCDWebServerHTTPStatusCode_RequestHeaderFieldsTooLarge = 431
};

/**
 *  Convenience constants for "server error" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, RNGCDWebServerServerErrorHTTPStatusCode) {
  kRNGCDWebServerHTTPStatusCode_InternalServerError = 500,
  kRNGCDWebServerHTTPStatusCode_NotImplemented = 501,
  kRNGCDWebServerHTTPStatusCode_BadGateway = 502,
  kRNGCDWebServerHTTPStatusCode_ServiceUnavailable = 503,
  kRNGCDWebServerHTTPStatusCode_GatewayTimeout = 504,
  kRNGCDWebServerHTTPStatusCode_HTTPVersionNotSupported = 505,
  kRNGCDWebServerHTTPStatusCode_InsufficientStorage = 507,
  kRNGCDWebServerHTTPStatusCode_LoopDetected = 508,
  kRNGCDWebServerHTTPStatusCode_NotExtended = 510,
  kRNGCDWebServerHTTPStatusCode_NetworkAuthenticationRequired = 511
};
