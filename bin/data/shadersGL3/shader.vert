OF_GLSL_SHADER_HEADER

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
out vec4 vertexColor;

void main(){
	vertexColor = vec4(0.0, 0.0, 0.0, 1.0);
	gl_Position = modelViewProjectionMatrix * position;
}
