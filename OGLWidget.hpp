#ifndef OGLEXAMPLE_OGLWIDGET
#define OGLEXAMPLE_OGLWIDGET

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_2_Compatibility>

// default OpenGL version is OpenGL SE 2.0
//class OGLWidget : public QOpenGLWidget, public QOpenGLFunctions
// create OGL widget compatible with OpenGL 3.2
class OGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_2_Compatibility
{
    Q_OBJECT
public:
    OGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

#endif
