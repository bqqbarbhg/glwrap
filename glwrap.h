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

#ifndef GLWRAP_NAMESPACE_NAME
#define GLWRAP_NAMESPACE_NAME gl
#endif

namespace GLWRAP_NAMESPACE_NAME
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

#define GLWRAP_ATTACH_HANDLE(active, handle) (BoundHandle::attachHandle(active, handle))
#define GLWRAP_CHECK_ACTIVE(target, cond) if (cond) GLWRAP_ASSERT(isActive(target), "Handle is active")
#define GLWRAP_CHECK_ACTIVE_OUT(expr) GLWRAP_ASSERT(expr, "Handle is active")
#define GLWRAP_AC_ASSERT(e, m) GLWRAP_ASSERT(e, m)

#else

#define GLWRAP_ATTACH_HANDLE(active, handle) (active)
#define GLWRAP_CHECK_ACTIVE(target, cond)
#define GLWRAP_CHECK_ACTIVE_OUT(target)
#define GLWRAP_AC_ASSERT(e, m)

#endif

#ifndef GLWRAP_NO_MOVE

#define GLWRAP_MOVE(x) x

#else

#define GLWRAP_MOVE(x)

#endif

#define GLWRAP_MAKE_OCLASS_BEGIN(OClassName, ClassName) \
class OClassName : public ClassName \
{ \
public: \
	OClassName() : ClassName() { } \
	OClassName(ClassName c) : ClassName(c) { } \
	OClassName(GLuint handle) : ClassName(handle) { } \
	GLWRAP_MOVE(OClassName(OClassName&& o) : ClassName(std::move(o)) { o.m_handle = 0; }) \
	void swap(OClassName& o) { ClassName::swap(o); } \
	OClassName& operator=(OClassName o) { swap(o); return *this; } \
	static OClassName Create() { return ClassName::Create(); } \
	~OClassName() \
	{ \
		Delete(); \
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
	GLWRAP_MOVE(OClassName(OClassName&& o) : ClassName(std::move(o)) { o.m_handle = 0; }) \
	void swap(OClassName& o) { ClassName::swap(o); } \
	OClassName& operator=(OClassName o) { swap(o); return *this; } \
	~OClassName() \
	{ \
		Delete(); \
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

enum EnumGlobalParamName
{
	ACTIVE_TEXTURE = GL_ACTIVE_TEXTURE,
	ALIASED_LINE_WIDTH_RANGE = GL_ALIASED_LINE_WIDTH_RANGE,
	SMOOTH_LINE_WIDTH_RANGE = GL_SMOOTH_LINE_WIDTH_RANGE,
	SMOOTH_LINE_WIDTH_GRANULARITY = GL_SMOOTH_LINE_WIDTH_GRANULARITY,
	ARRAY_BUFFER_BINDING = GL_ARRAY_BUFFER_BINDING,
	BLEND = GL_BLEND,
	BLEND_COLOR = GL_BLEND_COLOR,
	BLEND_DST_ALPHA = GL_BLEND_DST_ALPHA,
	BLEND_DST_RGB = GL_BLEND_DST_RGB,
	BLEND_EQUATION_ALPHA = GL_BLEND_EQUATION_ALPHA,
	BLEND_EQUATION_RGB = GL_BLEND_EQUATION_RGB,
	BLEND_SRC_ALPHA = GL_BLEND_SRC_ALPHA,
	BLEND_SRC_RGB = GL_BLEND_SRC_RGB,
	COLOR_CLEAR_VALUE = GL_COLOR_CLEAR_VALUE,
	COLOR_LOGIC_OP = GL_COLOR_LOGIC_OP,
	COLOR_WRITEMASK = GL_COLOR_WRITEMASK,
	COMPRESSED_TEXTURE_FORMATS = GL_COMPRESSED_TEXTURE_FORMATS,
	CULL_FACE = GL_CULL_FACE,
	CURRENT_PROGRAM = GL_CURRENT_PROGRAM,
	DEPTH_CLEAR_VALUE = GL_DEPTH_CLEAR_VALUE,
	DEPTH_FUNC = GL_DEPTH_FUNC,
	DEPTH_RANGE = GL_DEPTH_RANGE,
	DEPTH_TEST = GL_DEPTH_TEST,
	DEPTH_WRITEMASK = GL_DEPTH_WRITEMASK,
	DITHER = GL_DITHER,
	DOUBLEBUFFER = GL_DOUBLEBUFFER,
	DRAW_BUFFER = GL_DRAW_BUFFER,
	DRAW_FRAMEBUFFER_BINDING = GL_DRAW_FRAMEBUFFER_BINDING,
	READ_FRAMEBUFFER_BINDING = GL_READ_FRAMEBUFFER_BINDING,
	ELEMENT_ARRAY_BUFFER_BINDING = GL_ELEMENT_ARRAY_BUFFER_BINDING,
	RENDERBUFFER_BINDING = GL_RENDERBUFFER_BINDING,
	FRAGMENT_SHADER_DERIVATIVE_HINT = GL_FRAGMENT_SHADER_DERIVATIVE_HINT,
	LINE_SMOOTH = GL_LINE_SMOOTH,
	LINE_SMOOTH_HINT = GL_LINE_SMOOTH_HINT,
	LINE_WIDTH = GL_LINE_WIDTH,
	LOGIC_OP_MODE = GL_LOGIC_OP_MODE,
	MAX_3D_TEXTURE_SIZE = GL_MAX_3D_TEXTURE_SIZE,
	MAX_CLIP_DISTANCES = GL_MAX_CLIP_DISTANCES,
	MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,
	MAX_COMBINED_TEXTURE_IMAGE_UNITS = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
	MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,
	MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,
	MAX_VARYING_COMPONENTS = GL_MAX_VARYING_COMPONENTS,
	MAX_COMBINED_UNIFORM_BLOCKS = GL_MAX_COMBINED_UNIFORM_BLOCKS,
	MAX_CUBE_MAP_TEXTURE_SIZE = GL_MAX_CUBE_MAP_TEXTURE_SIZE,
	MAX_DRAW_BUFFERS = GL_MAX_DRAW_BUFFERS,
	MAX_ELEMENTS_INDICES = GL_MAX_ELEMENTS_INDICES,
	MAX_ELEMENTS_VERTICES = GL_MAX_ELEMENTS_VERTICES,
	MAX_FRAGMENT_UNIFORM_COMPONENTS = GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
	MAX_FRAGMENT_INPUT_COMPONENTS = GL_MAX_FRAGMENT_INPUT_COMPONENTS,
	MAX_PROGRAM_TEXEL_OFFSET = GL_MAX_PROGRAM_TEXEL_OFFSET,
	MIN_PROGRAM_TEXEL_OFFSET = GL_MIN_PROGRAM_TEXEL_OFFSET,
	MAX_RECTANGLE_TEXTURE_SIZE = GL_MAX_RECTANGLE_TEXTURE_SIZE,
	MAX_TEXTURE_IMAGE_UNITS = GL_MAX_TEXTURE_IMAGE_UNITS,
	MAX_TEXTURE_LOD_BIAS = GL_MAX_TEXTURE_LOD_BIAS,
	MAX_TEXTURE_SIZE = GL_MAX_TEXTURE_SIZE,
	MAX_RENDERBUFFER_SIZE = GL_MAX_RENDERBUFFER_SIZE,
	MAX_ARRAY_TEXTURE_LAYERS = GL_MAX_ARRAY_TEXTURE_LAYERS,
	MAX_TEXTURE_BUFFER_SIZE = GL_MAX_TEXTURE_BUFFER_SIZE,
	MAX_UNIFORM_BLOCK_SIZE = GL_MAX_UNIFORM_BLOCK_SIZE,
	MAX_VERTEX_ATTRIBS = GL_MAX_VERTEX_ATTRIBS,
	MAX_VERTEX_TEXTURE_IMAGE_UNITS = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
	MAX_GEOMETRY_TEXTURE_IMAGE_UNITS = GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,
	MAX_VERTEX_UNIFORM_COMPONENTS = GL_MAX_VERTEX_UNIFORM_COMPONENTS,
	MAX_VERTEX_OUTPUT_COMPONENTS = GL_MAX_VERTEX_OUTPUT_COMPONENTS,
	MAX_GEOMETRY_UNIFORM_COMPONENTS = GL_MAX_GEOMETRY_UNIFORM_COMPONENTS,
	MAX_SAMPLE_MASK_WORDS = GL_MAX_SAMPLE_MASK_WORDS,
	MAX_COLOR_TEXTURE_SAMPLES = GL_MAX_COLOR_TEXTURE_SAMPLES,
	MAX_DEPTH_TEXTURE_SAMPLES = GL_MAX_DEPTH_TEXTURE_SAMPLES,
	MAX_INTEGER_SAMPLES = GL_MAX_INTEGER_SAMPLES,
	MAX_SERVER_WAIT_TIMEOUT = GL_MAX_SERVER_WAIT_TIMEOUT,
	MAX_UNIFORM_BUFFER_BINDINGS = GL_MAX_UNIFORM_BUFFER_BINDINGS,
	UNIFORM_BUFFER_OFFSET_ALIGNMENT = GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
	MAX_VERTEX_UNIFORM_BLOCKS = GL_MAX_VERTEX_UNIFORM_BLOCKS,
	MAX_GEOMETRY_UNIFORM_BLOCKS = GL_MAX_GEOMETRY_UNIFORM_BLOCKS,
	MAX_GEOMETRY_INPUT_COMPONENTS = GL_MAX_GEOMETRY_INPUT_COMPONENTS,
	MAX_GEOMETRY_OUTPUT_COMPONENTS = GL_MAX_GEOMETRY_OUTPUT_COMPONENTS,
	MAX_VIEWPORT_DIMS = GL_MAX_VIEWPORT_DIMS,
	NUM_COMPRESSED_TEXTURE_FORMATS = GL_NUM_COMPRESSED_TEXTURE_FORMATS,
	PACK_ALIGNMENT = GL_PACK_ALIGNMENT,
	PACK_IMAGE_HEIGHT = GL_PACK_IMAGE_HEIGHT,
	PACK_LSB_FIRST = GL_PACK_LSB_FIRST,
	PACK_ROW_LENGTH = GL_PACK_ROW_LENGTH,
	PACK_SKIP_IMAGES = GL_PACK_SKIP_IMAGES,
	PACK_SKIP_PIXELS = GL_PACK_SKIP_PIXELS,
	PACK_SKIP_ROWS = GL_PACK_SKIP_ROWS,
	PACK_SWAP_BYTES = GL_PACK_SWAP_BYTES,
	PIXEL_PACK_BUFFER_BINDING = GL_PIXEL_PACK_BUFFER_BINDING,
	PIXEL_UNPACK_BUFFER_BINDING = GL_PIXEL_UNPACK_BUFFER_BINDING,
	POINT_FADE_THRESHOLD_SIZE = GL_POINT_FADE_THRESHOLD_SIZE,
	PRIMITIVE_RESTART_INDEX = GL_PRIMITIVE_RESTART_INDEX,
	PROGRAM_POINT_SIZE = GL_PROGRAM_POINT_SIZE,
	PROVOKING_VERTEX = GL_PROVOKING_VERTEX,
	POINT_SIZE = GL_POINT_SIZE,
	POINT_SIZE_GRANULARITY = GL_POINT_SIZE_GRANULARITY,
	POINT_SIZE_RANGE = GL_POINT_SIZE_RANGE,
	POLYGON_OFFSET_FACTOR = GL_POLYGON_OFFSET_FACTOR,
	POLYGON_OFFSET_UNITS = GL_POLYGON_OFFSET_UNITS,
	POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
	POLYGON_OFFSET_LINE = GL_POLYGON_OFFSET_LINE,
	POLYGON_OFFSET_POINT = GL_POLYGON_OFFSET_POINT,
	POLYGON_SMOOTH = GL_POLYGON_SMOOTH,
	POLYGON_SMOOTH_HINT = GL_POLYGON_SMOOTH_HINT,
	SAMPLE_BUFFERS = GL_SAMPLE_BUFFERS,
	SAMPLE_COVERAGE_VALUE = GL_SAMPLE_COVERAGE_VALUE,
	SAMPLE_COVERAGE_INVERT = GL_SAMPLE_COVERAGE_INVERT,
	SAMPLER_BINDING = GL_SAMPLER_BINDING,
	SAMPLES = GL_SAMPLES,
	SCISSOR_BOX = GL_SCISSOR_BOX,
	SCISSOR_TEST = GL_SCISSOR_TEST,
	STENCIL_BACK_PASS_DEPTH_FAIL = GL_STENCIL_BACK_PASS_DEPTH_FAIL,
	STENCIL_BACK_PASS_DEPTH_PASS = GL_STENCIL_BACK_PASS_DEPTH_PASS,
	STENCIL_BACK_REF = GL_STENCIL_BACK_REF,
	STENCIL_BACK_VALUE_MASK = GL_STENCIL_BACK_VALUE_MASK,
	STENCIL_BACK_WRITEMASK = GL_STENCIL_BACK_WRITEMASK,
	STENCIL_CLEAR_VALUE = GL_STENCIL_CLEAR_VALUE,
	STENCIL_FAIL = GL_STENCIL_FAIL,
	STENCIL_FUNC = GL_STENCIL_FUNC,
	STENCIL_PASS_DEPTH_FAIL = GL_STENCIL_PASS_DEPTH_FAIL,
	STENCIL_PASS_DEPTH_PASS = GL_STENCIL_PASS_DEPTH_PASS,
	STENCIL_REF = GL_STENCIL_REF,
	STENCIL_TEST = GL_STENCIL_TEST,
	STENCIL_VALUE_MASK = GL_STENCIL_VALUE_MASK,
	STENCIL_WRITEMASK = GL_STENCIL_WRITEMASK,
	STEREO = GL_STEREO,
	SUBPIXEL_BITS = GL_SUBPIXEL_BITS,
	TEXTURE_BINDING_1D = GL_TEXTURE_BINDING_1D,
	TEXTURE_BINDING_1D_ARRAY = GL_TEXTURE_BINDING_1D_ARRAY,
	TEXTURE_BINDING_2D = GL_TEXTURE_BINDING_2D,
	TEXTURE_BINDING_2D_ARRAY = GL_TEXTURE_BINDING_2D_ARRAY,
	TEXTURE_BINDING_2D_MULTISAMPLE = GL_TEXTURE_BINDING_2D_MULTISAMPLE,
	TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY,
	TEXTURE_BINDING_3D = GL_TEXTURE_BINDING_3D,
	TEXTURE_BINDING_BUFFER = GL_TEXTURE_BINDING_BUFFER,
	TEXTURE_BINDING_CUBE_MAP = GL_TEXTURE_BINDING_CUBE_MAP,
	TEXTURE_BINDING_RECTANGLE = GL_TEXTURE_BINDING_RECTANGLE,
	TEXTURE_COMPRESSION_HINT = GL_TEXTURE_COMPRESSION_HINT,
	TIMESTAMP = GL_TIMESTAMP,
	TRANSFORM_FEEDBACK_BUFFER_BINDING = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING,
	TRANSFORM_FEEDBACK_BUFFER_START = GL_TRANSFORM_FEEDBACK_BUFFER_START,
	TRANSFORM_FEEDBACK_BUFFER_SIZE = GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,
	UNIFORM_BUFFER_BINDING = GL_UNIFORM_BUFFER_BINDING,
	UNIFORM_BUFFER_START = GL_UNIFORM_BUFFER_START,
	UNIFORM_BUFFER_SIZE = GL_UNIFORM_BUFFER_SIZE,
	UNPACK_ALIGNMENT = GL_UNPACK_ALIGNMENT,
	UNPACK_IMAGE_HEIGHT = GL_UNPACK_IMAGE_HEIGHT,
	UNPACK_LSB_FIRST = GL_UNPACK_LSB_FIRST,
	UNPACK_ROW_LENGTH = GL_UNPACK_ROW_LENGTH,
	UNPACK_SKIP_IMAGES = GL_UNPACK_SKIP_IMAGES,
	UNPACK_SKIP_PIXELS = GL_UNPACK_SKIP_PIXELS,
	UNPACK_SKIP_ROWS = GL_UNPACK_SKIP_ROWS,
	UNPACK_SWAP_BYTES = GL_UNPACK_SWAP_BYTES,
	NUM_EXTENSIONS = GL_NUM_EXTENSIONS,
	MAJOR_VERSION = GL_MAJOR_VERSION,
	MINOR_VERSION = GL_MINOR_VERSION,
	CONTEXT_FLAGS = GL_CONTEXT_FLAGS,
	VIEWPORT = GL_VIEWPORT,
};

enum EnumTextureParamName
{
	TEXTURE_BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
	TEXTURE_BORDER_COLOR = GL_TEXTURE_BORDER_COLOR,
	TEXTURE_COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
	TEXTURE_COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
	TEXTURE_LOD_BIAS = GL_TEXTURE_LOD_BIAS,
	TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,
	TEXTURE_MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
	TEXTURE_MAX_LOD = GL_TEXTURE_MAX_LOD,
	TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
	TEXTURE_MIN_LOD = GL_TEXTURE_MIN_LOD,
	TEXTURE_SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
	TEXTURE_SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
	TEXTURE_SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
	TEXTURE_SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
	TEXTURE_SWIZZLE_RGBA = GL_TEXTURE_SWIZZLE_RGBA,
	TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
	TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
	TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R,
};

enum EnumTextureLevelParamName
{
	TEXTURE_WIDTH = GL_TEXTURE_WIDTH,
	TEXTURE_HEIGHT = GL_TEXTURE_HEIGHT,
	TEXTURE_DEPTH = GL_TEXTURE_DEPTH,
	TEXTURE_INTERNAL_FORMAT = GL_TEXTURE_INTERNAL_FORMAT,
	TEXTURE_RED_SIZE = GL_TEXTURE_RED_SIZE,
	TEXTURE_GREEN_SIZE = GL_TEXTURE_GREEN_SIZE,
	TEXTURE_BLUE_SIZE = GL_TEXTURE_BLUE_SIZE,
	TEXTURE_ALPHA_SIZE = GL_TEXTURE_ALPHA_SIZE,
	TEXTURE_DEPTH_SIZE = GL_TEXTURE_DEPTH_SIZE,
	TEXTURE_COMPRESSED = GL_TEXTURE_COMPRESSED,
	TEXTURE_COMPRESSED_IMAGE_SIZE = GL_TEXTURE_COMPRESSED_IMAGE_SIZE,
};

enum EnumClearMask
{
	COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT,
	DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT,
	STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT,
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

GLWRAP_ENUM_BEGIN(GlobalParamName)
GLWRAP_ENUM_ALLOW(GlobalParamName, EnumGlobalParamName)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(TextureParamName)
GLWRAP_ENUM_ALLOW(TextureParamName, EnumTextureParamName)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(TextureLevelParamName)
GLWRAP_ENUM_ALLOW(TextureLevelParamName, EnumTextureLevelParamName)
GLWRAP_ENUM_END()

GLWRAP_ENUM_BEGIN(ClearMask)
GLWRAP_ENUM_ALLOW(ClearMask, EnumClearMask)
GLWRAP_ENUM_END()

// -------
// | Color
// -------

struct Color
{
public:
	Color(float* rgba)
		: r(rgba[0]), g(rgba[1]), b(rgba[2]), a(rgba[3])
	{ }
	Color(float r, float g, float b, float a = 1.0f)
		: r(r), g(g), b(b), a(a)
	{ }
	static Color rgb(uint32_t col)
	{
		return Color(
			(col >> 16 & 0xFF) / 255.0f,
			(col >> 8 & 0xFF) / 255.0f,
			(col >> 0 & 0xFF) / 255.0f);
	}
	static Color rgba(uint32_t col)
	{
		return Color(
			(col >> 24 & 0xFF) / 255.0f,
			(col >> 16 & 0xFF) / 255.0f,
			(col >> 8 & 0xFF) / 255.0f,
			(col >> 0 & 0xFF) / 255.0f);
	}

	float r, g, b, a;
};

// ------------------
// | Common functions
// ------------------

inline int getNumGlobalParamValues(GlobalParamName pname)
{
																				#ifndef GLWRAP_NO_ENUMS
	switch (pname)
	{
	case GL_ACTIVE_TEXTURE: return 1;
	case GL_ALIASED_LINE_WIDTH_RANGE: return 2;
	case GL_SMOOTH_LINE_WIDTH_RANGE: return 2;
	case GL_SMOOTH_LINE_WIDTH_GRANULARITY: return 1;
	case GL_ARRAY_BUFFER_BINDING: return 1;
	case GL_BLEND: return 1;
	case GL_BLEND_COLOR: return 4;
	case GL_BLEND_DST_ALPHA: return 1;
	case GL_BLEND_DST_RGB: return 1;
	case GL_BLEND_EQUATION_ALPHA: return 1;
	case GL_BLEND_EQUATION_RGB: return 1;
	case GL_BLEND_SRC_ALPHA: return 1;
	case GL_BLEND_SRC_RGB: return 1;
	case GL_COLOR_CLEAR_VALUE: return 4;
	case GL_COLOR_LOGIC_OP: return 1;
	case GL_COLOR_WRITEMASK: return 4;
	case GL_COMPRESSED_TEXTURE_FORMATS: return 0;
	case GL_CULL_FACE: return 1;
	case GL_CURRENT_PROGRAM: return 1;
	case GL_DEPTH_CLEAR_VALUE: return 1;
	case GL_DEPTH_FUNC: return 1;
	case GL_DEPTH_RANGE: return 2;
	case GL_DEPTH_TEST: return 1;
	case GL_DEPTH_WRITEMASK: return 1;
	case GL_DITHER: return 1;
	case GL_DOUBLEBUFFER: return 1;
	case GL_DRAW_BUFFER: return 1;
	case GL_DRAW_FRAMEBUFFER_BINDING: return 1;
	case GL_READ_FRAMEBUFFER_BINDING: return 1;
	case GL_ELEMENT_ARRAY_BUFFER_BINDING: return 1;
	case GL_RENDERBUFFER_BINDING: return 1;
	case GL_FRAGMENT_SHADER_DERIVATIVE_HINT: return 1;
	case GL_LINE_SMOOTH: return 1;
	case GL_LINE_SMOOTH_HINT: return 1;
	case GL_LINE_WIDTH: return 1;
	case GL_LOGIC_OP_MODE: return 1;
	case GL_MAX_3D_TEXTURE_SIZE: return 1;
	case GL_MAX_CLIP_DISTANCES: return 1;
	case GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS: return 1;
	case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: return 1;
	case GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS: return 1;
	case GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS: return 1;
	case GL_MAX_VARYING_COMPONENTS: return 1;
	case GL_MAX_COMBINED_UNIFORM_BLOCKS: return 1;
	case GL_MAX_CUBE_MAP_TEXTURE_SIZE: return 1;
	case GL_MAX_DRAW_BUFFERS: return 1;
	case GL_MAX_ELEMENTS_INDICES: return 1;
	case GL_MAX_ELEMENTS_VERTICES: return 1;
	case GL_MAX_FRAGMENT_UNIFORM_COMPONENTS: return 1;
	case GL_MAX_FRAGMENT_INPUT_COMPONENTS: return 1;
	case GL_MAX_PROGRAM_TEXEL_OFFSET: return 1;
	case GL_MIN_PROGRAM_TEXEL_OFFSET: return 1;
	case GL_MAX_RECTANGLE_TEXTURE_SIZE: return 1;
	case GL_MAX_TEXTURE_IMAGE_UNITS: return 1;
	case GL_MAX_TEXTURE_LOD_BIAS: return 1;
	case GL_MAX_TEXTURE_SIZE: return 1;
	case GL_MAX_RENDERBUFFER_SIZE: return 1;
	case GL_MAX_ARRAY_TEXTURE_LAYERS: return 1;
	case GL_MAX_TEXTURE_BUFFER_SIZE: return 1;
	case GL_MAX_UNIFORM_BLOCK_SIZE: return 1;
	//case GL_MAX_VARYING_FLOATS (GL_MAX_VARYING_COMPONENTS): return 1;
	case GL_MAX_VERTEX_ATTRIBS: return 1;
	case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: return 1;
	case GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS: return 1;
	case GL_MAX_VERTEX_UNIFORM_COMPONENTS: return 1;
	case GL_MAX_VERTEX_OUTPUT_COMPONENTS: return 1;
	case GL_MAX_GEOMETRY_UNIFORM_COMPONENTS: return 1;
	case GL_MAX_SAMPLE_MASK_WORDS: return 1;
	case GL_MAX_COLOR_TEXTURE_SAMPLES: return 1;
	case GL_MAX_DEPTH_TEXTURE_SAMPLES: return 1;
	case GL_MAX_INTEGER_SAMPLES: return 1;
	case GL_MAX_SERVER_WAIT_TIMEOUT: return 1;
	case GL_MAX_UNIFORM_BUFFER_BINDINGS: return 1;
	case GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT: return 1;
	case GL_MAX_VERTEX_UNIFORM_BLOCKS: return 1;
	case GL_MAX_GEOMETRY_UNIFORM_BLOCKS: return 1;
	case GL_MAX_GEOMETRY_INPUT_COMPONENTS: return 1;
	case GL_MAX_GEOMETRY_OUTPUT_COMPONENTS: return 1;
	case GL_MAX_VIEWPORT_DIMS: return 1;
	case GL_NUM_COMPRESSED_TEXTURE_FORMATS: return 1;
	case GL_PACK_ALIGNMENT: return 1;
	case GL_PACK_IMAGE_HEIGHT: return 1;
	case GL_PACK_LSB_FIRST: return 1;
	case GL_PACK_ROW_LENGTH: return 1;
	case GL_PACK_SKIP_IMAGES: return 1;
	case GL_PACK_SKIP_PIXELS: return 1;
	case GL_PACK_SKIP_ROWS: return 1;
	case GL_PACK_SWAP_BYTES: return 1;
	case GL_PIXEL_PACK_BUFFER_BINDING: return 1;
	case GL_PIXEL_UNPACK_BUFFER_BINDING: return 1;
	case GL_POINT_FADE_THRESHOLD_SIZE: return 1;
	case GL_PRIMITIVE_RESTART_INDEX: return 1;
	case GL_PROGRAM_POINT_SIZE: return 1;
	case GL_PROVOKING_VERTEX: return 1;
	case GL_POINT_SIZE: return 1;
	case GL_POINT_SIZE_GRANULARITY: return 1;
	case GL_POINT_SIZE_RANGE: return 2;
	case GL_POLYGON_OFFSET_FACTOR: return 1;
	case GL_POLYGON_OFFSET_UNITS: return 1;
	case GL_POLYGON_OFFSET_FILL: return 1;
	case GL_POLYGON_OFFSET_LINE: return 1;
	case GL_POLYGON_OFFSET_POINT: return 1;
	case GL_POLYGON_SMOOTH: return 1;
	case GL_POLYGON_SMOOTH_HINT: return 1;
	case GL_SAMPLE_BUFFERS: return 1;
	case GL_SAMPLE_COVERAGE_VALUE: return 1;
	case GL_SAMPLE_COVERAGE_INVERT: return 1;
	case GL_SAMPLER_BINDING: return 1;
	case GL_SAMPLES: return 1;
	case GL_SCISSOR_BOX: return 4;
	case GL_SCISSOR_TEST: return 1;
	case GL_STENCIL_BACK_PASS_DEPTH_FAIL: return 1;
	case GL_STENCIL_BACK_PASS_DEPTH_PASS: return 1;
	case GL_STENCIL_BACK_REF: return 1;
	case GL_STENCIL_BACK_VALUE_MASK: return 1;
	case GL_STENCIL_BACK_WRITEMASK: return 1;
	case GL_STENCIL_CLEAR_VALUE: return 1;
	case GL_STENCIL_FAIL: return 1;
	case GL_STENCIL_FUNC: return 1;
	case GL_STENCIL_PASS_DEPTH_FAIL: return 1;
	case GL_STENCIL_PASS_DEPTH_PASS: return 1;
	case GL_STENCIL_REF: return 1;
	case GL_STENCIL_TEST: return 1;
	case GL_STENCIL_VALUE_MASK: return 1;
	case GL_STENCIL_WRITEMASK: return 1;
	case GL_STEREO: return 1;
	case GL_SUBPIXEL_BITS: return 1;
	case GL_TEXTURE_BINDING_1D: return 1;
	case GL_TEXTURE_BINDING_1D_ARRAY: return 1;
	case GL_TEXTURE_BINDING_2D: return 1;
	case GL_TEXTURE_BINDING_2D_ARRAY: return 1;
	case GL_TEXTURE_BINDING_2D_MULTISAMPLE: return 1;
	case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY: return 1;
	case GL_TEXTURE_BINDING_3D: return 1;
	case GL_TEXTURE_BINDING_BUFFER: return 1;
	case GL_TEXTURE_BINDING_CUBE_MAP: return 1;
	case GL_TEXTURE_BINDING_RECTANGLE: return 1;
	case GL_TEXTURE_COMPRESSION_HINT: return 1;
	case GL_TIMESTAMP: return 1;
	case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING: return 1;
	case GL_TRANSFORM_FEEDBACK_BUFFER_START: return 1;
	case GL_TRANSFORM_FEEDBACK_BUFFER_SIZE: return 1;
	case GL_UNIFORM_BUFFER_BINDING: return 1;
	case GL_UNIFORM_BUFFER_START: return 1;
	case GL_UNIFORM_BUFFER_SIZE: return 1;
	case GL_UNPACK_ALIGNMENT: return 1;
	case GL_UNPACK_IMAGE_HEIGHT: return 1;
	case GL_UNPACK_LSB_FIRST: return 1;
	case GL_UNPACK_ROW_LENGTH: return 1;
	case GL_UNPACK_SKIP_IMAGES: return 1;
	case GL_UNPACK_SKIP_PIXELS: return 1;
	case GL_UNPACK_SKIP_ROWS: return 1;
	case GL_UNPACK_SWAP_BYTES: return 1;
	case GL_NUM_EXTENSIONS: return 1;
	case GL_MAJOR_VERSION: return 1;
	case GL_MINOR_VERSION: return 1;
	case GL_CONTEXT_FLAGS: return 1;
	case GL_VIEWPORT: return 1;
	default: return 0;
	}
																				#else //GLWRAP_NO_ENUMS
	return 0;
																				#endif//GLWRAP_NO_ENUMS

}

inline int getNumTextureParamValues(TextureParamName pname)
{
																				#ifndef GLWRAP_NO_ENUMS
	switch (pname)
	{
	case GL_TEXTURE_BASE_LEVEL: return 1;
	case GL_TEXTURE_BORDER_COLOR: return 4;
	case GL_TEXTURE_COMPARE_MODE: return 1;
	case GL_TEXTURE_COMPARE_FUNC: return 1;
	case GL_TEXTURE_LOD_BIAS: return 1;
	case GL_TEXTURE_MAG_FILTER: return 1;
	case GL_TEXTURE_MAX_LEVEL: return 1;
	case GL_TEXTURE_MAX_LOD: return 1;
	case GL_TEXTURE_MIN_FILTER: return 1;
	case GL_TEXTURE_MIN_LOD: return 1;
	case GL_TEXTURE_SWIZZLE_R: return 1;
	case GL_TEXTURE_SWIZZLE_G: return 1;
	case GL_TEXTURE_SWIZZLE_B: return 1;
	case GL_TEXTURE_SWIZZLE_A: return 1;
	case GL_TEXTURE_SWIZZLE_RGBA: return 4;
	case GL_TEXTURE_WRAP_S: return 1;
	case GL_TEXTURE_WRAP_T: return 1;
	case GL_TEXTURE_WRAP_R: return 1;
	default: return 0;
	}
																				#else //GLWRAP_NO_ENUMS
return 0;
																				#endif//GLWRAP_NO_ENUMS
}

inline int getNumTextureLevelParamValues(TextureParamName pname)
{
																				#ifndef GLWRAP_NO_ENUMS
	switch (pname)
	{
	case TEXTURE_WIDTH: return 1;
	case TEXTURE_HEIGHT: return 1;
	case TEXTURE_DEPTH: return 1;
	case TEXTURE_INTERNAL_FORMAT: return 1;
	case TEXTURE_RED_SIZE: return 1;
	case TEXTURE_GREEN_SIZE: return 1;
	case TEXTURE_BLUE_SIZE: return 1;
	case TEXTURE_ALPHA_SIZE: return 1;
	case TEXTURE_DEPTH_SIZE: return 1;
	case TEXTURE_COMPRESSED: return 1;
	case TEXTURE_COMPRESSED_IMAGE_SIZE: return 1;
	default: return 0;
	}
																				#else //GLWRAP_NO_ENUMS
	return 0;
																				#endif//GLWRAP_NO_ENUMS
}

inline int isGetValueAmount(int amount, int num)
{
	return amount == 0 || amount == num;
}

inline GLint GetInteger(GlobalParamName pname)
{
	GLWRAP_ASSERT(isGetValueAmount(getNumGlobalParamValues(pname), 1), "Parameter has 1 component");

	GLint param;
	glGetIntegerv(pname, &param);
	return param;
}
inline void GetInteger(GlobalParamName pname, GLint *params)
{
	glGetIntegerv(pname, params);
}

inline GLfloat GetFloat(GlobalParamName pname)
{
	GLWRAP_ASSERT(isGetValueAmount(getNumGlobalParamValues(pname), 1), "Parameter has 1 component");

	GLfloat param;
	glGetFloatv(pname, &param);
	return param;
}
inline void GetFloat(GlobalParamName pname, GLfloat *params)
{
	glGetFloatv(pname, params);
}

inline GLboolean GetBoolean(GlobalParamName pname)
{
	GLWRAP_ASSERT(isGetValueAmount(getNumGlobalParamValues(pname), 1), "Parameter has 1 component");

	GLboolean param;
	glGetBooleanv(pname, &param);
	return param;
}
inline void GetBoolean(GlobalParamName pname, GLboolean *params)
{
	glGetBooleanv(pname, params);
}


inline std::pair<GLint, GLint> GetIntegerPair(GlobalParamName pname)
{
	GLWRAP_ASSERT(isGetValueAmount(getNumGlobalParamValues(pname), 2), "Parameter has 2 components");

	GLint pair[2];
	glGetIntegerv(pname, pair);
	return std::make_pair(pair[0], pair[1]);
}

inline std::pair<GLfloat, GLfloat> GetFloatPair(GlobalParamName pname)
{
	GLWRAP_ASSERT(isGetValueAmount(getNumGlobalParamValues(pname), 2), "Parameter has 2 components");

	GLfloat pair[2];
	glGetFloatv(pname, pair);
	return std::make_pair(pair[0], pair[1]);
}

inline Color GetColor(GlobalParamName pname)
{
	GLWRAP_ASSERT(isGetValueAmount(getNumGlobalParamValues(pname), 4), "Parameter has 4 components");

	GLfloat params[4];
	glGetFloatv(pname, params);
	return Color(params);
}

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
																				#ifndef GLWRAP_NO_EXPLICIT_OPERATORS
	explicit operator bool()
	{
		return initialized();
	}
																				#else //GLWRAP_NO_EXPLICIT_OPERATORS
	operator void*()
	{
		return initialized() ? this : 0;
	}
																				#endif//GLWRAP_NO_EXPLICIT_OPERATORS
protected:
	GLuint m_handle;
};

// -------------
// | BoundHandle
// -------------

class BoundHandle
{
public:
	BoundHandle()
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

// --------------
// | TBoundHandle
// --------------

class TBoundHandle : public BoundHandle
{
public:
	TBoundHandle(GLenum target)
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

	static const Wrap Clamp() { return Wrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE); }
	static const Wrap Repeat() { return Wrap(GL_REPEAT, GL_REPEAT); }
	static const Wrap Mirror() { return Wrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT); }
};

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
	static Filter Nearest() { return Filter(GL_NEAREST, GL_NEAREST); }
	static const Filter Bilinear() { return Filter(GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR); }
	static const Filter Trilinear() { return Filter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR); }
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
	static Filter Anisotropic(GLint max_anisotropy)
	{
		return Filter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, max_anisotropy);
	}
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
};

