/*
 * can_socketcan.h
 *
 *  Created on: Feb 6, 2017
 *      Author: johan
 */

#ifndef LIB_CSP_INCLUDE_CSP_DRIVERS_CAN_SOCKETCAN_H_
#define LIB_CSP_INCLUDE_CSP_DRIVERS_CAN_SOCKETCAN_H_

#include <csp/csp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

csp_iface_t * csp_can_socketcan_init(const char * ifc, int bitrate, int promisc);
int csp_can_socketcan_stop(void);

#ifdef __cplusplus
}
#endif
#endif /* LIB_CSP_INCLUDE_CSP_DRIVERS_CAN_SOCKETCAN_H_ */
