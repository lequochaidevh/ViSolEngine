#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include <GLES2/gl2ext.h>

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <gbm.h>
#include <unistd.h>

static const int WIDTH = 512;
static const int HEIGHT = 512;

int main() {

  int drm_fd = open("/dev/dri/renderD128", O_RDWR);
  if (drm_fd < 0) {
    perror("open render node");
    return -1;
  }

  gbm_device *gbm = gbm_create_device(drm_fd);

  gbm_bo *bo = gbm_bo_create(gbm, WIDTH, HEIGHT, GBM_FORMAT_ARGB8888,
                             GBM_BO_USE_RENDERING);

  EGLDisplay display = eglGetDisplay((EGLNativeDisplayType)gbm);

  eglInitialize(display, NULL, NULL);
  eglBindAPI(EGL_OPENGL_ES_API);

  EGLint config_attribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, EGL_NONE};

  EGLConfig config;
  EGLint num;
  eglChooseConfig(display, config_attribs, &config, 1, &num);

  EGLint ctx_attr[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

  EGLContext ctx = eglCreateContext(display, config, EGL_NO_CONTEXT, ctx_attr);

  eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);

  printf("Renderer: %s\n\n", glGetString(GL_RENDERER));

  /* ---- LOAD EXTENSIONS ---- */

  PFNEGLCREATEIMAGEKHRPROC eglCreateImageKHR_ptr =
      (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");

  PFNGLEGLIMAGETARGETTEXTURE2DOESPROC
  glEGLImageTargetTexture2DOES_ptr =
      (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress(
          "glEGLImageTargetTexture2DOES");

  if (!eglCreateImageKHR_ptr || !glEGLImageTargetTexture2DOES_ptr) {
    printf("Extension not supported\n");
    return -1;
  }

  /* ---- CREATE EGL IMAGE ---- */

  EGLImageKHR image =
      eglCreateImageKHR_ptr(display, EGL_NO_CONTEXT, EGL_NATIVE_PIXMAP_KHR,
                            (EGLClientBuffer)bo, NULL);

  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  glEGLImageTargetTexture2DOES_ptr(GL_TEXTURE_2D, (GLeglImageOES)image);

  GLuint fbo;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         tex, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    printf("FBO incomplete!\n");
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glFinish();

  unsigned char pixel[4];
  glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

  printf("Pixel[0,0] = %d %d %d %d\n", pixel[0], pixel[1], pixel[2], pixel[3]);

  printf("Done.\n");

  /* 7️⃣ Save PPM */

  /* ---- SAVE TO PPM ---- */

  unsigned char *pixels = (unsigned char *)malloc(WIDTH * HEIGHT * 4);

  glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  FILE *f = fopen("out.ppm", "wb");
  if (!f) {
    perror("fopen");
    return -1;
  }

  /* P6 binary PPM */
  fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

  /* OpenGL origin = bottom-left
     PPM expects top-left
     => flip vertically */
  for (int y = HEIGHT - 1; y >= 0; y--) {
    for (int x = 0; x < WIDTH; x++) {

      unsigned char *p = pixels + (y * WIDTH + x) * 4;

      /* write RGB only (skip alpha) */
      fwrite(p, 1, 3, f);
    }
  }

  fclose(f);
  free(pixels);

  printf("Saved out.ppm\n");

  return 0;
}