// --------------
// | BoundTexture
// --------------

#ifndef GLWRAP_NO_TEXTURE3D
#define GLWRAP_TEXTURE_ACTIVECHECK() \
	GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_1D, m_target == GL_TEXTURE_1D); \
	GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D); \
	GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D)
#else
#define GLWRAP_TEXTURE_ACTIVECHECK() \
	GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_1D, m_target == GL_TEXTURE_1D); \
	GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D)
#endif

class BoundTexture : public TBoundHandle
{
public:
	explicit BoundTexture(TextureTarget target)
		: TBoundHandle(target)
	{ }

	GLint GetInteger(TextureParamName pname) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		GLWRAP_ASSERT(isGetValueAmount(getNumTextureParamValues(pname), 1), "Parameter has 1 component");
		GLint param;
		glGetTexParameteriv(m_target, pname, &param);
		return param;
	}
	GLfloat GetInteger(TextureParamName pname, GLint *params) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		glGetTexParameteriv(m_target, pname, params);
	}
	GLfloat GetFloat(TextureParamName pname)
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		GLWRAP_ASSERT(isGetValueAmount(getNumTextureParamValues(pname), 1), "Parameter has 1 component");
		GLfloat param;
		glGetTexParameterfv(m_target, pname, &param);
		return param;
	}
	GLfloat GetFloat(TextureParamName pname, GLfloat *params) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		glGetTexParameterfv(m_target, pname, params);
	}
	GLboolean GetBoolean(TextureParamName pname) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		GLWRAP_ASSERT(isGetValueAmount(getNumTextureParamValues(pname), 1), "Parameter has 1 component");
		GLint param;
		glGetTexParameteriv(m_target, pname, &param);
		return param != 0;
	}
	Color GetColor(TextureParamName pname) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		GLWRAP_ASSERT(isGetValueAmount(getNumTextureParamValues(pname), 4), "Parameter has 4 components");
		GLfloat params[4];
		glGetTexParameterfv(m_target, pname, params);
		return Color(params);
	}

	GLint GetLevelInteger(TextureLevelParamName pname, GLint level = 0) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		GLWRAP_ASSERT(isGetValueAmount(getNumTextureLevelParamValues(pname), 1), "Parameter has 1 component");
		GLint param;
		glGetTexLevelParameteriv(m_target, level, pname, &param);
		return param;
	}
	GLfloat GetLevelInteger(TextureLevelParamName pname, GLint *params, GLint level = 0) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		glGetTexLevelParameteriv(m_target, level, pname, params);
	}
	GLfloat GetLevelFloat(TextureLevelParamName pname, GLint level=0)
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		GLWRAP_ASSERT(isGetValueAmount(getNumTextureLevelParamValues(pname), 1), "Parameter has 1 component");
		GLfloat param;
		glGetTexLevelParameterfv(m_target, level, pname, &param);
		return param;
	}
	GLfloat GetLevelFloat(TextureLevelParamName pname, GLfloat *params, GLint level = 0) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		glGetTexLevelParameterfv(m_target, level, pname, params);
	}
	GLboolean GetLevelBoolean(TextureLevelParamName pname, GLint level = 0) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		GLWRAP_ASSERT(isGetValueAmount(getNumTextureLevelParamValues(pname), 1), "Parameter has 1 component");
		GLint param;
		glGetTexLevelParameteriv(m_target, level, pname, &param);
		return param != 0;
	}
	Color GetLevelColor(TextureLevelParamName pname, GLint level = 0) const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		GLWRAP_ASSERT(isGetValueAmount(getNumTextureLevelParamValues(pname), 4), "Parameter has 4 components");
		GLfloat params[4];
		glGetTexLevelParameterfv(m_target, level, pname, params);
		return Color(params);
	}

	void SetFilter(const Filter& filter)
	{
		GLWRAP_TEXTURE_ACTIVECHECK();

		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, filter.min);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, filter.mag);
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		glTexParameteri(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, filter.max_anisotropy);
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
	}
	Filter GetFilter() const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();

		Filter filter;
		glGetTexParameteriv(m_target, GL_TEXTURE_MIN_FILTER, (GLint*)&filter.min);
		glGetTexParameteriv(m_target, GL_TEXTURE_MAG_FILTER, (GLint*)&filter.mag);
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		glGetTexParameteriv(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, &filter.max_anisotropy);
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
		return filter;
	}

	void Image1D(GLint level, InternalFormat internalformat, GLint width, GLint border, PixelFormat format, PixelType type, GLvoid* pixels)
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		glTexImage1D(m_target, level, internalformat, width, border, format, type, pixels);
	}
	void Image2D(GLint level, InternalFormat internalformat, GLint width, GLint height, GLint border, PixelFormat format, PixelType type, GLvoid* pixels)
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		glTexImage2D(m_target, level, internalformat, width, height, border, format, type, pixels);
	}
																				#ifndef GLWRAP_NO_TEXTURE3D
	void Image3D(GLint level, InternalFormat internalformat, GLint width, GLint height, GLint depth, GLint border, PixelFormat format, PixelType type, GLvoid* pixels)
	{
		GLWRAP_TEXTURE_ACTIVECHECK();
		glTexImage3D(m_target, level, internalformat, width, height, depth, border, format, type, pixels);
	}
																				#endif//GLWRAP_NO_TEXTURE3D

	void SetWrap(const Wrap& wrap)
	{
		GLWRAP_TEXTURE_ACTIVECHECK();

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap.s);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrap.t);
																				#ifndef GLWRAP_NO_TEXTURE3D
		if (wrap.r != GL_NONE)
			glTexParameteri(m_target, GL_TEXTURE_WRAP_R, wrap.r);
																				#endif//GLWRAP_NO_TEXTURE3D
	}
	Wrap GetWrap() const
	{
		GLWRAP_TEXTURE_ACTIVECHECK();

		Wrap wrap;
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_S, (GLint*)&wrap.s);
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_T, (GLint*)&wrap.t);
																				#ifndef GLWRAP_NO_TEXTURE3D
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_R, (GLint*)&wrap.r);
																				#endif//GLWRAP_NO_TEXTURE3D
		return wrap;
	}

	void Unbind()
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
	{ }
	explicit Texture(GLuint handle)
		: Handle(handle)
	{
		GLWRAP_TYPECHECK(glIsTexture, handle);
	}
	void swap(Texture& tex)
	{
		Handle::swap(tex);
	}

	void Delete()
	{
		if (m_handle)
		{
			glDeleteTextures(1, &m_handle);
			m_handle = 0;
		}
	}

	BoundTexture Bind(TextureTarget target) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Texture is initialized");
		glBindTexture(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(BoundTexture(target), m_handle);
	}

	static void Unbind(TextureTarget target)
	{
		glBindTexture(target, 0);
	}

	void Gen()
	{
		glGenTextures(1, &m_handle);
	}
	static Texture Create()
	{
		Texture tex;
		tex.Gen();
		return tex;
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(OTexture, Texture);
GLWRAP_MAKE_OCLASS_END();

// ----------------
// | BoundTexture1D
// ----------------

class BoundTexture1D : public BoundTexture
{
public:
	explicit BoundTexture1D(TextureTarget target = GL_TEXTURE_1D)
		: BoundTexture(target)
	{ }

	GLint GetWidth(GLint level=0) const
	{
		return GetLevelInteger(GL_TEXTURE_WIDTH, level);
	}

	void SetWrap(const Wrap& wrap)
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_1D, m_target == GL_TEXTURE_1D);

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap.s);
	}
	Wrap GetWrap() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_1D, m_target == GL_TEXTURE_1D);

		Wrap wrap;
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_S, (GLint*)&wrap.s);
		return wrap;
	}

	void Image(GLint level, InternalFormat internalformat, GLint width, GLint border, PixelFormat format, PixelType type, GLvoid* pixels)
	{
		Image1D(level, internalformat, width, border, format, type, pixels);
	}

	void Unbind()
	{
		glBindTexture(m_target, 0);
	}
};

