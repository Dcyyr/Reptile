#include"rppch.h"
#include"Shader.h"

#include<glad/glad.h>
#include<glm/gtc/type_ptr.hpp>

namespace Reptile {

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//创建一个空的顶点着色器句柄
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//向 GL 发送顶点着色器源代码
		//请注意，std::string 的.c_str 是以 NULL 字符结束的。
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
		//编译顶点着色器
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength 包括 NULL 字符
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			//
			glDeleteShader(vertexShader);

			RP_CORE_ERROR("{0}", infoLog.data());
			RP_CORE_ASSERT(false, "vertex shader failure");
			return;

		}

		//创建一个空的片段着色器句柄
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//向 GL 发送片段着色器源代码
		//请注意，std::string 的.c_str 是以 NULL 字符结束的。
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);
		//编译顶点着色器
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);


			RP_CORE_ERROR("{0}", infoLog.data());
			RP_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;

		}

		// 顶点着色器和片段着色器编译成功。
		// 现在是将它们连接到程序中的时候了。
		// 获取程序对象。
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		//将着色器附加到程序中
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		//连接我们的程序
		glLinkProgram(program);

		//注意这里的不同函数：glGetProgram* 而不是 glGetShader* 
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			//不要忘了着色器
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			RP_CORE_ERROR("{0}", infoLog.data());
			RP_CORE_ASSERT(false, "Shader link failure!");
			return;

		}

		//链接成功后，始终分离着色器。
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind()const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind()const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}