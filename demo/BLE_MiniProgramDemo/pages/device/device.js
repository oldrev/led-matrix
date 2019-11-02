const app = getApp()
Page({
    data: {
        inputText: 'Hello World!',
        receiveText: '',
        name: '',
        connectedDeviceId: '',
        services: {},
        characteristics: {},
        connected: true,
        currentIndex: 0,
    },
    bindInput: function (e) {
        this.setData({
            inputText: e.detail.value
        })
        console.log(e.detail.value)
    },
    SendFill_0: function() {
        var self = this;
        //包需要使用小端序        
        var bytes = new Uint8Array([
            0x66, // Magic = 0x66 固定的报文 Magic
            0x01, 0x00, 0x00, 0x00, //ID = 0x00000001 报文 ID
            0x03,                   // MESSAGE_DISPLAY_FILL 0x03 报文类型
            0x09, 0x00,     // 报文长度 0x09
            0x00 //填充的颜色索引
        ]);
        self.sendBytes(bytes.buffer);
    },
    SendFill_1: function () {
        var self = this;
        //包需要使用小端序        
        var bytes = new Uint8Array([
            0x66, // Magic = 0x66 固定的报文 Magic
            0x00, 0x00, 0x00, 0x00, //ID = 0x00000001 报文 ID
            0x03,                   // MESSAGE_DISPLAY_FILL 0x03 报文类型
            0x09, 0x00,     // 报文长度 0x09
            0x01 //填充的颜色索引
        ]);
        self.sendBytes(bytes.buffer);
    },
    SendFill_2: function () {
        var self = this;
        //包需要使用小端序        
        var bytes = new Uint8Array([
            0x66, // Magic = 0x66 固定的报文 Magic
            0x02, 0x00, 0x00, 0x00, //ID = 0x00000001 报文 ID
            0x03,                   // MESSAGE_DISPLAY_FILL 0x03 报文类型
            0x09, 0x00,     // 报文长度 0x09
            0x02 //填充的颜色索引
        ]);
        self.sendBytes(bytes.buffer);
    },    
    Send_SetPixelXY: function () {
        var self = this;
        //包需要使用小端序        
        var bytes = new Uint8Array([
            0x66, // Magic = 0x66 固定的报文 Magic
            0x02, 0x00, 0x00, 0x00, //ID = 0x00000001 报文 ID
            0x05,                   // MESSAGE_DISPLAY_SET_PIXELXY 0x05 报文类型
            13, 0x00,     // 报文长度 13
            0x02, 0x00, //X = 1
            0x00, 0x00, //Y = 0
            0x02 // 第二个颜色，红  
        ]);
        self.sendBytes(bytes.buffer);
    },        
    Send_SetPixel: function () {
        var self = this;        
        //包需要使用小端序        
        var bytes = new Uint8Array([
            0x66, // Magic = 0x66 固定的报文 Magic
            0x02, 0x00, 0x00, 0x00, //ID = 0x00000001 报文 ID
            0x04,                   // MESSAGE_DISPLAY_SET_PIXEL 0x04 报文类型
            11, 0x00,     // 报文长度 11
            self.data.currentIndex, 0x00, //index = self.data.currentIndex
            0x03 // 第三个颜色，绿
        ]);
        self.sendBytes(bytes.buffer);
        self.data.currentIndex += 1;
        if(self.data.currentIndex >= 10) {
            self.data.currentIndex = 0;
        }        
    },     
    Send: function () {
        var self = this
        var buffer = new ArrayBuffer(self.data.inputText.length)
        var dataView = new Uint8Array(buffer)
        for (var i = 0; i < self.data.inputText.length; i++) {
            dataView[i] = self.data.inputText.charCodeAt(i)
        }
        self.sendBytes(dataView);
    },
    sendBytes: function (buffer) {
        var self = this        
        if (self.data.connected) {
            console.log('已经连接了，准备发送报文');
            if (buffer.byteLength <= 20) {
                console.log('报文长度低于20，直接发送');
                console.log(buffer);
                wx.writeBLECharacteristicValue({
                    deviceId: self.data.connectedDeviceId,
                    serviceId: self.data.services[0].uuid,
                    characteristicId: self.data.characteristics[0].uuid,
                    value: buffer,
                    success: function (res) {
                        console.log('发送成功')
                    }
                });
            }
            else { //超过20字节需要分帧发送            
                console.log('报文长度大于20，分帧，实际长度=' + buffer.byteLength.toString());
                var packageIndex = 0;
                var sentLength = 0;
                for (var i = 0; i < buffer.byteLength; i += 20) {
                    var lengthToSend = Math.min(buffer.byteLength - sentLength, 20);
                    var frameView = new Uint8Array(buffer, i, lengthToSend);
                    wx.writeBLECharacteristicValue({
                        deviceId: self.data.connectedDeviceId,
                        serviceId: self.data.services[0].uuid,
                        characteristicId: self.data.characteristics[0].uuid,
                        value: frameView,
                        success: function (res) {
                            console.log('发送成功包：' + packageIndex.toString());
                        }
                    });
                    sentLength += lengthToSend;
                    packageIndex++;
                    // 至少等待 150ms
                    sleep(150);
                }
            }
        } else {
            wx.showModal({
                title: '提示',
                content: '蓝牙已断开',
                showCancel: false,
                success: function (res) {
                    self.setData({
                        searching: false
                    })
                }
            })
        }
    },
    onLoad: function (options) {
        var self = this
        console.log(options)
        self.setData({
            name: options.name,
            connectedDeviceId: options.connectedDeviceId
        })
        wx.getBLEDeviceServices({
            deviceId: self.data.connectedDeviceId,
            success: function (res) {
                console.log(res.services)
                self.setData({
                    services: res.services
                })
                wx.getBLEDeviceCharacteristics({
                    deviceId: options.connectedDeviceId,
                    serviceId: res.services[0].uuid,
                    success: function (res) {
                        console.log(res.characteristics)
                        self.setData({
                            characteristics: res.characteristics
                        })
                        wx.notifyBLECharacteristicValueChange({
                            state: true,
                            deviceId: options.connectedDeviceId,
                            serviceId: self.data.services[0].uuid,
                            characteristicId: self.data.characteristics[0].uuid,
                            success: function (res) {
                                console.log('启用notify成功')
                            }
                        })
                    }
                })
            }
        })
        wx.onBLEConnectionStateChange(function (res) {
            console.log(res.connected)
            self.setData({
                connected: res.connected
            })
        })
        wx.onBLECharacteristicValueChange(function (res) {
            var receiveText = app.buf2string(res.value)
            console.log('接收到数据：' + receiveText)
            self.setData({
                receiveText: receiveText
            })
        })
    },
    onReady: function () {

    },
    onShow: function () {

    },
    onHide: function () {

    },
    sleep: function (numberMillis) {
        var now = new Date();
        var exitTime = now.getTime() + numberMillis;
        while (true) {
            now = new Date();
            if (now.getTime() > exitTime) {
                return;
            }
        }
    }

})