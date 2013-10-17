#ifndef _INCLUDED_DISTR_GLWRAP_H
#define _INCLUDED_DISTR_GLWRAP_H

#include <utility>
#include <cstdint>
#include <string>
#include <limits>
#include <type_traits>

#if defined(GLWRAP_ENABLE_ASSERTS) && !defined(GLWRAP_ASSERT_CALLBACK)
#ifdef assert
#define GLWRAP_OLD_ASSERT_DEFINE assert
#endif
#include <cassert>
#endif

namespace gw
{

#ifdef GLWRAP_ENABLE_ASSERTS
#ifdef GLWRAP_ASSERT_CALLBACK
#define GLWRAP_ASSERT(x, m) GLWRAP_ASSERT_CALLBACK(x, m)
#else
#define GLWRAP_ASSERT(x, m) assert((x) && m)
#endif

#else

#define GLWRAP_ASSERT(x, m)

#endif

#ifdef GLWRAP_ENABLE_TYPECHECK

#define GLWRAP_TYPECHECK2(t, x) GLWRAP_ASSERT(t(x), "Handle refers to correct GL object type")
#define GLWRAP_TYPECHECK(t, x) GLWRAP_TYPECHECK2(t, x)

#else

#define GLWRAP_TYPECHECK(t, x)

#endif

#ifdef GLWRAP_ENABLE_ACTIVECHECK

#define GLWRAP_ATTACH_HANDLE(active, handle) (ActiveHandle::attachHandle(active, handle))
#define GLWRAP_CHECK_ACTIVE(target, cond) if (cond) GLWRAP_ASSERT(isActive(target), "Handle is active")

#else

#define GLWRAP_ATTACH_HANDLE(active, handle) (active)
#define GLWRAP_CHECK_ACTIVE(target, cond)

#endif

#define GLWRAP_MAKE_OCLASS_BEGIN(OClassName, ClassName) \
class OClassName : public ClassName \
{ \
public: \
	OClassName() : ClassName() { } \
	OClassName(ClassName c) : ClassName(c) { } \
	OClassName(GLuint handle) : ClassName(handle) { } \
	OClassName(OClassName&& o) : ClassName(std::move(o)) { o.m_handle = 0; } \
	void swap(OClassName& o) { ClassName::swap(o); } \
	OClassName& operator=(OClassName o) { swap(o); return *this; } \
	~OClassName() \
	{ \
		free(); \
	} \
private: \
	OClassName(const OClassName&); \
public:

#define GLWRAP_MAKE_OCLASS_BEGIN_NO_HANDLE(OClassName, ClassName) \
class OClassName : public ClassName \
{ \
public: \
	OClassName() : ClassName() { } \
	OClassName(ClassName c) : ClassName(c) { } \
	OClassName(OClassName&& o) : ClassName(std::move(o)) { o.m_handle = 0; } \
	void swap(OClassName& o) { ClassName::swap(o); } \
	OClassName& operator=(OClassName o) { swap(o); return *this; } \
	~OClassName() \
	{ \
		free(); \
	} \
private: \
	OClassName(const OClassName&); \
public:

#define GLWRAP_MAKE_OCLASS_END() };

// -------
// | Enums
// -------

#ifndef GLWRAP_NO_ENUMS

enum EnumShaderType
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
	GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
};

enum EnumTextureBuffer
{
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
};

enum EnumTextureTarget
{
	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_3D = GL_TEXTURE_3D,
	TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
	TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
	TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
	TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
	TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
	TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
};

enum EnumUnsignedType
{
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT,
};
enum EnumSignedType
{
	BYTE = GL_BYTE,
	SHORT = GL_SHORT,
	INT = GL_INT,
};
enum EnumFloat
{
	FLOAT = GL_FLOAT,
};
enum EnumDouble
{
	DOUBLE = GL_DOUBLE,
};
enum EnumHalfFloat
{
	HALF_FLOAT = GL_HALF_FLOAT,
};
enum Enum2101010RevInt
{
	INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
};
enum Enum2101010RevUInt
{
	UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
};
enum EnumPixelFormat
{
	RED = GL_RED,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
};
enum EnumInvPixelFormat
{
	BGR = GL_BGR,
	BGRA = GL_BGRA,
};
enum EnumDepthFormat
{
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	DEPTH_STENCIL = GL_DEPTH_STENCIL,
};
enum EnumSizedPixelFormat
{
	R8 = GL_R8,
	RG8 = GL_RG8,
	RGB8 = GL_RGB8,
	RGBA8 = GL_RGBA8,
};
enum EnumPixelType
{
	UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
	UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
	UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
	UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
	UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
	UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
	UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
	UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
	UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
	UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
	UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
};

enum EnumRenderMode
{
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
};

enum EnumMagFilterMode
{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
};

enum EnumMinFilterMode
{
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
};

enum EnumWrapMode
{
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	REPEAT = GL_REPEAT,
};

enum EnumBlendFactor
{
	ZERO = GL_ZERO,
	ONE = GL_ONE,
	SRC_COLOR = GL_SRC_COLOR,
	ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
	DST_COLOR = GL_DST_COLOR,
	ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
	SRC_ALPHA = GL_SRC_ALPHA,
	ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
	DST_ALPHA = GL_DST_ALPHA,
	ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
	CONSTANT_COLOR = GL_CONSTANT_COLOR,
	ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
	CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
	ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
};

enum EnumBlendEquation
{
	FUNC_ADD = GL_FUNC_ADD,
	FUNC_SUBTRACT = GL_FUNC_SUBTRACT,
	FUNC_REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
	MIN = GL_MIN,
	MAX = GL_MAX,
};

enum EnumDeleteStatus
{
	DELETE_STATUS = GL_DELETE_STATUS,
};

enum EnumInfoLogLength
{
	INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
};

enum EnumShaderParamName
{
	SHADER_TYPE = GL_SHADER_TYPE,
	COMPILE_STATUS = GL_COMPILE_STATUS,
	SHADER_SOURCE_LENGTH = GL_SHADER_SOURCE_LENGTH,
};

enum EnumProgramParamName
{
	LINK_STATUS = GL_LINK_STATUS,
	VALIDATE_STATUS = GL_VALIDATE_STATUS,
	ATTACHED_SHADERS = GL_ATTACHED_SHADERS,
	ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES,
	ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
	ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS,
	ACTIVE_UNIFORM_BLOCKS = GL_ACTIVE_UNIFORM_BLOCKS,
	ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
	ACTIVE_UNIFORM_MAX_LENGTH = GL_ACTIVE_UNIFORM_MAX_LENGTH,
	TRANSFORM_FEEDBACK_BUFFER_MODE = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
	TRANSFORM_FEEDBACK_VARYINGS = GL_TRANSFORM_FEEDBACK_VARYINGS,
	TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
	GEOMETRY_VERTICES_OUT = GL_GEOMETRY_VERTICES_OUT,
	GEOMETRY_INPUT_TYPE = GL_GEOMETRY_INPUT_TYPE,
	GEOMETRY_OUTPUT_TYPE = GL_GEOMETRY_OUTPUT_TYPE,
};

enum EnumBufferUsage
{
	STREAM_DRAW = GL_STREAM_DRAW,
	STREAM_READ = GL_STREAM_READ,
	STREAM_COPY = GL_STREAM_COPY,
	STATIC_DRAW = GL_STATIC_DRAW,
	STATIC_READ = GL_STATIC_READ,
	STATIC_COPY = GL_STATIC_COPY,
	DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
	DYNAMIC_READ = GL_DYNAMIC_READ,
	DYNAMIC_COPY = GL_DYNAMIC_COPY,
};

enum EnumBufferTarget
{
	ARRAY_BUFFER = GL_ARRAY_BUFFER,
	COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
	COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
	ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
	PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
	PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
	TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
	UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
};

enum EnumRenderbuffer
{
	RENDERBUFFER = GL_RENDERBUFFER,
};

enum EnumFramebufferTarget
{
	DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER,
	READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
	FRAMEBUFFER = GL_FRAMEBUFFER,
};

enum EnumFramebufferAttachment
{
	COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0,
	DEPTH_ATTACHMENT = GL_DEPTH_ATTACHMENT,
	STENCIL_ATTACHMENT = GL_STENCIL_ATTACHMENT,
	DEPTH_STENCIL_ATTACHMENT = GL_DEPTH_STENCIL_ATTACHMENT,
};

#define GLWRAP_ENUM_BEGIN(ClassName) class ClassName { private: GLenum m_value; \
public: \
	operator GLenum() const { return m_value; } \
	ClassName() : m_value(GL_NONE) { } \
	template <typename T> \
	ClassName(T t, typename std::enable_if<!std::is_enum<T>::value,int>::type=0) : m_value((GLenum)t) { }
#define GLWRAP_ENUM_ALLOW(ClassName, EnumName) public: ClassName(EnumName e) : m_value((GLenum)e) { }
#define GLWRAP_ENUM_END() };

#else //GLWRAP_NO_ENUMS

#define GLWRAP_ENUM_BEGIN(name) typedef GLenum name;
#define GLWRAP_ENUM_ALLOW(c, e)
#define GLWRAP_ENUM_END()

#endif//GLWRAP_NO_ENUMS

GLWRAP_ENUM_BEGIN(ShaderType)
GLWRAP_ENUM_ALLOW(ShaderType, EnumShaderType)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(RenderMode)
GLWRAP_ENUM_ALLOW(RenderMode, EnumRenderMode)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(IndexType)
GLWRAP_ENUM_ALLOW(IndexType, EnumUnsignedType)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(MinFilterMode)
GLWRAP_ENUM_ALLOW(MinFilterMode, EnumMagFilterMode)
GLWRAP_ENUM_ALLOW(MinFilterMode, EnumMinFilterMode)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(MagFilterMode)
GLWRAP_ENUM_ALLOW(MagFilterMode, EnumMagFilterMode)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(WrapMode)
GLWRAP_ENUM_ALLOW(WrapMode, EnumWrapMode)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(PixelType)
GLWRAP_ENUM_ALLOW(PixelType, EnumUnsignedType)
GLWRAP_ENUM_ALLOW(PixelType, EnumSignedType)
GLWRAP_ENUM_ALLOW(PixelType, EnumFloat)
GLWRAP_ENUM_ALLOW(PixelType, EnumPixelType)
GLWRAP_ENUM_ALLOW(PixelType, Enum2101010RevUInt)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(PixelFormat)
GLWRAP_ENUM_ALLOW(PixelFormat, EnumPixelFormat)
GLWRAP_ENUM_ALLOW(PixelFormat, EnumInvPixelFormat)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(InternalFormat)
GLWRAP_ENUM_ALLOW(InternalFormat, EnumPixelFormat)
GLWRAP_ENUM_ALLOW(InternalFormat, EnumDepthFormat)
GLWRAP_ENUM_ALLOW(InternalFormat, EnumSizedPixelFormat)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(TextureTarget)
GLWRAP_ENUM_ALLOW(TextureTarget, EnumTextureTarget)
GLWRAP_ENUM_ALLOW(TextureTarget, EnumTextureBuffer)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(BlendFactor)
GLWRAP_ENUM_ALLOW(BlendFactor, EnumBlendFactor)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(BlendEquation)
GLWRAP_ENUM_ALLOW(BlendEquation, EnumBlendEquation)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(AttribType)
GLWRAP_ENUM_ALLOW(AttribType, EnumSignedType)
GLWRAP_ENUM_ALLOW(AttribType, EnumUnsignedType)
GLWRAP_ENUM_ALLOW(AttribType, EnumFloat)
GLWRAP_ENUM_ALLOW(AttribType, EnumDouble)
GLWRAP_ENUM_ALLOW(AttribType, EnumHalfFloat)
GLWRAP_ENUM_ALLOW(AttribType, Enum2101010RevInt)
GLWRAP_ENUM_ALLOW(AttribType, Enum2101010RevUInt)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(ShaderParamName)
GLWRAP_ENUM_ALLOW(ShaderParamName, EnumShaderParamName)
GLWRAP_ENUM_ALLOW(ShaderParamName, EnumDeleteStatus)
GLWRAP_ENUM_ALLOW(ShaderParamName, EnumInfoLogLength)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(ProgramParamName)
GLWRAP_ENUM_ALLOW(ProgramParamName, EnumProgramParamName)
GLWRAP_ENUM_ALLOW(ProgramParamName, EnumDeleteStatus)
GLWRAP_ENUM_ALLOW(ProgramParamName, EnumInfoLogLength)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(BufferUsage)
GLWRAP_ENUM_ALLOW(BufferUsage, EnumBufferUsage)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(BufferTarget)
GLWRAP_ENUM_ALLOW(BufferTarget, EnumBufferTarget)
GLWRAP_ENUM_ALLOW(BufferTarget, EnumTextureBuffer)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(RenderbufferTarget)
GLWRAP_ENUM_ALLOW(RenderbufferTarget, EnumRenderbuffer)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(FramebufferTarget)
GLWRAP_ENUM_ALLOW(FramebufferTarget, EnumFramebufferTarget)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(FramebufferAttachment)
GLWRAP_ENUM_ALLOW(FramebufferAttachment, EnumFramebufferAttachment)
GLWRAP_ENUM_END()

// --------
// | Handle
// --------

class Handle
{
public:
	Handle()
		: m_handle(0)
	{ }
	explicit Handle(GLuint handle)
		: m_handle(handle)
	{ }
	void swap(Handle& h)
	{
		std::swap(m_handle, h.m_handle);
	}
	Handle& Handle::operator=(Handle hw)
	{
		swap(hw);
		return *this;
	}
	GLuint get() const { return m_handle; }
	bool initialized() const { return m_handle != 0; }

