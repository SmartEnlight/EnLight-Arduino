#pragma once
#include <SoftwareSerial.h>

class BluetoothManager {
private:
    SoftwareSerial bluetoothSerial;
public:
    BluetoothManager(byte rx, byte tx);
    
    auto Begin(int baudrate) -> void;
    auto SerialRead() -> char;
    auto SerialWrite(const char data) -> void;
    auto SerialWrite(const char data[]) -> void;
};