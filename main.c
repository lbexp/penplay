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

int isConnected = 0;

void InitConnection(libusb_context *ctx, libusb_device_handle *dev) {
    libusb_init(&ctx);
    // TODO: Adjust the dummy vid & pid into actual vid & pid
    dev = libusb_open_device_with_vid_pid(ctx, 0x18D1, 0x4EE7);
    libusb_claim_interface(dev, 0);

    if (dev) {
        isConnected = 1;
    }
}

void Listen(void (*cb)(char *)) {
    // TODO: Add logic to listen and invokes callback with the correct payload
    cb("test");
}

void ParseMouseMove(char *payload) {
    // TODO: Add logic to parse payload into mouse move data
    MouseMove(500, 500);
}

/*********************
 * Connection - end
 *********************/

/*********************
 * Main - start
 *********************/

int main() {
    printf("Initialize connection...");

    libusb_context *ctx = NULL;
    libusb_device_handle *dev = NULL;

    InitConnection(ctx, dev);

    if (isConnected) {
        printf("Connected!");
    }

    unsigned char data[64];
    int actualLength;
    int endpoint = 0x81;
    int r;

    while (isConnected) {
        Listen(ParseMouseMove);
        r = libusb_interrupt_transfer(dev, endpoint, data, sizeof(data),
                                      &actualLength, 1000);

        if (r == 0 && actualLength > 0) {
            printf("Received %d bytes: ", actualLength);

            for (int i = 0; i < actualLength; i++) {
                printf("%02X", data[i]);
            }

            printf("\n");
        } else {
            printf("Failed to received: %s\n", libusb_error_name(r));
        }
    }

    printf("Disconnected.");

    return 0;
}

/*********************
 * Main - end
 *********************/