// -----------
// | Texture1D
// -----------

class Texture1D : public Texture
{
public:
	Texture1D()
		: Texture()
	{
	}
	explicit Texture1D(GLuint handle)
		: Texture(handle)
	{
	}
	void swap(Texture1D& tex)
	{
		Handle::swap(tex);
	}

	BoundTexture1D Bind(TextureTarget target = GL_TEXTURE_1D) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Texture is initialized");
		glBindTexture(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(BoundTexture1D(target), m_handle);
	}
	static void Unbind(TextureTarget target = GL_TEXTURE_1D)
	{
		glBindTexture(target, 0);
	}

	static Texture1D Create()
	{
		Texture1D tex;
		tex.Gen();
		return tex;
	}
};
GLWRAP_MAKE_OCLASS_BEGIN(OTexture1D, Texture1D);
GLWRAP_MAKE_OCLASS_END();


// ----------------
// | BoundTexture2D
// ----------------

class BoundTexture2D : public BoundTexture
{
public:
	explicit BoundTexture2D(TextureTarget target = GL_TEXTURE_2D)
		: BoundTexture(target)
	{ }
		
	GLint GetWidth(GLint level=0) const
	{
		return GetLevelInteger(GL_TEXTURE_WIDTH, level);
	}
	GLint GetHeight(GLint level=0) const
	{
		return GetLevelInteger(GL_TEXTURE_HEIGHT, level);
	}

