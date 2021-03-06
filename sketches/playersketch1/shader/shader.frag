#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform sampler2DRect imageMask;

varying vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
    vec2 texCoord = vec2(pos.x , pos.y);
    vec4 rTxt = texture2DRect(tex0, texCoordVarying);
    vec4 gTxt = texture2DRect(tex1, texCoordVarying);
    vec4 bTxt = texture2DRect(tex2, texCoordVarying);
    vec4 mask = texture2DRect(imageMask, texCoordVarying);
    
    vec4 color = vec4(0, 0, 0, 0);
    color = mix(color, rTxt, mask.r);
    color = mix(color, gTxt, mask.g);
    color = mix(color, bTxt, mask.b);
    
    outputColor = bTxt;
}