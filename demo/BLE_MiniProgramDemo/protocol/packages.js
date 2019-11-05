var sf = require('./struct-fu');

const LedMatrixPackageHeader = sf.struct('header', [ 
    sf.uint8('magic'),
    sf.uint32le('id'),
    sf.uint8('type'),
    sf.uint16le('size'),
]);


function parseHeader(buffer) {    
    return LedMatrixPackageHeader.unpack(buffer);
}


function pack(packageID, type, data) {    
    let packagesize = 8 + data.byteLength;
    let headerValues = {
        'magic':    0x66,
        'id':       packageID,        
        'type':     type,
        'size':     packagesize
    };
    let headerBuffer = LedMatrixPackageHeader.pack(headerValues);
    let buffer = new ArrayBuffer(packagesize);
    var dataView = new Uint8Array(buffer);
    dataView.set(new Uint8Array(headerBuffer), 0);
    dataView.set(new Uint8Array(data), 8);
    return dataView.buffer;
}

function packNotification(type, data) {
    var id = Math.round(new Date().getTime() / 1000);
    return pack(id, type, data);
}

module.exports = {
    LedMatrixPackageHeader: LedMatrixPackageHeader,

    parseHeader: parseHeader,
    pack: pack,
    packNotification: packNotification,
}