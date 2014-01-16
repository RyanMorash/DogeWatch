#include <pebble.h>

Window *my_window;
TextLayer *text_layer;

enum {
	value = 0
};

void out_sent_handler(DictionaryIterator *sent, void *context) {
   // outgoing message was delivered
 }


 void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
   // outgoing message failed
 }


 void in_received_handler(DictionaryIterator *received, void *context) {
   // incoming message received
	 
	 // Check for fields you expect to receive
          Tuple *text_tuple = dict_find(received, value);

          // Act on the found fields received
          if (text_tuple) {
            text_layer_set_text(text_layer, text_tuple->value->cstring);
          }
 }


 void in_dropped_handler(AppMessageResult reason, void *context) {
   // incoming message dropped
 }

void handle_init(void) {
	// Create window
	my_window = window_create();
	window_stack_push(my_window, true /* Animated */);
	Layer *window_layer = window_get_root_layer(my_window);
	GRect bounds = layer_get_frame(window_layer);
	// Initiate AppMessage
	app_message_register_inbox_received(in_received_handler);
    app_message_register_inbox_dropped(in_dropped_handler);
    app_message_register_outbox_sent(out_sent_handler);
    app_message_register_outbox_failed(out_failed_handler);
	const uint32_t inbound_size = 64;
    const uint32_t outbound_size = 64;
    app_message_open(inbound_size, outbound_size);
	//Create Initial Text
	text_layer = text_layer_create((GRect){ .origin = { 0, 30 }, .size = bounds.size });
	text_layer_set_text(text_layer, "1 DOGE = 0.000 BTC");
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
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
