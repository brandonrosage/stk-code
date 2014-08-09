layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in vec3 nor[];

void main()
{
    for(int i=0; i < gl_in.length(); i++)
    {
        vec4 pos = gl_in[i].gl_Position;
        gl_Position = pos;
        EmitVertex();

        vec3 normal = nor[i];
        gl_Position = pos + .2 * vec4(normal, 0.);
        EmitVertex();

        EndPrimitive();
    }
}