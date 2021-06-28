/* WARNING! All changes made to this file will be lost! */

#ifndef W_INCLUDE_CSP_CSP_AUTOCONFIG_H_WAF
#define W_INCLUDE_CSP_CSP_AUTOCONFIG_H_WAF

#define GIT_REV "unknown"
#define CSP_FREERTOS 1
/* #undef CSP_POSIX */
/* #undef CSP_WINDOWS */
/* #undef CSP_MACOSX */
/* #undef CSP_DEBUG */
/* #undef CSP_USE_RDP */
#define CSP_USE_CRC32 1
/* #undef CSP_USE_HMAC */
/* #undef CSP_USE_XTEA */
/* #undef CSP_USE_PROMISC */
/* #undef CSP_USE_QOS */
/* #undef CSP_USE_DEDUP */
/* #undef CSP_USE_INIT_SHUTDOWN */
#define CSP_USE_CAN 1
#define CSP_USE_I2C 1
#define CSP_USE_KISS 1
/* #undef CSP_USE_ZMQHUB */
#define CSP_CONN_MAX 10
#define CSP_CONN_QUEUE_LENGTH 100
#define CSP_FIFO_INPUT 10
#define CSP_MAX_BIND_PORT 31
#define CSP_RDP_MAX_WINDOW 20
#define CSP_PADDING_BYTES 8
#define CSP_CONNECTION_SO 0
#define CSP_LOG_LEVEL_DEBUG 1
#define CSP_LOG_LEVEL_INFO 1
#define CSP_LOG_LEVEL_WARN 1
#define CSP_LOG_LEVEL_ERROR 1
#define CSP_LITTLE_ENDIAN 1
/* #undef CSP_BIG_ENDIAN */
#define CSP_HAVE_STDBOOL_H 1
/* #undef CSP_HAVE_LIBSOCKETCAN */
#define LIBCSP_VERSION "1.5"

#define LIBCSP_MODULE_NAME      "libcsp"

#endif /* W_INCLUDE_CSP_CSP_AUTOCONFIG_H_WAF */
