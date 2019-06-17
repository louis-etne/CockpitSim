#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Anemometer.h"
#include "Colors.h"
#include "Vector2D.h"

#define FPS 60


enum KEYS { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };


int main()
{
	bool redraw{ true };
	bool doexit{ false };
	bool key[4] = { false, false, false, false }; // 0 => UP, 1 => DOWN, 2 => LEFT, 3 => RIGHT

	if (!al_init()) {
		std::cerr << "Failed to initialize Allegro" << std::endl;
		return -1;
	}


	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}


	if (!al_init_primitives_addon()) {
		std::cerr << "Failed to initialize Allegro primitives addon" << std::endl;
		return -1;
	}


	// DISPLAY
	ALLEGRO_DISPLAY* display = al_create_display(800, 600);

	if (!display) {
		std::cerr << "Failed to create display" << std::endl;
		al_destroy_display(display);
		return -1;
	}
	

	// TIMER
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);

	if (!timer) {
		std::cerr << "Failed to create timer" << std::endl;
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}

	// EVENTS
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	
	if (!event_queue) {
		std::cerr << "Failed to create event_queue" << std::endl;
		al_destroy_event_queue(event_queue);
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// DRAW
	Anemometer anemometer{ Vector2D{ 5, 5 } };
	double angle{ 0.0 };

	al_start_timer(timer);

	while (!doexit) {
		ALLEGRO_EVENT event;

		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP]) angle += 1;
			else if (key[KEY_DOWN]) angle -= 1;

			redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(COLOR_APP_BKG);

			anemometer.set_hand_angle(angle);
			anemometer.draw();

			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}