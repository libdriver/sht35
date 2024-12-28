/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_sht35.h
 * @brief     driver sht35 header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-05
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/05  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/11/03  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_SHT35_H
#define DRIVER_SHT35_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup sht35_driver sht35 driver function
 * @brief    sht35 driver modules
 * @{
 */

/**
 * @addtogroup sht35_base_driver
 * @{
 */

/**
 * @brief sht35 address enumeration definition
 */
typedef enum
{
    SHT35_ADDRESS_0 = (0x44 << 1),        /**< ADDR pin connected to GND */
    SHT35_ADDRESS_1 = (0x45 << 1),        /**< ADDR pin connected to VCC */
} sht35_address_t;

/**
 * @brief sht35 bool enumeration definition
 */
typedef enum
{
    SHT35_BOOL_FALSE = 0x00,        /**< disable function */
    SHT35_BOOL_TRUE  = 0x01,        /**< enable function */
} sht35_bool_t;

/**
 * @brief sht35 rate enumeration definition
 */
typedef enum
{
    SHT35_RATE_0P5HZ = 0x20,        /**< 0.5Hz sample rate */
    SHT35_RATE_1HZ   = 0x21,        /**< 1Hz sample rate */
    SHT35_RATE_2HZ   = 0x22,        /**< 2Hz sample rate */
    SHT35_RATE_4HZ   = 0x23,        /**< 4Hz sample rate */
    SHT35_RATE_10HZ  = 0x27,        /**< 10Hz sample rate */
} sht35_rate_t;

/**
 * @brief sht35 repeatability enumeration definition
 */
typedef enum  
{
    SHT35_REPEATABILITY_HIGH   = 0x00,        /**< high repeatability */
    SHT35_REPEATABILITY_MEDIUM = 0x01,        /**< medium repeatability */
    SHT35_REPEATABILITY_LOW    = 0x02,        /**< low repeatability */
} sht35_repeatability_t;

/**
 * @brief sht35 status enumeration definition
 */
typedef enum  
{
    SHT35_STATUS_ALERT_PENDING_STATUS = (1 << 15),        /**< alert pending status */
    SHT35_STATUS_HEATER_ON            = (1 << 13),        /**< heater on */
    SHT35_STATUS_HUMIDITY_ALERT       = (1 << 11),        /**< humidity alert */
    SHT35_STATUS_TEMPERATURE_ALERT    = (1 << 10),        /**< temperature alert */
    SHT35_STATUS_SYSTEM_RESET         = (1 << 4),         /**< system reset */
    SHT35_STATUS_COMMAND_STATUS       = (1 << 1),         /**< command status */
    SHT35_STATUS_CHECKSUM_STATUS      = (1 << 0),         /**< checksum status */
} sht35_status_t;

/**
 * @brief sht35 handle structure definition
 */
typedef struct sht35_handle_s
{
    uint8_t (*iic_init)(void);                                                                     /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                                   /**< point to an iic_deinit function address */
    uint8_t (*iic_write_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write_address16 function address */
    uint8_t (*iic_read_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read_address16 function address */
    void (*delay_ms)(uint32_t ms);                                                                 /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                               /**< point to a debug_print function address */
    uint8_t iic_addr;                                                                              /**< iic device address */
    uint8_t repeatability;                                                                         /**< repeatability value */
    uint8_t inited;                                                                                /**< inited flag */
} sht35_handle_t;

/**
 * @brief sht35 information structure definition
 */
typedef struct sht35_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} sht35_info_t;

/**
 * @}
 */

/**
 * @defgroup sht35_link_driver sht35 link driver function
 * @brief    sht35 link driver modules
 * @ingroup  sht35_driver
 * @{
 */

/**
 * @brief     initialize sht35_handle_t structure
 * @param[in] HANDLE pointer to an sht35 handle structure
 * @param[in] STRUCTURE sht35_handle_t
 * @note      none
 */
#define DRIVER_SHT35_LINK_INIT(HANDLE, STRUCTURE)            memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to an sht35 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_SHT35_LINK_IIC_INIT(HANDLE, FUC)              (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to an sht35 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_SHT35_LINK_IIC_DEINIT(HANDLE, FUC)            (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_address16 function
 * @param[in] HANDLE pointer to an sht35 handle structure
 * @param[in] FUC pointer to an iic_read_address16 function address
 * @note      none
 */
#define DRIVER_SHT35_LINK_IIC_READ_ADDRESS16(HANDLE, FUC)    (HANDLE)->iic_read_address16 = FUC

/**
 * @brief     link iic_write_address16 function
 * @param[in] HANDLE pointer to an sht35 handle structure
 * @param[in] FUC pointer to an iic_write_address16 function address
 * @note      none
 */
#define DRIVER_SHT35_LINK_IIC_WRITE_ADDRESS16(HANDLE, FUC)   (HANDLE)->iic_write_address16 = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an sht35 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_SHT35_LINK_DELAY_MS(HANDLE, FUC)              (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an sht35 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_SHT35_LINK_DEBUG_PRINT(HANDLE, FUC)           (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup sht35_base_driver sht35 base driver function
 * @brief    sht35 base driver modules
 * @ingroup  sht35_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an sht35 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sht35_info(sht35_info_t *info);

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to an sht35 handle structure
 * @param[in] addr_pin chip iic address pin
 * @return    status code
 *            - 0 success
 *            - 1 set addr pin failed
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t sht35_set_addr_pin(sht35_handle_t *handle, sht35_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to an sht35 handle structure
 * @param[out] *addr_pin pointer to a chip iic address pin buffer
 * @return      status code
 *              - 0 success
 *              - 1 get addr pin failed
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t sht35_get_addr_pin(sht35_handle_t *handle, sht35_address_t *addr_pin);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an sht35 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t sht35_init(sht35_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an sht35 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sht35_deinit(sht35_handle_t *handle);

/**
 * @brief      read data once
 * @param[in]  *handle pointer to an sht35 handle structure
 * @param[in]  clock_stretching_enable clock stretching bool value
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_s pointer to a converted temperature buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_s pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 single read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sht35_single_read(sht35_handle_t *handle, sht35_bool_t clock_stretching_enable, 
                          uint16_t *temperature_raw, float *temperature_s,
                          uint16_t *humidity_raw, float *humidity_s
                         );

/**
 * @brief     start reading
 * @param[in] *handle pointer to an sht35 handle structure
 * @param[in] rate sample rate
 * @return    status code
 *            - 0 success
 *            - 1 start continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sht35_start_continuous_read(sht35_handle_t *handle, sht35_rate_t rate);

/**
 * @brief     stop reading
 * @param[in] *handle pointer to an sht35 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sht35_stop_continuous_read(sht35_handle_t *handle);

/**
 * @brief      read data continuously
 * @param[in]  *handle pointer to an sht35 handle structure
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_s pointer to a converted temperature buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_s pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 continuous read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sht35_continuous_read(sht35_handle_t *handle, 
                              uint16_t *temperature_raw, float *temperature_s, 
                              uint16_t *humidity_raw, float *humidity_s);

/**
 * @brief      get the current status
 * @param[in]  *handle pointer to an sht35 handle structure
 * @param[out] *status pointer to a status buffer
 * @return      status code
 *              - 0 success
 *              - 1 get status failed
 *              - 2 handle is NULL
 * @note        none
 */
uint8_t sht35_get_status(sht35_handle_t *handle, uint16_t *status);

/**
 * @brief     clear the current status
 * @param[in] *handle pointer to an sht35 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear status failed
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t sht35_clear_status(sht35_handle_t *handle);

/**
 * @brief     set the measurement repeatability
 * @param[in] *handle pointer to an sht35 handle structure
 * @param[in] repeatability measurement repeatability
 * @return    status code
 *            - 0 success
 *            - 1 set repeatability failed
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t sht35_set_repeatability(sht35_handle_t *handle, sht35_repeatability_t repeatability);

/**
 * @brief      get the measurement repeatability
 * @param[in]  *handle pointer to an sht35 handle structure
 * @param[out] *repeatability pointer to a measurement repeatability buffer
 * @return     status code
 *             - 0 success
 *             - 1 get repeatability failed
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sht35_get_repeatability(sht35_handle_t *handle, sht35_repeatability_t *repeatability);

/**
 * @brief     set the chip art
 * @param[in] *handle pointer to an sht35 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set art failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sht35_set_art(sht35_handle_t *handle);

/**
 * @brief     soft reset the chip
 * @param[in] *handle pointer to an sht35 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sht35_soft_reset(sht35_handle_t *handle);

/**
 * @brief     enable or disable the chip heater
 * @param[in] *handle pointer to an sht35 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sht35_set_heater(sht35_handle_t *handle, sht35_bool_t enable);

/**
 * @}
 */

/**
 * @defgroup sht35_extend_driver sht35 extend driver function
 * @brief    sht35 extend driver modules
 * @ingroup  sht35_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to an sht35 handle structure
 * @param[in] command chip command
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sht35_set_reg(sht35_handle_t *handle, uint16_t command);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to an sht35 handle structure
 * @param[in]  command chip command
 * @param[out] *buf pointer to data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sht35_get_reg(sht35_handle_t *handle, uint16_t command, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
