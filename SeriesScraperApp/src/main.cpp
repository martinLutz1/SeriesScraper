#include "application.h"
#include "message.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    qRegisterMetaType<Message>("Message");
    app.init();
    return app.exec();
}
