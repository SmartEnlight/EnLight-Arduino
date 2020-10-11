#include "BluetoothManager.h"

BluetoothManager::BluetoothManager(byte rx, byte tx) : bluetoothSerial(rx, tx) {

}

auto BluetoothManager::Begin(int baudrate) -> void {
    bluetoothSerial.begin(baudrate);
}

auto BluetoothManager::SerialRead() -> char {
    if (bluetoothSerial.available()) {
        return bluetoothSerial.read();
    } else {
        return '\0';
    }
}

auto BluetoothManager::SerialWrite(const char data) -> void {
    bluetoothSerial.write(data);
}

auto BluetoothManager::SerialWrite(const char data[]) -> void {
    bluetoothSerial.write(data);
}