/**
 *	@file	glext_inl.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GLEXT_INL_HPP
#define BKSGE_RENDER_GL_INL_GLEXT_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_api.hpp>

#if defined(__APPLE__)

#import <mach-o/dyld.h>
#import <stdlib.h>
#import <string.h>

static void* NSGLGetProcAddress(const char* name)
{
	NSSymbol symbol;
	char* symbolName;
	symbolName = (char*)malloc(strlen(name) + 2);
	strcpy(symbolName + 1, name);
	symbolName[0] = '_';
	symbol = NULL;
	if (NSIsSymbolNameDefined(symbolName))
	{
		symbol = NSLookupAndBindSymbol(symbolName);
	}
	free(symbolName);
	return symbol ? NSAddressOfSymbol(symbol) : NULL;
}

#endif	// defined(__APPLE__)

BKSGE_WARNING_PUSH()
#if defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION >= 80000)
BKSGE_WARNING_DISABLE_GCC("-Wcast-function-type")
#endif

#if defined(_WIN32)
#  define BKSGE_GL_GET_PROC_ADDRESS(name) wglGetProcAddress((LPCSTR)name)
#elif defined(__APPLE__)
#  define BKSGE_GL_GET_PROC_ADDRESS(name) NSGLGetProcAddress(name)
#elif defined(__sgi) || defined(__sun)
#  define BKSGE_GL_GET_PROC_ADDRESS(name) dlGetProcAddress(name)
#elif defined(__ANDROID__)
#  define BKSGE_GL_GET_PROC_ADDRESS(name) NULL /* TODO */
#else /* __linux */
#  define BKSGE_GL_GET_PROC_ADDRESS(name) (*glXGetProcAddressARB)((const GLubyte*)name)
#endif

#define BKSGE_GLEXT_FUNC(funcptr, funcname, ...)	\
	static funcptr p = (funcptr)BKSGE_GL_GET_PROC_ADDRESS(#funcname);	\
	if (p)	\
	{	\
		return p(__VA_ARGS__);	\
	}

// GL_VERSION_1_5

BKSGE_INLINE void APIENTRY glGenQueries(GLsizei n, GLuint* ids)
{
	BKSGE_GLEXT_FUNC(PFNGLGENQUERIESPROC, glGenQueries, n, ids);
}

BKSGE_INLINE void APIENTRY glDeleteQueries(GLsizei n, const GLuint* ids)
{
	BKSGE_GLEXT_FUNC(PFNGLDELETEQUERIESPROC, glDeleteQueries, n, ids);
}

BKSGE_INLINE void APIENTRY glBindBuffer(GLenum target, GLuint buffer)
{
	BKSGE_GLEXT_FUNC(PFNGLBINDBUFFERPROC, glBindBuffer, target, buffer);
}

BKSGE_INLINE void APIENTRY glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	BKSGE_GLEXT_FUNC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers, n, buffers);
}

BKSGE_INLINE void APIENTRY glGenBuffers(GLsizei n, GLuint* buffers)
{
	BKSGE_GLEXT_FUNC(PFNGLGENBUFFERSPROC, glGenBuffers, n, buffers);
}

BKSGE_INLINE void APIENTRY glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	BKSGE_GLEXT_FUNC(PFNGLBUFFERDATAPROC, glBufferData, target, size, data, usage);
}

// GL_VERSION_2_0

//BKSGE_INLINE void APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
//BKSGE_INLINE void APIENTRY glDrawBuffers(GLsizei n, const GLenum* bufs);
//BKSGE_INLINE void APIENTRY glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
//BKSGE_INLINE void APIENTRY glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
//BKSGE_INLINE void APIENTRY glStencilMaskSeparate(GLenum face, GLuint mask);

BKSGE_INLINE void APIENTRY glAttachShader(GLuint program, GLuint shader)
{
	BKSGE_GLEXT_FUNC(PFNGLATTACHSHADERPROC, glAttachShader, program, shader);
}

//BKSGE_INLINE void APIENTRY glBindAttribLocation(GLuint program, GLuint index, const GLchar* name);

