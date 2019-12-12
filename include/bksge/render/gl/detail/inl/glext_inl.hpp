/**
 *	@file	glext_inl.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_GLEXT_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_GLEXT_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/gl_h.hpp>

#if defined(__APPLE__)

#import <stdlib.h>
#import <string.h>
#include <AvailabilityMacros.h>

#if defined(MAC_OS_X_VERSION_10_3)

#include <dlfcn.h>

static void* NSGLGetProcAddress(const char* name)
{
	static void* image = NULL;

	if (image == NULL)
	{
		image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);
	}

	return image ? dlsym(image, name) : NULL;
}

#else

#include <mach-o/dyld.h>

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
#endif	// defined(MAC_OS_X_VERSION_10_3)
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

// GL_VERSION_1_4
BKSGE_INLINE void APIENTRY glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	BKSGE_GLEXT_FUNC(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate, sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

//BKSGE_INLINE void APIENTRY glMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
//BKSGE_INLINE void APIENTRY glMultiDrawElements(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
//BKSGE_INLINE void APIENTRY glPointParameterf(GLenum pname, GLfloat param);
//BKSGE_INLINE void APIENTRY glPointParameterfv(GLenum pname, const GLfloat *params);
//BKSGE_INLINE void APIENTRY glPointParameteri(GLenum pname, GLint param);
//BKSGE_INLINE void APIENTRY glPointParameteriv(GLenum pname, const GLint *params);
//BKSGE_INLINE void APIENTRY glFogCoordf(GLfloat coord);
//BKSGE_INLINE void APIENTRY glFogCoordfv(const GLfloat *coord);
//BKSGE_INLINE void APIENTRY glFogCoordd(GLdouble coord);
//BKSGE_INLINE void APIENTRY glFogCoorddv(const GLdouble *coord);
//BKSGE_INLINE void APIENTRY glFogCoordPointer(GLenum type, GLsizei stride, const void *pointer);
//BKSGE_INLINE void APIENTRY glSecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue);
//BKSGE_INLINE void APIENTRY glSecondaryColor3bv(const GLbyte *v);
//BKSGE_INLINE void APIENTRY glSecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue);
//BKSGE_INLINE void APIENTRY glSecondaryColor3dv(const GLdouble *v);
//BKSGE_INLINE void APIENTRY glSecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue);
//BKSGE_INLINE void APIENTRY glSecondaryColor3fv(const GLfloat *v);
//BKSGE_INLINE void APIENTRY glSecondaryColor3i(GLint red, GLint green, GLint blue);
//BKSGE_INLINE void APIENTRY glSecondaryColor3iv(const GLint *v);
//BKSGE_INLINE void APIENTRY glSecondaryColor3s(GLshort red, GLshort green, GLshort blue);
//BKSGE_INLINE void APIENTRY glSecondaryColor3sv(const GLshort *v);
//BKSGE_INLINE void APIENTRY glSecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue);
//BKSGE_INLINE void APIENTRY glSecondaryColor3ubv(const GLubyte *v);
//BKSGE_INLINE void APIENTRY glSecondaryColor3ui(GLuint red, GLuint green, GLuint blue);
//BKSGE_INLINE void APIENTRY glSecondaryColor3uiv(const GLuint *v);
//BKSGE_INLINE void APIENTRY glSecondaryColor3us(GLushort red, GLushort green, GLushort blue);
//BKSGE_INLINE void APIENTRY glSecondaryColor3usv(const GLushort *v);
//BKSGE_INLINE void APIENTRY glSecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void *pointer);
//BKSGE_INLINE void APIENTRY glWindowPos2d(GLdouble x, GLdouble y);
//BKSGE_INLINE void APIENTRY glWindowPos2dv(const GLdouble *v);
//BKSGE_INLINE void APIENTRY glWindowPos2f(GLfloat x, GLfloat y);
//BKSGE_INLINE void APIENTRY glWindowPos2fv(const GLfloat *v);
//BKSGE_INLINE void APIENTRY glWindowPos2i(GLint x, GLint y);
//BKSGE_INLINE void APIENTRY glWindowPos2iv(const GLint *v);
//BKSGE_INLINE void APIENTRY glWindowPos2s(GLshort x, GLshort y);
//BKSGE_INLINE void APIENTRY glWindowPos2sv(const GLshort *v);
//BKSGE_INLINE void APIENTRY glWindowPos3d(GLdouble x, GLdouble y, GLdouble z);
//BKSGE_INLINE void APIENTRY glWindowPos3dv(const GLdouble *v);
//BKSGE_INLINE void APIENTRY glWindowPos3f(GLfloat x, GLfloat y, GLfloat z);
//BKSGE_INLINE void APIENTRY glWindowPos3fv(const GLfloat *v);
//BKSGE_INLINE void APIENTRY glWindowPos3i(GLint x, GLint y, GLint z);
//BKSGE_INLINE void APIENTRY glWindowPos3iv(const GLint *v);
//BKSGE_INLINE void APIENTRY glWindowPos3s(GLshort x, GLshort y, GLshort z);
//BKSGE_INLINE void APIENTRY glWindowPos3sv(const GLshort *v);
//BKSGE_INLINE void APIENTRY glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
//BKSGE_INLINE void APIENTRY glBlendEquation(GLenum mode);

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

BKSGE_INLINE void APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	BKSGE_GLEXT_FUNC(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate, modeRGB, modeAlpha);
}

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

BKSGE_INLINE void APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	BKSGE_GLEXT_FUNC(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform, program, index, bufSize, length, size, type, name);
}

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
BKSGE_INLINE GLint APIENTRY glGetUniformLocation(GLuint program, const GLchar* name)
{
	BKSGE_GLEXT_FUNC(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation, program, name);
	return -1;
}
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

BKSGE_INLINE void APIENTRY glUniform1f(GLint location, GLfloat v0)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM1FPROC, glUniform1f, location, v0);
}

//BKSGE_INLINE void APIENTRY glUniform2f(GLint location, GLfloat v0, GLfloat v1);
//BKSGE_INLINE void APIENTRY glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
//BKSGE_INLINE void APIENTRY glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

BKSGE_INLINE void APIENTRY glUniform1i(GLint location, GLint v0)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM1IPROC, glUniform1i, location, v0);
}

//BKSGE_INLINE void APIENTRY glUniform2i(GLint location, GLint v0, GLint v1);
//BKSGE_INLINE void APIENTRY glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
//BKSGE_INLINE void APIENTRY glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
//BKSGE_INLINE void APIENTRY glUniform1fv(GLint location, GLsizei count, const GLfloat* value);

BKSGE_INLINE void APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM2FVPROC, glUniform2fv, location, count, value);
}

BKSGE_INLINE void APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM3FVPROC, glUniform3fv, location, count, value);
}

BKSGE_INLINE void APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM4FVPROC, glUniform4fv, location, count, value);
}

//BKSGE_INLINE void APIENTRY glUniform1iv(GLint location, GLsizei count, const GLint* value);
//BKSGE_INLINE void APIENTRY glUniform2iv(GLint location, GLsizei count, const GLint* value);
//BKSGE_INLINE void APIENTRY glUniform3iv(GLint location, GLsizei count, const GLint* value);
//BKSGE_INLINE void APIENTRY glUniform4iv(GLint location, GLsizei count, const GLint* value);
BKSGE_INLINE void APIENTRY glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv, location, count, transpose, value);
}

BKSGE_INLINE void APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv, location, count, transpose, value);
}

BKSGE_INLINE void APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv, location, count, transpose, value);
}

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

// GL_VERSION_3_1

//BKSGE_INLINE void APIENTRY glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
//BKSGE_INLINE void APIENTRY glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
//BKSGE_INLINE void APIENTRY glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer);
//BKSGE_INLINE void APIENTRY glPrimitiveRestartIndex(GLuint index);
//BKSGE_INLINE void APIENTRY glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
//BKSGE_INLINE void APIENTRY glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
//BKSGE_INLINE void APIENTRY glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);

BKSGE_INLINE GLuint APIENTRY glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName)
{
	BKSGE_GLEXT_FUNC(PFNGLGETUNIFORMBLOCKINDEXPROC, glGetUniformBlockIndex, program, uniformBlockName);
	return GL_INVALID_INDEX;
}

//BKSGE_INLINE void APIENTRY glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
//BKSGE_INLINE void APIENTRY glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

// GL_VERSION_3_2
//BKSGE_INLINE void APIENTRY glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
//BKSGE_INLINE void APIENTRY glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
//BKSGE_INLINE void APIENTRY glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
//BKSGE_INLINE void APIENTRY glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
//BKSGE_INLINE void APIENTRY glProvokingVertex(GLenum mode);
//BKSGE_INLINE GLsync APIENTRY glFenceSync(GLenum condition, GLbitfield flags);
//BKSGE_INLINE GLboolean APIENTRY glIsSync(GLsync sync);
//BKSGE_INLINE void APIENTRY glDeleteSync(GLsync sync);
//BKSGE_INLINE GLenum APIENTRY glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);
//BKSGE_INLINE void APIENTRY glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);
//BKSGE_INLINE void APIENTRY glGetInteger64v(GLenum pname, GLint64 *data);
//BKSGE_INLINE void APIENTRY glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
//BKSGE_INLINE void APIENTRY glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data);
//BKSGE_INLINE void APIENTRY glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params);
//BKSGE_INLINE void APIENTRY glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
//BKSGE_INLINE void APIENTRY glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
//BKSGE_INLINE void APIENTRY glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
//BKSGE_INLINE void APIENTRY glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val);
//BKSGE_INLINE void APIENTRY glSampleMaski(GLuint maskNumber, GLbitfield mask);

// GL_VERSION_3_3

BKSGE_INLINE void APIENTRY glQueryCounter(GLuint id, GLenum target)
{
	BKSGE_GLEXT_FUNC(PFNGLQUERYCOUNTERPROC, glQueryCounter, id, target);
}

BKSGE_INLINE void APIENTRY glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64* params)
{
	BKSGE_GLEXT_FUNC(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v, id, pname, params);
}

// GL_VERSION_4_0
//BKSGE_INLINE void APIENTRY glMinSampleShading(GLfloat value);
//BKSGE_INLINE void APIENTRY glBlendEquationi(GLuint buf, GLenum mode);
//BKSGE_INLINE void APIENTRY glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
//BKSGE_INLINE void APIENTRY glBlendFunci(GLuint buf, GLenum src, GLenum dst);
//BKSGE_INLINE void APIENTRY glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
//BKSGE_INLINE void APIENTRY glDrawArraysIndirect(GLenum mode, const void *indirect);
//BKSGE_INLINE void APIENTRY glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect);

BKSGE_INLINE void APIENTRY glUniform1d(GLint location, GLdouble x)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM1DPROC, glUniform1d, location, x);
}

//BKSGE_INLINE void APIENTRY glUniform2d(GLint location, GLdouble x, GLdouble y);
//BKSGE_INLINE void APIENTRY glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z);
//BKSGE_INLINE void APIENTRY glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
//BKSGE_INLINE void APIENTRY glUniform1dv(GLint location, GLsizei count, const GLdouble *value);

BKSGE_INLINE void APIENTRY glUniform2dv(GLint location, GLsizei count, const GLdouble *value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM2DVPROC, glUniform2dv, location, count, value);
}

BKSGE_INLINE void APIENTRY glUniform3dv(GLint location, GLsizei count, const GLdouble *value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM3DVPROC, glUniform3dv, location, count, value);
}

BKSGE_INLINE void APIENTRY glUniform4dv(GLint location, GLsizei count, const GLdouble *value)
{
	BKSGE_GLEXT_FUNC(PFNGLUNIFORM4DVPROC, glUniform4dv, location, count, value);
}

//BKSGE_INLINE void APIENTRY glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glGetUniformdv(GLuint program, GLint location, GLdouble *params);
//BKSGE_INLINE GLint APIENTRY glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar *name);
//BKSGE_INLINE GLuint APIENTRY glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar *name);
//BKSGE_INLINE void APIENTRY glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
//BKSGE_INLINE void APIENTRY glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
//BKSGE_INLINE void APIENTRY glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
//BKSGE_INLINE void APIENTRY glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint *indices);
//BKSGE_INLINE void APIENTRY glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint *params);
//BKSGE_INLINE void APIENTRY glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint *values);
//BKSGE_INLINE void APIENTRY glPatchParameteri(GLenum pname, GLint value);
//BKSGE_INLINE void APIENTRY glPatchParameterfv(GLenum pname, const GLfloat *values);
//BKSGE_INLINE void APIENTRY glBindTransformFeedback(GLenum target, GLuint id);
//BKSGE_INLINE void APIENTRY glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids);
//BKSGE_INLINE void APIENTRY glGenTransformFeedbacks(GLsizei n, GLuint *ids);
//BKSGE_INLINE GLboolean APIENTRY glIsTransformFeedback(GLuint id);
//BKSGE_INLINE void APIENTRY glPauseTransformFeedback(void);
//BKSGE_INLINE void APIENTRY glResumeTransformFeedback(void);
//BKSGE_INLINE void APIENTRY glDrawTransformFeedback(GLenum mode, GLuint id);
//BKSGE_INLINE void APIENTRY glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream);
//BKSGE_INLINE void APIENTRY glBeginQueryIndexed(GLenum target, GLuint index, GLuint id);
//BKSGE_INLINE void APIENTRY glEndQueryIndexed(GLenum target, GLuint index);
//BKSGE_INLINE void APIENTRY glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint *params);

// GL_VERSION_4_1
//BKSGE_INLINE void APIENTRY glReleaseShaderCompiler(void);
//BKSGE_INLINE void APIENTRY glShaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
//BKSGE_INLINE void APIENTRY glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
//BKSGE_INLINE void APIENTRY glDepthRangef(GLfloat n, GLfloat f);
//BKSGE_INLINE void APIENTRY glClearDepthf(GLfloat d);
//BKSGE_INLINE void APIENTRY glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
//BKSGE_INLINE void APIENTRY glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
//BKSGE_INLINE void APIENTRY glProgramParameteri(GLuint program, GLenum pname, GLint value);
//BKSGE_INLINE void APIENTRY glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program);
//BKSGE_INLINE void APIENTRY glActiveShaderProgram(GLuint pipeline, GLuint program);
//BKSGE_INLINE GLuint APIENTRY glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings);
//BKSGE_INLINE void APIENTRY glBindProgramPipeline(GLuint pipeline);
//BKSGE_INLINE void APIENTRY glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines);
//BKSGE_INLINE void APIENTRY glGenProgramPipelines(GLsizei n, GLuint *pipelines);
//BKSGE_INLINE GLboolean APIENTRY glIsProgramPipeline(GLuint pipeline);
//BKSGE_INLINE void APIENTRY glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glProgramUniform1i(GLuint program, GLint location, GLint v0);
//BKSGE_INLINE void APIENTRY glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value);
//BKSGE_INLINE void APIENTRY glProgramUniform1f(GLuint program, GLint location, GLfloat v0);
//BKSGE_INLINE void APIENTRY glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniform1d(GLuint program, GLint location, GLdouble v0);
//BKSGE_INLINE void APIENTRY glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniform1ui(GLuint program, GLint location, GLuint v0);
//BKSGE_INLINE void APIENTRY glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value);
//BKSGE_INLINE void APIENTRY glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1);
//BKSGE_INLINE void APIENTRY glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value);
//BKSGE_INLINE void APIENTRY glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1);
//BKSGE_INLINE void APIENTRY glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1);
//BKSGE_INLINE void APIENTRY glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1);
//BKSGE_INLINE void APIENTRY glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value);
//BKSGE_INLINE void APIENTRY glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
//BKSGE_INLINE void APIENTRY glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value);
//BKSGE_INLINE void APIENTRY glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
//BKSGE_INLINE void APIENTRY glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
//BKSGE_INLINE void APIENTRY glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
//BKSGE_INLINE void APIENTRY glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value);
//BKSGE_INLINE void APIENTRY glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
//BKSGE_INLINE void APIENTRY glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value);
//BKSGE_INLINE void APIENTRY glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
//BKSGE_INLINE void APIENTRY glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
//BKSGE_INLINE void APIENTRY glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
//BKSGE_INLINE void APIENTRY glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
//BKSGE_INLINE void APIENTRY glValidateProgramPipeline(GLuint pipeline);
//BKSGE_INLINE void APIENTRY glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
//BKSGE_INLINE void APIENTRY glVertexAttribL1d(GLuint index, GLdouble x);
//BKSGE_INLINE void APIENTRY glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y);
//BKSGE_INLINE void APIENTRY glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);
//BKSGE_INLINE void APIENTRY glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
//BKSGE_INLINE void APIENTRY glVertexAttribL1dv(GLuint index, const GLdouble *v);
//BKSGE_INLINE void APIENTRY glVertexAttribL2dv(GLuint index, const GLdouble *v);
//BKSGE_INLINE void APIENTRY glVertexAttribL3dv(GLuint index, const GLdouble *v);
//BKSGE_INLINE void APIENTRY glVertexAttribL4dv(GLuint index, const GLdouble *v);
//BKSGE_INLINE void APIENTRY glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
//BKSGE_INLINE void APIENTRY glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble *params);
//BKSGE_INLINE void APIENTRY glViewportArrayv(GLuint first, GLsizei count, const GLfloat *v);
//BKSGE_INLINE void APIENTRY glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
//BKSGE_INLINE void APIENTRY glViewportIndexedfv(GLuint index, const GLfloat *v);
//BKSGE_INLINE void APIENTRY glScissorArrayv(GLuint first, GLsizei count, const GLint *v);
//BKSGE_INLINE void APIENTRY glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glScissorIndexedv(GLuint index, const GLint *v);
//BKSGE_INLINE void APIENTRY glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble *v);
//BKSGE_INLINE void APIENTRY glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f);
//BKSGE_INLINE void APIENTRY glGetFloati_v(GLenum target, GLuint index, GLfloat *data);
//BKSGE_INLINE void APIENTRY glGetDoublei_v(GLenum target, GLuint index, GLdouble *data);

// GL_VERSION_4_2
//BKSGE_INLINE void APIENTRY glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
//BKSGE_INLINE void APIENTRY glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
//BKSGE_INLINE void APIENTRY glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
//BKSGE_INLINE void APIENTRY glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params);
//BKSGE_INLINE void APIENTRY glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
//BKSGE_INLINE void APIENTRY glMemoryBarrier(GLbitfield barriers);
//BKSGE_INLINE void APIENTRY glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
//BKSGE_INLINE void APIENTRY glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
//BKSGE_INLINE void APIENTRY glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount);
//BKSGE_INLINE void APIENTRY glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);

// GL_VERSION_4_3
//BKSGE_INLINE void APIENTRY glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
//BKSGE_INLINE void APIENTRY glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
//BKSGE_INLINE void APIENTRY glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
//BKSGE_INLINE void APIENTRY glDispatchComputeIndirect(GLintptr indirect);
//BKSGE_INLINE void APIENTRY glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
//BKSGE_INLINE void APIENTRY glFramebufferParameteri(GLenum target, GLenum pname, GLint param);
//BKSGE_INLINE void APIENTRY glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params);
//BKSGE_INLINE void APIENTRY glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
//BKSGE_INLINE void APIENTRY glInvalidateTexImage(GLuint texture, GLint level);
//BKSGE_INLINE void APIENTRY glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length);
//BKSGE_INLINE void APIENTRY glInvalidateBufferData(GLuint buffer);
//BKSGE_INLINE void APIENTRY glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments);
//BKSGE_INLINE void APIENTRY glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glMultiDrawArraysIndirect(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
//BKSGE_INLINE void APIENTRY glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
//BKSGE_INLINE void APIENTRY glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params);
//BKSGE_INLINE GLuint APIENTRY glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name);
//BKSGE_INLINE void APIENTRY glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
//BKSGE_INLINE void APIENTRY glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params);
//BKSGE_INLINE GLint APIENTRY glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name);
//BKSGE_INLINE GLint APIENTRY glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar *name);
//BKSGE_INLINE void APIENTRY glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
//BKSGE_INLINE void APIENTRY glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
//BKSGE_INLINE void APIENTRY glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
//BKSGE_INLINE void APIENTRY glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
//BKSGE_INLINE void APIENTRY glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
//BKSGE_INLINE void APIENTRY glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
//BKSGE_INLINE void APIENTRY glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
//BKSGE_INLINE void APIENTRY glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
//BKSGE_INLINE void APIENTRY glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
//BKSGE_INLINE void APIENTRY glVertexAttribBinding(GLuint attribindex, GLuint bindingindex);
//BKSGE_INLINE void APIENTRY glVertexBindingDivisor(GLuint bindingindex, GLuint divisor);
BKSGE_INLINE void APIENTRY glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled)
{
	BKSGE_GLEXT_FUNC(PFNGLDEBUGMESSAGECONTROLPROC, glDebugMessageControl, source, type, severity, count, ids, enabled);
}
//BKSGE_INLINE void APIENTRY glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
BKSGE_INLINE void APIENTRY glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam)
{
	BKSGE_GLEXT_FUNC(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback, callback, userParam);
}
//BKSGE_INLINE GLuint APIENTRY glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
//BKSGE_INLINE void APIENTRY glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message);
//BKSGE_INLINE void APIENTRY glPopDebugGroup(void);
//BKSGE_INLINE void APIENTRY glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
//BKSGE_INLINE void APIENTRY glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
//BKSGE_INLINE void APIENTRY glObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label);
//BKSGE_INLINE void APIENTRY glGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);

// GL_VERSION_4_4
//BKSGE_INLINE void APIENTRY glBufferStorage(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
//BKSGE_INLINE void APIENTRY glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
//BKSGE_INLINE void APIENTRY glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
//BKSGE_INLINE void APIENTRY glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
//BKSGE_INLINE void APIENTRY glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
//BKSGE_INLINE void APIENTRY glBindTextures(GLuint first, GLsizei count, const GLuint *textures);
//BKSGE_INLINE void APIENTRY glBindSamplers(GLuint first, GLsizei count, const GLuint *samplers);
//BKSGE_INLINE void APIENTRY glBindImageTextures(GLuint first, GLsizei count, const GLuint *textures);
//BKSGE_INLINE void APIENTRY glBindVertexBuffers(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);

// GL_VERSION_4_5
BKSGE_INLINE void APIENTRY glClipControl(GLenum origin, GLenum depth)
{
	BKSGE_GLEXT_FUNC(PFNGLCLIPCONTROLPROC, glClipControl, origin, depth);
}

//BKSGE_INLINE void APIENTRY glCreateTransformFeedbacks(GLsizei n, GLuint *ids);
//BKSGE_INLINE void APIENTRY glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer);
//BKSGE_INLINE void APIENTRY glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
//BKSGE_INLINE void APIENTRY glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint *param);
//BKSGE_INLINE void APIENTRY glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint *param);
//BKSGE_INLINE void APIENTRY glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
//BKSGE_INLINE void APIENTRY glCreateBuffers(GLsizei n, GLuint *buffers);
//BKSGE_INLINE void APIENTRY glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
//BKSGE_INLINE void APIENTRY glNamedBufferData(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
//BKSGE_INLINE void APIENTRY glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
//BKSGE_INLINE void APIENTRY glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
//BKSGE_INLINE void APIENTRY glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
//BKSGE_INLINE void APIENTRY glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
//BKSGE_INLINE void *APIENTRY glMapNamedBuffer(GLuint buffer, GLenum access);
//BKSGE_INLINE void *APIENTRY glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
//BKSGE_INLINE GLboolean APIENTRY glUnmapNamedBuffer(GLuint buffer);
//BKSGE_INLINE void APIENTRY glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length);
//BKSGE_INLINE void APIENTRY glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 *params);
//BKSGE_INLINE void APIENTRY glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void **params);
//BKSGE_INLINE void APIENTRY glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
//BKSGE_INLINE void APIENTRY glCreateFramebuffers(GLsizei n, GLuint *framebuffers);
//BKSGE_INLINE void APIENTRY glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
//BKSGE_INLINE void APIENTRY glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param);
//BKSGE_INLINE void APIENTRY glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
//BKSGE_INLINE void APIENTRY glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
//BKSGE_INLINE void APIENTRY glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf);
//BKSGE_INLINE void APIENTRY glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum *bufs);
//BKSGE_INLINE void APIENTRY glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src);
//BKSGE_INLINE void APIENTRY glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments);
//BKSGE_INLINE void APIENTRY glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value);
//BKSGE_INLINE void APIENTRY glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value);
//BKSGE_INLINE void APIENTRY glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value);
//BKSGE_INLINE void APIENTRY glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
//BKSGE_INLINE void APIENTRY glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
//BKSGE_INLINE GLenum APIENTRY glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target);
//BKSGE_INLINE void APIENTRY glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint *param);
//BKSGE_INLINE void APIENTRY glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glCreateRenderbuffers(GLsizei n, GLuint *renderbuffers);
//BKSGE_INLINE void APIENTRY glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glCreateTextures(GLenum target, GLsizei n, GLuint *textures);
//BKSGE_INLINE void APIENTRY glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer);
//BKSGE_INLINE void APIENTRY glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
//BKSGE_INLINE void APIENTRY glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
//BKSGE_INLINE void APIENTRY glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
//BKSGE_INLINE void APIENTRY glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
//BKSGE_INLINE void APIENTRY glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
//BKSGE_INLINE void APIENTRY glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
//BKSGE_INLINE void APIENTRY glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
//BKSGE_INLINE void APIENTRY glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
//BKSGE_INLINE void APIENTRY glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
//BKSGE_INLINE void APIENTRY glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
//BKSGE_INLINE void APIENTRY glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
//BKSGE_INLINE void APIENTRY glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
//BKSGE_INLINE void APIENTRY glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
//BKSGE_INLINE void APIENTRY glTextureParameterf(GLuint texture, GLenum pname, GLfloat param);
//BKSGE_INLINE void APIENTRY glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat *param);
//BKSGE_INLINE void APIENTRY glTextureParameteri(GLuint texture, GLenum pname, GLint param);
//BKSGE_INLINE void APIENTRY glTextureParameterIiv(GLuint texture, GLenum pname, const GLint *params);
//BKSGE_INLINE void APIENTRY glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint *params);
//BKSGE_INLINE void APIENTRY glTextureParameteriv(GLuint texture, GLenum pname, const GLint *param);
//BKSGE_INLINE void APIENTRY glGenerateTextureMipmap(GLuint texture);
//BKSGE_INLINE void APIENTRY glBindTextureUnit(GLuint unit, GLuint texture);
//BKSGE_INLINE void APIENTRY glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
//BKSGE_INLINE void APIENTRY glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void *pixels);
//BKSGE_INLINE void APIENTRY glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat *params);
//BKSGE_INLINE void APIENTRY glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat *params);
//BKSGE_INLINE void APIENTRY glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint *params);
//BKSGE_INLINE void APIENTRY glGetTextureParameteriv(GLuint texture, GLenum pname, GLint *params);
//BKSGE_INLINE void APIENTRY glCreateVertexArrays(GLsizei n, GLuint *arrays);
//BKSGE_INLINE void APIENTRY glDisableVertexArrayAttrib(GLuint vaobj, GLuint index);
//BKSGE_INLINE void APIENTRY glEnableVertexArrayAttrib(GLuint vaobj, GLuint index);
//BKSGE_INLINE void APIENTRY glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer);
//BKSGE_INLINE void APIENTRY glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
//BKSGE_INLINE void APIENTRY glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
//BKSGE_INLINE void APIENTRY glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
//BKSGE_INLINE void APIENTRY glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
//BKSGE_INLINE void APIENTRY glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
//BKSGE_INLINE void APIENTRY glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
//BKSGE_INLINE void APIENTRY glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor);
//BKSGE_INLINE void APIENTRY glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint *param);
//BKSGE_INLINE void APIENTRY glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint *param);
//BKSGE_INLINE void APIENTRY glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);
//BKSGE_INLINE void APIENTRY glCreateSamplers(GLsizei n, GLuint *samplers);
//BKSGE_INLINE void APIENTRY glCreateProgramPipelines(GLsizei n, GLuint *pipelines);
//BKSGE_INLINE void APIENTRY glCreateQueries(GLenum target, GLsizei n, GLuint *ids);
//BKSGE_INLINE void APIENTRY glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
//BKSGE_INLINE void APIENTRY glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
//BKSGE_INLINE void APIENTRY glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
//BKSGE_INLINE void APIENTRY glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
//BKSGE_INLINE void APIENTRY glMemoryBarrierByRegion(GLbitfield barriers);
//BKSGE_INLINE void APIENTRY glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
//BKSGE_INLINE void APIENTRY glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels);
//BKSGE_INLINE GLenum APIENTRY glGetGraphicsResetStatus(void);
//BKSGE_INLINE void APIENTRY glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void *pixels);
//BKSGE_INLINE void APIENTRY glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
//BKSGE_INLINE void APIENTRY glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
//BKSGE_INLINE void APIENTRY glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
//BKSGE_INLINE void APIENTRY glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint *params);
//BKSGE_INLINE void APIENTRY glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint *params);
//BKSGE_INLINE void APIENTRY glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
//BKSGE_INLINE void APIENTRY glGetnMapdv(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v);
//BKSGE_INLINE void APIENTRY glGetnMapfv(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v);
//BKSGE_INLINE void APIENTRY glGetnMapiv(GLenum target, GLenum query, GLsizei bufSize, GLint *v);
//BKSGE_INLINE void APIENTRY glGetnPixelMapfv(GLenum map, GLsizei bufSize, GLfloat *values);
//BKSGE_INLINE void APIENTRY glGetnPixelMapuiv(GLenum map, GLsizei bufSize, GLuint *values);
//BKSGE_INLINE void APIENTRY glGetnPixelMapusv(GLenum map, GLsizei bufSize, GLushort *values);
//BKSGE_INLINE void APIENTRY glGetnPolygonStipple(GLsizei bufSize, GLubyte *pattern);
//BKSGE_INLINE void APIENTRY glGetnColorTable(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *table);
//BKSGE_INLINE void APIENTRY glGetnConvolutionFilter(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *image);
//BKSGE_INLINE void APIENTRY glGetnSeparableFilter(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void *row, GLsizei columnBufSize, void *column, void *span);
//BKSGE_INLINE void APIENTRY glGetnHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
//BKSGE_INLINE void APIENTRY glGetnMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void *values);
//BKSGE_INLINE void APIENTRY glTextureBarrier(void);

// GL_EXT_framebuffer_object

//BKSGE_INLINE GLboolean APIENTRY glIsRenderbufferEXT(GLuint renderbuffer)
//{
//	BKSGE_GLEXT_FUNC(PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT, renderbuffer);
//	return GL_FALSE;
//}

BKSGE_INLINE void APIENTRY glBindRenderbufferEXT(GLenum target, GLuint renderbuffer)
{
	BKSGE_GLEXT_FUNC(PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT, target, renderbuffer);
}

BKSGE_INLINE void APIENTRY glDeleteRenderbuffersEXT(GLsizei n, const GLuint* renderbuffers)
{
	BKSGE_GLEXT_FUNC(PFNGLDELETERENDERBUFFERSEXTPROC, glDeleteRenderbuffersEXT, n, renderbuffers);
}

BKSGE_INLINE void APIENTRY glGenRenderbuffersEXT(GLsizei n, GLuint* renderbuffers)
{
	BKSGE_GLEXT_FUNC(PFNGLGENRENDERBUFFERSEXTPROC, glGenRenderbuffersEXT, n, renderbuffers);
}

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

#endif // BKSGE_RENDER_GL_DETAIL_INL_GLEXT_INL_HPP
