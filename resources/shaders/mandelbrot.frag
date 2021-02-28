#version 400
/* Fragment shader that renders Mandelbrot set */
// precision highp float;

/* Width and height of screen in pixels */ 
uniform vec2 u_resolution;

/* Point on the complex plane that will be mapped to the center of the screen */
uniform vec2 u_zoomCenter;

/* Distance between left and right edges of the screen. This essentially specifies
   which points on the plane are mapped to left and right edges of the screen.
  Together, u_zoomCenter and u_zoomSize determine which piece of the complex
   plane is displayed. */
uniform float u_zoomSize;

/* How many iterations to do before deciding that a point is in the set. */
uniform int u_maxIterations;


// out vec4 frag_color;

vec2 f(vec2 z, vec2 c) {
	return mat2(z,-z.y,z.x)*z + c;
}
vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d) {
    return a + b*cos( 6.28318*(c*t+d) );
}
void main() {
  int iterations = 0;
  vec2 uv = gl_FragCoord.xy / u_resolution;
  
  /* Decide which point on the complex plane this fragment corresponds to.*/
  vec2 c = u_zoomCenter + (uv * 4.0 - vec2(2.0)) * (u_zoomSize / 4.0);
  
  /* Now iterate the function. */
  vec2 z = vec2(0.0);
  bool escaped = false;
  for (int i = 0; i < u_maxIterations; i++) {

    iterations = i;
    z = f(z, c);
    if (length(z) > 2.0) {
      escaped = true;
      break;
    }
  }
  gl_FragColor = escaped ? vec4(palette(float(iterations)/ float(u_maxIterations), vec3(0.02, 0.02, 0.03), vec3(0.1, 0.2, 0.3), vec3(0.0, 0.3, 0.2), vec3(0.0, 0.5, 0.8)), 1.0) : vec4(vec3(0.3, 0.5, 0.8), 1.0);
  // gl_FragColor = vec4(1.0,0.2,0.2,1.0);
}
