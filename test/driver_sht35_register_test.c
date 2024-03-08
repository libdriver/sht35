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
 * @file      driver_sht35_register_test.c
 * @brief     driver sht35 register test source file
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
 
#include "driver_sht35_register_test.h"
#include <stdlib.h>

static sht35_handle_t gs_handle;        /**< sht35 handle */

/**
 * @brief     register test
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sht35_register_test(sht35_address_t addr_pin)
{
    uint8_t res;
    uint16_t status;
    sht35_info_t info;
    sht35_address_t address_pin;
    sht35_repeatability_t repeatability;
    
    /* link functions */
    DRIVER_SHT35_LINK_INIT(&gs_handle, sht35_handle_t);
    DRIVER_SHT35_LINK_IIC_INIT(&gs_handle, sht35_interface_iic_init);
    DRIVER_SHT35_LINK_IIC_DEINIT(&gs_handle, sht35_interface_iic_deinit);
    DRIVER_SHT35_LINK_IIC_READ_ADDRESS16(&gs_handle, sht35_interface_iic_read_address16);
    DRIVER_SHT35_LINK_IIC_WRITE_ADDRESS16(&gs_handle, sht35_interface_iic_write_address16);
    DRIVER_SHT35_LINK_DELAY_MS(&gs_handle, sht35_interface_delay_ms);
    DRIVER_SHT35_LINK_DEBUG_PRINT(&gs_handle, sht35_interface_debug_print);
    
    /* sht35 info */
    res = sht35_info(&info);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        sht35_interface_debug_print("sht35: chip is %s.\n", info.chip_name);
        sht35_interface_debug_print("sht35: manufacturer is %s.\n", info.manufacturer_name);
        sht35_interface_debug_print("sht35: interface is %s.\n", info.interface);
        sht35_interface_debug_print("sht35: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sht35_interface_debug_print("sht35: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sht35_interface_debug_print("sht35: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sht35_interface_debug_print("sht35: max current is %0.2fmA.\n", info.max_current_ma);
        sht35_interface_debug_print("sht35: max temperature is %0.1fC.\n", info.temperature_max);
        sht35_interface_debug_print("sht35: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    sht35_interface_debug_print("sht35: start register test.\n");
    
    /* sht35_set_addr_pin/sht35_get_addr_pin test */
    sht35_interface_debug_print("sht35: sht35_set_addr_pin/sht35_get_addr_pin test.\n");
    
    /* set address pin 0 */
    res = sht35_set_addr_pin(&gs_handle, SHT35_ADDRESS_0);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set addr pin failed.\n");
       
        return 1;
    }
    sht35_interface_debug_print("sht35: set address pin 0.\n");
    res = sht35_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: get addr pin failed.\n");
       
        return 1;
    }
    sht35_interface_debug_print("sht35: check addr pin %s.\n", (SHT35_ADDRESS_0==address_pin)?"ok":"error");
    
    /* set address pin 1 */
    res = sht35_set_addr_pin(&gs_handle, SHT35_ADDRESS_1);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set addr pin failed.\n");
       
        return 1;
    }
    sht35_interface_debug_print("sht35: set address pin 1.\n");
    res = sht35_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: get addr pin failed.\n");
       
        return 1;
    }
    sht35_interface_debug_print("sht35: check addr pin %s.\n", (SHT35_ADDRESS_1==address_pin)?"ok":"error");
    
    /* set address pin */
    res = sht35_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set addr pin failed.\n");
       
        return 1;
    }
    
    /* sht35 init */
    res = sht35_init(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: init failed.\n");
       
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    
    /* sht35_set_repeatability/sht35_get_repeatability test */
    sht35_interface_debug_print("sht35: sht35_set_repeatability/sht35_get_repeatability test.\n");
    
    /* set high */
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_HIGH);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    sht35_interface_debug_print("sht35: set repeatability high.\n");
    res = sht35_get_repeatability(&gs_handle, &repeatability);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: get repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    sht35_interface_debug_print("sht35: check repeatability pin %s.\n", (SHT35_REPEATABILITY_HIGH==repeatability)?"ok":"error");
    
    /* set medium */
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_MEDIUM);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    sht35_interface_debug_print("sht35: set repeatability medium.\n");
    res = sht35_get_repeatability(&gs_handle, &repeatability);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: get repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    sht35_interface_debug_print("sht35: check repeatability pin %s.\n", (SHT35_REPEATABILITY_MEDIUM==repeatability)?"ok":"error");
    
    /* set low */
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_LOW);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    sht35_interface_debug_print("sht35: set repeatability low.\n");
    res = sht35_get_repeatability(&gs_handle, &repeatability);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: get repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    sht35_interface_debug_print("sht35: check repeatability pin %s.\n", (SHT35_REPEATABILITY_LOW==repeatability)?"ok":"error");
    
    /* set art test */
    sht35_interface_debug_print("sht35: set art test.\n");
    res = sht35_set_art(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set art failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    sht35_interface_debug_print("sht35: check art %s.\n", (res==0)?"ok":"error");
    
    /* sht35_set_heater test*/
    sht35_interface_debug_print("sht35: set heater test.\n");
    
    /* enable heater */
    res = sht35_set_heater(&gs_handle, SHT35_BOOL_TRUE);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set heater failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    sht35_interface_debug_print("sht35: enable heater.\n");
    sht35_interface_debug_print("sht35: check heater %s.\n", (res==0)?"ok":"error");
    
    /* disable heater */
    res = sht35_set_heater(&gs_handle, SHT35_BOOL_FALSE);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set heater failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    sht35_interface_debug_print("sht35: disable heater.\n");
    sht35_interface_debug_print("sht35: check heater %s.\n", (res==0)?"ok":"error");
    
    /* get_status test*/
    sht35_interface_debug_print("sht35: get status test.\n");
    res = sht35_get_status(&gs_handle, (uint16_t *)&status);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: get status failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    sht35_interface_debug_print("sht35: check status 0x%02X.\n", status);
    
    /* clear_status test*/
    sht35_interface_debug_print("sht35: clear status test.\n");
    res = sht35_clear_status(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: clear status failed.\n");
        (void)sht35_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    sht35_interface_debug_print("sht35: check clear status %s.\n", (res==0)?"ok":"error");
    
    /* finish register test */
    sht35_interface_debug_print("sht35: finish register test.\n");
    (void)sht35_deinit(&gs_handle);
    
    return 0;
}
