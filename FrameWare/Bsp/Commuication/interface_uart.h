#ifndef __INTERFACE_UART_H
#define __INTERFACE_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <usart.h>
#define MSGMAXLEN 256

typedef struct {
    uint8_t rBuf[MSGMAXLEN];
    uint16_t rLen;
    uint8_t tBuf[MSGMAXLEN];
    uint16_t tLen;
} UartMsg_t;

void uart_init(UART_HandleTypeDef *huart);
void UART_IDLECallBack(UART_HandleTypeDef *huart);
void usart_printf(UART_HandleTypeDef *huart, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif