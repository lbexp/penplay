#include <ApplicationServices/ApplicationServices.h>
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

void InitConnection() { isConnected = 1; }

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
    InitConnection();

    if (isConnected) {
        printf("Connected!");
    }

    while (isConnected) {
        Listen(ParseMouseMove);
    }

    printf("Disconnected.");

    return 0;
}

/*********************
 * Main - end
 *********************/