	GLuint releaseHandle()
	{
		GLuint handle = m_handle;
		m_handle = 0;
		return handle;
	}
protected:
	GLuint m_handle;
};

// --------------
// | ActiveHandle
// --------------

class ActiveHandle
{
public:
	ActiveHandle()
																				#ifdef  GLWRAP_ENABLE_ACTIVECHECK
		: m_handle(0)
																				#endif//GLWRAP_ENABLE_ACTIVECHECK
	{ }

																				#ifdef  GLWRAP_ENABLE_ACTIVECHECK
	template <typename T>
	static T attachHandle(T t, GLuint handle)
	{ t.m_handle = handle; return t; }

	bool isHandle(GLuint handle) const
	{
		if (m_handle == 0) return true;
		else return handle == m_handle;
	}

	bool isActive(GLenum target) const
	{
		if (m_handle == 0) return true;
		int bound;
		glGetIntegerv(target, &bound);
		return (GLuint)bound == m_handle;
	}

	GLuint getHandle() const { return m_handle; }
																				#endif

protected:
																				#ifdef  GLWRAP_ENABLE_ACTIVECHECK
	GLuint m_handle;
																				#endif//GLWRAP_ENABLE_ACTIVECHECK
};

// ---------------
// | TActiveHandle
// ---------------

class TActiveHandle : public ActiveHandle
{
public:
	TActiveHandle(GLenum target)
		: m_target(target)
	{ }

