#define EGL_EGLEXT_PROTOTYPES
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include <cstdio>
#include <cstdlib>
#include <vector>

// Simple shader sources
const char *vshader_src = R"(#version 300 es
layout(location = 0) in vec3 pos;
void main() {
    gl_Position = vec4(pos, 1.0);
})";

const char *fshader_src = R"(#version 300 es
precision mediump float;
out vec4 fragColor;
void main() {
    fragColor = vec4(1.0, 0.2, 0.1, 1.0);
})";

GLuint compile_shader(GLenum type, const char *src) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint ok;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    char log[512];
    glGetShaderInfoLog(shader, 512, NULL, log);
    printf("Shader compile error:\n%s\n", log);
    exit(1);
  }
  return shader;
}

GLuint create_program() {
  GLuint vs = compile_shader(GL_VERTEX_SHADER, vshader_src);
  GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fshader_src);

  GLuint prog = glCreateProgram();
  glAttachShader(prog, vs);
  glAttachShader(prog, fs);
  glLinkProgram(prog);

  GLint ok;
  glGetProgramiv(prog, GL_LINK_STATUS, &ok);
  if (!ok) {
    char log[512];
    glGetProgramInfoLog(prog, 512, NULL, log);
    printf("Program link error:\n%s\n", log);
    exit(1);
  }
  return prog;
}

int main() {
  // 1️⃣ Get surfaceless display
  EGLDisplay display = eglGetPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA,
                                             EGL_DEFAULT_DISPLAY, NULL);

  if (display == EGL_NO_DISPLAY) {
    printf("Failed to get EGL display\n");
    return -1;
  }

  if (!eglInitialize(display, NULL, NULL)) {
    printf("Failed to initialize EGL\n");
    return -1;
  }

  eglBindAPI(EGL_OPENGL_ES_API);

  // 2️⃣ Choose config
  EGLint config_attribs[] = {EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
                             EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, EGL_NONE};

  EGLConfig config;
  EGLint num_configs;
  eglChooseConfig(display, config_attribs, &config, 1, &num_configs);

  // 3️⃣ Create context
  EGLint ctx_attr[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

  EGLContext ctx = eglCreateContext(display, config, EGL_NO_CONTEXT, ctx_attr);
  eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);

  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Vendor: %s\n", glGetString(GL_VENDOR));
  printf("Version: %s\n", glGetString(GL_VERSION));

  // 4️⃣ Create FBO
  const int width = 512;
  const int height = 512;

  GLuint fbo, tex;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         tex, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    printf("FBO not complete\n");
    return -1;
  }

  glViewport(0, 0, width, height);
  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // 5️⃣ Render triangle
  GLuint prog = create_program();
  glUseProgram(prog);

  float vertices[] = {0.0f, 0.6f, 0.0f, -0.6f, -0.6f, 0.0f, 0.6f, -0.6f, 0.0f};

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glFinish();

  // 6️⃣ Read pixels
  std::vector<unsigned char> pixels(width * height * 4);
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

  // 7️⃣ Save PPM
  FILE *f = fopen("output.ppm", "wb");
  fprintf(f, "P6\n%d %d\n255\n", width, height);

  for (int i = 0; i < width * height; i++) {
    fwrite(&pixels[i * 4], 1, 3, f); // RGB only
  }

  fclose(f);

  printf("Saved output.ppm\n");

  eglTerminate(display);
  return 0;
}
