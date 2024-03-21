#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// UUIDs for custom services
#define CUSTOM_SERVICE_UUID "CC4A6A80-51E0-11E3-B451-0002A5D5C51B"
#define DEVICE_INFORMATION_SERVICE_UUID "180A"
#define BATTERY_SERVICE_UUID "180F"
#define GENERIC_SERVICE_UUID "1804"
#define CUSTOM_SERVICE_UUID_2 "18FF"

// UUIDs for custom characteristics
#define CUSTOM_CHARACTERISTIC_UUID_1 "835AB4C0-51E4-11E3-A5BD-0002A5D5C51B"
#define CUSTOM_CHARACTERISTIC_UUID_2 "8CD67DA0-DA9B-11E3-9087-0002A5D5C51B"
#define ENVIRONMENTAL_SENSING_SERVICE_UUID "0000181A-0000-1000-8000-00805f9b34fb"
#define TEMPERATURE_MEASUREMENT_CHAR_UUID "2A1C" // Typically used for Temperature Measurement
#define MEASUREMENT_INTERVAL_CHAR_UUID    "2A21" // Typically used for Measurement Interval
#define BATTERY_LEVEL_CHAR_UUID "2A19"
#define GENERIC_CHAR_UUID "2A07"
#define CUSTOM_CHAR_UUID "2AFF"

// Declare characteristics
BLECharacteristic *customCharacteristic1;
BLECharacteristic *customCharacteristic2;
BLECharacteristic *temperatureMeasurementCharacteristic;
BLECharacteristic *measurementIntervalCharacteristic;
BLECharacteristic *batteryLevelChar;
BLECharacteristic *genericChar;
BLECharacteristic *customChar;

void setup() {
  BLEDevice::init("51224");

  BLEServer *pServer = BLEDevice::createServer();

  // Custom Service 1
  BLEService *customService1 = pServer->createService(CUSTOM_SERVICE_UUID);
  customCharacteristic1 = customService1->createCharacteristic(
    CUSTOM_CHARACTERISTIC_UUID_1,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );
  customCharacteristic2 = customService1->createCharacteristic(
    CUSTOM_CHARACTERISTIC_UUID_2,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );
  temperatureMeasurementCharacteristic = customService1->createCharacteristic(
    TEMPERATURE_MEASUREMENT_CHAR_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );
  measurementIntervalCharacteristic = customService1->createCharacteristic(
    MEASUREMENT_INTERVAL_CHAR_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );
  customService1->start();

  // Device Information Service
  BLEService *deviceInformationService = pServer->createService(DEVICE_INFORMATION_SERVICE_UUID);
  // Add characteristics such as Model Number, Serial Number, Firmware Revision, Manufacturer Name etc.
  // ...

  deviceInformationService->start();

  // Battery Service
  BLEService *batteryService = pServer->createService(BATTERY_SERVICE_UUID);
  batteryLevelChar = batteryService->createCharacteristic(
    BATTERY_LEVEL_CHAR_UUID,
    BLECharacteristic::PROPERTY_READ
  );
  // Set the initial battery level value
  batteryLevelChar->setValue("100");
  batteryService->start();

  // Generic Service (used for ESS in this example)
  BLEService *genericService = pServer->createService(GENERIC_SERVICE_UUID);
  genericChar = genericService->createCharacteristic(
    GENERIC_CHAR_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  genericService->start();

  // Custom Service 2
  BLEService *customService2 = pServer->createService(CUSTOM_SERVICE_UUID_2);
  customChar = customService2->createCharacteristic(
    CUSTOM_CHAR_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
  );
  customService2->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  BLEAdvertisementData advertisementData;

  // Set manufacturer data
  uint8_t manufacturerData[3] = {0x0C, 0x01, 0x03}; // Last two bytes can be your custom data
  advertisementData.setManufacturerData(std::string((char *)manufacturerData, sizeof(manufacturerData)));
  pAdvertising->setAdvertisementData(advertisementData);

  pAdvertising->addServiceUUID(CUSTOM_SERVICE_UUID);
  pAdvertising->addServiceUUID(DEVICE_INFORMATION_SERVICE_UUID);
  pAdvertising->addServiceUUID(BATTERY_SERVICE_UUID);
  pAdvertising->addServiceUUID(GENERIC_SERVICE_UUID);
  pAdvertising->addServiceUUID(CUSTOM_SERVICE_UUID_2);
  pAdvertising->setScanResponse(true);
  pAdvertising->start();
}

void loop() {
  // Nothing to do here, characteristics are static.
  delay(1000);
}