	void SetWrap(const Wrap& wrap)
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap.s);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrap.t);
	}
	Wrap GetWrap() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_2D, m_target == GL_TEXTURE_2D);

		Wrap wrap;
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_S, (GLint*)&wrap.s);
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_T, (GLint*)&wrap.t);
		return wrap;
	}

	void Image(GLint level, InternalFormat internalformat, GLint width, GLint height, GLint border, PixelFormat format, PixelType type, GLvoid* pixels)
	{
		Image2D(level, internalformat, width, height, border, format, type, pixels);
	}

	void Unbind()
	{
		glBindTexture(m_target, 0);
	}
};

// -----------
// | Texture2D
// -----------

class Texture2D : public Texture
{
public:
	Texture2D()
		: Texture()
	{
	}
	explicit Texture2D(GLuint handle)
		: Texture(handle)
	{
	}
	void swap(Texture2D& tex)
	{
		Handle::swap(tex);
	}

	BoundTexture2D Bind(TextureTarget target=GL_TEXTURE_2D) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Texture is initialized");
		glBindTexture(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(BoundTexture2D(target), m_handle);
	}
	static void Unbind(TextureTarget target=GL_TEXTURE_2D)
	{
		glBindTexture(target, 0);
	}

	static Texture2D Create()
	{
		Texture2D tex;
		tex.Gen();
		return tex;
	}
};
GLWRAP_MAKE_OCLASS_BEGIN(OTexture2D, Texture2D);
GLWRAP_MAKE_OCLASS_END();

