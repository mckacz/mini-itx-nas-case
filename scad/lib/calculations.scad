case_mb_offset_2d = [
    mb_flange_off + mb_flange,
    (case_dim[1] - mb_dim[1]) / 2,
    0
] + mb_offset;

case_mb_offset = [
    case_mb_offset_2d[0],
    case_mb_offset_2d[1],
    mb_mount_height,
];

case_top_offset = [
    0,
    0,
    z_belt + pillar_height
];

frame_dim = [
    case_dim[0] - 1.2*pillar_width - 2*extra,
    case_dim[1] - 1.2*pillar_width - 2*extra,
];

frame_offset = [
    (case_dim[0] - frame_dim[0]) / 2,
    (case_dim[1] - frame_dim[1]) / 2,
    z_belt + pillar_thick,
];

case_bottom_panel_dim = [
    case_dim[0] - 2*bp_hex_belt - 2*panel_extra,
    case_dim[1] - 2*bp_hex_belt - 2*panel_extra,
];

case_bottom_panel_rotation = [
    180,
    0,
    0,
];

case_bottom_panel_offset = [
    (case_dim[0] - case_bottom_panel_dim[0]) / 2,
    case_dim[1] - (case_dim[1] - case_bottom_panel_dim[1]) / 2,
    wall - panel_thick
];

case_top_panel_dim = [
    case_dim[0] - 2*tp_belt - 2*panel_extra,
    case_dim[1] - 2*tp_belt - 2*panel_extra,
];

case_top_panel_offset = [
    (case_dim[0] - case_top_panel_dim[0]) / 2,
    (case_dim[1] - case_top_panel_dim[1]) / 2,
    pillar_height + 2*z_belt - panel_thick - panel_slot_wall,
];

case_top_panel_chamfer = pillar_width;

case_front_panel_dim = [
    case_dim[1] + 2 * panel_slot_depth - 2 * pillar_width,
    pillar_height + 2 * panel_slot_depth
];

case_front_panel_rotation = [
    90,
    0,
    -90,
];

case_front_panel_offset = [
    case_dim[0] - panel_slot_wall - panel_thick,
    (case_dim[1] + case_front_panel_dim[0]) / 2,
    z_belt - panel_slot_wall,
];

case_back_panel_rotation = [
    90,
    0,
    -90,
];

case_back_panel_offset = [
    panel_slot_wall + panel_thick,
    case_dim[1] - (case_dim[1] - case_front_panel_dim[0]) / 2,
    z_belt - panel_slot_wall,
];

case_side_panel_dim = [
    case_dim[0] + 2 * panel_slot_depth - 2 * pillar_width,
    pillar_height + 2 * panel_slot_depth
];

case_left_panel_rotation = [
    90,
    0,
    0,
];

case_left_panel_offset = [
    (case_dim[0] - case_front_panel_dim[0]) / 2,
    panel_slot_wall + panel_thick,
    z_belt - panel_slot_wall,
];

case_right_panel_rotation = [
    90,
    0,
    180,
];

case_right_panel_offset = [
    case_side_panel_dim[0] + (case_dim[0] - case_front_panel_dim[0]) / 2,
    case_dim[1] - panel_slot_wall - panel_thick,
    z_belt - panel_slot_wall,
];

fan_hole_offset = (fan_size - fan_hole_distance) / 2;
fan_head_thick = fan_thick - 2 * fan_collar_thick - extra;
fan_mount_head_offset =  fan_mount_y_offset - fan_collar_thick - extra / 2;

fan_hole_offsets = [
    [
        fan_hole_offset,
        0,
        fan_hole_offset,
    ],
    [
            fan_hole_offset + fan_hole_distance,
        0,
        fan_hole_offset,
    ],
    [
        fan_hole_offset,
        0,
            fan_hole_offset + fan_hole_distance,
    ],
    [
            fan_hole_offset + fan_hole_distance,
        0,
            fan_hole_offset + fan_hole_distance,
    ],
];
