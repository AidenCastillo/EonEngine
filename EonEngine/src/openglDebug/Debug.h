#pragma once
#include <glad/glad.h>

void glDebugOutput(GLenum source,
	GLenum  type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
	);