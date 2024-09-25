#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <polygon.h>
#include <rasterizer.h>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DisplayQImage(QImage &i);

    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_actionLoad_Scene_triggered();

    void on_actionSave_Image_triggered();

    void on_actionEquilateral_Triangle_triggered();

    void on_actionQuit_Esc_triggered();

    void on_actionNone_triggered();

    void on_actionLambertian_triggered();

    void on_actionToon1_triggered();

    void on_actionToon2_triggered();

    void on_actionBlinn_Phong_triggered();

    void on_actionIridescent_triggered();

    void on_actionLine_triggered();

private:
    Ui::MainWindow *ui;
    Polygon LoadOBJ(const QString &file, const QString &polyName);

    //This is used to display the QImage produced by RenderScene in the GUI
    QGraphicsScene graphics_scene;

    //This is the image rendered by your program when it loads a scene
    QImage rendered_image;

    //The instance of the Rasterizer used to render our scene
    Rasterizer rasterizer;

    // String for reflection model mode selecting
    string mode;

    // Store AA value
    int AA;
};

#endif // MAINWINDOW_H
