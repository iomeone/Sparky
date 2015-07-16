#include "ShaderFactory.h"

namespace sparky { namespace graphics { namespace ShaderFactory {

#if defined(SPARKY_PLATFORM_WIN32)

	const char* default_shader_vert =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec2 uv;\n"
		"layout (location = 2) in vec2 mask_uv;\n"
		"layout (location = 3) in float tid;\n"
		"layout (location = 4) in float mid;\n"
		"layout (location = 5) in vec4 color;\n"
		"\n"
		"uniform mat4 pr_matrix;\n"
		"uniform mat4 vw_matrix = mat4(1.0);\n"
		"uniform mat4 ml_matrix = mat4(1.0);\n"
		"\n"
		"uniform mat4 mask_matrix;\n"
		"\n"
		"out DATA\n"
		"{\n"
		"	vec4 position;\n"
		"	vec2 uv;\n"
		"	vec2 mask_uv;\n"
		"	float tid;\n"
		"	float mid;\n"
		"	vec4 color;\n"
		"} vs_out;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
		"	vs_out.position = ml_matrix * position;\n"
		"	vs_out.uv = uv;\n"
		"	vs_out.tid = tid;\n"
		"	vs_out.mid = mid;\n"
		"	vs_out.color = color;\n"
		"	vs_out.mask_uv = mask_uv;\n"
		"}\n";

	const char* default_shader_frag =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"\n"
		"in DATA\n"
		"{\n"
		"	vec4 position;\n"
		"	vec2 uv;\n"
		"	vec2 mask_uv;\n"
		"	float tid;\n"
		"	float mid;\n"
		"	vec4 color;\n"
		"} fs_in;\n"
		"\n"
		"uniform sampler2D textures[32];\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec4 texColor = fs_in.color;\n"
		"	vec4 maskColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"	if (fs_in.tid > 0.0)\n"
		"	{\n"
		"		int tid = int(fs_in.tid - 0.5);\n"
		"		texColor = fs_in.color * texture(textures[tid], fs_in.uv);\n"
		"	}\n"
		"	if (fs_in.mid > 0.0)\n"
		"	{\n"
		"		int mid = int(fs_in.mid - 0.5);\n"
		"		maskColor = texture(textures[mid], fs_in.mask_uv);\n"
		"	}\n"
		"	color = texColor * maskColor; // vec4(1.0 - maskColor.x, 1.0 - maskColor.y, 1.0 - maskColor.z, 1.0);\n"
		"}\n";

	const char* simple_shader_vert =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec2 uv;\n"
		"layout (location = 2) in vec2 mask_uv;\n"
		"layout (location = 3) in float tid;\n"
		"layout (location = 4) in float mid;\n"
		"layout (location = 5) in vec4 color;\n"
		"\n"
		"uniform mat4 pr_matrix;\n"
		"\n"
		"out DATA\n"
		"{\n"
		"	vec2 uv;\n"
		"} vs_out;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = pr_matrix * position;\n"
		"	vs_out.uv = uv;\n"
		"}\n";

	const char* simple_shader_frag =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"\n"
		"uniform sampler2D tex;\n"
		"\n"
		"in DATA\n"
		"{\n"
		"	vec2 uv;\n"
		"} fs_in;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = texture(tex, fs_in.uv);\n"
		"}\n";

#elif defined(SPARKY_PLATFORM_WEB)

	const char* default_shader_vert =
		"attribute highp vec4 position;\n"
		"attribute highp vec2 uv;\n"
		"attribute highp float tid;\n"
		"attribute highp vec4 color;\n"
		"\n"
		"uniform highp mat4 pr_matrix;\n"
		"uniform highp mat4 vw_matrix;\n"
		"uniform highp mat4 ml_matrix;\n"
		"\n"
		"varying highp vec4 vs_position;\n"
		"varying highp vec2 vs_uv;\n"
		"varying highp float vs_tid;\n"
		"varying highp vec4 vs_color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = pr_matrix * position;\n"
		"	vs_position = position;\n"
		"	vs_uv = uv;\n"
		"	vs_tid = tid;\n"
		"	vs_color = color;\n"
		"}\n";

