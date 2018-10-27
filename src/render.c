#include <jvcr_ecm_01/machine.h>
#include <jvcr_ecm_01/display.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <jvcr_ecm_01/ram.h>
#include <time.h>
#include <math.h>

static GLFWwindow *window;

struct GLpoint {
  GLint x;
  GLint y;
};

static struct GLpoint setup_viewport(GLFWwindow *window) {
  int screen_width, screen_height;
  glfwGetFramebufferSize(window, &screen_width, &screen_height);

  float w_r = screen_width / (float) DISPLAY_WIDTH;
  float h_r = screen_height / (float) DISPLAY_HEIGHT;
  float r;

  if (w_r > h_r) {
    r = h_r;
  } else {
    r = w_r;
  }

  int width = DISPLAY_WIDTH * (int) r;
  int height = DISPLAY_HEIGHT * (int) r;

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

static void create_texture(JvcrDisplay *display) {
  glGenTextures(1, &display->texture_id);
  glBindTexture(GL_TEXTURE_2D, display->texture_id);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA8,
               DISPLAY_WIDTH,
               DISPLAY_HEIGHT,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               display->texture);
}

static void update_texture(JvcrDisplay *display) {
  glBindTexture(GL_TEXTURE_2D, display->texture_id);
  glTexSubImage2D(GL_TEXTURE_2D,
                  0,
                  0,
                  0,
                  DISPLAY_WIDTH,
                  DISPLAY_HEIGHT,
                  GL_RGBA,
                  GL_UNSIGNED_BYTE,
                  display->texture);
}

static void error_callback(int error, const char *description) {
  fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

static void setup_windows(JvcrDisplay *display) {
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(DISPLAY_WIDTH * 4,
                            DISPLAY_HEIGHT * 4,
                            "JVCR-ECM-01",
                            NULL,
                            NULL); // TODO: set actual screen size in a config
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
}

static void fill_texture(Jvcr *machine) {
  for (u32 x = 0; x < DISPLAY_WIDTH; x++) {
    for (u32 y = 0; y < DISPLAY_HEIGHT; y++) {
      byte color_index = pget(machine, x, y);
      RGBA color = get_rgba(machine, color_index);

      size_t index = y * DISPLAY_WIDTH + x;
      byte *tex = machine->display->texture;
      tex[4 * index + 0] = color.red;
      tex[4 * index + 1] = color.green;
      tex[4 * index + 2] = color.blue;
      tex[4 * index + 3] = color.alpha;
    }
  }
}

void rendering_init(Jvcr *machine) {
  setup_windows(machine->display);
  fill_texture(machine);
  create_texture(machine->display);
}

void rendering_stop(Jvcr *machine) {
  glDeleteTextures(1, &machine->display->texture_id);

  glfwDestroyWindow(window);
  glfwTerminate();
};

void Draw(Jvcr *machine) {
  struct GLpoint sizes = setup_viewport(window);

  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, machine->display->texture_id);

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

static double get_current_time() {
  struct timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  time_t s = spec.tv_sec;
  double ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
  if (ms > 999) {
    s++;
    ms = 0;
  }
  return s + ms/1000.0;
}

void RunLoop(Jvcr *machine) {
  double start_time = get_current_time();
  double prev_time = get_current_time();
  while (!glfwWindowShouldClose(window)) {
    double end_time = get_current_time();
    double delta_time = end_time - prev_time;
    prev_time = get_current_time();
    machine->time = end_time - start_time;

    // TODO: somehow separate this calls to fit the logic and documentation
    if (machine->onDraw != NULL) machine->onDraw(machine, delta_time);
    if (machine->onUpdate != NULL) machine->onUpdate(machine, delta_time);
    if (machine->onUpdate60 != NULL) machine->onUpdate60(machine, delta_time);

    fill_texture(machine);
    update_texture(machine->display);
    Draw(machine);
  }
}