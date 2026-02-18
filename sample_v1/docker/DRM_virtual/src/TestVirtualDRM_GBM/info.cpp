#define EGL_EGLEXT_PROTOTYPES

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

  /* 1️⃣ Open DRM device */
  int drm_fd = open("/dev/dri/card0", O_RDWR);
  if (drm_fd < 0) {
    perror("open drm");
    return -1;
  }

  /* 2️⃣ Create GBM device */
  gbm_device *gbm = gbm_create_device(drm_fd);
  if (!gbm) {
    printf("Failed to create GBM device\n");
    return -1;
  }

  /* 3️⃣ Create GBM buffer */
  gbm_bo *bo = gbm_bo_create(gbm, WIDTH, HEIGHT, GBM_FORMAT_ARGB8888,
                             GBM_BO_USE_RENDERING);

  if (!bo) {
    printf("Failed to create GBM BO\n");
    return -1;
  }

  /* 4️⃣ Create EGL display */
  EGLDisplay display = eglGetPlatformDisplay(EGL_PLATFORM_GBM_KHR, gbm, NULL);

  if (display == EGL_NO_DISPLAY) {
    printf("eglGetPlatformDisplay failed\n");
    return -1;
  }

  if (!eglInitialize(display, NULL, NULL)) {
    printf("eglInitialize failed\n");
    return -1;
  }

  eglBindAPI(EGL_OPENGL_ES_API);

  EGLint config_attribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT, EGL_NONE};

  EGLConfig config;
  EGLint num;
  eglChooseConfig(display, config_attribs, &config, 1, &num);

  EGLint ctx_attr[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

  EGLContext ctx = eglCreateContext(display, config, EGL_NO_CONTEXT, ctx_attr);

  if (ctx == EGL_NO_CONTEXT) {
    printf("eglCreateContext failed\n");
    return -1;
  }

  eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);

  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Vendor  : %s\n", glGetString(GL_VENDOR));
  printf("Version : %s\n\n", glGetString(GL_VERSION));

  /* 5️⃣ Load extension functions */

  auto eglCreateImageKHR_ptr =
      (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");

  auto eglDestroyImageKHR_ptr =
      (PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");

  auto glEGLImageTargetTexture2DOES_ptr =
      (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress(
          "glEGLImageTargetTexture2DOES");

  if (!eglCreateImageKHR_ptr || !eglDestroyImageKHR_ptr ||
      !glEGLImageTargetTexture2DOES_ptr) {

    printf("Required extensions missing\n");
    return -1;
  }

  /* 6️⃣ Create EGLImage from GBM BO */

  EGLImageKHR image =
      eglCreateImageKHR_ptr(display, EGL_NO_CONTEXT, EGL_NATIVE_PIXMAP_KHR,
                            (EGLClientBuffer)bo, NULL);

  if (image == EGL_NO_IMAGE_KHR) {
    printf("Failed to create EGLImage\n");
    return -1;
  }

  /* 7️⃣ Create GL texture from EGLImage */

  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  glEGLImageTargetTexture2DOES_ptr(GL_TEXTURE_2D, (GLeglImageOES)image);

  /* 8️⃣ Create FBO */

  GLuint fbo;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         tex, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    printf("FBO incomplete\n");
    return -1;
  }

  /* 9️⃣ Render */

  glViewport(0, 0, WIDTH, HEIGHT);
  glClearColor(0.1f, 0.6f, 0.9f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glFinish();

  printf("Rendered into GBM buffer successfully\n");

  /* 🔟 Export DMA-BUF */

  int dma_fd = gbm_bo_get_fd(bo);
  if (dma_fd >= 0) {
    printf("DMA-BUF FD: %d\n", dma_fd);
    close(dma_fd);
  }

  /* Cleanup */

  eglDestroyImageKHR_ptr(display, image);
  eglDestroyContext(display, ctx);
  eglTerminate(display);

  gbm_bo_destroy(bo);
  gbm_device_destroy(gbm);
  close(drm_fd);

  return 0;
}