BKSGE_INLINE void APIENTRY glCompileShader(GLuint shader)
{
	BKSGE_GLEXT_FUNC(PFNGLCOMPILESHADERPROC, glCompileShader, shader);
}

BKSGE_INLINE GLuint APIENTRY glCreateProgram(void)
{
	BKSGE_GLEXT_FUNC(PFNGLCREATEPROGRAMPROC, glCreateProgram);
	return 0u;
}

BKSGE_INLINE GLuint APIENTRY glCreateShader(GLenum type)
{
	BKSGE_GLEXT_FUNC(PFNGLCREATESHADERPROC, glCreateShader, type);
	return 0u;
}

BKSGE_INLINE void APIENTRY glDeleteProgram(GLuint program)
{
	BKSGE_GLEXT_FUNC(PFNGLDELETEPROGRAMPROC, glDeleteProgram, program);
}

BKSGE_INLINE void APIENTRY glDeleteShader(GLuint shader)
{
	BKSGE_GLEXT_FUNC(PFNGLDELETESHADERPROC, glDeleteShader, shader);
}

//BKSGE_INLINE void APIENTRY glDetachShader(GLuint program, GLuint shader);

BKSGE_INLINE void APIENTRY glDisableVertexAttribArray(GLuint index)
{
	BKSGE_GLEXT_FUNC(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray, index);
}

BKSGE_INLINE void APIENTRY glEnableVertexAttribArray(GLuint index)
{
	BKSGE_GLEXT_FUNC(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray, index);
}

//BKSGE_INLINE void APIENTRY glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
//BKSGE_INLINE void APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
//BKSGE_INLINE void APIENTRY glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
//BKSGE_INLINE GLint APIENTRY glGetAttribLocation(GLuint program, const GLchar* name);

BKSGE_INLINE void APIENTRY glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	BKSGE_GLEXT_FUNC(PFNGLGETPROGRAMIVPROC, glGetProgramiv, program, pname, params);
}

BKSGE_INLINE void APIENTRY glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	BKSGE_GLEXT_FUNC(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog, program, bufSize, length, infoLog);
}

BKSGE_INLINE void APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	BKSGE_GLEXT_FUNC(PFNGLGETSHADERIVPROC, glGetShaderiv, shader, pname, params);
}

BKSGE_INLINE void APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	BKSGE_GLEXT_FUNC(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog, shader, bufSize, length, infoLog);
}

//BKSGE_INLINE void APIENTRY glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);
//BKSGE_INLINE GLint APIENTRY glGetUniformLocation(GLuint program, const GLchar* name);
//BKSGE_INLINE void APIENTRY glGetUniformfv(GLuint program, GLint location, GLfloat* params);
//BKSGE_INLINE void APIENTRY glGetUniformiv(GLuint program, GLint location, GLint* params);
//BKSGE_INLINE void APIENTRY glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params);
//BKSGE_INLINE void APIENTRY glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params);
//BKSGE_INLINE void APIENTRY glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params);
//BKSGE_INLINE void APIENTRY glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer);
//BKSGE_INLINE GLboolean APIENTRY glIsProgram(GLuint program);
//BKSGE_INLINE GLboolean APIENTRY glIsShader(GLuint shader);

BKSGE_INLINE void APIENTRY glLinkProgram(GLuint program)
{
	BKSGE_GLEXT_FUNC(PFNGLLINKPROGRAMPROC, glLinkProgram, program);
}

BKSGE_INLINE void APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length)
{
	BKSGE_GLEXT_FUNC(PFNGLSHADERSOURCEPROC, glShaderSource, shader, count, string, length);
}

BKSGE_INLINE void APIENTRY glUseProgram(GLuint program)
{
	BKSGE_GLEXT_FUNC(PFNGLUSEPROGRAMPROC, glUseProgram, program);
}

