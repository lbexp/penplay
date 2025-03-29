#include <ApplicationServices/ApplicationServices.h>

class MouseEvent {
  public:
    static void move(int x, int y);
    static void click(int x, int y);
};
