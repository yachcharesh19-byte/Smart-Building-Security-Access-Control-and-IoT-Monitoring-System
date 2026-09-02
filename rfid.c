#include <LPC21xx.h>
#include "header.h"
const char stored_rfid[13] = "4900C9C08FCF";
int rfid_compare(char *s)
{
    int i;
    for(i = 0; i < 12; i++)
    {
        if(s[i] != stored_rfid[i])
            return 0;
    }
    return 1;
}
int rfid_check(void)
{
    char s[13];
    uart0_string("\r\nWaiting for RFID Card...\r\n");
    uart0_rx_string(s);
    uart0_string("\r\nRFID ID: ");
    uart0_string(s);
    if(rfid_compare(s))
        return 1;
    return 0;
}