//BKSGE_INLINE void APIENTRY glUniform1f(GLint location, GLfloat v0);
//BKSGE_INLINE void APIENTRY glUniform2f(GLint location, GLfloat v0, GLfloat v1);
//BKSGE_INLINE void APIENTRY glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
//BKSGE_INLINE void APIENTRY glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
//BKSGE_INLINE void APIENTRY glUniform1i(GLint location, GLint v0);
//BKSGE_INLINE void APIENTRY glUniform2i(GLint location, GLint v0, GLint v1);
//BKSGE_INLINE void APIENTRY glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
//BKSGE_INLINE void APIENTRY glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
//BKSGE_INLINE void APIENTRY glUniform1fv(GLint location, GLsizei count, const GLfloat* value);
//BKSGE_INLINE void APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat* value);
//BKSGE_INLINE void APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat* value);
//BKSGE_INLINE void APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat* value);
//BKSGE_INLINE void APIENTRY glUniform1iv(GLint location, GLsizei count, const GLint* value);
//BKSGE_INLINE void APIENTRY glUniform2iv(GLint location, GLsizei count, const GLint* value);
//BKSGE_INLINE void APIENTRY glUniform3iv(GLint location, GLsizei count, const GLint* value);
//BKSGE_INLINE void APIENTRY glUniform4iv(GLint location, GLsizei count, const GLint* value);
//BKSGE_INLINE void APIENTRY glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//BKSGE_INLINE void APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//BKSGE_INLINE void APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
//BKSGE_INLINE void APIENTRY glValidateProgram(GLuint program);
//BKSGE_INLINE void APIENTRY glVertexAttrib1d(GLuint index, GLdouble x);
//BKSGE_INLINE void APIENTRY glVertexAttrib1dv(GLuint index, const GLdouble* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib1f(GLuint index, GLfloat x);
//BKSGE_INLINE void APIENTRY glVertexAttrib1fv(GLuint index, const GLfloat* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib1s(GLuint index, GLshort x);
//BKSGE_INLINE void APIENTRY glVertexAttrib1sv(GLuint index, const GLshort* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y);
//BKSGE_INLINE void APIENTRY glVertexAttrib2dv(GLuint index, const GLdouble* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
//BKSGE_INLINE void APIENTRY glVertexAttrib2fv(GLuint index, const GLfloat* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib2s(GLuint index, GLshort x, GLshort y);
//BKSGE_INLINE void APIENTRY glVertexAttrib2sv(GLuint index, const GLshort* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);
//BKSGE_INLINE void APIENTRY glVertexAttrib3dv(GLuint index, const GLdouble* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
//BKSGE_INLINE void APIENTRY glVertexAttrib3fv(GLuint index, const GLfloat* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z);
//BKSGE_INLINE void APIENTRY glVertexAttrib3sv(GLuint index, const GLshort* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4Nbv(GLuint index, const GLbyte* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4Niv(GLuint index, const GLint* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4Nsv(GLuint index, const GLshort* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
//BKSGE_INLINE void APIENTRY glVertexAttrib4Nubv(GLuint index, const GLubyte* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4Nuiv(GLuint index, const GLuint* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4Nusv(GLuint index, const GLushort* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4bv(GLuint index, const GLbyte* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
//BKSGE_INLINE void APIENTRY glVertexAttrib4dv(GLuint index, const GLdouble* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
//BKSGE_INLINE void APIENTRY glVertexAttrib4fv(GLuint index, const GLfloat* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4iv(GLuint index, const GLint* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
//BKSGE_INLINE void APIENTRY glVertexAttrib4sv(GLuint index, const GLshort* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4ubv(GLuint index, const GLubyte* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4uiv(GLuint index, const GLuint* v);
//BKSGE_INLINE void APIENTRY glVertexAttrib4usv(GLuint index, const GLushort* v);

BKSGE_INLINE void APIENTRY glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	BKSGE_GLEXT_FUNC(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer, index, size, type, normalized, stride, pointer);
}

// GL_VERSION_3_0

