OF_GLSL_SHADER_HEADER

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 meshColor;
out vec4 vertexColor;

void main(){
	vertexColor = meshColor;
	gl_Position = modelViewProjectionMatrix * position;
}
