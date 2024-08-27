OF_GLSL_SHADER_HEADER

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 vertexColor;
out vec4 color;

void main(){
	color = vertexColor;
	gl_Position = modelViewProjectionMatrix * position;
}