	GLenum getTarget() const { return m_target; }

protected:
	GLenum m_target;
};

// ------
// | Wrap
// ------

struct Wrap
{
public:
	Wrap()
		: s(GL_NONE), t(GL_NONE), r(GL_NONE)
	{ }
	Wrap(WrapMode s, WrapMode t, WrapMode r=GL_NONE)
		: s(s), t(t), r(r)
	{ }

	WrapMode s, t, r;

	static const Wrap Clamp;
	static const Wrap Repeat;
	static const Wrap Mirror;
};

const Wrap Wrap::Clamp(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
const Wrap Wrap::Repeat(GL_REPEAT, GL_REPEAT);
const Wrap Wrap::Mirror(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);

// --------
// | Filter
// --------

struct Filter
{
public:
	Filter()
		: min(GL_NONE), mag(GL_NONE)
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		, max_anisotropy(0)
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
	{ }
	Filter(MinFilterMode min, MagFilterMode mag
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		, GLint max_anisotropy=0
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
		)
		: min(min), mag(mag)
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		, max_anisotropy(max_anisotropy)
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
	{ }

	MinFilterMode min;
	MagFilterMode mag;
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
	GLint max_anisotropy;
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
	static const Filter Nearest;
	static const Filter Bilinear;
	static const Filter Trilinear;
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
	static Filter Anisotropic(GLint max_anisotropy)
	{
		return Filter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, max_anisotropy);
	}
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
};
const Filter Filter::Nearest(GL_NEAREST, GL_NEAREST);
const Filter Filter::Bilinear(GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR);
const Filter Filter::Trilinear(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

// ---------------
// | ActiveTexture
// ---------------

class ActiveTexture : public TActiveHandle
{
public:
	explicit ActiveTexture(TextureTarget target=GL_TEXTURE_2D)
		: TActiveHandle(target)
	{ }

	int getWidth() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);
		int w;
		glGetTexLevelParameteriv(m_target, 0, GL_TEXTURE_WIDTH, &w);
		return w;
	}
	int getHeight() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);
		int h;
		glGetTexLevelParameteriv(m_target, 0, GL_TEXTURE_WIDTH, &h);
		return h;
	}

	void setFilter(const Filter& filter)
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);

		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, filter.min);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, filter.mag);
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		glTexParameteri(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, filter.max_anisotropy);
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
	}
	Filter getFilter() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);

		Filter filter;
		glGetTexParameteriv(m_target, GL_TEXTURE_MIN_FILTER, (GLint*)&filter.min);
		glGetTexParameteriv(m_target, GL_TEXTURE_MAG_FILTER, (GLint*)&filter.mag);
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		glGetTexParameteriv(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, &filter.max_anisotropy);
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
		return filter;
	}

	void setWrap(const Wrap& wrap)
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap.s);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrap.t);
	}
	Wrap getWrap() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);

		Wrap wrap;
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_S, (GLint*)&wrap.s);
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_T, (GLint*)&wrap.t);
		return wrap;
	}

	void image2D(GLint level, InternalFormat internalformat, GLint width, GLint height, GLint border, PixelFormat format, PixelType type, GLvoid* pixels)
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);
		glTexImage2D(m_target, level, internalformat, width, height, border, format, type, pixels);
	}

	void unbind()
	{
		glBindTexture(m_target, 0);
	}
};

// ---------
// | Texture
// ---------

class Texture : public Handle
{
public:
	Texture()
		: Handle()
	{
	}
	explicit Texture(GLuint handle)
		: Handle(handle)
	{
		GLWRAP_TYPECHECK(glIsTexture, handle);
	}
	void swap(Texture& tex)
	{
		Handle::swap(tex);
	}
	Texture& operator=(Texture t)
	{
		swap(t);													
		return *this;
	}
	void free()
	{
		if (m_handle)
		{
			glDeleteTextures(1, &m_handle);
			m_handle = 0;
		}
	}

	ActiveTexture bind(TextureTarget target=GL_TEXTURE_2D) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Texture is initialized");
		glBindTexture(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(ActiveTexture(target), m_handle);
	}
	static void unbind(TextureTarget target=GL_TEXTURE_2D)
	{
		glBindTexture(target, 0);
	}
	static void enable()
	{
		glEnable(GL_TEXTURE);
	}
	static void disable()
	{
		glDisable(GL_TEXTURE);
	}

	void gen()
	{
		glGenTextures(1, &m_handle);
	}
	static Texture create()
	{
		Texture tex;
		tex.gen();
		return tex;
	}
	
};
GLWRAP_MAKE_OCLASS_BEGIN(OTexture, Texture);
GLWRAP_MAKE_OCLASS_END();

// -----------------
// | ActiveTexture3D
// -----------------

class ActiveTexture3D : public ActiveTexture
{
public:
	ActiveTexture3D(TextureTarget target=GL_TEXTURE_3D)
		: ActiveTexture(target)
	{ }
	int getWidth() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D);
		return ActiveTexture::getWidth();
	}
	int getHeight() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D);
		return ActiveTexture::getHeight();
	}

	void setFilter(const Filter& filter)
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D);
		ActiveTexture::setFilter(filter);
	}
	Filter getFilter() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D);
		return ActiveTexture::getFilter();
	}

	void setWrap(const Wrap& wrap)
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D);

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap.s);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrap.t);
		if (wrap.r != GL_NONE)
			glTexParameteri(m_target, GL_TEXTURE_WRAP_R, wrap.r);
	}
	Wrap getWrap() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D);

		Wrap wrap;
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_S, (GLint*)&wrap.s);
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_T, (GLint*)&wrap.t);
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_R, (GLint*)&wrap.r);
		return wrap;
	}

	void unbind()
	{
		glBindTexture(m_target, 0);
	}
};

																				#ifndef GLWRAP_NO_TEXTURE3D