//BKSGE_INLINE void APIENTRY glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
//BKSGE_INLINE void APIENTRY glGetBooleani_v(GLenum target, GLuint index, GLboolean* data);
//BKSGE_INLINE void APIENTRY glGetIntegeri_v(GLenum target, GLuint index, GLint* data);
//BKSGE_INLINE void APIENTRY glEnablei(GLenum target, GLuint index);
//BKSGE_INLINE void APIENTRY glDisablei(GLenum target, GLuint index);
//BKSGE_INLINE GLboolean APIENTRY glIsEnabledi(GLenum target, GLuint index);
//BKSGE_INLINE void APIENTRY glBeginTransformFeedback(GLenum primitiveMode);
//BKSGE_INLINE void APIENTRY glEndTransformFeedback(void);
//BKSGE_INLINE void APIENTRY glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
//BKSGE_INLINE void APIENTRY glBindBufferBase(GLenum target, GLuint index, GLuint buffer);
//BKSGE_INLINE void APIENTRY glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode);
//BKSGE_INLINE void APIENTRY glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
//BKSGE_INLINE void APIENTRY glClampColor(GLenum target, GLenum clamp);
//BKSGE_INLINE void APIENTRY glBeginConditionalRender(GLuint id, GLenum mode);
//BKSGE_INLINE void APIENTRY glEndConditionalRender(void);
//BKSGE_INLINE void APIENTRY glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
//BKSGE_INLINE void APIENTRY glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params);
//BKSGE_INLINE void APIENTRY glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params);
//BKSGE_INLINE void APIENTRY glVertexAttribI1i(GLuint index, GLint x);
//BKSGE_INLINE void APIENTRY glVertexAttribI2i(GLuint index, GLint x, GLint y);
//BKSGE_INLINE void APIENTRY glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z);
//BKSGE_INLINE void APIENTRY glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w);
//BKSGE_INLINE void APIENTRY glVertexAttribI1ui(GLuint index, GLuint x);
//BKSGE_INLINE void APIENTRY glVertexAttribI2ui(GLuint index, GLuint x, GLuint y);
//BKSGE_INLINE void APIENTRY glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z);
//BKSGE_INLINE void APIENTRY glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
//BKSGE_INLINE void APIENTRY glVertexAttribI1iv(GLuint index, const GLint* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI2iv(GLuint index, const GLint* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI3iv(GLuint index, const GLint* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI4iv(GLuint index, const GLint* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI1uiv(GLuint index, const GLuint* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI2uiv(GLuint index, const GLuint* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI3uiv(GLuint index, const GLuint* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI4uiv(GLuint index, const GLuint* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI4bv(GLuint index, const GLbyte* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI4sv(GLuint index, const GLshort* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI4ubv(GLuint index, const GLubyte* v);
//BKSGE_INLINE void APIENTRY glVertexAttribI4usv(GLuint index, const GLushort* v);
//BKSGE_INLINE void APIENTRY glGetUniformuiv(GLuint program, GLint location, GLuint* params);
//BKSGE_INLINE void APIENTRY glBindFragDataLocation(GLuint program, GLuint color, const GLchar* name);
//BKSGE_INLINE GLint APIENTRY glGetFragDataLocation(GLuint program, const GLchar* name);
//BKSGE_INLINE void APIENTRY glUniform1ui(GLint location, GLuint v0);
//BKSGE_INLINE void APIENTRY glUniform2ui(GLint location, GLuint v0, GLuint v1);
//BKSGE_INLINE void APIENTRY glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
//BKSGE_INLINE void APIENTRY glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
//BKSGE_INLINE void APIENTRY glUniform1uiv(GLint location, GLsizei count, const GLuint* value);
//BKSGE_INLINE void APIENTRY glUniform2uiv(GLint location, GLsizei count, const GLuint* value);
//BKSGE_INLINE void APIENTRY glUniform3uiv(GLint location, GLsizei count, const GLuint* value);
//BKSGE_INLINE void APIENTRY glUniform4uiv(GLint location, GLsizei count, const GLuint* value);
//BKSGE_INLINE void APIENTRY glTexParameterIiv(GLenum target, GLenum pname, const GLint* params);
//BKSGE_INLINE void APIENTRY glTexParameterIuiv(GLenum target, GLenum pname, const GLuint* params);
//BKSGE_INLINE void APIENTRY glGetTexParameterIiv(GLenum target, GLenum pname, GLint* params);
//BKSGE_INLINE void APIENTRY glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params);
//BKSGE_INLINE void APIENTRY glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value);
//BKSGE_INLINE void APIENTRY glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value);
//BKSGE_INLINE void APIENTRY glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value);
//BKSGE_INLINE void APIENTRY glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
//BKSGE_INLINE const GLubyte* APIENTRY glGetStringi(GLenum name, GLuint index);
//BKSGE_INLINE GLboolean APIENTRY glIsRenderbuffer(GLuint renderbuffer);
//BKSGE_INLINE void APIENTRY glBindRenderbuffer(GLenum target, GLuint renderbuffer);
//BKSGE_INLINE void APIENTRY glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers);
//BKSGE_INLINE void APIENTRY glGenRenderbuffers(GLsizei n, GLuint* renderbuffers);
//BKSGE_INLINE void APIENTRY glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params);
//BKSGE_INLINE GLboolean APIENTRY glIsFramebuffer(GLuint framebuffer);

