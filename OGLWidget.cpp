#include "OGLWidget.hpp"

#include <iostream>



OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    std::cout << "Construct OGLWidget\n";
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    uint32_t buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    ShaderProgramSource source = ParseShader("../resources/shaders/Basic.shader");

    unsigned int shader = CreateShaders(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);
    //glColorMaterial(GL_AMBIENT_AND_DIFFUSE);
    //glColorMaterial(GL_FRONT_AND_BACK | GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);

    //uint32_t buffer;
    //glGenBuffers(1, &buffer);
}

void OGLWidget::paintGL()
{
    // if contect needs to be implemented in other place
    //QOpenGLFunctions_3_2_Compatibility *fa = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_2_Compatibility>();

    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    /*
    // draw a line
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f); 
    glEnd();

    // draw a triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5f, 0.0, 0.0f);
    glVertex3f(0.0f, -0.5, 0.0f); 
    glVertex3f(-0.5f, 0.0, 0.0f);
    glEnd();
    */
}

void OGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

ShaderProgramSource OGLWidget::ParseShader(const std::string &filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)) {
        if ( line.find("#shader") != std::string::npos ) {
            if ( line.find("vertex") != std::string::npos )
                type = ShaderType::VERTEX;
            else if ( line.find("fragment") != std::string::npos )
                type = ShaderType::FRAGMENT;
        } else {
            ss[(int)type] << line << std::endl;
        }
    }

    stream.close();

    return { ss[0].str(), ss[1].str() };
}

unsigned int OGLWidget::CompileShader(unsigned int type, const std::string &source)
{
    QOpenGLFunctions_3_2_Compatibility *fa = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_2_Compatibility>();

    unsigned int id = fa->glCreateShader(type);
    const char *src = source.c_str();
    // although src is a pointer, it needs the pointer to that pointer
    // nullptr means string is null ended
    fa->glShaderSource(id, 1, &src, nullptr);
    fa->glCompileShader(id);

    int result;
    fa->glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if ( result == GL_FALSE ) {
        int length;
        fa->glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        auto message = new char[length];
        fa->glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << std::endl;
        std::cout << message << std::endl;
        delete[] message;
        fa->glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int OGLWidget::CreateShaders(const std::string &vertexShader, const std::string &fragmentShader)
{
    QOpenGLFunctions_3_2_Compatibility *fa = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_2_Compatibility>();
    
    unsigned int program = fa->glCreateProgram();
    
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    fa->glAttachShader(program, vs);
    fa->glAttachShader(program, fs);
    fa->glLinkProgram(program);
    fa->glValidateProgram(program);

    // since they are already linked , they can be deleted now
    fa->glDeleteShader(vs);
    fa->glDeleteShader(fs);

    return program;
}