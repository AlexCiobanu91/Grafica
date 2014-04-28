uniform sampler2D textura1; 
out vec4 out_color;
in vec3 color;
in vec2 texcoord;
void main () {

  vec4 texel = texture(textura1, texcoord);
  // folosit pentru transparenta
  if (!((texel.r < 0.1) && (texel.g < 0.1) && (texel.b < 0.1))) discard;
  out_color = vec4(texel.r + color.r, texel.g + color.g, texel.b + color.b, 1);
}
