# version 400

uniform sampler2D Texture;
uniform float shading;

in vec4 Color;
in vec2 TexCoord;

out vec4 fColor;
 
 void main()
 {
	fColor = 0.75*Color + texture2D(Texture, TexCoord);
 }