// Use only one configuration
//
// include <config/passive_mini_itx.scad>;
// include <config/passive_mini_itx_1x3.5_hdd.scad>;
// include <config/passive_mini_itx_2x3.5_hdd_fan.scad>;
include <config/passive_mini_itx_2x3.5_hdd_fan_lcd.scad>;
/////////////////////////////////////////////////////////

include <BOSL2/std.scad>;
include <BOSL2/walls.scad>;
include <lib/all.scad>;

// Do not render the whole case at once - it will not be printable.
// Render each part separately.
// To render a single part, prefix it with ! (exclamation mark) and render.

// skeleton
case_top();
case_top_caps(); // print 4 elements
case_pillars();  // print 4 elements
case_bottom();
case_legs();     // print 4 elements

// panels
case_panel_top();
case_panel_bottom();
case_panel_left();
case_panel_right();
case_panel_back();
case_panel_front();

// accessories
accessories() {
    hdd35_frame();
    hdd35_frame();
};

// motherboard
if ($preview) {
    mb();
}