BKSGE_INLINE void APIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	BKSGE_GLEXT_FUNC(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer, target, framebuffer);
}

BKSGE_INLINE void APIENTRY glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	BKSGE_GLEXT_FUNC(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers, n, framebuffers);
}

BKSGE_INLINE void APIENTRY glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	BKSGE_GLEXT_FUNC(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers, n, framebuffers);
}

//BKSGE_INLINE GLenum APIENTRY glCheckFramebufferStatus(GLenum target);
//BKSGE_INLINE void APIENTRY glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);

BKSGE_INLINE void APIENTRY glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	BKSGE_GLEXT_FUNC(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D, target, attachment, textarget, texture, level);
}

//BKSGE_INLINE void APIENTRY glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
//BKSGE_INLINE void APIENTRY glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
//BKSGE_INLINE void APIENTRY glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params);
//BKSGE_INLINE void APIENTRY glGenerateMipmap(GLenum target);
//BKSGE_INLINE void APIENTRY glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
//BKSGE_INLINE void APIENTRY glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
//BKSGE_INLINE void* APIENTRY glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
//BKSGE_INLINE void APIENTRY glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length);

BKSGE_INLINE void APIENTRY glBindVertexArray(GLuint array)
{
	BKSGE_GLEXT_FUNC(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray, array);
}

BKSGE_INLINE void APIENTRY glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
	BKSGE_GLEXT_FUNC(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays, n, arrays);
}

BKSGE_INLINE void APIENTRY glGenVertexArrays(GLsizei n, GLuint* arrays)
{
	BKSGE_GLEXT_FUNC(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays, n, arrays);
}

//BKSGE_INLINE GLboolean APIENTRY glIsVertexArray(GLuint array);

// GL_VERSION_3_3

BKSGE_INLINE void APIENTRY glQueryCounter(GLuint id, GLenum target)
{
	BKSGE_GLEXT_FUNC(PFNGLQUERYCOUNTERPROC, glQueryCounter, id, target);
}

BKSGE_INLINE void APIENTRY glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64* params)
{
	BKSGE_GLEXT_FUNC(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v, id, pname, params);
}

// GL_EXT_framebuffer_object