// -----------
// | Texture3D
// -----------

class Texture3D : public Texture
{
public:
	Texture3D()
		: Texture()
	{
	}
	explicit Texture3D(GLuint handle)
		: Texture(handle)
	{
		GLWRAP_TYPECHECK(glIsTexture, handle);
	}
	void swap(Texture3D& tex)
	{
		Texture::swap(tex);
	}
	Texture3D& operator=(Texture3D t)
	{
		swap(t);													
		return *this;
	}

	ActiveTexture bind(TextureTarget target=GL_TEXTURE_3D) const
	{
		Texture::bind(target);
		return GLWRAP_ATTACH_HANDLE(ActiveTexture3D(target), m_handle);
	}
	static void unbind(TextureTarget target=GL_TEXTURE_3D)
	{
		Texture::unbind(target);
	}

	static Texture3D create()
	{
		Texture3D t;
		t.gen();
		return t;
	}
};
GLWRAP_MAKE_OCLASS_BEGIN(OTexture3D, Texture3D);
GLWRAP_MAKE_OCLASS_END();
																				#endif//GLWRAP_NO_TEXTURE3D

																				#ifndef GLWRAP_NO_SAMPLER

// ---------------
// | ActiveSampler
// ---------------

class ActiveSampler : public ActiveHandle
{
public:
	ActiveSampler(GLuint unit=0)
		: m_unit(unit)
	{ }

	void unbind()
	{
		glBindSampler(m_unit, 0);
	}
private:
	GLuint m_unit;
};

// ---------
// | Sampler
// ---------												

class Sampler : public Handle
{
public:
	Sampler()
		: Handle()
	{ }
	explicit Sampler(GLuint handle)
		: Handle(handle)
	{
		GLWRAP_TYPECHECK(glIsSampler, handle);
	}
	void swap(Sampler& s)
	{
		Handle::swap(s);
	}
	Sampler& operator=(Sampler s)
	{
		swap(s);
		return *this;
	}
	void free()
	{
		if (m_handle)
		{
			glDeleteSamplers(1, &m_handle);
			m_handle = 0;
		}
	}

	ActiveSampler bind(GLuint unit=0) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		glBindSampler(unit, m_handle);
		return GLWRAP_ATTACH_HANDLE(ActiveSampler(unit), m_handle);
	}
	static void unbind(GLuint unit=0)
	{
		glBindSampler(unit, 0);
	}

	void setFilter(const Filter& filter)
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		glSamplerParameteri(m_handle, GL_TEXTURE_MIN_FILTER, filter.min);
		glSamplerParameteri(m_handle, GL_TEXTURE_MAG_FILTER, filter.mag);
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		glSamplerParameteri(m_handle, GL_TEXTURE_MAX_ANISOTROPY_EXT, filter.max_anisotropy);
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
	}
	Filter getFilter() const
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		Filter filter;
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_MIN_FILTER, (GLint*)&filter.min);
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_MAG_FILTER, (GLint*)&filter.mag);
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_MAX_ANISOTROPY_EXT, &filter.max_anisotropy);
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
		return filter;
	}

	void setWrap(const Wrap& wrap)
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_S, wrap.s);
		glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_T, wrap.t);
		if (wrap.r != GL_NONE)
			glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_R, wrap.r);
	}
	Wrap getWrap() const
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		Wrap wrap;
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_WRAP_S, (GLint*)&wrap.s);
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_WRAP_T, (GLint*)&wrap.t);
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_WRAP_R, (GLint*)&wrap.r);
		return wrap;
	}

	void gen()
	{
		GLWRAP_ASSERT(m_handle == 0, "Sampler is uninitialized");
		glGenSamplers(1, &m_handle);
	}

	static Sampler create()
	{
		Sampler s;
		s.gen();
		return s;
	}
};
GLWRAP_MAKE_OCLASS_BEGIN(OSampler, Sampler);
GLWRAP_MAKE_OCLASS_END();

																				#endif//GLWRAP_NO_SAMPLER

// -------
// | Blend
// -------

struct Blend
{
	Blend()
		: src(GL_NONE), dst(GL_NONE)
																				#ifndef GLWRAP_NO_BLEND_SEPARATE
		, alphaSrc(GL_NONE), alphaDst(GL_NONE)
																				#endif//GLWRAP_NO_BLEND_SEPARATE
																				#ifndef GLWRAP_NO_BLEND_MODE
		, mode(GL_NONE)
																				#ifndef GLWRAP_NO_BLEND_SEPARATE
		, alphaMode(GL_NONE)
																				#endif//GLWRAP_NO_BLEND_SEPARATE
																				#endif//GLWRAP_NO_BLEND_MODE
	{ }
	Blend(BlendFactor src, BlendFactor dst
																				#ifndef GLWRAP_NO_BLEND_MODE
		, BlendEquation mode=GL_FUNC_ADD
																				#endif//GLWRAP_NO_BLEND_MODE
		)
		: src(src), dst(dst)
		, alphaSrc(GL_NONE), alphaDst(GL_NONE)
																				#ifndef GLWRAP_NO_BLEND_MODE
		, mode(mode), alphaMode(GL_NONE)
																				#endif//GLWRAP_NO_BLEND_MODE
	{ }

																				#ifndef GLWRAP_NO_BLEND_SEPARATE
	Blend(BlendFactor src, BlendFactor dst, BlendFactor alphaSrc, BlendFactor alphaDst
																				#ifndef GLWRAP_NO_BLEND_MODE
		, BlendEquation mode=GL_FUNC_ADD, BlendEquation alphaMode=GL_FUNC_ADD
																				#endif//GLWRAP_NO_BLEND_MODE
		)
		: src(src), dst(dst)
		, alphaSrc(alphaSrc), alphaDst(alphaDst)
																				#ifndef GLWRAP_NO_BLEND_MODE
		, mode(mode), alphaMode(alphaMode)
																				#endif//GLWRAP_NO_BLEND_MODE
	{ }
																				#endif//GLWRAP_NO_BLEND_SEPARATE

