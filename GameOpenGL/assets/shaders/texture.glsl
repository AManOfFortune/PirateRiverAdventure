#type vertex
#version 330 core
			    
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_NormalMapIndex;
layout(location = 5) in float a_TilingFactor;

uniform mat4 u_ProjectionViewMatrix;

out vec3 v_Position;
out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out float v_NormalMapIndex;
out float v_TilingFactor;

void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_NormalMapIndex = a_NormalMapIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ProjectionViewMatrix * vec4(a_Position, 1.0);	
}

#type fragment
#version 330 core
			    
layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_NormalMapIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform float u_AmbientStrength;

void main()
{
	// Get color from main texture.
	vec4 texColor = v_Color;
	switch(int(v_TexIndex))
	{
		case 0: texColor *= texture(u_Textures[0], v_TexCoord * v_TilingFactor); break;
		case 1: texColor *= texture(u_Textures[1], v_TexCoord * v_TilingFactor); break;
		case 2: texColor *= texture(u_Textures[2], v_TexCoord * v_TilingFactor); break;
		case 3: texColor *= texture(u_Textures[3], v_TexCoord * v_TilingFactor); break;
		case 4: texColor *= texture(u_Textures[4], v_TexCoord * v_TilingFactor); break;
		case 5: texColor *= texture(u_Textures[5], v_TexCoord * v_TilingFactor); break;
		case 6: texColor *= texture(u_Textures[6], v_TexCoord * v_TilingFactor); break;
		case 7: texColor *= texture(u_Textures[7], v_TexCoord * v_TilingFactor); break;
		case 8: texColor *= texture(u_Textures[8], v_TexCoord * v_TilingFactor); break;
		case 9: texColor *= texture(u_Textures[9], v_TexCoord * v_TilingFactor); break;
		case 10: texColor *= texture(u_Textures[10], v_TexCoord * v_TilingFactor); break;
		case 11: texColor *= texture(u_Textures[11], v_TexCoord * v_TilingFactor); break;
		case 12: texColor *= texture(u_Textures[12], v_TexCoord * v_TilingFactor); break;
		case 13: texColor *= texture(u_Textures[13], v_TexCoord * v_TilingFactor); break;
		case 14: texColor *= texture(u_Textures[14], v_TexCoord * v_TilingFactor); break;
		case 15: texColor *= texture(u_Textures[15], v_TexCoord * v_TilingFactor); break;
	}

	// Get normal from normal map.
	vec4 normal;
	switch(int(v_NormalMapIndex))
	{
		case 16: normal = texture(u_Textures[16], v_TexCoord * v_TilingFactor); break;
		case 17: normal = texture(u_Textures[17], v_TexCoord * v_TilingFactor); break;
		case 18: normal = texture(u_Textures[18], v_TexCoord * v_TilingFactor); break;
		case 19: normal = texture(u_Textures[19], v_TexCoord * v_TilingFactor); break;
		case 20: normal = texture(u_Textures[20], v_TexCoord * v_TilingFactor); break;
		case 21: normal = texture(u_Textures[21], v_TexCoord * v_TilingFactor); break;
		case 22: normal = texture(u_Textures[22], v_TexCoord * v_TilingFactor); break;
		case 23: normal = texture(u_Textures[23], v_TexCoord * v_TilingFactor); break;
		case 24: normal = texture(u_Textures[24], v_TexCoord * v_TilingFactor); break;
		case 25: normal = texture(u_Textures[25], v_TexCoord * v_TilingFactor); break;
		case 26: normal = texture(u_Textures[26], v_TexCoord * v_TilingFactor); break;
		case 27: normal = texture(u_Textures[27], v_TexCoord * v_TilingFactor); break;
		case 28: normal = texture(u_Textures[28], v_TexCoord * v_TilingFactor); break;
		case 29: normal = texture(u_Textures[29], v_TexCoord * v_TilingFactor); break;
		case 30: normal = texture(u_Textures[30], v_TexCoord * v_TilingFactor); break;
		case 31: normal = texture(u_Textures[31], v_TexCoord * v_TilingFactor); break;
	}

	// Calculate diffuse light
	vec3 normalNormalized = normalize(normal.rgb * 2.0f - 1.0f);
	vec3 lightDirNormalized = normalize(u_LightPos - v_Position);
	float diffuseStrength = max(dot(normalNormalized, lightDirNormalized), 0.0f);
	vec4 diffuseLight = vec4(diffuseStrength * u_LightColor, 1.0f);

	// Calculate ambient light
	vec4 ambientLight = vec4(u_AmbientStrength * u_LightColor, 1.0f);

	color = texColor * (ambientLight + diffuseLight);
}