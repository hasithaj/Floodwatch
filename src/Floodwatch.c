#include <pebble.h>

define Num_menu_sections = 4;
define Num_menu_icons = 3;
define Num_first_menu_items = 3;
define Num_second_menu_items = 1;


static Window *main_window;
static ScrollLayer *s_scroll_layer;
static TextLayer *title_layer;
static TextLayer *region_layer;
static TextLayer *reports_layer;
static ContentIndicator *s_indicator;
static Layer *s_indicator_up_layer, *s_indicator_down_layer;

static char reports[] =("Flood Count\n\nProximity to Closest Flood\n\nBanjir Twitter\n\nContact Help\n\nConfigure Area\n\n");


static void main_window_load(Window *window) {

  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);


  title_layer = text_layer_create(
    GRect(0, 0,window_bounds.size.w, window_bounds.size.h));
  text_layer_set_text_alignment(title_layer, GTextAlignmentCenter);
  text_layer_set_text(title_layer, "FloodWatch");
  text_layer_set_text_color(title_layer, GColorBlack);
  text_layer_set_background_color(title_layer, GColorClear);
  text_layer_set_font(title_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  layer_add_child(window_layer, text_layer_get_layer(title_layer));

  region_layer = text_layer_create(
    GRect(0, 20,window_bounds.size.w, window_bounds.size.h));
  text_layer_set_text_alignment(region_layer, GTextAlignmentCenter);
  text_layer_set_text(region_layer, "Jakarta - Timur");
  text_layer_set_text_color(region_layer, GColorWhite);
  text_layer_set_background_color(region_layer, GColorClear);
  text_layer_set_font(region_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  layer_add_child(window_layer, text_layer_get_layer(region_layer));


  s_scroll_layer = scroll_layer_create(window_bounds);
 scroll_layer_set_click_config_onto_window(s_scroll_layer, window);
 scroll_layer_set_shadow_hidden(s_scroll_layer, true);
 layer_add_child(window_layer, scroll_layer_get_layer(s_scroll_layer));

 // Get the ContentIndicator from the ScrollLayer
 s_indicator = scroll_layer_get_content_indicator(s_scroll_layer);

 // Create two Layers to draw the arrows
 s_indicator_up_layer = layer_create(GRect(window_bounds.origin.x, window_bounds.origin.y,
                                     window_bounds.size.w, STATUS_BAR_LAYER_HEIGHT));
 s_indicator_down_layer = layer_create(GRect(0, window_bounds.size.h - STATUS_BAR_LAYER_HEIGHT,
                                       window_bounds.size.w, STATUS_BAR_LAYER_HEIGHT));
 layer_add_child(window_layer, s_indicator_up_layer);
 layer_add_child(window_layer, s_indicator_down_layer);

 // Configure the properties of each indicator
 const ContentIndicatorConfig up_config = (ContentIndicatorConfig) {
   .layer = s_indicator_up_layer,
   .times_out = false,
   .alignment = GAlignCenter,
   .colors = {
     .foreground = GColorBlack,
     .background = GColorLightGray
   }
 };
 content_indicator_configure_direction(s_indicator, ContentIndicatorDirectionUp,
                                       &up_config);

 const ContentIndicatorConfig down_config = (ContentIndicatorConfig) {
   .layer = s_indicator_down_layer,
   .times_out = false,
   .alignment = GAlignCenter,
   .colors = {
     .foreground = GColorBlack,
     .background = GColorLightGray
   }
 };
 content_indicator_configure_direction(s_indicator, ContentIndicatorDirectionDown,
                                       &down_config);

 reports_layer = text_layer_create(GRect(0, 50, window_bounds.size.w, 2000));
 text_layer_set_text(reports_layer, reports);
 text_layer_set_text_alignment(reports_layer, GTextAlignmentCenter);
 text_layer_set_font(reports_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
 text_layer_set_text_color(region_layer, GColorBlack);
 text_layer_set_background_color(region_layer, GColorClear);
 scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(reports_layer));

 GSize text_size = text_layer_get_content_size(reports_layer);
 layer_set_frame(text_layer_get_layer(reports_layer),
                 GRect(0, 50, window_bounds.size.w, text_size.h));
 scroll_layer_set_content_size(s_scroll_layer, text_size);
}


  /*reports_layer = text_layer_create(
    GRect(0, 60,window_bounds.size.w, window_bounds.size.h));
  text_layer_set_text_alignment(reports_layer, GTextAlignmentLeft);
  text_layer_set_text(reports_layer, "Current Flood Reports\n\nEmergency Contacts\n\nReport Flood\n\n");
  text_layer_set_text_color(reports_layer, GColorBlack);
  text_layer_set_background_color(reports_layer, GColorClear);
  text_layer_set_font(reports_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(reports_layer));
}*/


static void main_window_unload(Window *window) {
  text_layer_destroy(title_layer);
  text_layer_destroy(region_layer);
  text_layer_destroy(reports_layer);
  scroll_layer_destroy(s_scroll_layer);
  layer_destroy(s_indicator_up_layer);
  layer_destroy(s_indicator_down_layer);


}

static void init(void) {
  main_window = window_create();
  window_set_background_color(main_window, GColorPictonBlue);

  window_set_window_handlers(main_window,(WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload});

    window_stack_push(main_window, true);
}

static void deinit(void) {
  window_destroy(main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
