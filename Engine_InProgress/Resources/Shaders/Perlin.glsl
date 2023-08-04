#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D al_tex; //texture used in al_draw_bitmap
varying vec4 varying_color;
varying vec2 varying_texcoord;
uniform sampler2D tex1;
uniform sampler2D tex2;
varying vec2 tex_uv;

vec2 random(vec2 uv) {
    uv = vec2(dot(uv, vec2(121.1, 311.7)), dot(uv, vec2(262.5, 183.3)));
    return -1.0 + 2.0 * fract(sin(uv) * 3.0);
}

float noise(vec2 uv) {
    vec2 uv_index = floor(uv);
    vec2 uv_fract = fract(uv);

    vec2 blur = smoothstep(0.0, 1.0, uv_fract);

    return mix(mix(dot(random(uv_index + vec2(0.0, 0.0)), uv_fract - vec2(0.0, 0.0)), dot(random(uv_index + vec2(1.0, 0.0)), uv_fract - vec2(1.0, 0.0)), blur.x), mix(dot(random(uv_index + vec2(0.0, 1.0)), uv_fract - vec2(0.0, 1.0)), dot(random(uv_index + vec2(1.0, 1.0)), uv_fract - vec2(1.0, 1.0)), blur.x), blur.y) + 0.5;
}

const int max_octaves = 6;

float FBM(vec2 uv)
{
    float result = 0.0;
    float ampl = 1.0;
    float freq = 0.005;

    for(int oct = 0; oct < max_octaves; oct++)
    {
        result += ampl * noise(uv * freq);
        ampl *= 0.5;
        freq *= 2.0;
    }

    return result;
}

void main(void) {
    float t = 0.0;
    t = FBM(varying_texcoord.xy * 100.0);
    vec4 color = texture2D(al_tex, varying_texcoord.xy);
    vec4 texture_color = texture2D(tex1, varying_texcoord.xy) * t;
    gl_FragColor = mix(color, texture_color, texture_color.a);
}