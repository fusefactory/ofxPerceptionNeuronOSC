#version 330
    
in vec4 vertColor;
out vec4 outColor;

void main()
{
	float dist = dot(gl_PointCoord - 0.5, gl_PointCoord - 0.5);
//    float alpha = smoothstep(0.4, 0, dist) * vertColor.a;
	outColor = vec4(vertColor.rgb, 1.0);
}
