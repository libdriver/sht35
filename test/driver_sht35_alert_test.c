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
 * @file      driver_sht35_alert_test.c
 * @brief     driver sht35 alert test source file
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

#include "driver_sht35_alert_test.h"

static sht35_handle_t gs_handle;        /**< sht35 handle */

/**
 * @brief     interface receive callback
 * @param[in] type receive type
 * @note      none
 */
static void a_receive_callback(uint16_t type)
{
    switch (type)
    {
        case SHT35_STATUS_ALERT_PENDING_STATUS :
        {
            sht35_interface_debug_print("sht35: irq alert pending status.\n");
            
            break;
        }
        case SHT35_STATUS_HUMIDITY_ALERT :
        {
            sht35_interface_debug_print("sht35: irq humidity alert.\n");
            
            break;
        }
        case SHT35_STATUS_TEMPERATURE_ALERT :
        {
            sht35_interface_debug_print("sht35: irq temperature alert.\n");
            
            break;
        }
    }
}

/**
 * @brief  alert test irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t sht35_alert_test_irq_handler(void)
{
    if (sht35_irq_handler(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     alert test
 * @param[in] addr_pin iic device address
 * @param[in] high_limit_temperature high limit temperature
 * @param[in] high_limit_humidity high limit humidity
 * @param[in] low_limit_temperature low limit temperature
 * @param[in] low_limit_humidity low limit humidity
 * @param[in] timeout timeout in ms
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sht35_alert_test(sht35_address_t addr_pin, 
                         float high_limit_temperature, float high_limit_humidity,
                         float low_limit_temperature, float low_limit_humidity,
                         uint32_t timeout)
{
    uint8_t res;
    uint32_t i;
    uint16_t set;
    uint16_t clear;
    sht35_info_t info;
    
    /* link functions */
    DRIVER_SHT35_LINK_INIT(&gs_handle, sht35_handle_t);
    DRIVER_SHT35_LINK_IIC_INIT(&gs_handle, sht35_interface_iic_init);
    DRIVER_SHT35_LINK_IIC_DEINIT(&gs_handle, sht35_interface_iic_deinit);
    DRIVER_SHT35_LINK_IIC_READ_ADDRESS16(&gs_handle, sht35_interface_iic_read_address16);
    DRIVER_SHT35_LINK_IIC_WRITE_ADDRESS16(&gs_handle, sht35_interface_iic_write_address16);
    DRIVER_SHT35_LINK_DELAY_MS(&gs_handle, sht35_interface_delay_ms);
    DRIVER_SHT35_LINK_DEBUG_PRINT(&gs_handle, sht35_interface_debug_print);
    DRIVER_SHT35_LINK_RECEIVE_CALLBACK(&gs_handle, a_receive_callback);
    
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
    
    /* start alert test */
    sht35_interface_debug_print("sht35: start alert test.\n");
    
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
    
    /* set art */
    res = sht35_set_art(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set art failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    
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
    
    /* set high repeatability */
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_HIGH);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* alert limit convert to register */
    res = sht35_alert_limit_convert_to_register(&gs_handle, high_limit_temperature, high_limit_humidity, &set);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: alert limit convert to register failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* alert limit convert to register */
    res = sht35_alert_limit_convert_to_register(&gs_handle, high_limit_temperature - 1.0f, high_limit_humidity + 1.0f, &clear);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: alert limit convert to register failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set high alert limit */
    res = sht35_set_high_alert_limit(&gs_handle, set, clear);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set high alert limit failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* alert limit convert to register */
    res = sht35_alert_limit_convert_to_register(&gs_handle, low_limit_temperature, low_limit_humidity, &set);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: alert limit convert to register failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* alert limit convert to register */
    res = sht35_alert_limit_convert_to_register(&gs_handle, low_limit_temperature - 1.0f, low_limit_humidity + 1.0f, &clear);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: alert limit convert to register failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set low alert limit */
    res = sht35_set_low_alert_limit(&gs_handle, set, clear);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set low alert limit failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sht35_interface_debug_print("sht35: high limit temperature is %.02fC.\n", high_limit_temperature);
    sht35_interface_debug_print("sht35: high limit humidity is %.02f%%.\n", high_limit_humidity);
    sht35_interface_debug_print("sht35: low limit temperature is %.02fC.\n", low_limit_temperature);
    sht35_interface_debug_print("sht35: low limit humidity is %.02f%%.\n", low_limit_humidity);
    
    /* clear status */
    res = sht35_clear_status(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: clear status failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_10HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i = 0; i < timeout; i++)
    {
        sht35_interface_delay_ms(1);
    }
    
    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* finish alert test */
    sht35_interface_debug_print("sht35: finish alert test.\n");
    (void)sht35_deinit(&gs_handle);

    return 0;
}
