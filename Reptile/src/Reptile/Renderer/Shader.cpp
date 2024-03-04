#include"rppch.h"
#include"Shader.h"

#include<glad/glad.h>
#include<glm/gtc/type_ptr.hpp>

namespace Reptile {

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//����һ���յĶ�����ɫ�����
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//�� GL ���Ͷ�����ɫ��Դ����
		//��ע�⣬std::string ��.c_str ���� NULL �ַ������ġ�
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
		//���붥����ɫ��
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength ���� NULL �ַ�
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			//
			glDeleteShader(vertexShader);

			RP_CORE_ERROR("{0}", infoLog.data());
			RP_CORE_ASSERT(false, "vertex shader failure");
			return;

		}

		//����һ���յ�Ƭ����ɫ�����
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//�� GL ����Ƭ����ɫ��Դ����
		//��ע�⣬std::string ��.c_str ���� NULL �ַ������ġ�
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);
		//���붥����ɫ��
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

		// ������ɫ����Ƭ����ɫ������ɹ���
		// �����ǽ��������ӵ������е�ʱ���ˡ�
		// ��ȡ�������
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		//����ɫ�����ӵ�������
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		//�������ǵĳ���
		glLinkProgram(program);

		//ע������Ĳ�ͬ������glGetProgram* ������ glGetShader* 
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			//��Ҫ������ɫ��
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			RP_CORE_ERROR("{0}", infoLog.data());
			RP_CORE_ASSERT(false, "Shader link failure!");
			return;

		}

		//���ӳɹ���ʼ�շ�����ɫ����
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