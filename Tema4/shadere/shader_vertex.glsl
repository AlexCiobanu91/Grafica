#version 140

in vec3 in_position_Asleep;		
in vec3 in_normals_Asleep;	
in vec2 in_texcoord_Asleep;

in vec3 in_position_Annoyed;
in vec3 in_normals_Annoyed;
in vec2 in_texcoord_Annoyed;

in vec3 in_position_Surprised;
in vec3 in_normals_Surprised;
in vec2 in_texcoord_Surprised;

uniform mat4 model_matrix, view_matrix, projection_matrix;
uniform int stare;
uniform int frame;
uniform int nr_frames;

out vec2 texcoord;
out vec3 world_pos;
out vec3 world_normal;

void Surprise()
{
	texcoord = in_texcoord_Surprised;
	// Calculare pas;
	vec3 pas, crtPos;
	pas.x = (in_position_Surprised.x - in_position_Asleep.x) / nr_frames;
	pas.y = (in_position_Surprised.y - in_position_Asleep.y) / nr_frames;
	pas.z = (in_position_Surprised.z - in_position_Asleep.z) / nr_frames;
	crtPos.x = pas.x * frame + in_position_Asleep.x;
	crtPos.y = pas.y * frame + in_position_Asleep.y;
	crtPos.z = pas.z * frame + in_position_Asleep.z;
	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(crtPos,1);

}

void Annoy()
{
	texcoord = in_texcoord_Annoyed;

	// Calculare pas;
	vec3 pas, crtPos;
	pas.x = (in_position_Annoyed.x - in_position_Surprised.x)/nr_frames;
	pas.y = (in_position_Annoyed.y - in_position_Surprised.y)/nr_frames;
	pas.z = (in_position_Annoyed.z - in_position_Surprised.z)/nr_frames;

	crtPos.x = pas.x * frame + in_position_Surprised.x;
	crtPos.y = pas.y * frame + in_position_Surprised.y;
	crtPos.z = pas.z * frame + in_position_Surprised.z;

	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(crtPos,1);
}

void Sleep()
{
	texcoord = in_texcoord_Asleep;

	// Calculare pas;
	vec3 pas, crtPos;
	pas.x = (in_position_Asleep.x - in_position_Annoyed.x)/nr_frames;
	pas.y = (in_position_Asleep.y - in_position_Annoyed.y)/nr_frames;
	pas.z = (in_position_Asleep.z - in_position_Annoyed.z)/nr_frames;

	crtPos.x = pas.x * frame + in_position_Annoyed.x;
	crtPos.y = pas.y * frame + in_position_Annoyed.y;
	crtPos.z = pas.z * frame + in_position_Annoyed.z;

	gl_Position = projection_matrix*view_matrix*model_matrix*vec4(crtPos,1);
}

void main()
{
	world_pos = (model_matrix * vec4(in_position_Asleep,1)).xyz;
	world_normal = normalize(mat3(model_matrix) *  in_normals_Asleep);

	if (stare == 0) {
		texcoord = in_texcoord_Asleep;
		gl_Position = projection_matrix*view_matrix*model_matrix*vec4(in_position_Asleep,1);
	} else if (stare == 1) {
		Surprise();
	} else if (stare == 2) {
		Annoy();
	} else if (stare == 3) {
		Sleep();
	}
}
