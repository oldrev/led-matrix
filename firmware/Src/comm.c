#include <string.h>
#include <cmsis_os.h>

#include "main.h"
#include "stm32f1xx_hal_conf.h"

#include "comm.h"
#include "devices/jdy08.h"

Comm g_comm;

int Comm_Init(osMessageQId queue)
{
    memset(&g_comm, 0, sizeof(g_comm));
    g_comm.Queue = queue;
    Comm_BeginPackage();
    return 0;
}

int Comm_BeginPackage()
{
    g_comm.Buffer.ReceivedOn = 0;
    g_comm.Buffer.ReceivedSize = 0;
    g_comm.Buffer.Size = 0;
    return 0;
}

/**
 * 接收帧并组报文
 **/
int Comm_ReceiveFrame(const void* frameBuffer, uint16_t frameSize)
{
    // TODO 处理手机端问题，报文没发完的超时
    // 还有数据没有接收完成，说明在接收半途
    Comm_PackageBuffer* buffer = &g_comm.Buffer;
    uint32_t now = HAL_GetTick();
    uint16_t packageRestSize = buffer->Size - buffer->ReceivedSize;
    if (packageRestSize == 0) { // 开始接收第一帧
        if (frameSize < COMM_REMOTE_PACKAGE_HEADER_SIZE) {
            goto __RECEIVED_BAD_FRAME;
        }
        //先解析报文头
        Comm_RemoteHeader ph;
        Comm_ParsePackageHeader(frameBuffer, &ph);
        //检查是否正确的 Magic
        if (ph.Magic != COMM_REMOTE_HEADER_MAGIC) {
            goto __RECEIVED_BAD_FRAME;
        }
        if (ph.Size > COMM_PACKAGE_CAPACITY
            || ph.Size < COMM_REMOTE_PACKAGE_HEADER_SIZE) { // 错误的报文尺寸，超过最大 512 字节
            goto __RECEIVED_BAD_FRAME;
        }
        buffer->Size = ph.Size < COMM_PACKAGE_CAPACITY ? ph.Size : COMM_PACKAGE_CAPACITY;
        buffer->ReceivedSize = frameSize;
        memcpy(buffer->Package, frameBuffer, frameSize);
        buffer->ReceivedOn = now;
    } else { //接收半途中
        if((now - buffer->ReceivedOn) > COMM_FRAME_INTERVAL_MAX) {
            // 帧之间超时了，放弃接收，准备接收下一个报文
            goto __RECEIVED_BAD_FRAME;
        }
        memcpy(buffer->Package + buffer->ReceivedSize, frameBuffer, frameSize);
        buffer->ReceivedSize += frameSize;
        buffer->ReceivedOn = now;
    }

    if (buffer->ReceivedSize >= buffer->Size) {
        // 组成了一个完整的包，就直接发到消息队列
        osMessagePut(g_comm.Queue, (uint32_t)buffer->Package, 0); // Send Message
        Comm_BeginPackage();
    }

    return 0;

__RECEIVED_BAD_FRAME:
    Comm_BeginPackage();
    return -1;
}

void Comm_ParsePackageHeader(const void* buf, Comm_RemoteHeader* header)
{
    //先解析报文头
    /*
    const uint8_t* bytes = (const uint8_t*)buf;
    header->Magic = bytes[0];
    header->ID = *((uint32_t*)(bytes + 1));
    header->Type = bytes[5];
    header->Size = *((uint16_t*)(bytes + 6));
    */
   memcpy(header, buf, sizeof(Comm_RemoteHeader));
}

void Comm_PackPackageHeader(const Comm_RemoteHeader* header, void* buf)
{
    /*uint8_t* bytes = (uint8_t*)buf;
    bytes[0] = COMM_REMOTE_HEADER_MAGIC;
    memcpy(bytes + 1, &header->ID, sizeof(uint32_t));
    bytes[5] = header->Type;
    memcpy(bytes + 6, &header->Size, sizeof(uint16_t));
    */
   memcpy(buf, header, sizeof(Comm_RemoteHeader));
}

int Comm_SendPackage(uint8_t packageType, const void* body, uint16_t bodySize) { return 0; }

int Comm_ReplyPackage(uint32_t packageID, uint8_t packageType, const void* body, uint16_t bodySize)
{
    uint16_t packageSize = bodySize + COMM_REMOTE_PACKAGE_HEADER_SIZE;
    Comm_RemoteHeader header = {
        .Type = packageType,
        .ID = packageID,
        .Size = packageSize,
    };
    Comm_PackPackageHeader(&header, g_comm.TXBuffer);
    memcpy(g_comm.TXBuffer + COMM_REMOTE_PACKAGE_HEADER_SIZE, body, bodySize);
    if (JDY08_Transmit(g_comm.TXBuffer, packageSize) != 0) {
        return -1;
    }
    return 0;
}