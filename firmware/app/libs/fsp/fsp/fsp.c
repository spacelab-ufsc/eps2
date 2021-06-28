/*
 * fsp.c
 * 
 * Copyright (C) 2017-2019, Federal University of Santa Catarina.
 * 
 * This file is part of FloripaSat-FSP.
 * 
 * FloripaSat-FSP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-FSP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with FloripaSat-FSP. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief FloripaSat Protocol library implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.0
 * 
 * \date 06/11/2017
 * 
 * \addtogroup fsp
 * \{
 */

#include "fsp.h"
#include "crc.h"

uint8_t fsp_my_adr;

uint8_t fsp_decode_pos = 0;

void fsp_init(uint8_t module_adr)
{
    fsp_my_adr = module_adr;
    
    fsp_decode_pos = 0;
}

void fsp_reset()
{
    fsp_decode_pos = 0;
}

void fsp_gen_data_pkt(uint8_t *data, uint8_t data_len, uint8_t dst_adr, uint8_t ack, fsp_packet_t *fsp)
{
    if (ack == FSP_PKT_WITH_ACK)
    {
        fsp_gen_pkt(data, data_len, dst_adr, FSP_PKT_TYPE_DATA_WITH_ACK, fsp);
    }
    else
    {
        fsp_gen_pkt(data, data_len, dst_adr, FSP_PKT_TYPE_DATA, fsp);
    }
}

void fsp_gen_cmd_pkt(uint8_t cmd, uint8_t dst_adr, uint8_t ack, fsp_packet_t *fsp)
{
    if (ack == FSP_PKT_WITH_ACK)
    {
        fsp_gen_pkt(&cmd, 1, dst_adr, FSP_PKT_TYPE_CMD_WITH_ACK, fsp);
    }
    else
    {
        fsp_gen_pkt(&cmd, 1, dst_adr, FSP_PKT_TYPE_CMD, fsp);
    }
}

void fsp_gen_ack_pkt(uint8_t dst_adr, fsp_packet_t *fsp)
{
    fsp_gen_pkt((void*)0, 0, dst_adr, FSP_PKT_TYPE_ACK, fsp);
}

void fsp_gen_nack_pkt(uint8_t dst_adr, fsp_packet_t *fsp)
{
    fsp_gen_pkt((void*)0, 0, dst_adr, FSP_PKT_TYPE_NACK, fsp);
}

void fsp_gen_pkt(uint8_t *payload, uint8_t payload_len, uint8_t dst_adr, uint8_t type, fsp_packet_t *fsp)
{
    fsp->sod        = FSP_PKT_SOD;
    fsp->src_adr    = fsp_my_adr;
    fsp->dst_adr    = dst_adr;
    fsp->length     = payload_len;
    fsp->type       = type;
    
    uint8_t i = 0;
    for(i=0; i<payload_len; i++)
    {
        fsp->payload[i] = payload[i];
    }
    
    fsp->crc16      = crc16_CCITT(FSP_CRC16_INITIAL_VALUE, &fsp->src_adr, fsp->length + 4);
}

void fsp_encode(fsp_packet_t *fsp, uint8_t *pkt, uint8_t *pkt_len)
{
    uint8_t i = 0;
    
    pkt[i++] = fsp->sod;
    pkt[i++] = fsp->src_adr;
    pkt[i++] = fsp->dst_adr;
    pkt[i++] = fsp->length;
    pkt[i++] = fsp->type;
    
    uint8_t j = 0;
    for(j=0; j<fsp->length; j++)
    {
        pkt[i++] = fsp->payload[j];
    }
    
    pkt[i++] = (uint8_t)(fsp->crc16 >> 8);
    pkt[i++] = (uint8_t)(fsp->crc16);
    
    *pkt_len = i;
}

uint8_t fsp_decode(uint8_t byte, fsp_packet_t *fsp)
{
    switch(fsp_decode_pos)
    {
        case FSP_PKT_POS_SOD:
            if (byte == FSP_PKT_SOD)
            {
                fsp->sod = byte;
                
                fsp_decode_pos++;
                
                return FSP_PKT_NOT_READY;
            }
            else
            {
                return FSP_PKT_INVALID;
            }
        case FSP_PKT_POS_SRC_ADR:
            fsp->src_adr = byte;
            fsp_decode_pos++;
            
            return FSP_PKT_NOT_READY;
        case FSP_PKT_POS_DST_ADR:
            fsp->dst_adr = byte;
            fsp_decode_pos++;
            
            if (byte == fsp_my_adr)
            {
                return FSP_PKT_NOT_READY;
            }
            else
            {
                return FSP_PKT_WRONG_ADR;
            }
        case FSP_PKT_POS_LEN:
            if (byte > FSP_PAYLOAD_MAX_LENGTH)
            {
                fsp_decode_pos = FSP_PKT_POS_SOD;
                
                return FSP_PKT_INVALID;
            }
            else
            {
                fsp->length = byte;
                fsp_decode_pos++;
                
                return FSP_PKT_NOT_READY;
            }
        case FSP_PKT_POS_TYPE:
            fsp->type = byte;
            fsp_decode_pos++;
            
            return FSP_PKT_NOT_READY;
        default:
            if (fsp_decode_pos < (FSP_PKT_POS_TYPE + fsp->length + 1))          // Payload
            {
                fsp->payload[fsp_decode_pos - FSP_PKT_POS_TYPE - 1] = byte;
                fsp_decode_pos++;
                
                return FSP_PKT_NOT_READY;
            }
            else if (fsp_decode_pos == (FSP_PKT_POS_TYPE + fsp->length + 1))    // CRC16 MSB
            {
                fsp->crc16 = (uint16_t)(byte << 8);
                
                fsp_decode_pos++;
                
                return FSP_PKT_NOT_READY;
            }
            else if (fsp_decode_pos == (FSP_PKT_POS_TYPE + fsp->length + 2))    // CRC16 LSB
            {
                fsp->crc16 |= (uint16_t)(byte);
                
                fsp_decode_pos = FSP_PKT_POS_SOD;
                
                if (fsp->crc16 == crc16_CCITT(FSP_CRC16_INITIAL_VALUE, &fsp->src_adr, fsp->length + 4))
                {
                    return FSP_PKT_READY;
                }
                else
                {
                    return FSP_PKT_INVALID;
                }
            }
            else
            {
                fsp_decode_pos = FSP_PKT_POS_SOD;
                
                return FSP_PKT_ERROR;
            }
    }
}

//! \} End of fsp group
