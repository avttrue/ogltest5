uniform sampler2D u_texture;
varying highp vec2 v_textcoord;

void main(void)
{
    gl_FragColor = texture2D(u_texture, v_textcoord);
}
