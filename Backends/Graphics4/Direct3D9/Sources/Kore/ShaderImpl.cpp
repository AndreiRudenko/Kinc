#include "pch.h"

#include <kinc/graphics4/shader.h>
#include <kinc/math/core.h>

#include "Direct3D9.h"

#include <cstdio>

#undef min
#undef max

using namespace Kore;

void kinc_g4_shader_init(kinc_g4_shader_t *shader, void *_data, size_t length, kinc_g4_shader_type_t type) {
	unsigned index = 0;

	u8 *data = (u8 *)_data;
	int attributesCount = data[index++];
	for (int i = 0; i < attributesCount; ++i) {
		char name[256];
		for (unsigned i2 = 0; i2 < 255; ++i2) {
			name[i2] = data[index++];
			if (name[i2] == 0) break;
		}
		strcpy(shader->impl.attributes[i].name, name);
		shader->impl.attributes[i].index = index++;
	}
	shader->impl.attributes[attributesCount].name[0] = 0;

	u8 constantCount = data[index++];
	for (unsigned i = 0; i < constantCount; ++i) {
		char name[256];
		for (unsigned i2 = 0; i2 < 255; ++i2) {
			name[i2] = data[index++];
			if (name[i2] == 0) break;
		}
		strcpy(shader->impl.constants[i].name, name);
		shader->impl.constants[i].regtype = data[index++];
		shader->impl.constants[i].regindex = data[index++];
		shader->impl.constants[i].regcount = data[index++];
	}
	shader->impl.constants[constantCount].name[0] = 0;

	HRESULT hr;
	if (type == KINC_G4_SHADER_TYPE_VERTEX)
		hr = device->CreateVertexShader((DWORD *)&data[index], (IDirect3DVertexShader9 **)&shader);
	else
		hr = device->CreatePixelShader((DWORD *)&data[index], (IDirect3DPixelShader9 **)&shader);
	// if (FAILED(hr)) throw Exception("CreateShader failed");
}

void kinc_g4_shader_init_from_source(kinc_g4_shader_t *shader, const char *source, kinc_g4_shader_type_t type) {}

void kinc_g4_shader_destroy(kinc_g4_shader_t *shader) {}
