#ifndef UI_TRIP_DATA_H
#define UI_TRIP_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

  lv_updatable_screen_t tripDataScreen;

  static lv_obj_t *xte_label;
  static lv_obj_t *brg_label;
  static lv_obj_t *vmg_label;
  static lv_obj_t *rng_label;
  static lv_obj_t *ttg_at_vmg_label;

  /**
   * Trip data display 
   */
  static void lv_trip_data_display(lv_obj_t *parent) {

    lv_obj_t *main_label = lv_label_create(parent);
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, -105);
    lv_label_set_recolor(main_label, true);
    lv_label_set_text(main_label, "TRIP  #0080ff " LV_SYMBOL_GPS " #");

    xte_label = lv_label_create(parent);
    lv_obj_align(xte_label, LV_ALIGN_TOP_LEFT, 10, 40);
#if LV_FONT_MONTSERRAT_20
    lv_obj_set_style_text_font(xte_label, &lv_font_montserrat_20, 0);
#endif
    lv_label_set_text(xte_label, "XTE (nm):                 --");

    brg_label = lv_label_create(parent);
    lv_obj_align(brg_label, LV_ALIGN_TOP_LEFT, 10, 80);
#if LV_FONT_MONTSERRAT_20
    lv_obj_set_style_text_font(brg_label, &lv_font_montserrat_20, 0);
#endif
    lv_label_set_text(brg_label, "BRG (t deg):            --");

    vmg_label = lv_label_create(parent);
    lv_obj_align(vmg_label, LV_ALIGN_TOP_LEFT, 10, 120);
#if LV_FONT_MONTSERRAT_20
    lv_obj_set_style_text_font(vmg_label, &lv_font_montserrat_20, 0);
#endif
    lv_label_set_text(vmg_label, "VMG (kn):                 --");

    rng_label = lv_label_create(parent);
    lv_obj_align(rng_label, LV_ALIGN_TOP_LEFT, 10, 160);
#if LV_FONT_MONTSERRAT_20
    lv_obj_set_style_text_font(rng_label, &lv_font_montserrat_20, 0);
#endif
    lv_label_set_text(rng_label, "RNG (nm):                --");

    ttg_at_vmg_label = lv_label_create(parent);
    lv_obj_align(ttg_at_vmg_label, LV_ALIGN_TOP_LEFT, 10, 200);
#if LV_FONT_MONTSERRAT_20
    lv_obj_set_style_text_font(ttg_at_vmg_label, &lv_font_montserrat_20, 0);
#endif
    lv_label_set_text(ttg_at_vmg_label, "TTG@VMG:              --");
  }

  static void trip_data_update_cb() {
  }

  void init_tripDataScreen() {
    tripDataScreen.screen = lv_obj_create(NULL);  // Creates a Screen object
    tripDataScreen.init_cb = lv_trip_data_display;
    tripDataScreen.update_cb = trip_data_update_cb;
  }


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
