#version 150

uniform sampler2DRect tex0;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
    vec4 rTxt = texture2DRect(tex0, texCoordVarying);
	if(rTxt.r == 1.0)
		rTxt.a = 0.0;
    
    outputColor = rTxt;
}