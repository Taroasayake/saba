//
// Copyright(c) 2016-2017 benikabocha.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

#include "ViewerContext.h"

#include "../GL/GLObject.h"
#include "../GL/GLVertexUtil.h"

namespace saba
{
	class BackImage
	{
	public:
		BackImage();

		bool Initialize(const ViewerContext& ctxt);

		void SetWVPMatrix(const glm::mat4 wvp) { m_WVP = wvp; }

		void Draw(GLuint TexureId, float scale, float x,float y, float z);

	private:
		GLProgramObject	m_prog;


		GLuint vao;
		GLuint vertexbuffer;
		GLuint uvbuffer;


		int m_vertexPosition_modelspace;
		int m_vertexUV;
		GLuint MatrixID;
		GLuint TextureID;

		//GLint		m_uWVP;
		glm::mat4	m_WVP;

	};
}

