#include "plug.h"

void audio_callback(void *bufferData, unsigned int frames)
{
  if (frames < N)
    return;
  if (frames > N)
  {
    frames = N;
  }
  // memcpy(global_frames, bufferData, frames * sizeof(Frame) * 2);
  Frame *frames_data = bufferData;
  for (size_t i = 0; i < frames; ++i)
  {
    in[i] = frames_data[i].left;
  }
}
void plug_init(Plug *plug, const char *music_file_path)
{
  plug->music = LoadMusicStream(music_file_path);

  SetMusicVolume(plug->music, 0.2f);
  PlayMusicStream(plug->music);
  AttachAudioStreamProcessor(plug->music.stream, audio_callback);
}

void plug_update_frame(Plug *plug)
{

  int W = GetRenderWidth();
  int H = GetRenderHeight();

  // Update
  UpdateMusicStream(plug->music);

  // play/pause
  if (IsKeyPressed(KEY_SPACE))
  {
    if (IsMusicStreamPlaying(plug->music))
      PauseMusicStream(plug->music);
    else
      PlayMusicStream(plug->music);
  }

  BeginDrawing();
  // Draw
  ClearBackground(GRAY);
  // draw bars
  // fft
  fft(in, out, 1, N, PI);
  printf("Called\n");
  printf("Width %d\n",W);
  printf("N %d\n",N);

  float cell_width = (float)W / N;
  for (size_t i = 0; i < N; ++i)
  {
    // float ratio = global_frames[i].left;
    float ratio = amplitude(out[i]);

    DrawRectangle(i * cell_width, H / 2 - H / 2 * ratio, cell_width,
                  H / 2 * ratio, RED);
    printf("i = %zu\n",i);
  }
  printf("End loop\n");
  EndDrawing();
  printf("End drawing\n");
}