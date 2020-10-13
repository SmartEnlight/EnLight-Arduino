#pragma once
#include <SoftwareSerial.h>

namespace TinyModule {
    class Bluetooth {
    private:
        SoftwareSerial _bluetoothSerial;
    public:
        Bluetooth(uint8_t rx, uint8_t tx);
        
        auto Begin(int baudrate) -> void;
        auto SerialRead() -> char;
        auto SerialWrite(const char data) -> void;
        auto SerialWrite(const char data[]) -> void;
    };
}