	void apply() const
	{
		// If one of blend components is empty the other one must be
		GLWRAP_ASSERT((src != GL_NONE) == (dst != GL_NONE), "Source and destination are both defined or undefined");
																				#ifndef GLWRAP_NO_BLEND_SEPARATE
		GLWRAP_ASSERT((alphaSrc != GL_NONE) == (alphaDst != GL_NONE), "Alpha source and destination are both defined or undefined");
		// Alpha blend mode requires color blend mode
		GLWRAP_ASSERT((alphaSrc == GL_NONE) || (src != GL_NONE), "If alpha blending is defined color blending must be defined too");
																				#endif//GLWRAP_NO_BLEND_SEPARATE

		if (!src) {
			glDisable(GL_BLEND);
		} else {
			glEnable(GL_BLEND);
																				#ifndef GLWRAP_NO_BLEND_SEPARATE
			if (alphaSrc) {
																				#ifndef GLWRAP_NO_BLEND_MODE
				glBlendEquationSeparate(mode, alphaMode);
																				#endif//GLWRAP_NO_BLEND_MODE
				glBlendFuncSeparate(src, dst, alphaSrc, alphaDst);

			} else
																				#endif//GLWRAP_NO_BLEND_SEPARATE	
			{
																				#ifndef GLWRAP_NO_BLEND_MODE
				glBlendEquation(mode);
																				#endif//GLWRAP_NO_BLEND_MODE
				glBlendFunc(src, dst);
			}
		}
	}

	BlendFactor src, dst;
																				#ifndef GLWRAP_NO_BLEND_SEPARATE
	BlendFactor alphaSrc, alphaDst;
																				#endif//GLWRAP_NO_BLEND_SEPARATE
																				#ifndef GLWRAP_NO_BLEND_MODE
	BlendEquation mode, alphaMode;
																				#endif//GLWRAP_NO_BLEND_MODE

	static const Blend None;
	static const Blend Additive;
	static const Blend AdditiveAlpha;
	static const Blend AlphaBlend;
	static const Blend Opaque;
	static const Blend Mulitply;
};
const Blend Blend::None;
const Blend Blend::Additive(GL_ONE, GL_ONE);
const Blend Blend::AdditiveAlpha(GL_SRC_ALPHA, GL_ONE);
const Blend Blend::AlphaBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
const Blend Blend::Opaque(GL_ONE, GL_ZERO);
const Blend Blend::Mulitply(GL_ZERO, GL_SRC_COLOR);

// -------
// | Color
// -------

struct Color
{
public:
	Color(float r, float g, float b, float a=1.0f)
		: r(r), g(g), b(b), a(a)
	{ }
	static Color rgb(uint32_t col)
	{
		return Color(
			(col >> 16 & 0xFF) / 255.0f,
			(col >> 8  & 0xFF) / 255.0f,
			(col >> 0  & 0xFF) / 255.0f);
	}
	static Color rgba(uint32_t col)
	{
		return Color(
			(col >> 24 & 0xFF) / 255.0f,
			(col >> 16 & 0xFF) / 255.0f,
			(col >> 8  & 0xFF) / 255.0f,
			(col >> 0  & 0xFF) / 255.0f);
	}

	float r, g, b, a;
};

// ---------------------
// | VertexAttribPointer
// ---------------------

struct VertexAttribPointer
{
public:
	VertexAttribPointer()
		: size(-1)
	{ }
	VertexAttribPointer(GLuint index, GLint size, AttribType type, GLboolean normalized, GLsizei stride, GLvoid *pointer)
		: index(index)
		, size(size)
		, type(type)
		, normalized(normalized)
		, stride(stride)
		, pointer(pointer)
	{ }

	void enable() const
	{
		GLWRAP_ASSERT(size != -1, "VertexAttribPointer is initialized");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}
	void disable() const 
	{
		GLWRAP_ASSERT(size != -1, "VertexAttribPointer is initialized");
		glDisableVertexAttribArray(index);
	}

	GLuint index;
	GLint size;
	AttribType type;
	GLboolean normalized;
	GLsizei stride;
	GLvoid *pointer;
};

// --------------------------
// | NamedVertexAttribPointer
// --------------------------

struct NamedVertexAttribPointer : public VertexAttribPointer
{
public:
	NamedVertexAttribPointer()
		: VertexAttribPointer()
	{ }
	NamedVertexAttribPointer(GLuint index, GLint size, AttribType type, GLboolean normalized, GLsizei stride, GLvoid *pointer, std::string name)
		: VertexAttribPointer(index, size, type, normalized, stride, pointer)
		, name(std::move(name))
	{ }

	std::string name;
};

// --------
// | Shader
// --------

class Shader : public Handle
{
public:
	Shader()
		: Handle()
	{ }
	Shader(GLuint handle)
		: Handle(handle)
	{
		GLWRAP_TYPECHECK(glIsShader, handle);
	}
	void swap(Shader& s)
	{
		Handle::swap(s);
	}
	Shader& operator=(Shader p)
	{
		swap(p);
		return *this;
	}
	void free()
	{
		if (m_handle)
		{
			glDeleteShader(m_handle);
			m_handle = 0;
		}
	}

	void source(const GLchar* source)
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		glShaderSource(m_handle, 1, &source, nullptr);
	}
	void source(const GLchar* source, GLint length)
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		glShaderSource(m_handle, 1, &source, &length);
	}
	void source(const std::string& source)
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		const GLchar* data = source.data();
		GLint size = source.size();
		glShaderSource(m_handle, 1, &data, &size);
	}
	void source(GLint num, const GLchar** sources, const GLint* lengths=nullptr)
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		glShaderSource(m_handle, num, sources, lengths);
	}

	void compile()
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		GLWRAP_ASSERT(getParam(GL_SHADER_SOURCE_LENGTH) != 0, "Shader has no source");
		glCompileShader(m_handle);
	}

	GLint getParam(ShaderParamName pname) const
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		GLint t;
		glGetShaderiv(m_handle, pname, &t);
		return t;
	}

	GLint getInfoLogLength() const
	{
		return getParam(GL_INFO_LOG_LENGTH);
	}
	void getInfoLog(GLsizei bufSize, GLsizei *length, GLchar* infoLog) const
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		glGetShaderInfoLog(m_handle, bufSize, length, infoLog);
	}
	std::string getInfoLog() const
	{
		std::string str;
		GLint len = getInfoLogLength();
		str.resize(len + 1);
		getInfoLog(str.size(), nullptr, &str[0]);
		str.resize(len);
		return str;
	}

	static Shader create(ShaderType type)
	{
		return Shader(glCreateShader(type));
	}
};

GLWRAP_MAKE_OCLASS_BEGIN_NO_HANDLE(OShader, Shader);
OShader(GLuint handle) : Shader(handle) { }
GLWRAP_MAKE_OCLASS_END();

// ---------------
// | ActiveProgram
// ---------------

