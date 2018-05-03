#version 320 es

layout(location = 0) in highp vec2 v_tex_coord;

layout(location = 8) uniform sampler2D u_tex;

layout(location = 0) out highp vec4 frag_color;

void main() {
  frag_color = texture(u_tex, v_tex_coord);
  //frag_color = vec4(v_tex_coord, 1.0, 1.0);
  //frag_color = vec4(1.0, 1.0, 1.0, 1.0);
}