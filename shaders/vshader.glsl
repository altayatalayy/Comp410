#version 150

in   vec4 vPosition;
in   vec3 vNormal;

out  vec3 fN;
out  vec3 fL;
out  vec3 fE;


uniform mat4 u_MVP;
uniform vec4 LightPosition;

void main() {
    fN = vNormal;
    fE = vPosition.xyz;
    fL = LightPosition.xyz;
    if( LightPosition.w != 0.0 ) {
        fL = LightPosition.xyz - vPosition.xyz;
}
    gl_Position = u_MVP*vPosition;
}