class ActiveProgram : public ActiveHandle
{
public:
	void uniform(GLint location, GLfloat v0) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform1f(location, v0); }
	void uniform(GLint location, GLfloat v0, GLfloat v1) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform2f(location, v0, v1); }
	void uniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform3f(location, v0, v1, v2); }
	void uniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform4f(location, v0, v1, v2, v3); }

	void uniform(GLint location, GLint v0) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform1i(location, v0); }
	void uniform(GLint location, GLint v0, GLint v1) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform2i(location, v0, v1); }
	void uniform(GLint location, GLint v0, GLint v1, GLint v2) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform3i(location, v0, v1, v2); }
	void uniform(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform4i(location, v0, v1, v2, v3); }

	void uniform(GLint location, GLuint v0) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform1ui(location, v0); }
	void uniform(GLint location, GLuint v0, GLuint v1) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform2ui(location, v0, v1); }
	void uniform(GLint location, GLuint v0, GLuint v1, GLuint v2) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform3ui(location, v0, v1, v2); }
	void uniform(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform4ui(location, v0, v1, v2, v3); }

																				#ifdef  GLWRAP_GLM
	void uniform(GLint location, const glm::vec2& v) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform2fv(location, glm::value_ptr(v)); }
	void uniform(GLint location, const glm::vec3& v) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform3fv(location, glm::value_ptr(v)); }
	void uniform(GLint location, const glm::vec4& v) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform4fv(location, glm::value_ptr(v)); }
																				#endif//GLWRAP_GLM

	void unuse()
	{
		glUseProgram(0);
	}
};

// ---------
// | Program
// ---------

class Program : public Handle
{
public:
	Program()
		: Handle()
	{ }
	explicit Program(GLuint handle)
		: Handle(handle)
	{
		GLWRAP_TYPECHECK(glIsProgram, handle);
	}
	void swap(Program& p)
	{
		Handle::swap(p);
	}
	Program& operator=(Program p)
	{
		swap(p);
		return *this;
	}
	void free()
	{
		if (m_handle)
		{
			glDeleteProgram(m_handle);
			m_handle = 0;
		}
	}

	void attachShader(Shader shader)
	{
		GLWRAP_ASSERT(m_handle != 0, "Program is initialized");
		GLWRAP_ASSERT(shader.initialized(), "Shader to attach is initialized");
		glAttachShader(m_handle, shader.get());
	}

	void detachShader(Shader shader)
	{
		GLWRAP_ASSERT(m_handle != 0, "Program is initialized");
		GLWRAP_ASSERT(shader.initialized(), "Shader to attach is initialized");
		glDetachShader(m_handle, shader.get());
	}

	void link()
	{
		glLinkProgram(m_handle);
	}

	ActiveProgram use() const
	{
		GLWRAP_ASSERT(m_handle != 0, "Program is initialized");
		GLWRAP_ASSERT(getParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		glUseProgram(m_handle);
		return GLWRAP_ATTACH_HANDLE(ActiveProgram(), m_handle);
	}
	
	GLint getParam(ProgramParamName pname) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Program is initialized");
		GLint t;
		glGetProgramiv(m_handle, pname, &t);
		return t;
	}

