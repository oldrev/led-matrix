#include <string.h>
#include <cmsis_os.h>

#include "comm.h"
#include "devices/devices.h"
#include "devices/jdy08.h"

static JDY08_Device g_device;

static void ClearRX();
static int BeginRX();

#define DEFAULT_BROADCASTING_NAME "磕 MoveBoard"
#define DEFAULT_POWER "+POWR:0"
#define DEFAULT_WXEN "+WXEN:0"
#define DEFAULT_CLSS "+CLSS:A3"

int JDY08_Init(UART_HandleTypeDef* uart, DMA_HandleTypeDef* dma)
{
    g_device.Uart = uart;
    g_device.Dma = dma;
    g_device.Mode = JDY08_AT_MODE;
    ClearRX();

    // 进入 AT 模式
    HAL_GPIO_WritePin(BLE_PWRC_GPIO_Port, BLE_PWRC_Pin, RESET);
    HAL_GPIO_WritePin(BLE_ATCMD_GPIO_Port, BLE_ATCMD_Pin, RESET);

    int resetRequired = 0;

    HAL_Delay(250);

    // 通过读取版本来检查蓝牙模块是否正常
    if (JDY08_SendAT("AT+VER") != 0) {
        return -1;
    }
    char* atResult = (char*)g_device.RXBuffer;
    if (strncmp((char*)atResult, "+JDY-08", 7) != 0) {
        return -1;
    }

    if (JDY08_EnsureWeixinEnabled(&resetRequired) != 0) {
        return -1;
    }

    if (JDY08_EnsureClass(&resetRequired) != 0) {
        return -1;
    }

    if (JDY08_EnsureBroadcastingName(&resetRequired) != 0) {
        return -1;
    }

    if (JDY08_EnsurePower(&resetRequired) != 0) {
        return -1;
    }

    if (resetRequired) {
        JDY08_Reset();
        HAL_Delay(1200);
    }

    // 退出 AT 模式
    HAL_GPIO_WritePin(BLE_ATCMD_GPIO_Port, BLE_ATCMD_Pin, SET);

    // 再次启动接收，准备实际数据的接收
    ClearRX();
    g_device.Mode = JDY08_TRANS_MODE;

    return 0;
}

/** 阻塞地发送 AT 命令
 *
 *
 */
int JDY08_SendAT(const char* cmd)
{
    ClearRX();
    if (BeginRX() != 0) {
        return -1;
    }

    if (HAL_UART_Transmit_DMA(g_device.Uart, (uint8_t*)cmd, strlen(cmd)) != HAL_OK) {
        return -1;
    }

    while (!g_device.IsReceived) {
    }

    return 0;
}

/** 阻塞地发送 AT 命令并等待返回 '+OK'
 *
 *
 */
int JDY08_SendATAndWaitOK(const char* cmd)
{
    if (JDY08_SendAT(cmd) != 0) {
        return -1;
    }
    if (strncmp((char*)g_device.RXBuffer, "+OK", 3) != 0) {
        return -1;
    }
    return 0;
}

/** 重启蓝牙模块
 *
 */
int JDY08_Reset()
{
    if (JDY08_SendATAndWaitOK("AT+RST") != HAL_OK) {
        return -1;
    }
    HAL_Delay(1200);
    return 0;
}

/** 验证蓝牙广播名称
 *
 */
int JDY08_EnsureBroadcastingName(int* resetRequired)
{
    // 查询广播名称
    if (JDY08_SendAT("AT+NAME") != HAL_OK) {
        return -1;
    }
    // 比较广播名称
    if (strncmp(
            "+NAME:" DEFAULT_BROADCASTING_NAME, (char*)g_device.RXBuffer, strlen("+NAME:" DEFAULT_BROADCASTING_NAME))
        != 0) {
        //不符合，则修改
        if (JDY08_SendATAndWaitOK("AT+NAME" DEFAULT_BROADCASTING_NAME) != HAL_OK) {
            return -1;
        }
        // 修改成功，重启模块
        if (!*resetRequired) {
            *resetRequired = 1;
        }
    }

    return 0;
}

/** 验证微信启用
 *
 */
