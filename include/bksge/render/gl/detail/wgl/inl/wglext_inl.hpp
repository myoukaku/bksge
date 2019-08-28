/**
 *	@file	wglext_inl.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_WGL_INL_WGLEXT_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_WGL_INL_WGLEXT_INL_HPP

#include <bksge/config.hpp>
#if defined(BKSGE_PLATFORM_WIN32)

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/gl_h.hpp>
#include <bksge/render/gl/detail/wgl/wglext.hpp>

BKSGE_WARNING_PUSH()
#if defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION >= 80000)
BKSGE_WARNING_DISABLE_GCC("-Wcast-function-type")
#endif

#define BKSGE_WGLEXT_FUNC(funcptr, funcname, ...)	\
	static funcptr p = (funcptr)wglGetProcAddress(#funcname);	\
	if (p)	\
	{	\
		return p(__VA_ARGS__);	\
	}


// WGL_ARB_buffer_region
//HANDLE WINAPI wglCreateBufferRegionARB (HDC hDC, int iLayerPlane, UINT uType);
//VOID WINAPI wglDeleteBufferRegionARB (HANDLE hRegion);
//BOOL WINAPI wglSaveBufferRegionARB (HANDLE hRegion, int x, int y, int width, int height);
//BOOL WINAPI wglRestoreBufferRegionARB (HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc);

// WGL_ARB_create_context
BKSGE_INLINE HGLRC WINAPI wglCreateContextAttribsARB (HDC hDC, HGLRC hShareContext, const int *attribList)
{
	BKSGE_WGLEXT_FUNC(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB, hDC, hShareContext, attribList);
	return NULL;
}

// WGL_ARB_extensions_string
//const char *WINAPI wglGetExtensionsStringARB (HDC hdc);

// WGL_ARB_make_current_read
//BOOL WINAPI wglMakeContextCurrentARB (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
//HDC WINAPI wglGetCurrentReadDCARB (void);

// WGL_ARB_pbuffer
//HPBUFFERARB WINAPI wglCreatePbufferARB (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
//HDC WINAPI wglGetPbufferDCARB (HPBUFFERARB hPbuffer);
//int WINAPI wglReleasePbufferDCARB (HPBUFFERARB hPbuffer, HDC hDC);
//BOOL WINAPI wglDestroyPbufferARB (HPBUFFERARB hPbuffer);
//BOOL WINAPI wglQueryPbufferARB (HPBUFFERARB hPbuffer, int iAttribute, int *piValue);

// WGL_ARB_pixel_format
//BOOL WINAPI wglGetPixelFormatAttribivARB (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues);
//BOOL WINAPI wglGetPixelFormatAttribfvARB (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues);
//BOOL WINAPI wglChoosePixelFormatARB (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

// WGL_ARB_render_texture
//BOOL WINAPI wglBindTexImageARB (HPBUFFERARB hPbuffer, int iBuffer);
//BOOL WINAPI wglReleaseTexImageARB (HPBUFFERARB hPbuffer, int iBuffer);
//BOOL WINAPI wglSetPbufferAttribARB (HPBUFFERARB hPbuffer, const int *piAttribList);

// WGL_3DL_stereo_control
//BOOL WINAPI wglSetStereoEmitterState3DL (HDC hDC, UINT uState);

// WGL_AMD_gpu_association
//UINT WINAPI wglGetGPUIDsAMD (UINT maxCount, UINT *ids);
//INT WINAPI wglGetGPUInfoAMD (UINT id, INT property, GLenum dataType, UINT size, void *data);
//UINT WINAPI wglGetContextGPUIDAMD (HGLRC hglrc);
//HGLRC WINAPI wglCreateAssociatedContextAMD (UINT id);
//HGLRC WINAPI wglCreateAssociatedContextAttribsAMD (UINT id, HGLRC hShareContext, const int *attribList);
//BOOL WINAPI wglDeleteAssociatedContextAMD (HGLRC hglrc);
//BOOL WINAPI wglMakeAssociatedContextCurrentAMD (HGLRC hglrc);
//HGLRC WINAPI wglGetCurrentAssociatedContextAMD (void);
//VOID WINAPI wglBlitContextFramebufferAMD (HGLRC dstCtx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

// WGL_EXT_display_color_table
//GLboolean WINAPI wglCreateDisplayColorTableEXT (GLushort id);
//GLboolean WINAPI wglLoadDisplayColorTableEXT (const GLushort *table, GLuint length);
//GLboolean WINAPI wglBindDisplayColorTableEXT (GLushort id);
//VOID WINAPI wglDestroyDisplayColorTableEXT (GLushort id);

// WGL_EXT_extensions_string
//const char *WINAPI wglGetExtensionsStringEXT (void);

// WGL_EXT_make_current_read
//BOOL WINAPI wglMakeContextCurrentEXT (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
//HDC WINAPI wglGetCurrentReadDCEXT (void);

// WGL_EXT_pbuffer
//HPBUFFEREXT WINAPI wglCreatePbufferEXT (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList);
//HDC WINAPI wglGetPbufferDCEXT (HPBUFFEREXT hPbuffer);
//int WINAPI wglReleasePbufferDCEXT (HPBUFFEREXT hPbuffer, HDC hDC);
//BOOL WINAPI wglDestroyPbufferEXT (HPBUFFEREXT hPbuffer);
//BOOL WINAPI wglQueryPbufferEXT (HPBUFFEREXT hPbuffer, int iAttribute, int *piValue);

// WGL_EXT_pixel_format
//BOOL WINAPI wglGetPixelFormatAttribivEXT (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, int *piValues);
//BOOL WINAPI wglGetPixelFormatAttribfvEXT (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, FLOAT *pfValues);
//BOOL WINAPI wglChoosePixelFormatEXT (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

// WGL_EXT_swap_control
BKSGE_INLINE BOOL WINAPI wglSwapIntervalEXT(int interval)
{
	BKSGE_WGLEXT_FUNC(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT, interval);
	return false;
}
//int WINAPI wglGetSwapIntervalEXT (void);

// WGL_I3D_digital_video_control
//BOOL WINAPI wglGetDigitalVideoParametersI3D (HDC hDC, int iAttribute, int *piValue);
//BOOL WINAPI wglSetDigitalVideoParametersI3D (HDC hDC, int iAttribute, const int *piValue);

// WGL_I3D_gamma
//BOOL WINAPI wglGetGammaTableParametersI3D (HDC hDC, int iAttribute, int *piValue);
//BOOL WINAPI wglSetGammaTableParametersI3D (HDC hDC, int iAttribute, const int *piValue);
//BOOL WINAPI wglGetGammaTableI3D (HDC hDC, int iEntries, USHORT *puRed, USHORT *puGreen, USHORT *puBlue);
//BOOL WINAPI wglSetGammaTableI3D (HDC hDC, int iEntries, const USHORT *puRed, const USHORT *puGreen, const USHORT *puBlue);

// WGL_I3D_genlock
//BOOL WINAPI wglEnableGenlockI3D (HDC hDC);
//BOOL WINAPI wglDisableGenlockI3D (HDC hDC);
//BOOL WINAPI wglIsEnabledGenlockI3D (HDC hDC, BOOL *pFlag);
//BOOL WINAPI wglGenlockSourceI3D (HDC hDC, UINT uSource);
//BOOL WINAPI wglGetGenlockSourceI3D (HDC hDC, UINT *uSource);
//BOOL WINAPI wglGenlockSourceEdgeI3D (HDC hDC, UINT uEdge);
//BOOL WINAPI wglGetGenlockSourceEdgeI3D (HDC hDC, UINT *uEdge);
//BOOL WINAPI wglGenlockSampleRateI3D (HDC hDC, UINT uRate);
//BOOL WINAPI wglGetGenlockSampleRateI3D (HDC hDC, UINT *uRate);
//BOOL WINAPI wglGenlockSourceDelayI3D (HDC hDC, UINT uDelay);
//BOOL WINAPI wglGetGenlockSourceDelayI3D (HDC hDC, UINT *uDelay);
//BOOL WINAPI wglQueryGenlockMaxSourceDelayI3D (HDC hDC, UINT *uMaxLineDelay, UINT *uMaxPixelDelay);

// WGL_I3D_image_buffer
//LPVOID WINAPI wglCreateImageBufferI3D (HDC hDC, DWORD dwSize, UINT uFlags);
//BOOL WINAPI wglDestroyImageBufferI3D (HDC hDC, LPVOID pAddress);
//BOOL WINAPI wglAssociateImageBufferEventsI3D (HDC hDC, const HANDLE *pEvent, const LPVOID *pAddress, const DWORD *pSize, UINT count);
//BOOL WINAPI wglReleaseImageBufferEventsI3D (HDC hDC, const LPVOID *pAddress, UINT count);

// WGL_I3D_swap_frame_lock
//BOOL WINAPI wglEnableFrameLockI3D (void);
//BOOL WINAPI wglDisableFrameLockI3D (void);
//BOOL WINAPI wglIsEnabledFrameLockI3D (BOOL *pFlag);
//BOOL WINAPI wglQueryFrameLockMasterI3D (BOOL *pFlag);

// WGL_I3D_swap_frame_usage
//BOOL WINAPI wglGetFrameUsageI3D (float *pUsage);
//BOOL WINAPI wglBeginFrameTrackingI3D (void);
//BOOL WINAPI wglEndFrameTrackingI3D (void);
//BOOL WINAPI wglQueryFrameTrackingI3D (DWORD *pFrameCount, DWORD *pMissedFrames, float *pLastMissedUsage);

// WGL_NV_DX_interop
//BOOL WINAPI wglDXSetResourceShareHandleNV (void *dxObject, HANDLE shareHandle);
//HANDLE WINAPI wglDXOpenDeviceNV (void *dxDevice);
//BOOL WINAPI wglDXCloseDeviceNV (HANDLE hDevice);
//HANDLE WINAPI wglDXRegisterObjectNV (HANDLE hDevice, void *dxObject, GLuint name, GLenum type, GLenum access);
//BOOL WINAPI wglDXUnregisterObjectNV (HANDLE hDevice, HANDLE hObject);
//BOOL WINAPI wglDXObjectAccessNV (HANDLE hObject, GLenum access);
//BOOL WINAPI wglDXLockObjectsNV (HANDLE hDevice, GLint count, HANDLE *hObjects);
//BOOL WINAPI wglDXUnlockObjectsNV (HANDLE hDevice, GLint count, HANDLE *hObjects);

// WGL_NV_copy_image
//BOOL WINAPI wglCopyImageSubDataNV (HGLRC hSrcRC, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, HGLRC hDstRC, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);

// WGL_NV_delay_before_swap
//BOOL WINAPI wglDelayBeforeSwapNV (HDC hDC, GLfloat seconds);

// WGL_NV_gpu_affinity
//BOOL WINAPI wglEnumGpusNV (UINT iGpuIndex, HGPUNV *phGpu);
//BOOL WINAPI wglEnumGpuDevicesNV (HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice);
//HDC WINAPI wglCreateAffinityDCNV (const HGPUNV *phGpuList);
//BOOL WINAPI wglEnumGpusFromAffinityDCNV (HDC hAffinityDC, UINT iGpuIndex, HGPUNV *hGpu);
//BOOL WINAPI wglDeleteDCNV (HDC hdc);

// WGL_NV_present_video
//int WINAPI wglEnumerateVideoDevicesNV (HDC hDc, HVIDEOOUTPUTDEVICENV *phDeviceList);
//BOOL WINAPI wglBindVideoDeviceNV (HDC hDc, unsigned int uVideoSlot, HVIDEOOUTPUTDEVICENV hVideoDevice, const int *piAttribList);
//BOOL WINAPI wglQueryCurrentContextNV (int iAttribute, int *piValue);

// WGL_NV_swap_group
//BOOL WINAPI wglJoinSwapGroupNV (HDC hDC, GLuint group);
//BOOL WINAPI wglBindSwapBarrierNV (GLuint group, GLuint barrier);
//BOOL WINAPI wglQuerySwapGroupNV (HDC hDC, GLuint *group, GLuint *barrier);
//BOOL WINAPI wglQueryMaxSwapGroupsNV (HDC hDC, GLuint *maxGroups, GLuint *maxBarriers);
//BOOL WINAPI wglQueryFrameCountNV (HDC hDC, GLuint *count);
//BOOL WINAPI wglResetFrameCountNV (HDC hDC);

// WGL_NV_vertex_array_range
//void *WINAPI wglAllocateMemoryNV (GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);
//void WINAPI wglFreeMemoryNV (void *pointer);

// WGL_NV_video_capture
//BOOL WINAPI wglBindVideoCaptureDeviceNV (UINT uVideoSlot, HVIDEOINPUTDEVICENV hDevice);
//UINT WINAPI wglEnumerateVideoCaptureDevicesNV (HDC hDc, HVIDEOINPUTDEVICENV *phDeviceList);
//BOOL WINAPI wglLockVideoCaptureDeviceNV (HDC hDc, HVIDEOINPUTDEVICENV hDevice);
//BOOL WINAPI wglQueryVideoCaptureDeviceNV (HDC hDc, HVIDEOINPUTDEVICENV hDevice, int iAttribute, int *piValue);
//BOOL WINAPI wglReleaseVideoCaptureDeviceNV (HDC hDc, HVIDEOINPUTDEVICENV hDevice);

// WGL_NV_video_output
//BOOL WINAPI wglGetVideoDeviceNV (HDC hDC, int numDevices, HPVIDEODEV *hVideoDevice);
//BOOL WINAPI wglReleaseVideoDeviceNV (HPVIDEODEV hVideoDevice);
//BOOL WINAPI wglBindVideoImageNV (HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer);
//BOOL WINAPI wglReleaseVideoImageNV (HPBUFFERARB hPbuffer, int iVideoBuffer);
//BOOL WINAPI wglSendPbufferToVideoNV (HPBUFFERARB hPbuffer, int iBufferType, unsigned long *pulCounterPbuffer, BOOL bBlock);
//BOOL WINAPI wglGetVideoInfoNV (HPVIDEODEV hpVideoDevice, unsigned long *pulCounterOutputPbuffer, unsigned long *pulCounterOutputVideo);

// WGL_OML_sync_control
//BOOL WINAPI wglGetSyncValuesOML (HDC hdc, INT64 *ust, INT64 *msc, INT64 *sbc);
//BOOL WINAPI wglGetMscRateOML (HDC hdc, INT32 *numerator, INT32 *denominator);
//INT64 WINAPI wglSwapBuffersMscOML (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder);
//INT64 WINAPI wglSwapLayerBuffersMscOML (HDC hdc, INT fuPlanes, INT64 target_msc, INT64 divisor, INT64 remainder);
//BOOL WINAPI wglWaitForMscOML (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder, INT64 *ust, INT64 *msc, INT64 *sbc);
//BOOL WINAPI wglWaitForSbcOML (HDC hdc, INT64 target_sbc, INT64 *ust, INT64 *msc, INT64 *sbc);

#undef BKSGE_WGLEXT_FUNC

BKSGE_WARNING_POP()

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // defined(BKSGE_PLATFORM_WIN32)

#endif // BKSGE_RENDER_GL_DETAIL_WGL_INL_WGLEXT_INL_HPP
