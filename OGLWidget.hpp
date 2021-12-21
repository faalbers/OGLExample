#ifndef OGLEXAMPLE_OGLWIDGET
#define OGLEXAMPLE_OGLWIDGET

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_2_Compatibility>
#include <QOpenGLVersionFunctionsFactory>
#include <string>
#include <fstream>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

// default OpenGL version is OpenGL SE 2.0
//class OGLWidget : public QOpenGLWidget, public QOpenGLFunctions
// create OGL widget compatible with OpenGL 3.2
class OGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_2_Compatibility
{
    Q_OBJECT
public:
    OGLWidget(QWidget *parent = nullptr);

    ShaderProgramSource  ParseShader(const std::string &filePath);
    unsigned int         CompileShader(unsigned int type, const std::string &source);
    unsigned int         CreateShaders(const std::string &vertexShader, const std::string &fragmentShader);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

#endif
