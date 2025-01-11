#include "interface_uart.h"
#include "common.h"
#include <string.h>
#include <stdarg.h>


UartMsg_t uart2Msg;

extern DMA_HandleTypeDef hdma_usart2_rx;

static void (*OnRecvEnd2)(uint8_t* data, uint16_t len);

static void Uart2_SetRxCpltCallBack(void (* xerc)(uint8_t* , uint16_t))
{
   OnRecvEnd2 = xerc;
}

void uart_init(UART_HandleTypeDef *huart)
{
    __HAL_UART_CLEAR_IDLEFLAG(huart); 
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);

#define XX(id) \
    if (huart->Instance == USART##id) {\
        Uart##id##_SetRxCpltCallBack(OnUart##id##Cmd); \
        HAL_UART_Receive_DMA(&huart##id , uart##id##Msg.rBuf, MSGMAXLEN); \
        RetargetInit(&huart##id); \
    } 
    XX(2);
#undef XX
}

void UART_IDLECallBack(UART_HandleTypeDef *huart)
{
    uint16_t temp;  

#define XX(id) \
    if(huart->Instance == USART##id) \
	{ \
		if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET)) \
        { \
            __HAL_UART_CLEAR_IDLEFLAG(&huart##id); \
            HAL_UART_DMAStop(&huart##id); \
            temp = __HAL_DMA_GET_COUNTER(&hdma_usart##id##_rx);\
            uart##id##Msg.rLen = MSGMAXLEN - temp; \
            OnRecvEnd##id(uart##id##Msg.rBuf, uart##id##Msg.rLen); \
            memset(uart##id##Msg.rBuf, 0, uart##id##Msg.rLen); \
            HAL_UART_Receive_DMA(&huart##id, uart##id##Msg.rBuf, MSGMAXLEN); \
        } \
    } 
    XX(2);
#undef XX
 
}


void usart_printf(UART_HandleTypeDef *huart, const char *fmt, ...)
{
    uint16_t len;
    va_list args;
    va_start(args, fmt);
#define XX(id) \
    if (huart->Instance == USART##id) { \
        len = vsnprintf((char*)uart##id##Msg.tBuf, MSGMAXLEN, fmt, args); \
        if (len >= MSGMAXLEN)  \
            len = MSGMAXLEN - 1; \
        HAL_UART_Transmit_DMA(huart, uart##id##Msg.tBuf, len); \
    } 
    XX(2);
#undef XX
    va_end(args);
    
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
}