// ----------------
// | BoundTexture3D
// ----------------

class BoundTexture3D : public BoundTexture
{
public:
	BoundTexture3D(TextureTarget target=GL_TEXTURE_3D)
		: BoundTexture(target)
	{ }
	GLint GetWidth(GLint level=0) const
	{
		return GetLevelInteger(GL_TEXTURE_WIDTH, level);
	}
	GLint GetHeight(GLint level = 0) const
	{
		return GetLevelInteger(GL_TEXTURE_HEIGHT, level);
	}
	GLint GetDepth(GLint level = 0) const
	{
		return GetLevelInteger(GL_TEXTURE_DEPTH, level);
	}

	void SetWrap(const Wrap& wrap)
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D);

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap.s);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrap.t);
		if (wrap.r != GL_NONE)
			glTexParameteri(m_target, GL_TEXTURE_WRAP_R, wrap.r);
	}
	Wrap GetWrap() const
	{
		GLWRAP_CHECK_ACTIVE(GL_TEXTURE_BINDING_3D, m_target == GL_TEXTURE_3D);

		Wrap wrap;
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_S, (GLint*)&wrap.s);
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_T, (GLint*)&wrap.t);
		glGetTexParameteriv(m_target, GL_TEXTURE_WRAP_R, (GLint*)&wrap.r);
		return wrap;
	}

	void Image(GLint level, InternalFormat internalformat, GLint width, GLint height, GLint depth, GLint border, PixelFormat format, PixelType type, GLvoid* pixels)
	{
		Image3D(level, internalformat, width, height, depth, border, format, type, pixels);
	}

	void Unbind()
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

	BoundTexture3D Bind(TextureTarget target=GL_TEXTURE_3D) const
	{
		Texture::Bind(target);
		return GLWRAP_ATTACH_HANDLE(BoundTexture3D(target), m_handle);
	}
	static void Unbind(TextureTarget target=GL_TEXTURE_3D)
	{
		Texture::Unbind(target);
	}

	static Texture3D Create()
	{
		Texture3D t;
		t.Gen();
		return t;
	}
};
GLWRAP_MAKE_OCLASS_BEGIN(OTexture3D, Texture3D);
GLWRAP_MAKE_OCLASS_END();
																				#endif//GLWRAP_NO_TEXTURE3D

																				#ifndef GLWRAP_NO_SAMPLER

