
uniform mat4 view_matrix, projection_matrix, model_matrix;
in vec3 in_position;		
in vec3 in_speed;
in vec3 in_color;
in vec2 in_texcoord;
out vec3 color;
out vec2 texcoord;
uniform int crtTime; 
 
void main () {
 
 vec3 particlePosition;
 // calculam noua pozitie a particulei in functie de viteza si timpul curent
 particlePosition = vec3(in_position.x + in_speed.x * crtTime,
                            in_position.y + in_speed.y * crtTime,
                            in_position.z + in_speed.z * crtTime); 
  color = in_color;
  texcoord = in_texcoord;
  gl_Position = projection_matrix * view_matrix * vec4(particlePosition, 1.0);

}