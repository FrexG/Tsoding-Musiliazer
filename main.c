#include <dlfcn.h>
#include "musiliazer.h"
#include "plug.h"

const char *libplug_filename = "libplug.so";
void *libplug = NULL;
plug_init_t plug_init = NULL;
plug_update_frame_t plug_update = NULL;
Plug plug = {};

int main(int argc, char **argv)
{
  if (argc == 0)
  {
    fprintf(stderr, "ERROR: no input file provided\n");
    return 1;
  }

  if (argc > 2)
  {
    fprintf(stderr, "ERROR: provide only one input file\n");
    return 1;
  }
  const char *music_file_path = argv[1];

  InitWindow(W, H, "Musializer");
  InitAudioDevice();
  SetTargetFPS(30);

  if (!reload_libplug())
    return 1;

  plug_init(&plug, music_file_path);

  while (!WindowShouldClose())
  {
    // main game loop
    // reload pluging
    if (IsKeyPressed(KEY_R))
    {
      if (!reload_libplug())
        return 1;
    }
    plug_update(&plug);
  }

  return 0;
}

bool reload_libplug(void)
{
  if (libplug != NULL)
  {
    if (dlclose(libplug) != 0)
    {
      fprintf(stderr, "ERROR: Failed to close previously loaded library: %s\n", dlerror());
      return false;
    }
    libplug = NULL;
    plug_init = NULL;
    plug_update = NULL;
  }
  libplug = dlopen(libplug_filename, RTLD_NOW);

  if (libplug == NULL)
  {
    fprintf(stderr, "ERROR: could not load so %s:%s\n", libplug_filename, dlerror());
    return false;
  }

  plug_init = dlsym(libplug, "plug_init");
  if (plug_init == NULL)
  {
    fprintf(stderr, "ERROR: could not find symbol in %s:%s\n", libplug_filename, dlerror());
    return false;
  }

  plug_update = dlsym(libplug, "plug_update_frame");
  if (plug_update == NULL)
  {
    fprintf(stderr, "ERROR: could not find symbol in %s:%s\n", libplug_filename, dlerror());
    return false;
  }

  printf("Address of plug_init pointer %p\n", plug_init);
  printf("Address of plug_update pointer %p\n", plug_update);
  return true;
}