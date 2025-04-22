#include <ApplicationServices/ApplicationServices.h>
#include <libusb-1.0/libusb.h>
#include <stdio.h>

/*********************
 * Mouse functionalities - start
 *********************/

void MouseMove(int x, int y) {
    CGPoint point = CGPointMake(x, y);
    CGEventRef moveEvent = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved,
                                                   point, kCGMouseButtonLeft);
    CGEventPost(kCGHIDEventTap, moveEvent);
    CFRelease(moveEvent);
}

void MouseClick(int x, int y) {
    CGPoint point = CGPointMake(x, y);

    CGEventRef mouseDown = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown,
                                                   point, kCGMouseButtonLeft);
    CGEventRef mouseUp = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp,
                                                 point, kCGMouseButtonLeft);

    CGEventPost(kCGHIDEventTap, mouseDown);
    CGEventPost(kCGHIDEventTap, mouseUp);

    CFRelease(mouseDown);
    CFRelease(mouseUp);
}

/*********************
 * Mouse functionalities - end
 *********************/

/*********************
 * Connection - start
 *********************/

libusb_context *ctx = NULL;
libusb_device_handle *dev = NULL;
int isConnected = 0;

#define GOOGLE_VID 0x18D1
#define ANDROID_PID 0x2D00

void InitConnection(libusb_context *ctx, libusb_device_handle *dev) {
    printf("Initialize connection...");

    while (!isConnected) {
        libusb_init(&ctx);
        dev = libusb_open_device_with_vid_pid(ctx, GOOGLE_VID, ANDROID_PID);
        libusb_claim_interface(dev, 0);

        if (dev) {
            isConnected = 1;
            printf("Connected!");
        }
    }
}

/**
 * Parsing 8 bytes of pen data
 */
void ParseData(char *data) {
    uint16_t x = data[0] | (data[1] << 8);
    uint16_t y = data[2] | (data[3] << 8);
    uint8_t pressure = data[4];
    uint8_t touch = data[5];
}

void Listen() {
    unsigned char data[64];
    int actualLength;
    int endpoint = 0x81;
    int r;

    r = libusb_interrupt_transfer(dev, endpoint, data, sizeof(data),
                                  &actualLength, 1000);

    if (r == 0 && actualLength > 0) {
        ParseData((char *)data);
    } else {
        printf("Failed to received: %s\n", libusb_error_name(r));
    }
}

/*********************
 * Connection - end
 *********************/

/*********************
 * Main - start
 *********************/

int main() {
    InitConnection(ctx, dev);

    while (isConnected) {
        Listen();
    }

    printf("Disconnected.");

    return 0;
}

/*********************
 * Main - end
 *********************/
