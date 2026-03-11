#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DEVICE_COUNT 10

typedef enum {
    TEMPERATURE_SENSOR = 1,
    PRESSURE_SENSOR = 2,
    BATTERY_SENSOR = 3
} DeviceType;

struct Device {
    char name[30];
    int type;
    union {
        float temperature;
        int pressure;
        float voltage;
    } reading;
};

typedef void (*DeviceCallback)(struct Device *);

void battery_monitor(struct Device *device) {
    if (device->reading.voltage < 3.3f) {
        printf("%s: Battery Low (%.2f V)\n", device->name, device->reading.voltage);
    } else {
        printf("%s: Battery OK (%.2f V)\n", device->name, device->reading.voltage);
    }
}

void temperature_monitor(struct Device *device) {
    if (device->reading.temperature > 60.0f) {
        printf("%s: HIGH TEMP ALERT (%.2f C)\n", device->name, device->reading.temperature);
    } else {
        printf("%s: Temperature Normal (%.2f C)\n", device->name, device->reading.temperature);
    }
}

void pressure_monitor(struct Device *device) {
    if (device->reading.pressure > 130) {
        printf("%s: HIGH PRESSURE ALERT (%d kPa)\n", device->name, device->reading.pressure);
    } else {
        printf("%s: Pressure Normal (%d kPa)\n", device->name, device->reading.pressure);
    }
}

void anomaly_score_monitor(struct Device *device) {
    float score = 0.0f;

    if (device->type == TEMPERATURE_SENSOR) {
        score = (device->reading.temperature / 100.0f) * 100.0f;
    } else if (device->type == PRESSURE_SENSOR) {
        score = (device->reading.pressure / 200.0f) * 100.0f;
    } else if (device->type == BATTERY_SENSOR) {
        score = ((4.5f - device->reading.voltage) / 1.5f) * 100.0f;
    }

    if (score < 0.0f) {
        score = 0.0f;
    }
    if (score > 100.0f) {
        score = 100.0f;
    }

    printf("%s: Custom Callback - Anomaly Score %.2f/100\n", device->name, score);
}

void process_device(struct Device *device, void (*callback)(struct Device *)) {
    callback(device);
}

void assign_random_reading(struct Device *device) {
    if (device->type == TEMPERATURE_SENSOR) {
        device->reading.temperature = 20.0f + ((float)rand() / RAND_MAX) * 70.0f;
    } else if (device->type == PRESSURE_SENSOR) {
        device->reading.pressure = 80 + (rand() % 81);
    } else {
        device->reading.voltage = 3.0f + ((float)rand() / RAND_MAX) * 1.5f;
    }
}

void print_raw_reading(struct Device *device) {
    if (device->type == TEMPERATURE_SENSOR) {
        printf("%s -> Temperature: %.2f C\n", device->name, device->reading.temperature);
    } else if (device->type == PRESSURE_SENSOR) {
        printf("%s -> Pressure: %d kPa\n", device->name, device->reading.pressure);
    } else {
        printf("%s -> Voltage: %.2f V\n", device->name, device->reading.voltage);
    }
}

int main(void) {
    struct Device *devices;
    int index;

    srand((unsigned int)time(NULL));

    devices = (struct Device *)malloc(sizeof(struct Device) * DEVICE_COUNT);
    if (devices == NULL) {
        printf("Memory allocation failed for devices.\n");
        return 1;
    }

    printf("Custom Callback: anomaly_score_monitor\n");
    printf("Device array memory address: %p\n\n", (void *)devices);

    for (index = 0; index < DEVICE_COUNT; index++) {
        struct Device *current = devices + index;

        if (index % 3 == 0) {
            strcpy(current->name, "TempSensor");
            current->type = TEMPERATURE_SENSOR;
        } else if (index % 3 == 1) {
            strcpy(current->name, "PressureSensor");
            current->type = PRESSURE_SENSOR;
        } else {
            strcpy(current->name, "BatterySensor");
            current->type = BATTERY_SENSOR;
        }

        assign_random_reading(current);
    }

    printf("Simulating 10 random device readings...\n\n");
    for (index = 0; index < DEVICE_COUNT; index++) {
        struct Device *current = devices + index;
        print_raw_reading(current);

        if (current->type == TEMPERATURE_SENSOR) {
            process_device(current, temperature_monitor);
        } else if (current->type == PRESSURE_SENSOR) {
            process_device(current, pressure_monitor);
        } else {
            process_device(current, battery_monitor);
        }

        process_device(current, anomaly_score_monitor);
    }

    free(devices);
    return 0;
}