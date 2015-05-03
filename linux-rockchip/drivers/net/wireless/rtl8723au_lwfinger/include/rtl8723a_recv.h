/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __RTL8723A_RECV_H__
#define __RTL8723A_RECV_H__

#include <rtl8192c_recv.h>

void rtl8192c_query_rx_phy_status(union recv_frame *prframe, struct phy_stat *pphy_stat);
void rtl8192c_process_phy_info(struct rtw_adapter *padapter, void *prframe);
void update_recvframe_attrib(union recv_frame *precvframe, struct recv_stat *prxstat);
void update_recvframe_phyinfo(union recv_frame *precvframe, struct phy_stat *pphy_info);

#endif