int JDY08_EnsureWeixinEnabled(int* resetRequired)
{
    // 查询广播名称
    if (JDY08_SendAT("AT+WXEN") != HAL_OK) {
        return -1;
    }
    // 比较广播名称
    if (strncmp(DEFAULT_WXEN, (char*)g_device.RXBuffer, strlen(DEFAULT_WXEN)) != 0) {
        //没有打开微信则打开
        if (JDY08_SendATAndWaitOK("AT+WXEN1") != HAL_OK) {
            return -1;
        }
        // 修改成功，重启模块
        if (!*resetRequired) {
            *resetRequired = 1;
        }
    }

    return 0;
}

/** 验证并设置无线功率
 *
 * */
int JDY08_EnsurePower(int* resetRequired)
{
    if (JDY08_SendAT("AT+POWR") != HAL_OK) {
        return -1;
    }
    // 比较是否为我们设定的最大功率
    if (strncmp(DEFAULT_POWER, (char*)g_device.RXBuffer, strlen(DEFAULT_POWER)) != 0) {
        //不符合，则修改
        if (JDY08_SendATAndWaitOK("AT+POWR0") != HAL_OK) {
            return -1;
        }
        // 修改成功，重启模块
        if (!*resetRequired) {
            *resetRequired = 1;
        }
    }
    return 0;
}

/** 验证并设置类型
 *
 * */
int JDY08_EnsureClass(int* resetRequired)
{
    if (JDY08_SendAT("AT+CLSS") != HAL_OK) {
        return -1;
    }

    if (strncmp(DEFAULT_CLSS, (char*)g_device.RXBuffer, strlen(DEFAULT_CLSS)) != 0) {
        //不符合，则修改
        if (JDY08_SendATAndWaitOK("AT+CLSSA3") != HAL_OK) {
            return -1;
        }
        // 修改成功，重启模块
        if (!*resetRequired) {
            *resetRequired = 1;
        }
    }
    return 0;
}

int JDY08_IsConnected() { return (int)HAL_GPIO_ReadPin(BLE_STAT_GPIO_Port, BLE_STAT_Pin); }

int JDY08_BeginDataRX()
{
    g_device.Mode = JDY08_TRANS_MODE;
    ClearRX();
    Comm_BeginPackage();
    BeginRX();
    return 0;
}

int JDY08_Transmit(const void* buf, uint16_t bufSize)
{
    if (HAL_UART_Transmit_DMA(g_device.Uart, (uint8_t*)buf, bufSize) != HAL_OK) {
        return -1;
    }
    return 0;
}

int JDY08_OnReceived()
{

    uint32_t flags = __HAL_UART_GET_FLAG(g_device.Uart, UART_FLAG_IDLE); //获取IDLE标志位
    if (flags != RESET) // idle标志被置位
    {
        __HAL_UART_CLEAR_IDLEFLAG(g_device.Uart); //清除标志位
        uint32_t temp = g_device.Uart->Instance->SR; //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
        temp = g_device.Uart->Instance->DR; //读取数据寄存器中的数据
        // HAL_UART_DMAStop(g_device.Uart); //
        HAL_UART_AbortReceive(g_device.Uart);
        temp = g_device.Dma->Instance->CNDTR; // 获取DMA中未传输的数据个数，NDTR寄存器分析见下面
        g_device.RXSize = JDY08_RX_CAPACITY - temp; //总计数减去未传输的数据个数，得到已经接收的数据个数
        if (g_device.Mode == JDY08_AT_MODE) { // AT 模式缓冲区留给后面的处理
            g_device.IsReceived = 1; // 接受完成标志位置1
        } else { // 透传模式把收到的包存入消息队列
            Comm_ReceiveFrame(g_device.RXBuffer, g_device.RXSize);
            g_device.Mode = JDY08_TRANS_MODE;
            BeginRX(); // 重新启动 DMA 接收
        }
    }
    return 0;
}

static void ClearRX()
{
    memset(g_device.RXBuffer, 0, JDY08_RX_CAPACITY);
    g_device.IsReceived = 0;
    g_device.RXSize = 0;
}

static int BeginRX()
{
    // 打开DMA接收，数据存入数组中。
    if (HAL_UART_Receive_DMA(g_device.Uart, g_device.RXBuffer, JDY08_RX_CAPACITY) != HAL_OK) {
        return -1;
    }
    return 0;
}