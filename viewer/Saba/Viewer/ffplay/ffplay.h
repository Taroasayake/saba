

#pragma once
#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif
	
	int ffplay_main1(int argc, char** argv);
	int ffplay_main2();
	int ffplay_main3(SDL_Window* wh, SDL_Renderer* rd, int winx, int winy);
	int changeVideoFrame();
	int ffplay_event(SDL_Event event);
	double ffplay_getpos();
	int64_t ffplay_getstreamsecond();
	void ffplay_seekpos(double pos);
	void ffplay_pause();
	int ffplay_getpause();
	int ffplay_isfullscreen();
	int ffplay_getmute();
	void ffplay_togglemute();
	void ffplay_toggle_full_screen();
	int changeVideo(const char* filename);
	void ffvideo_pollEvent();
	unsigned int GetVideoTexId();

	extern int frame_width;
	extern 	int frame_hight;
	extern double frame_rate_e ;
	extern int64_t strream_bitrate;
	
	extern char video_format[1024];

	extern const char* input_filename;
	extern int ffplay_seekbar;
	
#ifdef __cplusplus
}
#endif