	GLint getUniformLocation(const GLchar* name) const
	{
		GLWRAP_ASSERT(getParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		return glGetUniformLocation(m_handle, name);
	}
	GLint getUniformLocation(const std::string& name) const
	{
		GLWRAP_ASSERT(getParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		return getUniformLocation(name.c_str());
	}

	GLint getAttribLocation(const GLchar* name) const
	{
		GLWRAP_ASSERT(getParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		return glGetAttribLocation(m_handle, name);
	}
	GLint getAttribLocation(const std::string& name) const
	{
		GLWRAP_ASSERT(getParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		return glGetAttribLocation(m_handle, name.c_str());
	}

	void bindAttribLocation(GLuint index, const GLchar* name) const
	{
		GLWRAP_ASSERT(getParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		glBindAttribLocation(m_handle, index, name);
	}
	void bindAttrib(const VertexAttribPointer& attrib, const GLchar* name) const
	{
		GLWRAP_ASSERT(getParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		glBindAttribLocation(m_handle, attrib.index, name);
	}
	void bindAttrib(const NamedVertexAttribPointer& attrib) const
	{
		GLWRAP_ASSERT(getParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		glBindAttribLocation(m_handle, attrib.index, attrib.name.c_str());
	}

	GLint getInfoLogLength() const
	{
		return getParam(GL_INFO_LOG_LENGTH);
	}
	void getInfoLog(GLsizei bufSize, GLsizei *length, GLchar* infoLog) const
	{
		glGetProgramInfoLog(m_handle, bufSize, length, infoLog);
	}
	std::string getInfoLog() const
	{
		std::string str;
		GLint len = getInfoLogLength();
		str.resize(len + 1);
		getInfoLog(str.size(), nullptr, &str[0]);
		str.resize(len);
		return str;
	}

	static Program create()
	{
		return Program(glCreateProgram());
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(OProgram, Program);
GLWRAP_MAKE_OCLASS_END();

// --------------
// | ActiveBuffer
// --------------

class ActiveBuffer : public TActiveHandle
{
public:
	ActiveBuffer(BufferTarget target)
		: TActiveHandle(target)
	{ }

	void bufferData(const GLvoid* data, GLsizei size, BufferUsage usage=GL_STATIC_DRAW)
	{
		GLWRAP_CHECK_ACTIVE(GL_ARRAY_BUFFER_BINDING, m_target == GL_ARRAY_BUFFER);
		GLWRAP_CHECK_ACTIVE(GL_ELEMENT_ARRAY_BUFFER_BINDING, m_target == GL_ELEMENT_ARRAY_BUFFER);
		glBufferData(m_target, size, data, usage);
	}

	void unbind()
	{
		glBindBuffer(m_target, 0);
	}
};

// --------
// | Buffer
// --------

class Buffer : public Handle
{
public:
	Buffer()
		: Handle()
	{ }
	Buffer(GLuint buffer)
		: Handle(buffer)
	{
		GLWRAP_TYPECHECK(glIsBuffer, buffer);
	}
	void swap(Buffer& b)
	{
		Handle::swap(b);
	}
	Buffer& operator=(Buffer b)
	{
		swap(b);
		return *this;
	}
	void free()
	{
		if (m_handle)
		{
			glDeleteBuffers(1, &m_handle);
			m_handle = 0;
		}
	}

	ActiveBuffer bind(BufferTarget target) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Buffer is initialized");
		glBindBuffer(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(ActiveBuffer(target), m_handle);
	}
	static void unbind(BufferTarget target)
	{
		glBindBuffer(target, 0);
	}

	void gen()
	{
		GLWRAP_ASSERT(m_handle == 0, "Buffer is uninitialized");
		glGenBuffers(1, &m_handle);
	}
	static Buffer create()
	{
		Buffer b;
		b.gen();
		return b;
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(OBuffer, Buffer);
GLWRAP_MAKE_OCLASS_END();

// ---------
// | TBuffer
// ---------

class TBuffer : public Buffer
{
public:
	TBuffer()
		: Buffer()
		, m_target(GL_NONE)
	{ }
	explicit TBuffer(BufferTarget target)
		: Buffer()
		, m_target(target)
	{
	}
	TBuffer(BufferTarget target, GLuint buffer)
		: Buffer(buffer)
		, m_target(target)
	{
		GLWRAP_TYPECHECK(glIsBuffer, buffer);
	}
	void swap(TBuffer& b)
	{
		Buffer::swap(b);
		std::swap(m_target, b.m_target);
	}
	TBuffer& operator=(TBuffer b)
	{
		swap(b);
		return *this;
	}

	using Buffer::bind;
	ActiveBuffer bind() const
	{
		GLWRAP_ASSERT(m_target != GL_NONE, "Buffer target is initialized");
		Buffer::bind(m_target);
		return GLWRAP_ATTACH_HANDLE(ActiveBuffer(m_target), m_handle);
	}
	void unbind() const
	{
		GLWRAP_ASSERT(m_target != GL_NONE, "Buffer target is initialized");
		Buffer::unbind(m_target);
	}

	BufferTarget getTarget() const
	{
		return m_target;
	}

	static TBuffer create(BufferTarget target)
	{
		TBuffer buf(target);
		buf.gen();
		return buf;
	}
private:
	GLenum m_target;
};

GLWRAP_MAKE_OCLASS_BEGIN_NO_HANDLE(OTBuffer, TBuffer);
OTBuffer(BufferTarget target) : TBuffer(target) { }
OTBuffer(BufferTarget target, GLuint handle) : TBuffer(target, handle) { }
GLWRAP_MAKE_OCLASS_END();

// -------------------
// | ActiveIndexBuffer
// -------------------

class ActiveIndexBuffer : public ActiveBuffer
{
public:
	ActiveIndexBuffer(IndexType indexType=GL_NONE)
		: ActiveBuffer(GL_ELEMENT_ARRAY_BUFFER)
		, m_indexType(indexType)
	{ }

	IndexType getIndexType() const { return m_indexType; }

	void drawElements(RenderMode mode, GLsizei count, GLint offset=0) const
	{
		GLWRAP_CHECK_ACTIVE(GL_ELEMENT_ARRAY_BUFFER_BINDING, true);
		glDrawElements(mode, count, m_indexType, (const GLvoid*)offset);
	}
private:
	GLenum m_indexType;
};

// -------------
// | IndexBuffer
// -------------

class IndexBuffer : public Buffer
{
public:
	IndexBuffer()
		: Buffer()
		, m_type(GL_NONE)
	{ }
	explicit IndexBuffer(IndexType type)
		: Buffer()
		, m_type(type)
	{
	}
	IndexBuffer(IndexType type, GLuint buffer)
		: Buffer(buffer)
		, m_type(type)
	{
		GLWRAP_TYPECHECK(glIsBuffer, buffer);
	}
	void swap(IndexBuffer& b)
	{
		Buffer::swap(b);
		std::swap(m_type, b.m_type);
	}
	IndexBuffer& operator=(IndexBuffer b)
	{
		swap(b);
		return *this;
	}
	ActiveIndexBuffer bind() const
	{
		Buffer::bind(GL_ELEMENT_ARRAY_BUFFER);
		return GLWRAP_ATTACH_HANDLE(ActiveIndexBuffer(m_type), m_handle);
	}
	void unbind()
	{
		Buffer::unbind(GL_ELEMENT_ARRAY_BUFFER);
	}
	IndexType getIndexType() const
	{
		return m_type;
	}

	static IndexBuffer create(IndexType type)
	{
		IndexBuffer buf(type);
		buf.gen();
		return buf;
	}
private:
	GLenum m_type;
};

GLWRAP_MAKE_OCLASS_BEGIN_NO_HANDLE(OIndexBuffer, IndexBuffer);
OIndexBuffer(IndexType type) : IndexBuffer(type) { }
OIndexBuffer(IndexType type, GLuint buffer) : IndexBuffer(type, buffer) { }
GLWRAP_MAKE_OCLASS_END();

// --------------------
// | ActiveRenderbuffer
// --------------------

class ActiveRenderbuffer : public TActiveHandle
{
public:
	ActiveRenderbuffer(RenderbufferTarget target=GL_RENDERBUFFER)
		: TActiveHandle(target)
	{ }

	void storage(InternalFormat internalformat, GLsizei width, GLsizei height)
	{
		GLWRAP_CHECK_ACTIVE(GL_RENDERBUFFER_BINDING, m_target == GL_RENDERBUFFER);
		glRenderbufferStorage(m_target, internalformat, width, height);
	}

	void unbind()
	{
		glBindRenderbuffer(m_target, 0);
	}
};

// --------------
// | Renderbuffer
// --------------

class Renderbuffer : public Handle
{
public:
	Renderbuffer()
		: Handle()
	{ }
	explicit Renderbuffer(GLuint handle)
		: Handle(handle)
	{
		GLWRAP_TYPECHECK(glIsFramebuffer, handle);
	}
	Renderbuffer(Renderbuffer&& f)
		: Handle(std::move(f))
	{ }
	void swap(Renderbuffer& f)
	{
		Handle::swap(f);
	}
	Renderbuffer& operator=(Renderbuffer f)
	{
		swap(f);
		return *this;
	}
	void free()
	{
		if (m_handle)
		{
			glDeleteRenderbuffers(1, &m_handle);
			m_handle = 0;
		}
	}

	ActiveRenderbuffer bind(RenderbufferTarget target=GL_RENDERBUFFER) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Renerbuffer is initialized");
		glBindRenderbuffer(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(ActiveRenderbuffer(target), m_handle);
	}
	static void unbind(RenderbufferTarget target=GL_RENDERBUFFER)
	{
		glBindRenderbuffer(target, 0);
	}

	void gen()
	{
		GLWRAP_ASSERT(m_handle == 0, "Renderbuffer is uninitialized");
		glGenRenderbuffers(1, &m_handle);
	}
	static Renderbuffer create()
	{
		Renderbuffer r;
		r.gen();
		return r;
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(ORenderbuffer, Renderbuffer);
GLWRAP_MAKE_OCLASS_END();

// -------------------
// | ActiveFramebuffer
// -------------------

class ActiveFramebuffer : public TActiveHandle
{
public:
	ActiveFramebuffer(FramebufferTarget target=GL_FRAMEBUFFER)
		: TActiveHandle(target)
	{ }

	void texture(FramebufferAttachment attachment, Texture texture, GLint level=0)
	{
		GLWRAP_CHECK_ACTIVE(GL_FRAMEBUFFER_BINDING, m_target == GL_FRAMEBUFFER);
		GLWRAP_ASSERT(texture.initialized(), "Texture is initialized");
		glFramebufferTexture(m_target, attachment, texture.get(), level);
	}
	void texture2D(FramebufferAttachment attachment, ActiveTexture textarget, Texture texture, GLint level=0)
	{
		GLWRAP_CHECK_ACTIVE(GL_FRAMEBUFFER_BINDING, m_target == GL_FRAMEBUFFER);
		GLWRAP_ASSERT(texture.initialized(), "Texture is initialized");
																				#ifdef GLWRAP_ENABLE_ACTIVECHECK
		GLWRAP_ASSERT(!texture.initialized() || textarget.isHandle(texture.get()), "Bound texture is passed texture");
		if (textarget.getTarget() == GL_TEXTURE_2D)
			GLWRAP_ASSERT(textarget.isActive(GL_TEXTURE_BINDING_2D), "Bound texture is active");
																				#endif//GLWRAP_ENABLE_ACTIVECHECK
		glFramebufferTexture2D(m_target, attachment, textarget.getTarget(), texture.get(), level);
	}

	void renderbuffer(FramebufferAttachment attachment, ActiveRenderbuffer renderbuffertarget, Renderbuffer renderbuffer)
	{
		GLWRAP_CHECK_ACTIVE(GL_FRAMEBUFFER_BINDING, m_target == GL_FRAMEBUFFER);
		GLWRAP_ASSERT(renderbuffer.initialized(), "Renderbuffer is initialized");
																				#ifdef GLWRAP_ENABLE_ACTIVECHECK
		GLWRAP_ASSERT(!renderbuffer.initialized() || renderbuffertarget.isHandle(renderbuffer.get()), "Bound renderbuffer is passed renderbuffer");
		if (renderbuffertarget.getTarget() == GL_RENDERBUFFER)
			GLWRAP_ASSERT(renderbuffertarget.isActive(GL_RENDERBUFFER_BINDING), "Bound texture is active");
																				#endif//GLWRAP_ENABLE_ACTIVECHECK
		glFramebufferRenderbuffer(m_target, attachment, renderbuffertarget.getTarget(), renderbuffer.get());
	}

	GLenum checkStatus()
	{
		GLWRAP_CHECK_ACTIVE(GL_FRAMEBUFFER_BINDING, m_target == GL_FRAMEBUFFER);
		return glCheckFramebufferStatus(m_target);
	}

	void unbind()
	{
		glBindFramebuffer(m_target, 0);
	}
};

// -------------
// | Framebuffer
// -------------

class Framebuffer : public Handle
{
public:
	Framebuffer()
		: Handle()
	{ }
	explicit Framebuffer(GLuint handle)
		: Handle(handle)
	{
		GLWRAP_TYPECHECK(glIsFramebuffer, handle);
	}
	Framebuffer(Framebuffer&& f)
		: Handle(std::move(f))
	{ }
	void swap(Framebuffer& f)
	{
		Handle::swap(f);
	}
	Framebuffer& operator=(Framebuffer f)
	{
		swap(f);
		return *this;
	}
	void free()
	{
		if (m_handle)
		{
			glDeleteFramebuffers(1, &m_handle);
			m_handle = 0;
		}
	}

	ActiveFramebuffer bind(FramebufferTarget target=GL_FRAMEBUFFER) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Framebuffer is initialized");
		glBindFramebuffer(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(ActiveFramebuffer(target), m_handle);
	}
	static void unbind(FramebufferTarget target=GL_FRAMEBUFFER)
	{
		glBindFramebuffer(target, 0);
	}

	void gen()
	{
		GLWRAP_ASSERT(m_handle == 0, "Framebuffer is uninitialized");
		glGenFramebuffers(1, &m_handle);
	}

	static Framebuffer create()
	{
		Framebuffer f;
		f.gen();
		return f;
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(OFramebuffer, Framebuffer);
GLWRAP_MAKE_OCLASS_END();

inline void clearStencil(GLint stencil)
{
	glClearStencil(stencil);
}

inline void clearDepth(GLclampd depth)
{
	glClearDepth(depth);
}

inline void clearColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

inline void clear(GLenum mask)
{
	glClear(mask);
}
inline void clear(GLenum mask, const Color& color)
{
	clearColor(color);
	glClear(mask);
}
inline void clear(GLenum mask, const Color& color, GLclampd depth)
{
	clearColor(color);
	clearDepth(depth);
	glClear(mask);
}
inline void clear(GLenum mask, const Color& color, GLclampd depth, GLint stencil)
{
	clearStencil(stencil);
	clearColor(color);
	clearDepth(depth);
	glClear(mask);
}

inline GLenum getError()
{
	return glGetError();
}

inline void drawArrays(GLenum mode, GLint first, GLint count)
{
	glDrawArrays(mode, first, count);
}

inline void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
	glDrawElements(mode, count, type, indices);
}
inline void drawElements(GLenum mode, GLsizei count, GLenum type, GLuint offset=0)
{
	glDrawElements(mode, count, type, (const GLvoid*)offset);
}
inline void drawElements(GLenum mode, GLsizei count, ActiveIndexBuffer indexBuffer, GLuint offset=0)
{
	glDrawElements(mode, count, indexBuffer.getIndexType(), (const GLvoid*)offset);
}

																				#ifndef GLWRAP_NO_BASE_VERTEX																					
inline void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLint baseVertex)
{
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
	glDrawElementsBaseVertex(mode, count, type, indices, baseVertex);
}
inline void drawElements(GLenum mode, GLsizei count, GLenum type, Buffer indexBuffer, GLuint offset, GLint baseVertex)
{
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
	indexBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
	glDrawElementsBaseVertex(mode, count, type, (const GLvoid*)offset, baseVertex);
}
inline void drawElements(GLenum mode, GLsizei count, IndexBuffer indexBuffer, GLuint offset, GLint baseVertex)
{
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);	
	indexBuffer.bind();
	glDrawElementsBaseVertex(mode, count, indexBuffer.getIndexType(), (const GLvoid*)offset, baseVertex);
}
																				#endif

}//namespace gw

#undef GLWRAP_ASSERT
#undef GLWRAP_TYPECHECK2
#undef GLWRAP_TYPECHECK
#undef GLWRAP_CHECK_ACTIVE
#undef GLWRAP_ATTACH_HANDLE
#undef GLWRAP_MAKE_OCLASS_BEGIN
#undef GLWRAP_MAKE_OCLASS_BEGIN_NO_HANDLE
#undef GLWRAP_MAKE_OCLASS_END
#undef GLWRAP_ENUM_BEGIN
#undef GLWRAP_ENUM_ALLOW
#undef GLWRAP_ENUM_END
#undef GLWRAP_ENUM_ASSERT
#ifdef GLWRAP_OLD_ASSERT_DEFINE
#define assert GLWRAP_OLD_ASSERT_DEFINE
#undef GLWRAP_OLD_ASSERT_DEFINE
#endif

#endif