//BKSGE_INLINE GLboolean APIENTRY glIsRenderbufferEXT(GLuint renderbuffer)
//{
//	BKSGE_GLEXT_FUNC(PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT, renderbuffer);
//	return GL_FALSE;
//}
//
//BKSGE_INLINE void APIENTRY glBindRenderbufferEXT(GLenum target, GLuint renderbuffer)
//{
//	BKSGE_GLEXT_FUNC(PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT, target, renderbuffer);
//}
//
//BKSGE_INLINE void APIENTRY glDeleteRenderbuffersEXT(GLsizei n, const GLuint* renderbuffers)
//{
//	BKSGE_GLEXT_FUNC(PFNGLDELETERENDERBUFFERSEXTPROC, glDeleteRenderbuffersEXT, n, renderbuffers);
//}
//
//BKSGE_INLINE void APIENTRY glGenRenderbuffersEXT(GLsizei n, GLuint* renderbuffers)
//{
//	BKSGE_GLEXT_FUNC(PFNGLGENRENDERBUFFERSEXTPROC, glGenRenderbuffersEXT, n, renderbuffers);
//}
//
//BKSGE_INLINE void APIENTRY glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
//{
//	BKSGE_GLEXT_FUNC(PFNGLRENDERBUFFERSTORAGEEXTPROC, glRenderbufferStorageEXT, target, internalformat, width, height);
//}
//
//BKSGE_INLINE void APIENTRY glGetRenderbufferParameterivEXT(GLenum target, GLenum pname, GLint* params)
//{
//	BKSGE_GLEXT_FUNC(PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC, glGetRenderbufferParameterivEXT, target, pname, params);
//}
//
//BKSGE_INLINE GLboolean APIENTRY glIsFramebufferEXT(GLuint framebuffer)
//{
//	BKSGE_GLEXT_FUNC(PFNGLISFRAMEBUFFEREXTPROC, glIsFramebufferEXT, framebuffer);
//	return GL_FALSE;
//}
//
//BKSGE_INLINE void APIENTRY glBindFramebufferEXT(GLenum target, GLuint framebuffer)
//{
//	BKSGE_GLEXT_FUNC(PFNGLBINDFRAMEBUFFEREXTPROC, glBindFramebufferEXT, target, framebuffer);
//}
//
//BKSGE_INLINE void APIENTRY glDeleteFramebuffersEXT(GLsizei n, const GLuint* framebuffers)
//{
//	BKSGE_GLEXT_FUNC(PFNGLDELETEFRAMEBUFFERSEXTPROC, glDeleteFramebuffersEXT, n, framebuffers);
//}
//
//BKSGE_INLINE void APIENTRY glGenFramebuffersEXT(GLsizei n, GLuint* framebuffers)
//{
//	BKSGE_GLEXT_FUNC(PFNGLGENFRAMEBUFFERSEXTPROC, glGenFramebuffersEXT, n, framebuffers);
//}
//
//BKSGE_INLINE GLenum APIENTRY glCheckFramebufferStatusEXT(GLenum target)
//{
//	BKSGE_GLEXT_FUNC(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, glCheckFramebufferStatusEXT, target);
//	return GL_FRAMEBUFFER_UNDEFINED;
//}
//
//BKSGE_INLINE void APIENTRY glFramebufferTexture1DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
//{
//	BKSGE_GLEXT_FUNC(PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, glFramebufferTexture1DEXT, target, attachment, textarget, texture, level);
//}
//
//BKSGE_INLINE void APIENTRY glFramebufferTexture2DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
//{
//	BKSGE_GLEXT_FUNC(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, glFramebufferTexture2DEXT, target, attachment, textarget, texture, level);
//}
//
//BKSGE_INLINE void APIENTRY glFramebufferTexture3DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
//{
//	BKSGE_GLEXT_FUNC(PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, glFramebufferTexture3DEXT, target, attachment, textarget, texture, level, zoffset);
//}
//
//BKSGE_INLINE void APIENTRY glFramebufferRenderbufferEXT(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
//{
//	BKSGE_GLEXT_FUNC(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC, glFramebufferRenderbufferEXT, target, attachment, renderbuffertarget, renderbuffer);
//}
//
//BKSGE_INLINE void APIENTRY glGetFramebufferAttachmentParameterivEXT(GLenum target, GLenum attachment, GLenum pname, GLint* params)
//{
//	BKSGE_GLEXT_FUNC(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, glGetFramebufferAttachmentParameterivEXT, target, attachment, pname, params);
//}
//
//BKSGE_INLINE void APIENTRY glGenerateMipmapEXT(GLenum target)
//{
//	BKSGE_GLEXT_FUNC(PFNGLGENERATEMIPMAPEXTPROC, glGenerateMipmapEXT, target);
//}

#undef BKSGE_GL_GET_PROC_ADDRESS
#undef BKSGE_GLEXT_FUNC

BKSGE_WARNING_POP()

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GLEXT_INL_HPP
