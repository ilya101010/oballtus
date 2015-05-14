#pragma once
#include "libs.h"

namespace GLIZ
{
    class Shader
    {
        string name;
        string ShaderText;
        GLenum ShaderType;
    public:
        GLuint ShaderIndex;
        inline static string ShaderTypeName(GLenum ShaderType)
        {
            switch(ShaderType)
            {
                case GL_VERTEX_SHADER: return "vertex";
                case GL_GEOMETRY_SHADER: return "geometry";
                case GL_FRAGMENT_SHADER: return "fragment";
                default: return "unknown";
            }
        }
        inline static string ReadEntireFile(const string& path)
        {
            ifstream f;
            f.open(path.c_str());
            if(!f.is_open())
            {
                char msg[1024];
                sprintf(msg, "Cannot open file %s", path.c_str());
                // Throw(msg); TODO: exception handling
            }
            //
            string line, result;
            //
            while (f)
            {
                getline(f, line);
                result += line + "\n";
            }
            //
            for (int j = 0; j < result.length(); j++)
            {
                unsigned char c = result[j];
                if (c >= 128) result[j] = ' ';
            }
            return result;
        }
        inline void Create()
        {
            ShaderIndex = glCreateShader(ShaderType);
            ShaderText = ReadEntireFile(name);
            const char *strFileData = ShaderText.c_str();
            glShaderSource(ShaderIndex, 1, &strFileData, NULL);
            //
            glCompileShader(ShaderIndex);
            //
            GLint status = 0;
            glGetShaderiv(ShaderIndex, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
                GLint infoLogLength;
                glGetShaderiv(ShaderIndex, GL_INFO_LOG_LENGTH, &infoLogLength);
                //
                GLchar *strInfoLog = new GLchar[infoLogLength + 1];
                glGetShaderInfoLog(ShaderIndex, infoLogLength, NULL, strInfoLog);
                //
                char msg[4*4096];
                sprintf(msg, "Compile failure in %s shader:\n%s\n----\n",
                        ShaderTypeName(ShaderType).c_str(), strInfoLog //, shaderText.c_str()
                );
                printf(msg);
                delete[] strInfoLog;
                // Throw(msg); TODO: exception handling
            }
        }
        Shader(const string& name, GLenum ShaderType)
        {
            this->name=name;
            this->ShaderType=ShaderType;
            Create();
        }
    };

    class ShaderProgram
    {
        // shader types: vertex, fragment, geometry...
        map<int, Shader*> shaders;
        string name;
        inline static string ShaderSuffix(GLenum ShaderType)
        {
            switch(ShaderType)
            {
                case GL_VERTEX_SHADER: return ".v";
                case GL_FRAGMENT_SHADER: return ".f";
                case GL_GEOMETRY_SHADER: return ".g";
                default: return "._";
            }
        }

    public:
        GLuint ID;
        void AddShader(GLenum ShaderType)
        {
            string ShaderName = name+ShaderSuffix(ShaderType)+".glsl.c";
            Shader* shader = new Shader(ShaderName, ShaderType);
            shaders[ShaderType]=shader;
        }

        void Create()
        {
            ID = glCreateProgram();
            for(map<int, Shader*>::const_iterator i = shaders.begin(); i != shaders.end(); ++i)
                glAttachShader(ID,i->second->ShaderIndex);
            glLinkProgram(ID);
            GLint flink, fval;
            glGetProgramiv(ID,GL_LINK_STATUS, &flink);
            if(!flink)
            {
                char msg[4096];
                GLsizei size = sizeof(msg);
                glGetProgramInfoLog(ID,size,&size,msg);
                cout << "ERROR: Shader Program Link failed:" << endl;
                cout << msg << endl;
                // TODO: exception handling
            }
            glValidateProgram(ID);
            glGetProgramiv(ID,GL_VALIDATE_STATUS, &fval);
            if(!fval)
            {
                char msg[4096];
                GLsizei size = sizeof(msg);
                glGetProgramInfoLog(ID,size,&size,msg);
                cout << "ERROR: Shader Program Validate failed:" << endl;
                cout << msg << endl;
                // TODO: exception handling
            }
            cout << "Shader Program Success!" << endl;
        }

        ShaderProgram(string name)
        {
            this->name=name; // name == path
        }


    };

}