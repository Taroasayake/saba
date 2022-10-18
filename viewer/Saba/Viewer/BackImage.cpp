//
// Copyright(c) 2016-2017 benikabocha.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#include "BackImage.h"

#include <GL/gl3w.h>

#include <Saba/GL/GLSLUtil.h>
#include <Saba/GL/GLShaderUtil.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform.hpp>

namespace saba
{
	BackImage::BackImage()
	{
	}

	bool BackImage::Initialize(const ViewerContext & ctxt)
	{
		if (m_prog == 0)
		{
			GLSLShaderUtil glslShaderUtil;
			glslShaderUtil.SetShaderDir(ctxt.GetShaderDir());
			m_prog = glslShaderUtil.CreateProgram("BackImage");
			if (m_prog == 0)
			{
				return false;
			}
		}


		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		float w = 1280;
		float h = 720;
		float sf = 0.03;

		static const GLfloat g_vertex_buffer_data[] = {
			sf * w * 0.5 * -1.0f,	0.0f,			0.0f,
			sf * w * 0.5 * 1.0f,	0.0f,			0.0f,
			sf* w * 0.5 * 1.0f,		sf * h * 1.0f,	0.0f,
			sf* w * 0.5 * -1.0f,	0.0f,			0.0f,
			sf* w * 0.5 * -1.0f,	sf* h * 1.0f,	0.0f,
			sf* w * 0.5 * 1.0f,		sf* h * 1.0f,	0.0f,
		};

		//1280/720


		GLfloat vertex_uv[] = { 
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
		};


		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


		
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uv), vertex_uv, GL_STATIC_DRAW);


		m_vertexPosition_modelspace = glGetAttribLocation(m_prog, "vertexPosition_modelspace");
		m_vertexUV = glGetAttribLocation(m_prog, "vertexUV");

		MatrixID = glGetUniformLocation(m_prog, "MVP");

		TextureID = glGetUniformLocation(m_prog, "myTextureSampler");

		glBindVertexArray(0);

		return true;
	}

	void BackImage::Draw(GLuint TexureId, float scale, float x, float y, float z)
	{
		glBindVertexArray(vao);

		glUseProgram(m_prog);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexureId);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(m_vertexPosition_modelspace);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			m_vertexPosition_modelspace,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(m_vertexUV);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		m_WVP = glm::translate(m_WVP, glm::vec3(x, y, z));
		m_WVP = glm::scale(m_WVP, glm::vec3(scale, scale, scale));

		SetUniform(MatrixID, m_WVP);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		
		glUseProgram(0);
		glBindVertexArray(0);

	}
}
