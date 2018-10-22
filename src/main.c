#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 256
#define HEIGHT 144

const float RATIO = WIDTH / (float) HEIGHT;

struct GLpoint {
  GLint x;
  GLint y;
};

static void error_callback(int error, const char *description) {
  fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

static struct GLpoint setup_viewport(GLFWwindow *window) {
  int screen_width, screen_height;
  glfwGetFramebufferSize(window, &screen_width, &screen_height);

  float w_r = screen_width / (float) WIDTH;
  float h_r = screen_height / (float) HEIGHT;
  float r;

  if (w_r > h_r) {
    r = h_r;
  } else {
    r = w_r;
  }

  int width = WIDTH * (int) r;
  int height = HEIGHT * (int) r;

//  printf("[%f %f] [%d %d] [%d %d]\n", w_r, h_r, screen_width, screen_height, width, height);

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glViewport(0, 0, screen_width, screen_height);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0, screen_width, screen_height, 0, 1, -1);

  struct GLpoint point = {width, height};
  return point;
}

static void create_texture(const GLvoid *pixels) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

int main(void) {
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(WIDTH * 4, HEIGHT * 4, "Simple example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  GLubyte data[WIDTH * HEIGHT * 4];
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  for (size_t i = 0; i < WIDTH; i++) {
    for (size_t j = 0; j < HEIGHT; j++) {
      size_t index = j * WIDTH + i;
      size_t c = i * j;
      data[4 * index + 0] = 0xFF * (c % 2); // R
      data[4 * index + 1] = 0xFF * (c % 2); // G
      data[4 * index + 2] = 0xFF * (c % 2); // B
      data[4 * index + 3] = 0xFF;                   // A
    }
  }

  create_texture(&data[0]);

  while (!glfwWindowShouldClose(window)) {
    struct GLpoint sizes = setup_viewport(window);

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3i(0, 0, 0);
    glTexCoord2i(0, 1);
    glVertex3i(0, sizes.y, 0);
    glTexCoord2i(1, 1);
    glVertex3i(sizes.x, sizes.y, 0);
    glTexCoord2i(1, 0);
    glVertex3i(sizes.x, 0, 0);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteTextures(1, &texture_id);

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}