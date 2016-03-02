#include "stm32f4xx_hal.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"

void CDC_Itf_Send(uint8_t* pbuf, uint32_t Len);
