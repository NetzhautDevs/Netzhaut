#ifndef NH_NETWORK_HTTP_H
#define NH_NETWORK_HTTP_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * netzhaut _ Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

#include "Socket.h"
#include "Common/Includes.h"

#include "../nh-core/Util/LinkedList.h"

#include <stdint.h>
#include <unistd.h>

#endif

/** @addtogroup NetworkEnums Enums
 *  \ingroup Network
 *  @{
 */

    typedef enum NH_NETWORK_HTTP_RESPONSE {
        NH_NETWORK_HTTP_RESPONSE_CONTINUE = 100,
        NH_NETWORK_HTTP_RESPONSE_SWITCHING_PROTOCOL = 101,
        NH_NETWORK_HTTP_RESPONSE_PROCESSING = 102,
        NH_NETWORK_HTTP_RESPONSE_EARLY_HINTS = 103,
        NH_NETWORK_HTTP_RESPONSE_OK = 200,
        NH_NETWORK_HTTP_RESPONSE_CREATED = 201,
        NH_NETWORK_HTTP_RESPONSE_ACCEPTED = 202,
        NH_NETWORK_HTTP_RESPONSE_NON_AUTHORITATIVE_INFORMATION = 203,
        NH_NETWORK_HTTP_RESPONSE_NO_CONTENT = 204,
        NH_NETWORK_HTTP_RESPONSE_RESET_CONTENT = 205,
        NH_NETWORK_HTTP_RESPONSE_PARTIAL_CONTENT = 206,
        NH_NETWORK_HTTP_RESPONSE_MULTI_STATUS = 207,
        NH_NETWORK_HTTP_RESPONSE_ALREADY_REPORTED = 208,
        NH_NETWORK_HTTP_RESPONSE_IM_USED = 226,
        NH_NETWORK_HTTP_RESPONSE_MULTIPLE_CHOICE = 300,
        NH_NETWORK_HTTP_RESPONSE_MOVED_PERMANENTLY = 301,
        NH_NETWORK_HTTP_RESPONSE_FOUND = 302,
        NH_NETWORK_HTTP_RESPONSE_SEE_OTHER = 303,
        NH_NETWORK_HTTP_RESPONSE_NOT_MODIFIED = 304,
        NH_NETWORK_HTTP_RESPONSE_USE_PROXY = 305,
        NH_NETWORK_HTTP_RESPONSE_UNUSED = 306,
        NH_NETWORK_HTTP_RESPONSE_TEMPORARY_REDIRECT = 307,
        NH_NETWORK_HTTP_RESPONSE_PERMANENT_REDIRECT = 308,
        NH_NETWORK_HTTP_RESPONSE_BAD_REQUEST = 400,
        NH_NETWORK_HTTP_RESPONSE_UNAUTHORIZED = 401,
        NH_NETWORK_HTTP_RESPONSE_PAYMENT_REQUIRED = 402,
        NH_NETWORK_HTTP_RESPONSE_FORBIDDEN = 403,
        NH_NETWORK_HTTP_RESPONSE_NOT_FOUND = 404,
        NH_NETWORK_HTTP_RESPONSE_METHOD_NOT_ALLOWED = 405,
        NH_NETWORK_HTTP_RESPONSE_NOT_ACCEPTABLE = 406,
        NH_NETWORK_HTTP_RESPONSE_PROXY_AUTHENTICATION_REQUIRED = 407,
        NH_NETWORK_HTTP_RESPONSE_REQUEST_TIMEOUT = 408,
        NH_NETWORK_HTTP_RESPONSE_CONFLICT = 409,
        NH_NETWORK_HTTP_RESPONSE_GONE = 410,
        NH_NETWORK_HTTP_RESPONSE_LENGTH_REQUIRED = 411,
        NH_NETWORK_HTTP_RESPONSE_PRECONDITION_FAILED = 412,
        NH_NETWORK_HTTP_RESPONSE_PAYLOAD_TOO_LARGE = 413,
        NH_NETWORK_HTTP_RESPONSE_URI_TOO_LONG = 414,
        NH_NETWORK_HTTP_RESPONSE_UNSUPPORTED_MEDIA_TYPE = 415,
        NH_NETWORK_HTTP_RESPONSE_RANGE_NOT_SATISFIABLE = 416,
        NH_NETWORK_HTTP_RESPONSE_EXPECTATION_FAILED = 417,
        NH_NETWORK_HTTP_RESPONSE_IM_A_TEAPOT = 418,
        NH_NETWORK_HTTP_RESPONSE_MISDIRECTED_REQUEST = 421,
        NH_NETWORK_HTTP_RESPONSE_UNPROCESSABLE_ENTITY = 422,
        NH_NETWORK_HTTP_RESPONSE_LOCKED = 423,
        NH_NETWORK_HTTP_RESPONSE_FAILED_DEPENDENCY = 424,
        NH_NETWORK_HTTP_RESPONSE_TOO_EARLY = 425,
        NH_NETWORK_HTTP_RESPONSE_UPGRADE_REQUIRED = 426,
        NH_NETWORK_HTTP_RESPONSE_PRECONDITION_REQUIRED = 428,
        NH_NETWORK_HTTP_RESPONSE_TOO_MANY_REQUESTS = 429,
        NH_NETWORK_HTTP_RESPONSE_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
        NH_NETWORK_HTTP_RESPONSE_UNAVAILABLE_FOR_LEGAL_REASONS = 451,
        NH_NETWORK_HTTP_RESPONSE_INTERNAL_SERVER_ERROR = 500,
        NH_NETWORK_HTTP_RESPONSE_NOT_IMPLEMENTED = 501,
        NH_NETWORK_HTTP_RESPONSE_BAD_GATEWAY = 502,
        NH_NETWORK_HTTP_RESPONSE_SERVICE_UNAVAILABLE = 503,
        NH_NETWORK_HTTP_RESPONSE_GATEWAY_TIMEOUT = 504,
        NH_NETWORK_HTTP_RESPONSE_HTTP_VERSION_NOT_SUPPORTED = 505,
        NH_NETWORK_HTTP_RESPONSE_VARIANT_ALSO_NEGOTIATES = 506,
        NH_NETWORK_HTTP_RESPONSE_INSUFFICIENT_STORAGE = 507,
        NH_NETWORK_HTTP_RESPONSE_LOOP_DETECTED = 508,
        NH_NETWORK_HTTP_RESPONSE_NOT_EXTENDED = 510,
        NH_NETWORK_HTTP_RESPONSE_NETWORK_AUTHENTICATION_REQUIRED = 511,
    } NH_NETWORK_HTTP_RESPONSE;    

    typedef enum NH_NETWORK_HTTP_REQUEST {
        NH_NETWORK_HTTP_REQUEST_GET = 0,    
        NH_NETWORK_HTTP_REQUEST_HEAD,    
        NH_NETWORK_HTTP_REQUEST_POST,    
        NH_NETWORK_HTTP_REQUEST_PUT,    
        NH_NETWORK_HTTP_REQUEST_DELETE,    
        NH_NETWORK_HTTP_REQUEST_CONNECT,    
        NH_NETWORK_HTTP_REQUEST_OPTIONS,    
        NH_NETWORK_HTTP_REQUEST_TRACE,    
        NH_NETWORK_HTTP_REQUEST_PATCH,    
    } NH_NETWORK_HTTP_REQUEST;

    typedef enum NH_NETWORK_HTTP_HEADER {
        NH_NETWORK_HTTP_HEADER_WWW_AUTHENTICATE = 0,
        NH_NETWORK_HTTP_HEADER_AUTHORIZATION,
        NH_NETWORK_HTTP_HEADER_PROXY_AUTHENTICATE,
        NH_NETWORK_HTTP_HEADER_PROXY_AUTHORIZATION,
        NH_NETWORK_HTTP_HEADER_AGE,
        NH_NETWORK_HTTP_HEADER_CACHE_CONTROL,
        NH_NETWORK_HTTP_HEADER_CLEAR_SITE_DATA,
        NH_NETWORK_HTTP_HEADER_EXPIRES,
        NH_NETWORK_HTTP_HEADER_PRAGMA,
        NH_NETWORK_HTTP_HEADER_WARNING,
        NH_NETWORK_HTTP_HEADER_ACCEPT_CH,
        NH_NETWORK_HTTP_HEADER_ACCEPT_CH_LIFETIME,
        NH_NETWORK_HTTP_HEADER_EARLY_DATA,
        NH_NETWORK_HTTP_HEADER_CONTENT_DPR,
        NH_NETWORK_HTTP_HEADER_DPR,
        NH_NETWORK_HTTP_HEADER_DEVICE_MEMORY,
        NH_NETWORK_HTTP_HEADER_SAVE_DATA,
        NH_NETWORK_HTTP_HEADER_VIEWPORT_WIDTH,
        NH_NETWORK_HTTP_HEADER_WIDTH,
        NH_NETWORK_HTTP_HEADER_LAST_MODIFIED,
        NH_NETWORK_HTTP_HEADER_ETAG,
        NH_NETWORK_HTTP_HEADER_IF_MATCH,
        NH_NETWORK_HTTP_HEADER_IF_NONE_MATCH,
        NH_NETWORK_HTTP_HEADER_IF_MODIFIED_SINCE,
        NH_NETWORK_HTTP_HEADER_IF_UNMODIFIED_SINCE,
        NH_NETWORK_HTTP_HEADER_VARY,
        NH_NETWORK_HTTP_HEADER_CONNECTION,
        NH_NETWORK_HTTP_HEADER_KEEP_ALIVE,
        NH_NETWORK_HTTP_HEADER_ACCEPT,
        NH_NETWORK_HTTP_HEADER_ACCEPT_CHARSET,
        NH_NETWORK_HTTP_HEADER_ACCEPT_ENCODING,
        NH_NETWORK_HTTP_HEADER_ACCEPT_LANGUAGE,
        NH_NETWORK_HTTP_HEADER_EXPECT,
        NH_NETWORK_HTTP_HEADER_MAX_FORWARDS,
        NH_NETWORK_HTTP_HEADER_COOKIE,
        NH_NETWORK_HTTP_HEADER_SET_COOKIE,
        NH_NETWORK_HTTP_HEADER_COOKIE2,
        NH_NETWORK_HTTP_HEADER_SET_COOKIE2,
        NH_NETWORK_HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN,
        NH_NETWORK_HTTP_HEADER_ACCESS_CONTROL_ALLOW_CREDENTIALS,
        NH_NETWORK_HTTP_HEADER_ACCESS_CONTROL_ALLOW_HEADERS,
        NH_NETWORK_HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS,
        NH_NETWORK_HTTP_HEADER_ACCESS_CONTROL_EXPOSE_HEADERS,
        NH_NETWORK_HTTP_HEADER_ACCESS_CONTROL_MAX_AGE,
        NH_NETWORK_HTTP_HEADER_ACCESS_CONTROL_REQUEST_HEADERS,
        NH_NETWORK_HTTP_HEADER_ACCESS_CONTROL_REQUEST_METHOD,
        NH_NETWORK_HTTP_HEADER_ORIGIN,
        NH_NETWORK_HTTP_HEADER_TIMING_ALLOW_ORIGIN,
        NH_NETWORK_HTTP_HEADER_DNT,
        NH_NETWORK_HTTP_HEADER_TK,
        NH_NETWORK_HTTP_HEADER_CONTENT_DISPOSITION,
        NH_NETWORK_HTTP_HEADER_CONTENT_LENGTH,
        NH_NETWORK_HTTP_HEADER_CONTENT_TYPE,
        NH_NETWORK_HTTP_HEADER_CONTENT_ENCODING,
        NH_NETWORK_HTTP_HEADER_CONTENT_LANGUAGE,
        NH_NETWORK_HTTP_HEADER_CONTENT_LOCATION,
        NH_NETWORK_HTTP_HEADER_FORWARDED,
        NH_NETWORK_HTTP_HEADER_X_FORWARDED_FOR,
        NH_NETWORK_HTTP_HEADER_X_FORWARDED_HOST,
        NH_NETWORK_HTTP_HEADER_X_FORWARDED_PROTO,
        NH_NETWORK_HTTP_HEADER_VIA,
        NH_NETWORK_HTTP_HEADER_LOCATION,
        NH_NETWORK_HTTP_HEADER_FROM,
        NH_NETWORK_HTTP_HEADER_HOST,
        NH_NETWORK_HTTP_HEADER_REFERER,
        NH_NETWORK_HTTP_HEADER_REFERRER_POLICY,
        NH_NETWORK_HTTP_HEADER_USER_AGENT,
        NH_NETWORK_HTTP_HEADER_ALLOW,
        NH_NETWORK_HTTP_HEADER_SERVER,
        NH_NETWORK_HTTP_HEADER_ACCEPT_RANGES,
        NH_NETWORK_HTTP_HEADER_RANGE,
        NH_NETWORK_HTTP_HEADER_IF_RANGE,
        NH_NETWORK_HTTP_HEADER_CONTENT_RANGE,
        NH_NETWORK_HTTP_HEADER_CROSS_ORIGIN_EMBEDDER_POLICY,
        NH_NETWORK_HTTP_HEADER_CROSS_ORIGIN_OPENER_POLICY,
        NH_NETWORK_HTTP_HEADER_CROSS_ORIGIN_RESOURCE_POLICY,
        NH_NETWORK_HTTP_HEADER_CONTENT_SECURITY_POLICY,
        NH_NETWORK_HTTP_HEADER_CONTENT_SECURITY_POLICY_REPORT_ONLY,
        NH_NETWORK_HTTP_HEADER_EXPECT_CT,
        NH_NETWORK_HTTP_HEADER_FEATURE_POLICY,
        NH_NETWORK_HTTP_HEADER_STRICT_TRANSPORT_SECURITY,
        NH_NETWORK_HTTP_HEADER_UPGRADE_INSECURE_REQUESTS,
        NH_NETWORK_HTTP_HEADER_X_CONTENT_TYPE_OPTIONS,
        NH_NETWORK_HTTP_HEADER_X_DOWNLOAD_OPTIONS,
        NH_NETWORK_HTTP_HEADER_X_FRAME_OPTIONS,
        NH_NETWORK_HTTP_HEADER_X_PERMITTED_CROSS_DOMAIN_POLICIES,
        NH_NETWORK_HTTP_HEADER_X_POWERED_BY,
        NH_NETWORK_HTTP_HEADER_X_XSS_PROTECTION,
        NH_NETWORK_HTTP_HEADER_PUBLIC_KEY_PINS,
        NH_NETWORK_HTTP_HEADER_PUBLIC_KEY_PINS_REPORT_ONLY,
        NH_NETWORK_HTTP_HEADER_SEC_FETCH_SITE,
        NH_NETWORK_HTTP_HEADER_SEC_FETCH_MODE,
        NH_NETWORK_HTTP_HEADER_SEC_FETCH_USER,
        NH_NETWORK_HTTP_HEADER_SEC_FETCH_DEST,
        NH_NETWORK_HTTP_HEADER_LAST_EVENT_ID,
        NH_NETWORK_HTTP_HEADER_NEL,
        NH_NETWORK_HTTP_HEADER_PING_FROM,
        NH_NETWORK_HTTP_HEADER_PING_TO,
        NH_NETWORK_HTTP_HEADER_REPORT_TO,
        NH_NETWORK_HTTP_HEADER_TRANSFER_ENCODING,
        NH_NETWORK_HTTP_HEADER_TE,
        NH_NETWORK_HTTP_HEADER_TRAILER,
        NH_NETWORK_HTTP_HEADER_SEC_WEBSOCKET_KEY,
        NH_NETWORK_HTTP_HEADER_SEC_WEBSOCKET_EXTENSIONS,
        NH_NETWORK_HTTP_HEADER_SEC_WEBSOCKET_ACCEPT,
        NH_NETWORK_HTTP_HEADER_SEC_WEBSOCKET_PROTOCOL,
        NH_NETWORK_HTTP_HEADER_SEC_WEBSOCKET_VERSION,
        NH_NETWORK_HTTP_HEADER_ACCEPT_PUSH_POLICY,
        NH_NETWORK_HTTP_HEADER_ACCEPT_SIGNATURE,
        NH_NETWORK_HTTP_HEADER_ALT_SVC,
        NH_NETWORK_HTTP_HEADER_DATE,
        NH_NETWORK_HTTP_HEADER_LARGE_ALLOCATION,
        NH_NETWORK_HTTP_HEADER_LINK,
        NH_NETWORK_HTTP_HEADER_PUSH_POLICY,
        NH_NETWORK_HTTP_HEADER_RETRY_AFTER,
        NH_NETWORK_HTTP_HEADER_SIGNATURE,
        NH_NETWORK_HTTP_HEADER_SIGNED_HEADERS,
        NH_NETWORK_HTTP_HEADER_SERVER_TIMING,
        NH_NETWORK_HTTP_HEADER_SERVICE_WORKER_ALLOWED,
        NH_NETWORK_HTTP_HEADER_SOURCEMAP,
        NH_NETWORK_HTTP_HEADER_UPGRADE,
        NH_NETWORK_HTTP_HEADER_X_DNS_PREFETCH_CONTROL,
        NH_NETWORK_HTTP_HEADER_X_FIREFOX_SPDY,
        NH_NETWORK_HTTP_HEADER_X_PINGBACK,
        NH_NETWORK_HTTP_HEADER_X_REQUESTED_WITH,
        NH_NETWORK_HTTP_HEADER_X_ROBOTS_TAG,
        NH_NETWORK_HTTP_HEADER_X_UA_COMPATIBLE,
    } NH_NETWORK_HTTP_HEADER;

