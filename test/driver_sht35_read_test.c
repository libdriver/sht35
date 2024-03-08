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
 * @file      driver_sht35_read_test.c
 * @brief     driver sht35 read test source file
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

#include "driver_sht35_read_test.h"

static sht35_handle_t gs_handle;        /**< sht35 handle */

/**
 * @brief     read test
 * @param[in] addr_pin is the iic device address
 * @param[in] times is test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sht35_read_test(sht35_address_t addr_pin, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    sht35_info_t info;
    
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
    
    /* start read test */
    sht35_interface_debug_print("sht35: start read test.\n");
    
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
    
    /* set default heater */
    res = sht35_set_heater(&gs_handle, SHT35_BOOL_TRUE);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set heater failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    sht35_interface_debug_print("sht35: continuous read.\n");
    
    /* set low repeatability */
    sht35_interface_debug_print("sht35: set low repeatability.\n");
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_LOW);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rate 0.5Hz */
    sht35_interface_debug_print("sht35: set rate 0.5Hz.\n");
    
    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_0P5HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);
    
        /* wait 2500 ms */
        sht35_interface_delay_ms(2500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 1Hz */
    sht35_interface_debug_print("sht35: set rate 1Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_1HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1500 ms */
        sht35_interface_delay_ms(1500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 2Hz */
    sht35_interface_debug_print("sht35: set rate 2Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_2HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht35_interface_delay_ms(1000);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 4Hz */
    sht35_interface_debug_print("sht35: set rate 4Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_4HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht35_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 10Hz */
    sht35_interface_debug_print("sht35: set rate 10Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_10HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht35_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set medium repeatability */
    sht35_interface_debug_print("sht35: set medium repeatability.\n");
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_MEDIUM);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rate 0.5Hz */
    sht35_interface_debug_print("sht35: set rate 0.5Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_0P5HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 2500 ms */
        sht35_interface_delay_ms(2500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 1Hz */
    sht35_interface_debug_print("sht35: set rate 1Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_1HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1500 ms */
        sht35_interface_delay_ms(1500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 2Hz */
    sht35_interface_debug_print("sht35: set rate 2Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_2HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht35_interface_delay_ms(1000);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 4Hz */
    sht35_interface_debug_print("sht35: set rate 4Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_4HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht35_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 10Hz */
    sht35_interface_debug_print("sht35: set rate 10Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_10HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht35_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set high repeatability */
    sht35_interface_debug_print("sht35: set high repeatability.\n");
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_HIGH);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rate 0.5Hz */
    sht35_interface_debug_print("sht35: set rate 0.5Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_0P5HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 2500 ms */
        sht35_interface_delay_ms(2500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 1Hz */
    sht35_interface_debug_print("sht35: set rate 1Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_1HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1500 ms */
        sht35_interface_delay_ms(1500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 2Hz */
    sht35_interface_debug_print("sht35: set rate 2Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_2HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht35_interface_delay_ms(1000);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 4Hz */
    sht35_interface_debug_print("sht35: set rate 4Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_4HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht35_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* set rate 10Hz */
    sht35_interface_debug_print("sht35: set rate 10Hz.\n");

    /* start continuous read */
    res = sht35_start_continuous_read(&gs_handle, SHT35_RATE_10HZ);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: start continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: continuous read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht35_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht35_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: stop continuous failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht35_interface_delay_ms(10);

    /* link iic read address16 with scl */
    DRIVER_SHT35_LINK_IIC_READ_ADDRESS16(&gs_handle, sht35_interface_iic_scl_read_address16);
    sht35_interface_debug_print("sht35: single read.\n");

    /* set low repeatability */
    sht35_interface_debug_print("sht35: set low repeatability.\n");
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_LOW);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_single_read(&gs_handle, SHT35_BOOL_TRUE, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: single read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht35_interface_delay_ms(1000);
    }

    /* set medium repeatability */
    sht35_interface_debug_print("sht35: set medium repeatability.\n");
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_MEDIUM);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_single_read(&gs_handle, SHT35_BOOL_TRUE, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: single read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht35_interface_delay_ms(1000);
    }

    /* set high repeatability */
    sht35_interface_debug_print("sht35: set high repeatability.\n");
    res = sht35_set_repeatability(&gs_handle, SHT35_REPEATABILITY_HIGH);
    if (res != 0)
    {
        sht35_interface_debug_print("sht35: set repeatability failed.\n");
        (void)sht35_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_single_read(&gs_handle, SHT35_BOOL_TRUE, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: single read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht35_interface_delay_ms(1000);
    }

    /* disable clock stretching */
    sht35_interface_debug_print("sht35: disable clock stretching.\n");
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht35_single_read(&gs_handle, SHT35_BOOL_FALSE, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht35_interface_debug_print("sht35: single read failed.\n");
            (void)sht35_deinit(&gs_handle);
            
            return 1;
        }
        sht35_interface_debug_print("sht35: temperature is %0.2fC.\n", temperature_s);
        sht35_interface_debug_print("sht35: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht35_interface_delay_ms(1000);
    }

    /* finish read test */
    sht35_interface_debug_print("sht35: finish read test.\n");
    (void)sht35_deinit(&gs_handle);

    return 0;
}