// --------------
// | BoundSampler
// --------------

class BoundSampler : public BoundHandle
{
public:
	BoundSampler(GLuint unit=0)
		: m_unit(unit)
	{ }

	void Unbind()
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
	void Delete()
	{
		if (m_handle)
		{
			glDeleteSamplers(1, &m_handle);
			m_handle = 0;
		}
	}

	BoundSampler Bind(GLuint unit=0) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		glBindSampler(unit, m_handle);
		return GLWRAP_ATTACH_HANDLE(BoundSampler(unit), m_handle);
	}
	static void Unbind(GLuint unit=0)
	{
		glBindSampler(unit, 0);
	}

	void SetFilter(const Filter& filter)
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		glSamplerParameteri(m_handle, GL_TEXTURE_MIN_FILTER, filter.min);
		glSamplerParameteri(m_handle, GL_TEXTURE_MAG_FILTER, filter.mag);
																				#ifndef GLWRAP_FILTER_NO_ANISOTROPIC
		glSamplerParameteri(m_handle, GL_TEXTURE_MAX_ANISOTROPY_EXT, filter.max_anisotropy);
																				#endif//GLWRAP_FILTER_NO_ANISOTROPIC
	}
	Filter GetFilter() const
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

	void SetWrap(const Wrap& wrap)
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_S, wrap.s);
		glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_T, wrap.t);
		if (wrap.r != GL_NONE)
			glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_R, wrap.r);
	}
	Wrap GetWrap() const
	{
		GLWRAP_ASSERT(m_handle != 0, "Sampler is initialized");
		Wrap wrap;
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_WRAP_S, (GLint*)&wrap.s);
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_WRAP_T, (GLint*)&wrap.t);
		glGetSamplerParameteriv(m_handle, GL_TEXTURE_WRAP_R, (GLint*)&wrap.r);
		return wrap;
	}

	void Gen()
	{
		GLWRAP_ASSERT(m_handle == 0, "Sampler is uninitialized");
		glGenSamplers(1, &m_handle);
	}

	static Sampler Create()
	{
		Sampler s;
		s.Gen();
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

	void Apply() const
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

	void Enable() const
	{
		GLWRAP_ASSERT(size != -1, "VertexAttribPointer is initialized");
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}
	void Disable() const 
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
	void Delete()
	{
		if (m_handle)
		{
			glDeleteShader(m_handle);
			m_handle = 0;
		}
	}

	void Source(const GLchar* source)
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		glShaderSource(m_handle, 1, &source, nullptr);
	}
	void Source(const GLchar* source, GLint length)
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		glShaderSource(m_handle, 1, &source, &length);
	}
	void Source(const std::string& source)
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		const GLchar* data = source.data();
		GLint size = source.size();
		glShaderSource(m_handle, 1, &data, &size);
	}
	void Source(GLint num, const GLchar** sources, const GLint* lengths=nullptr)
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		glShaderSource(m_handle, num, sources, lengths);
	}

	void Compile()
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		GLWRAP_ASSERT(GetParam(GL_SHADER_SOURCE_LENGTH) != 0, "Shader has no source");
		glCompileShader(m_handle);
	}

	GLint GetParam(ShaderParamName pname) const
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		GLint t;
		glGetShaderiv(m_handle, pname, &t);
		return t;
	}

	GLint GetInfoLogLength() const
	{
		return GetParam(GL_INFO_LOG_LENGTH);
	}
	void GetInfoLog(GLsizei bufSize, GLsizei *length, GLchar* infoLog) const
	{
		GLWRAP_ASSERT(m_handle, "Shader is initialized");
		glGetShaderInfoLog(m_handle, bufSize, length, infoLog);
	}
	std::string GetInfoLog() const
	{
		std::string str;
		GLint len = GetInfoLogLength();
		str.resize(len + 1);
		GetInfoLog(str.size(), nullptr, &str[0]);
		str.resize(len);
		return str;
	}

	static Shader Create(ShaderType type)
	{
		return Shader(glCreateShader(type));
	}
};

