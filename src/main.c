#include <pebble.h>

Window *my_window;
TextLayer *text_layer;

void handle_init(void) {
	my_window = window_create();
	window_stack_push(my_window, true /* Animated */);
	Layer *window_layer = window_get_root_layer(my_window);
	GRect bounds = layer_get_frame(window_layer);
	
	text_layer = text_layer_create((GRect){ .origin = { 0, 30 }, .size = bounds.size });
	text_layer_set_text(text_layer, "1 DOGE = 0.00000048 BTC");
	text_layer_set_font(text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_COMIC_SANS_25)));
	layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

void handle_deinit(void) {
	  text_layer_destroy(text_layer);
	  window_destroy(my_window);
}

int main(void) {
	  handle_init();
	  app_event_loop();
	  handle_deinit();
}
