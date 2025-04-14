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

void initConnection() { isConnected = 1; }

/*********************
 * Connection - end
 *********************/

/*
 * Main - start
 */

int main() {
    initConnection();

    while (isConnected) {
        MouseMove(500, 500);
        printf("Hello world!");
    }

    return 0;
}

/*********************
 * Main - end
 *********************/