/** @} */

/** @addtogroup NetworkStructs Structs
 *  \ingroup Network
 *  @{
 */

    typedef struct nh_network_HTTPPayload {
        char *header_p;
        char *body_p;
    } nh_network_HTTPPayload;   

    typedef struct nh_network_HTTPRequest {
        NH_NETWORK_HTTP_REQUEST type;
        nh_LinkedList Headers; 
    } nh_network_HTTPRequest;

/** @} */

/** @addtogroup NetworkFunctions Functions
 *  \ingroup Network
 *  @{
 */

    nh_network_HTTPRequest nh_network_initHTTPRequest(
        NH_NETWORK_HTTP_REQUEST type
    );

    NH_API_RESULT nh_network_appendHTTPHeader(
        nh_network_HTTPRequest *Request_p, NH_NETWORK_HTTP_HEADER type, char *value_p
    );

    NH_API_RESULT nh_network_getHTTPHeaderValue(
        char *response_p, char *set_p, NH_NETWORK_HTTP_HEADER type
    );

    NH_NETWORK_HTTP_RESPONSE nh_network_getHTTPResponseCode(
        char *response_p
    );

    NH_API_RESULT nh_network_sendDataRequestViaHTTP(
        nh_network_ClientSocket *Socket_p, char *host_p, char *path_p, bool secure
    );

    nh_network_HTTPPayload nh_network_convertToHTTPPayload(
        void *data_p
    );

/** @} */

#endif 
