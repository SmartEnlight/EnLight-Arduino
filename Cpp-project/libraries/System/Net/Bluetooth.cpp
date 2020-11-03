#include "Bluetooth.hpp"

namespace System::Net {
    Bluetooth::Bluetooth(uint8_t rx, uint8_t tx) : _bluetoothSerial(rx, tx) {

    }

    auto Bluetooth::Begin(int baudrate) -> void {
        _bluetoothSerial.begin(baudrate);
    }

    auto Bluetooth::SerialRead() -> char {
        if (_bluetoothSerial.available()) {
            return _bluetoothSerial.read();
        } else {
            return '\0';
        }
    }

    auto Bluetooth::SerialWrite(const char data) -> void {
        _bluetoothSerial.write(data);
    }

    auto Bluetooth::SerialWrite(const char data[]) -> void {
        _bluetoothSerial.write(data);
    }
}