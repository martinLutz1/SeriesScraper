#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
class MainWindow;
class JsonParser;

class Application
{

public:
    Application(int &argc, char *argv[]);
    ~Application();

    // Initialzie the application
    void init();

    // Execute the application
    int exec();

    void setEpisode(int index, QString episode);


private:
    // Dont derive form QApplication
    QApplication app;

    // Create view after QApplication
    MainWindow* view;
    JsonParser* jsonParser;

    QStringList episodes;

public slots:
    //void onCellChanged(int row, int coloumn);

};

#endif // APPLICATION_H