	const char* default_shader_frag =
		"precision highp float; \n"
		"\n"
		"uniform highp vec4 colour;\n"
		"uniform highp vec2 light_pos;\n"
		"\n"
		"varying highp vec4 vs_position;\n"
		"varying highp vec2 vs_uv;\n"
		"varying highp float vs_tid;\n"
		"varying highp vec4 vs_color;\n"
		"\n"
		"uniform sampler2D texture_0;\n"
		"uniform sampler2D texture_1;\n"
		"uniform sampler2D texture_2;\n"
		"uniform sampler2D texture_3;\n"
		"uniform sampler2D texture_4;\n"
		"uniform sampler2D texture_5;\n"
		"uniform sampler2D texture_6;\n"
		"uniform sampler2D texture_7;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	float intensity = 1.0 / length(vs_position.xy - light_pos);\n"
		"	vec4 texColor = vs_color;\n"
		"	if (vs_tid > 0.0)\n"
		"	{\n"
		"		int tid = int(vs_tid - 0.5);\n"
		"		if (tid == 0)\n"
		"			texColor = vs_color * texture2D(texture_0, vs_uv);\n"
		"		else if (tid == 1)\n"
		"			texColor = vs_color * texture2D(texture_1, vs_uv);\n"
		"		else if (tid == 2)\n"
		"			texColor = vs_color * texture2D(texture_2, vs_uv);\n"
		"		else if (tid == 3)\n"
		"			texColor = vs_color * texture2D(texture_3, vs_uv);\n"
		"		else if (tid == 4)\n"
		"			texColor = vs_color * texture2D(texture_4, vs_uv);\n"
		"		else if (tid == 5)\n"
		"			texColor = vs_color * texture2D(texture_5, vs_uv);\n"
		"		else if (tid == 6)\n"
		"			texColor = vs_color * texture2D(texture_6, vs_uv);\n"
		"		else if (tid == 7)\n"
		"			texColor = vs_color * texture2D(texture_7, vs_uv);\n"
		"	}\n"
		"	gl_FragColor = texColor * intensity;\n"
		"}\n";

	const char* simple_shader_vertex =
		"#version 140\n"
		"\n"
		"attribute vec4 position;\n"
		"attribute vec2 uv;\n"
		"attribute float tid;\n"
		"attribute vec4 color;\n"
		"\n"
		"uniform mat4 pr_matrix;\n"
		"\n"
		"varying vec2 vs_uv;\n"
		"varying float vs_tid;\n"
		"varying vec4 vs_color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = pr_matrix * position;\n"
		"	vs_uv = uv;\n"
		"}\n";

	const char* simple_shader_fragment =
		"#version 140\n"
		"\n"
		"uniform sampler2D tex;\n"
		"\n"
		"varying vec4 vs_position;\n"
		"varying vec2 vs_uv;\n"
		"varying float vs_tid;\n"
		"varying vec4 vs_color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = texture2D(tex, vs_uv);\n"
		"}\n";

#endif

	const char* basic_light_shader_vert =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec2 uv;\n"
		"layout (location = 2) in float tid;\n"
		"layout (location = 3) in vec4 color;\n"
		"\n"
		"uniform mat4 pr_matrix;\n"
		"uniform mat4 vw_matrix = mat4(1.0);\n"
		"uniform mat4 ml_matrix = mat4(1.0);\n"
		"\n"
		"out DATA\n"
		"{\n"
		"	vec4 position;\n"
		"	vec2 uv;\n"
		"	float tid;\n"
		"	vec4 color;\n"
		"} vs_out;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
		"	vs_out.position = ml_matrix * position;\n"
		"	vs_out.uv = uv;\n"
		"	vs_out.tid = tid;\n"
		"	vs_out.color = color;\n"
		"}\n";

	const char* basic_light_shader_frag =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"\n"
		"uniform vec4 colour;\n"
		"uniform vec2 light_pos;\n"
		"\n"
		"in DATA\n"
		"{\n"
		"	vec4 position;\n"
		"	vec2 uv;\n"
		"	float tid;\n"
		"	vec4 color;\n"
		"} fs_in;\n"
		"\n"
		"uniform sampler2D textures[32];\n"
		"\n"
		"void main()\n"
		"{\n"
		"	float intensity = 1.0 / length(fs_in.position.xy - light_pos);\n"
		"	vec4 texColor = fs_in.color;\n"
		"	if (fs_in.tid > 0.0)\n"
		"	{\n"
		"		int tid = int(fs_in.tid - 0.5);\n"
		"		texColor = fs_in.color * texture(textures[tid], fs_in.uv);\n"
		"	}\n"
		"	color = texColor * intensity;\n"
		"}\n";

	Shader* DefaultShader()
	{
		return Shader::FromSource("Default Shader", default_shader_vert, default_shader_frag);
	}

	Shader* SimpleShader()
	{
		return Shader::FromSource("Simple Shader", simple_shader_vert, simple_shader_frag);
	}

	Shader* BasicLightShader()
	{
		return Shader::FromSource("Basic Light Shader", basic_light_shader_vert, basic_light_shader_frag);
	}

} } }