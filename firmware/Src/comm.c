#include <string.h>
#include <cmsis_os.h>

#include "main.h"
#include "stm32f1xx_hal_conf.h"

#include "comm.h"


Comm g_comm;

int Comm_Init(osMessageQId queue) {
    memset(&g_comm, 0, sizeof(g_comm));
    g_comm.Queue = queue;
    Comm_BeginPackage();
    return 0;
}


int Comm_BeginPackage() {
    g_comm.Buffer.ReceivedOn = 0;
    g_comm.Buffer.ReceivedSize = 0;
    g_comm.Buffer.Size = 0;
    return 0;
}


/**
 * 接收帧并组报文
 **/
int Comm_ReceiveFrame(const void* frameBuffer, uint16_t frameSize) {
    // TODO 处理手机端问题，报文没发完的超时
    // 还有数据没有接收完成，说明在接收半途
    Comm_PackageBuffer* buffer = &g_comm.Buffer;
    buffer->ReceivedOn = HAL_GetTick();
    if(buffer->Size - buffer->ReceivedSize > 0) {
        memcpy(buffer->Package + buffer->ReceivedSize, frameBuffer, frameSize);
        buffer->ReceivedSize += frameSize;
    }
    else { // 其他情况是开始接收
        if(frameSize < COMM_REMOTE_PACKAGE_HEADER_SIZE) {
            goto __RECEIVED_BAD_FRAME;
        }
        //先解析报文头
        Comm_RemoteHeader ph;
        Comm_ParsePackageHeader(frameBuffer, &ph);
        //检查是否正确的 Magic
        if(ph.Magic != COMM_REMOTE_HEADER_MAGIC) {
            goto __RECEIVED_BAD_FRAME;
        }
        if(ph.Size > COMM_PACKAGE_CAPACITY || ph.Size < COMM_REMOTE_PACKAGE_HEADER_SIZE) { // 错误的报文尺寸，超过最大 512 字节
            goto __RECEIVED_BAD_FRAME;
        }
        buffer->Size = ph.Size < COMM_PACKAGE_CAPACITY ? ph.Size : COMM_PACKAGE_CAPACITY;
        buffer->ReceivedSize = frameSize;
        memcpy(buffer->Package, frameBuffer, frameSize);
    }

    if(buffer->ReceivedSize >= buffer->Size) {
        // 组成了一个完整的包，就直接发到消息队列
        osMessagePut(g_comm.Queue, (uint32_t)buffer->Package, 0); // Send Message
        Comm_BeginPackage();
    }

    return 0;

__RECEIVED_BAD_FRAME:
    Comm_BeginPackage();
    return -1;
}


void Comm_ParsePackageHeader(const void* buf, Comm_RemoteHeader* header) {
    //先解析报文头
    const uint8_t* bytes = (const uint8_t *)buf;
    header->Magic = bytes[0];
    header->ID = *((uint32_t*)(bytes + 1));
    header->Type = bytes[5];
    header->Size = *((uint16_t*)(bytes + 6));
}