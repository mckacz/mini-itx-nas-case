// ########
// # CASE #
// ########

// base dimensions of the case
case_dim = [210, 210];

// wall thickness
wall = 2.5;

// chamfer size
chamfer = 8;

// top/bottom belt size
z_belt = chamfer;

// top/bottom belt thickness
z_belt_thick = chamfer;

// bottom plate hex pattern - belt size around the pattern
bp_hex_belt = 32;

// bottom plate hex pattern - thickness of hexagonal bracing
bp_hex_strut = wall;

// bottom plate hex pattern -  center-to-center spacing of hex cells
bp_hex_spacing = chamfer;

// top/bottom plate socket diameter
bp_socket_diam = 8;

// top/bottom plate socket depth
bp_socket_depth = z_belt - 3;

// top plate belt
tp_belt = z_belt;

// socket cap diameter
socket_cap_diam = bp_socket_diam;

// socket cap thickness
socket_cap_thick = 2;

// ###########
// # PILLARS #
// ###########

// pillar shelves location (Z axis) for additional equipment
pillar_shelves = [];

// pillar width
pillar_width = chamfer * 2;

// pillar height
pillar_height = 42;

// pillar hole diameter (for insert)
pillar_hole_diam = 4.5;

// pillar shelf hole diameter (for insert)
pillar_shelf_hole_depth = 4;

// pillar shelf hole diameter (for insert)
pillar_shelf_hole_diam = 4.5;

// pillar thickness
pillar_thick = 5;

// pillar support thickness
pillar_support_thick = 8;

// pillar join diameter
pillar_joint_diam = 3;

// pillar joint extra diameter for female side
pillar_joint_extra = 0.25;

// pillar joint height
pillar_joint_height = 3;

// ##########
// # PANELS #
// ##########

// list of solid panels
panel_solids = [
//     "top",
//     "bottom",
//     "left",
//     "right",
//     "back",
//     "front",
];

// front panel with socket for ESP32-S3-Touch-LCD-1.28
panel_front_with_lcd = false;

// panel thickenss
panel_thick = 1;

// panel slot depth
panel_slot_depth = 3;

// panel slot wall
panel_slot_wall = 2;

// extra value added to panel slots
panel_extra = 0.5;

// panel hex pattern - belt size around the pattern
panel_belt = 2;

// panel hex pattern - thickness of hexagonal bracing
panel_hex_strut = panel_belt;

// panel plate hex pattern - center-to-center spacing of hex cells
panel_hex_spacing = 8;

// panel plate - pattern depth for solid panels
panel_solid_pattern_depth = 0.5;

// back panel cutout for motherboard
panel_back_cutout = [
    164,
    45,
    0,
    0,
];

// ##################
// # 3.5" HDD frame #
// ##################

// frame width
hdd35_frame_width = 20;

// frame thickness
hdd35_frame_thick = 5;

// hdd mount hole inner diameter
hdd35_frame_mount_hole_diam = 3.5;

// hdd mount hole outer diameter
hdd35_frame_mount_hole_outer_diam = 8;

// hdd mount hole depth
hdd35_frame_mount_hole_depth = 3;

// offset between hard disk and frame
hdd35_offset = [0, 0];

// #############
// # CASE LEGS #
// #############

// leg diameter
leg_diam = 20;

// leg height
leg_height = 5;

// leg slot offset from each side
leg_slot_offset = 15;

// ###########
// # BIG FAN #
// ###########

// enable fan mounts
fan = false;

// fan on left?
fan_on_left = false;

// fan size (assuming that fan is square)
fan_size = 120;

// fan thickness
fan_thick = 25;

// fan collar thickness
fan_collar_thick = 3.8;

// distance between screw holes
fan_hole_distance = 105.5;

// screw hole diameter
fan_hole_diam = 4.3;

// fan mount dimensions
fan_mount_size = [15, 10, 34];

// fan mount offset from case edge
fan_mount_y_offset = 8;

// ######################
// # MOTHERBOARD MOUNTS #
// ######################

// motherboard mount height
mb_mount_height = 5;

// inner diameter of motherboard mount (insert diameter)
mb_mount_inner_diam = 5.5;

// outer diameter of motherboard mount
mb_mount_outer_diam = 10;

// ###############
// # MOTHERBOARD #
// ###############

// motheboard dimensions
mb_dim = [170, 170, 1.6];

// motherboard offset relative to the center
mb_offset = [0, 0];

// motherboard keepout zone on Z axis
mb_ko = 5;

// motherboard mounting hole diameter
mb_hole_d = 4;

// motherboard mounting holes positions
mb_holes = [
    [10.16, 6.35, 0],   // ATX C
    [33.02, 163.83, 0], // ATX F
    [165.1, 6.35, 0],   // ATX H
    [165.1, 163.83, 0], // ATX J
];

// motherboard backplate dimensions
mb_bp_dim = [159, 45];

// motherboard backplate offset
mb_bp_off = [0, 13.87, 0.25];

// motherboard backplate keepout depth
mb_bp_ko = 25;

// motherboard backplate flange dimensions
mb_flange = 2.5;

// motherboard backplate flange offset from motherboard edge
mb_flange_off = 2.5;

// motherboard backplate flange wall
mb_flange_wall = 1;

// ###########
// # HELPERS #
// ###########

$fn = 20;
eps = 0.01;
extra = 1.0;

side_vectors = [
  [0, 0, 0],
  [1, 0, 90],
  [1, 1, 180],
  [0, 1, 270],
];
