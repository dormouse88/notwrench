uniform sampler2D texture;
uniform float pixel_threshold;
uniform float blur_radius;

void main()
{
    float factor = 1.0 / (pixel_threshold + 0.001);
	vec2 diagpos;
	diagpos.x = floor( (gl_TexCoord[0].x + gl_TexCoord[0].y) * factor + 0.5) / factor;
	diagpos.y = floor( (gl_TexCoord[0].x - gl_TexCoord[0].y) * factor + 0.5) / factor;
	vec2 pos;
	pos.y = (diagpos.x - diagpos.y) / 2.0;
	pos.x = diagpos.x - pos.y;

	vec2 offx = vec2(blur_radius, 0.0);
	vec2 offy = vec2(0.0, blur_radius);

	vec4 pixel = texture2D(texture, pos.xy)               * 14.0 +
                 texture2D(texture, pos.xy - offx)        * 3.0 +
                 texture2D(texture, pos.xy + offx)        * 3.0 +
                 texture2D(texture, pos.xy - offy)        * 3.0 +
                 texture2D(texture, pos.xy + offy)        * 3.0 +
                 texture2D(texture, pos.xy - offx - offx) * 2.0 +
                 texture2D(texture, pos.xy + offx + offx) * 2.0 +
                 texture2D(texture, pos.xy - offy - offy) * 2.0 +
                 texture2D(texture, pos.xy + offy + offy) * 2.0;

	gl_FragColor =  gl_Color * (pixel / 34.0);
}