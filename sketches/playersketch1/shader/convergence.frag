#version 150

uniform sampler2DRect image;
uniform float rand;

in vec2 pos;
out vec4 outputColor;

void main (void)
{
        vec4 col = texture2DRect(image,pos);

        vec4 col_r = texture2DRect(image,pos + vec2(-35.0*rand,0));
        vec4 col_l = texture2DRect(image,pos + vec2( 35.0*rand,0));
        vec4 col_g = texture2DRect(image,pos + vec2( -7.5*rand,0));


        col.b = col.b + col_r.b*max(1.0,sin(pos.y*1.2)*2.5)*rand;
        col.r = col.r + col_l.r*max(1.0,sin(pos.y*1.2)*2.5)*rand;
        col.g = col.g + col_g.g*max(1.0,sin(pos.y*1.2)*2.5)*rand;


        outputColor = col;
}
