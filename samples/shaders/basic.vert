#version 320 es

layout(location = 0) in highp vec2 a_position;
layout(location = 2) in highp vec2 a_tex_coord;

layout(location = 0) out highp vec2 v_tex_coord;

layout(location = 3) uniform mat4 u_mvp;

void main() {
  //v_tex_coord = a_tex_coord;
  v_tex_coord = a_tex_coord;
  gl_Position = u_mvp * vec4(a_position, 0.0, 1.0);
}