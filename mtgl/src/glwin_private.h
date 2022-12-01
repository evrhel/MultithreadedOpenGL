#pragma once

#include <Windows.h>

#include <mtgl/mtgl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GLWIN_EVENT_QUEUE_SIZE 32

	union event_data
	{
		struct
		{
			char _unused[1];
		} resize;

		struct
		{
			int old_mx, old_my;
		} mouse_move;

		struct
		{
			int key;
			enum glwin_key_state action;
			int mods;
		} key;

		struct
		{
			unsigned int code;
			int repeat_count;
			int mods;
		} char_;
	
		struct
		{
			int button;
			enum glwin_key_state action;
			int mods;
		} mouse_button;
	};


	struct event
	{
		enum glwin_event_type type;
		glwin *win;
		union event_data data;
	};

	union callback
	{
		void *ptr;
		glwin_resize_cb_fn on_resize;
		glwin_mouse_move_cb_fn on_mouse_move;
		glwin_key_cb_fn on_key;
		glwin_char_cb_fn on_char;
		glwin_mouse_button_cb_fn on_mouse_button;
	};

	struct glwin
	{
		HWND hwnd;
		HDC hdc;
		glctx *main;
		gllock *lock;
		int should_close;
		int was_resized;
		int width, height;
		int mx, my;
		int dmx, dmy;
		int focused;
		int mods;

		enum glwin_key_state aMouseButtonStates[8];
		enum glwin_key_state aKeyStates[0x100];
		DWORD dwKeyMods;

		SHORT wheel;

		RAWINPUTDEVICE rid[2];

		union callback callbacks[glwin_event_last];

		struct event events[GLWIN_EVENT_QUEUE_SIZE];
		int event_last;

		void *user_data;

		LARGE_INTEGER start;
		LARGE_INTEGER freq;
	};

#ifdef __cplusplus
}
#endif