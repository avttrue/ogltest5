attribute highp vec4 a_position;
attribute highp vec2 a_textcoord;
attribute highp vec3 a_normal;
uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_modelMatrix;
varying highp vec4 v_position;
varying highp vec2 v_textcoord;
varying highp vec3 v_normal;

void main(void)
{
    mat4 mv_matrix = u_viewMatrix * u_modelMatrix;
    gl_Position = u_projectionMatrix * mv_matrix * a_position;
    v_textcoord = a_textcoord;
    v_normal = normalize(vec3(mv_matrix * vec4(a_normal, 0.0)));
    v_position = mv_matrix * a_position;
}
