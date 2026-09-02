#include <lpc21xx.h>
#include "header.h"
#define PIR (1<<15)
int main(void)
{
    int i;
    int rfid_attempt;
    int key_attempt;
    int granted;
    unsigned char entered[4];
    IODIR0 &= ~PIR;
    uart0_init(9600);
    rtc_init();
    lcd_init();
    servo_init();
    keypad_init();
    can1_init();
    wifi_connect();
    uart0_string("\r\nSMART BUILDING SECURITY\r\n");
    lcd_cmd(0x01);
    lcd_string("Smart Building");
    delay_ms(500);
    lcd_cmd(0x01);
    lcd_string("System Ready");
    uart0_string("\r\nSystem Ready\r\n");
    while(1)
    {
        lcd_cmd(0x01);
        lcd_string("Monitoring");
        uart0_string("\r\nMonitoring...");
        while((IOPIN0 & PIR) == 0);
        uart0_string("\r\nWelcome! Please proceed.");
        uart0_string("\r\nWaiting for RFID...");
        lcd_cmd(0x01);
        lcd_string("Welcome!");
        delay_ms(500);
        lcd_cmd(0x01);
        lcd_string("Waiting RFID");
        granted = 0;
        rfid_attempt = 0;
        while(rfid_attempt < 2)
        {
            if(rfid_check())
            {
                uart0_string("\r\nRFID Verified");
                lcd_cmd(0x01);
                lcd_string("RFID Verified");
                granted = 1;
                break;
            }
            rfid_attempt++;
            uart0_string("\r\nRFID Failed");
            lcd_cmd(0x01);
            lcd_string("RFID Failed");
            delay_ms(300);
        }
        if(granted == 0)
        {
            uart0_string("\r\nEnter Password");
            lcd_cmd(0x01);
            lcd_string("Enter Password");
            key_attempt = 0;
            while(key_attempt < 3)
            {
                for(i = 0; i < 4; i++)
                {
                    entered[i] = keypad_read();
                    lcd_data('*');
                }
                if(keypad_check(entered))
                {
                    uart0_string("\r\nPassword Verified");
                    lcd_cmd(0x01);
                    lcd_string("Pass Verified");
                    granted = 1;
                    break;
                }
                key_attempt++;
                if(key_attempt < 3)
                {
                    uart0_string("\r\nWrong Password, Try Again");
                    lcd_cmd(0x01);
                    lcd_string("Wrong, Retry");
                }
                else
                {
                    uart0_string("\r\nSorry, Access Denied");
                    lcd_cmd(0x01);
                    lcd_string("Sorry Denied");
                }
                delay_ms(300);
            }
        }
        //CAN + EEPROM LOG
        if(granted)
        {
            uart0_string("\r\nACCESS GRANTED");
            lcd_cmd(0x01);
            lcd_string("ACCESS GRANTED");
            eeprom();
            can1_parameter(1,0,0);
            servo_90deg();
            delay_sec(2);
            servo_0deg();
            uart0_string("\r\nDoor Closed");
            lcd_cmd(0x01);
            lcd_string("Door Closed");
        }
        else
        {
            uart0_string("\r\nACCESS DENIED");
            lcd_cmd(0x01);
            lcd_string("ACCESS DENIED");
            eeprom();
            can1_parameter(0,0,0);
            delay_sec(2);
        }
        delay_sec(1);
        lcd_cmd(0x01);
        lcd_string("Monitoring");
    }
}
