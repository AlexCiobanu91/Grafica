#version 140
out vec4 out_color;

uniform sampler2D textura1;
uniform sampler2D textura2;
uniform vec3 light_position;
uniform vec3 eye_position;
uniform int material_shininess;
uniform float material_kd;
uniform float material_ks;

in vec2 texcoord;
in vec3 world_pos;
in vec3 world_normal;

vec3 L;
vec3 V;
vec3 H;

void main(){
	float light=0;
	int nl;

  // calcul iluminare Phong
	L = normalize(light_position - world_pos); 
	V = normalize(eye_position - world_pos);
	H = normalize(L + V);

	if( dot(world_normal,L) > 0)
		nl = 1;
	else
		nl = 0;

	float ambient = 0.2;
	float col = 1;
	light = ambient + 
          material_kd * col * max(dot(world_normal, L), 0) + 
          material_ks * col * nl* pow((max(dot(world_normal, H), 0)), material_shininess);

	vec3 tex1 = texture(textura1, texcoord).xyz;
	vec3 tex2 = texture(textura2, texcoord).xyz;

	out_color = vec4(tex1, 1) * light;
}