GLWRAP_MAKE_OCLASS_BEGIN_NO_HANDLE(OShader, Shader);
OShader(GLuint handle) : Shader(handle) { }
static OShader Create(ShaderType type) { return Shader::Create(type); }
GLWRAP_MAKE_OCLASS_END();

// --------------
// | BoundProgram
// --------------

class BoundProgram : public BoundHandle
{
public:
	void Uniform(GLint location, GLfloat v0) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform1f(location, v0); }
	void Uniform(GLint location, GLfloat v0, GLfloat v1) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform2f(location, v0, v1); }
	void Uniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform3f(location, v0, v1, v2); }
	void Uniform(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform4f(location, v0, v1, v2, v3); }

	void Uniform(GLint location, GLint v0) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform1i(location, v0); }
	void Uniform(GLint location, GLint v0, GLint v1) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform2i(location, v0, v1); }
	void Uniform(GLint location, GLint v0, GLint v1, GLint v2) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform3i(location, v0, v1, v2); }
	void Uniform(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform4i(location, v0, v1, v2, v3); }

	void Uniform(GLint location, GLuint v0) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform1ui(location, v0); }
	void Uniform(GLint location, GLuint v0, GLuint v1) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform2ui(location, v0, v1); }
	void Uniform(GLint location, GLuint v0, GLuint v1, GLuint v2) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform3ui(location, v0, v1, v2); }
	void Uniform(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform4ui(location, v0, v1, v2, v3); }

																				#ifdef  GLWRAP_GLM
	void Uniform(GLint location, const glm::vec2& v) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform2fv(location, glm::value_ptr(v)); }
	void Uniform(GLint location, const glm::vec3& v) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform3fv(location, glm::value_ptr(v)); }
	void Uniform(GLint location, const glm::vec4& v) { GLWRAP_CHECK_ACTIVE(GL_CURRENT_PROGRAM, true); glUniform4fv(location, glm::value_ptr(v)); }
																				#endif//GLWRAP_GLM

	void Unbind()
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
	void Delete()
	{
		if (m_handle)
		{
			glDeleteProgram(m_handle);
			m_handle = 0;
		}
	}

	void AttachShader(Shader shader)
	{
		GLWRAP_ASSERT(m_handle != 0, "Program is initialized");
		GLWRAP_ASSERT(shader.initialized(), "Shader to attach is initialized");
		glAttachShader(m_handle, shader.get());
	}

	void DetachShader(Shader shader)
	{
		GLWRAP_ASSERT(m_handle != 0, "Program is initialized");
		GLWRAP_ASSERT(shader.initialized(), "Shader to attach is initialized");
		glDetachShader(m_handle, shader.get());
	}

	void Link()
	{
		glLinkProgram(m_handle);
	}

	BoundProgram Use() const
	{
		GLWRAP_ASSERT(m_handle != 0, "Program is initialized");
		GLWRAP_ASSERT(GetParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		glUseProgram(m_handle);
		return GLWRAP_ATTACH_HANDLE(BoundProgram(), m_handle);
	}
	
	BoundProgram Bind() const
	{
		return Use();
	}

	GLint GetParam(ProgramParamName pname) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Program is initialized");
		GLint t;
		glGetProgramiv(m_handle, pname, &t);
		return t;
	}

	GLint GetUniformLocation(const GLchar* name) const
	{
		GLWRAP_ASSERT(GetParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		return glGetUniformLocation(m_handle, name);
	}
	GLint GetUniformLocation(const std::string& name) const
	{
		GLWRAP_ASSERT(GetParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		return GetUniformLocation(name.c_str());
	}

	GLint GetAttribLocation(const GLchar* name) const
	{
		GLWRAP_ASSERT(GetParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		return glGetAttribLocation(m_handle, name);
	}
	GLint GetAttribLocation(const std::string& name) const
	{
		GLWRAP_ASSERT(GetParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		return glGetAttribLocation(m_handle, name.c_str());
	}

	void BindAttribLocation(GLuint index, const GLchar* name) const
	{
		GLWRAP_ASSERT(GetParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		glBindAttribLocation(m_handle, index, name);
	}
	void BindAttrib(const VertexAttribPointer& attrib, const GLchar* name) const
	{
		GLWRAP_ASSERT(GetParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		glBindAttribLocation(m_handle, attrib.index, name);
	}
	void BindAttrib(const NamedVertexAttribPointer& attrib) const
	{
		GLWRAP_ASSERT(GetParam(GL_LINK_STATUS) == GL_TRUE, "Program is linked succesfully");
		glBindAttribLocation(m_handle, attrib.index, attrib.name.c_str());
	}

	GLint GetInfoLogLength() const
	{
		return GetParam(GL_INFO_LOG_LENGTH);
	}
	void GetInfoLog(GLsizei bufSize, GLsizei *length, GLchar* infoLog) const
	{
		glGetProgramInfoLog(m_handle, bufSize, length, infoLog);
	}
	std::string GetInfoLog() const
	{
		std::string str;
		GLint len = GetInfoLogLength();
		str.resize(len + 1);
		GetInfoLog(str.size(), nullptr, &str[0]);
		str.resize(len);
		return str;
	}

	static Program Create()
	{
		return Program(glCreateProgram());
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(OProgram, Program);
GLWRAP_MAKE_OCLASS_END();

// -------------
// | BoundBuffer
// -------------

class BoundBuffer : public TBoundHandle
{
public:
	BoundBuffer(BufferTarget target)
		: TBoundHandle(target)
	{ }

	void Data(const GLvoid* data, GLsizei size, BufferUsage usage=GL_STATIC_DRAW)
	{
		GLWRAP_CHECK_ACTIVE(GL_ARRAY_BUFFER_BINDING, m_target == GL_ARRAY_BUFFER);
		GLWRAP_CHECK_ACTIVE(GL_ELEMENT_ARRAY_BUFFER_BINDING, m_target == GL_ELEMENT_ARRAY_BUFFER);
		glBufferData(m_target, size, data, usage);
	}

	void Unbind()
	{
		glBindBuffer(m_target, 0);
	}
};

// ---------------------
// | TargetedBoundBuffer
// ---------------------

template <GLenum Target>
class TargetedBoundBuffer : public BoundBuffer
{
public:
	TargetedBoundBuffer()
		: BoundBuffer(Target)
	{ }
	TargetedBoundBuffer(BoundBuffer b)
		: BoundBuffer(Target)
	{
		GLWRAP_ASSERT(b.getTarget() == Target, "Buffer has the expected target");
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
	void Delete()
	{
		if (m_handle)
		{
			glDeleteBuffers(1, &m_handle);
			m_handle = 0;
		}
	}

	BoundBuffer Bind(BufferTarget target) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Buffer is initialized");
		glBindBuffer(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(BoundBuffer(target), m_handle);
	}
	static void Unbind(BufferTarget target)
	{
		glBindBuffer(target, 0);
	}

	void Gen()
	{
		GLWRAP_ASSERT(m_handle == 0, "Buffer is uninitialized");
		glGenBuffers(1, &m_handle);
	}
	static Buffer Create()
	{
		Buffer b;
		b.Gen();
		return b;
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(OBuffer, Buffer);
GLWRAP_MAKE_OCLASS_END();

// -------------------
// | BoundRenderbuffer
// -------------------

class BoundRenderbuffer : public TBoundHandle
{
public:
	BoundRenderbuffer(RenderbufferTarget target=GL_RENDERBUFFER)
		: TBoundHandle(target)
	{ }

	void Storage(InternalFormat internalformat, GLsizei width, GLsizei height)
	{
		GLWRAP_CHECK_ACTIVE(GL_RENDERBUFFER_BINDING, m_target == GL_RENDERBUFFER);
		glRenderbufferStorage(m_target, internalformat, width, height);
	}

	void Unbind()
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
		GLWRAP_TYPECHECK(glIsRenderbuffer, handle);
	}
	void swap(Renderbuffer& f)
	{
		Handle::swap(f);
	}
	void Delete()
	{
		if (m_handle)
		{
			glDeleteRenderbuffers(1, &m_handle);
			m_handle = 0;
		}
	}

	BoundRenderbuffer Bind(RenderbufferTarget target=GL_RENDERBUFFER) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Renerbuffer is initialized");
		glBindRenderbuffer(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(BoundRenderbuffer(target), m_handle);
	}
	static void Unbind(RenderbufferTarget target=GL_RENDERBUFFER)
	{
		glBindRenderbuffer(target, 0);
	}

	void Gen()
	{
		GLWRAP_ASSERT(m_handle == 0, "Renderbuffer is uninitialized");
		glGenRenderbuffers(1, &m_handle);
	}
	static Renderbuffer Create()
	{
		Renderbuffer r;
		r.Gen();
		return r;
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(ORenderbuffer, Renderbuffer);
GLWRAP_MAKE_OCLASS_END();

// ------------------
// | BoundFramebuffer
// ------------------

class BoundFramebuffer : public TBoundHandle
{
public:
	BoundFramebuffer(FramebufferTarget target=GL_FRAMEBUFFER)
		: TBoundHandle(target)
	{ }

	void Texture(FramebufferAttachment attachment, GLWRAP_NAMESPACE_NAME::Texture texture, GLint level=0)
	{
		GLWRAP_CHECK_ACTIVE(GL_FRAMEBUFFER_BINDING, m_target == GL_FRAMEBUFFER);
		GLWRAP_ASSERT(texture.initialized(), "Texture is initialized");
		glFramebufferTexture(m_target, attachment, texture.get(), level);
	}
	void Texture2D(FramebufferAttachment attachment, BoundTexture textarget, GLWRAP_NAMESPACE_NAME::Texture texture, GLint level = 0)
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

	void Renderbuffer(FramebufferAttachment attachment, BoundRenderbuffer renderbuffertarget, Renderbuffer renderbuffer)
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

	GLenum CheckStatus()
	{
		GLWRAP_CHECK_ACTIVE(GL_FRAMEBUFFER_BINDING, m_target == GL_FRAMEBUFFER);
		return glCheckFramebufferStatus(m_target);
	}

	void Unbind()
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
	void swap(Framebuffer& f)
	{
		Handle::swap(f);
	}
	void Delete()
	{
		if (m_handle)
		{
			glDeleteFramebuffers(1, &m_handle);
			m_handle = 0;
		}
	}

	BoundFramebuffer Bind(FramebufferTarget target=GL_FRAMEBUFFER) const
	{
		GLWRAP_ASSERT(m_handle != 0, "Framebuffer is initialized");
		glBindFramebuffer(target, m_handle);
		return GLWRAP_ATTACH_HANDLE(BoundFramebuffer(target), m_handle);
	}
	static void Unbind(FramebufferTarget target=GL_FRAMEBUFFER)
	{
		glBindFramebuffer(target, 0);
	}

	void Gen()
	{
		GLWRAP_ASSERT(m_handle == 0, "Framebuffer is uninitialized");
		glGenFramebuffers(1, &m_handle);
	}

	static Framebuffer Create()
	{
		Framebuffer f;
		f.Gen();
		return f;
	}
};

GLWRAP_MAKE_OCLASS_BEGIN(OFramebuffer, Framebuffer);
GLWRAP_MAKE_OCLASS_END();

inline void DrawElements(RenderMode mode, GLsizei count, IndexType type, TargetedBoundBuffer<GL_ELEMENT_ARRAY_BUFFER> indexBuffer, unsigned int offset=0)
{
	GLWRAP_CHECK_ACTIVE_OUT(indexBuffer.isActive(GL_ELEMENT_ARRAY_BUFFER));
	glDrawElements(mode, count, type, (void*)offset);
}

inline void DrawElements(RenderMode mode, GLsizei count, IndexType type, const GLvoid* indices)
{
	GLWRAP_AC_ASSERT(GetInteger(GL_ELEMENT_ARRAY_BUFFER_BINDING) == 0, "No element array buffer bound");
	glDrawElements(mode, count, type, indices);
}

inline void DrawElements(RenderMode mode, GLsizei count, const GLuint* indices)
{
	DrawElements(mode, count, GL_UNSIGNED_INT, indices);
}

inline void DrawElements(RenderMode mode, GLsizei count, const GLushort* indices)
{
	DrawElements(mode, count, GL_UNSIGNED_SHORT, indices);
}

inline void DrawElements(RenderMode mode, GLsizei count, const GLubyte* indices)
{
	DrawElements(mode, count, GL_UNSIGNED_BYTE, indices);
}

inline void ClearStencil(GLint stencil)
{
	glClearStencil(stencil);
}

inline void ClearDepth(GLclampd depth)
{
	glClearDepth(depth);
}

inline void ClearColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

inline void Clear(ClearMask mask)
{
	glClear(mask);
}

inline GLenum GetError()
{
	return glGetError();
}

#ifndef GLWRAP_NO_EXT

namespace ext
{

// -------------
// | IndexFormat
// -------------

struct IndexFormat
{
	IndexFormat()
		: renderMode(GL_NONE)
		, count(0)
		, type(GL_NONE)
	{ }
	IndexFormat(RenderMode renderMode, GLuint count, IndexType type)
		: renderMode(renderMode)
		, count(count)
		, type(type)
	{ }

	RenderMode renderMode;
	GLuint count;
	IndexType type;
};

// ------------------
// | BoundIndexBuffer
// ------------------

class BoundIndexBuffer : public BoundBuffer
{
public:
	BoundIndexBuffer(const IndexFormat& format)
		: BoundBuffer(GL_ELEMENT_ARRAY_BUFFER)
		, m_format(format)
	{ }
	BoundIndexBuffer(const BoundBuffer& buf, const IndexFormat& format)
		: BoundBuffer(buf)
		, m_format(format)
	{ }

	void Draw()
	{
		DrawElements(m_format.renderMode, m_format.count, m_format.type, *this);
	}
	void Draw(unsigned int count, unsigned int offset=0)
	{
		GLWRAP_ASSERT(offset + count <= m_format.count, "Not drawing too much indices");
		DrawElements(m_format.renderMode, count, m_format.type, *this, offset);
	}

	IndexFormat getFormat() const { return m_format; }
private:
	IndexFormat m_format;
};

// -------------
// | IndexBuffer
// -------------

class IndexBuffer : public Buffer
{
public:
	IndexBuffer()
		: Buffer()
	{ }
	IndexBuffer(GLuint buffer)
		: Buffer(buffer)
	{
	}
	void swap(IndexBuffer& b)
	{
		Buffer::swap(b);
	}

	BoundIndexBuffer Bind(BufferTarget target = GL_ELEMENT_ARRAY_BUFFER) const
	{
		return BoundIndexBuffer(Buffer::Bind(target), m_format);
	}
	static void Unbind(BufferTarget target = GL_ELEMENT_ARRAY_BUFFER)
	{
		Buffer::Unbind(target);
	}

	static IndexBuffer Create()
	{
		IndexBuffer b;
		b.Gen();
		return b;
	}
private:
	IndexFormat m_format;
};

GLWRAP_MAKE_OCLASS_BEGIN(OIndexBuffer, IndexBuffer);
GLWRAP_MAKE_OCLASS_END();

}

#endif

}//namespace

#undef GLWRAP_ASSERT
#undef GLWRAP_TYPECHECK2
#undef GLWRAP_TYPECHECK
#undef GLWRAP_CHECK_ACTIVE
#undef GLWRAP_CHECK_ACTIVE_OUT
#undef GLWRAP_AC_ASSERT
#undef GLWRAP_ATTACH_HANDLE
#undef GLWRAP_TEXTURE_ACTIVECHECK
#undef GLWRAP_MAKE_OCLASS_BEGIN
#undef GLWRAP_MAKE_OCLASS_BEGIN_NO_HANDLE
#undef GLWRAP_MAKE_OCLASS_END
#undef GLWRAP_ENUM_BEGIN
#undef GLWRAP_ENUM_ALLOW
#undef GLWRAP_ENUM_END
#undef GLWRAP_ENUM_ASSERT
#undef GLWRAP_MOVE
#ifdef GLWRAP_OLD_ASSERT_DEFINE
#define assert GLWRAP_OLD_ASSERT_DEFINE
#undef GLWRAP_OLD_ASSERT_DEFINE
#endif

#endif