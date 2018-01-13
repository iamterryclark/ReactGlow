#version 150

precision highp float;
precision highp vec2;
precision highp vec3;

// http://www.pouet.net/prod.php?which=57245

out vec4 fragColor;
in vec4 posToFrag;

uniform float time;
uniform vec2 resolution;
uniform vec2 mouse;
uniform int vehicleSize;

uniform sampler2DRect positions;
uniform int maxCount;
float pulse = 0.0f;
float angle = 0.0f;
//uniform brightnessScale;

vec4 glowingOrb(vec3 vecPos, vec3 col, float pulseRate){

    float posLen;
    vec2 uv;

    vec2 pos = gl_FragCoord.xy / resolution;

    vecPos.xy = vecPos.xy / resolution;

    pos -= vecPos.xy;

    posLen = length(pos);

    pulse += pulseRate;
    angle += pulse;
    
    col[0] += (sin(angle) * angle) / 100000;
    col[1] += (sin(angle) * angle) / 100000;
    col[2] += (sin(angle) * angle) / 100000;

    return vec4(col/posLen, 1.);
}

void main( ){
    vec4 sumGlowingOrbs = vec4(0.0);

    for (int y = 0; y < 10; y++){
        for (int x = 0; x < 10; x++){
            int i = x + y * 10;
            vec4 pos = texture( positions, vec2(x,y) );

            if ( i < maxCount ) {
                sumGlowingOrbs += glowingOrb(pos.xyz, vec3(pos.w, pos.w, pos.w), pos.w);
            } else {
                break;
            }
        }
    }

    fragColor = sumGlowingOrbs;
}
