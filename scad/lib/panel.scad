// generic side panel
module case_panel(dim, chamfer = 0, cutout = undef, solid = false) {
    panel_color()
    difference() {
        union() {
            // frame around the panel
            rect_tube(
                size = dim,
                h = panel_thick,
                wall = panel_belt,
                anchor = FRONT + DOWN + LEFT
            );

            // hex pattern
            hex_panel(
                [
                    dim[0],
                    dim[1],
                    panel_thick,
                ],
                strut = panel_hex_strut,
                spacing = panel_hex_spacing,
                anchor = FRONT + DOWN + LEFT
            );

            // cutout
            if (cutout) {
                move([cutout[2] - panel_belt, cutout[3] - panel_belt])
                rect_tube(
                    size = [cutout[0] + 2 * panel_belt, cutout[1] + 2 * panel_belt],
                    h = panel_thick,
                    wall = panel_belt,
                    anchor = FRONT + DOWN + LEFT
                );
            }

            // solid panel
            if (solid) {
                cuboid(
                    [
                        dim[0],
                        dim[1],
                        panel_thick - panel_solid_pattern_depth,
                    ],
                    anchor = FRONT + DOWN + LEFT
                );
            }
        }

        // cutouts around the panel
        move(dim / -2)
        down(extra / 2)
        rect_tube(
            size = dim*2,
            isize = dim,
            h = panel_thick + extra,
            wall = panel_belt,
            anchor = FRONT + DOWN + LEFT
        );

        // chamfer for corners
        for (side = side_vectors) {
            move([
                side[0] * dim[0],
                side[1] * dim[1],
                -panel_thick / 2
            ])
            chamfer_edge_mask(
                l = panel_thick * 2,
                chamfer = chamfer,
                anchor = BOTTOM
            );
        }

        // cutout
        if (cutout) {
            move([cutout[2], cutout[3], -extra / 2])
            cuboid(
                [
                    cutout[0],
                    cutout[1],
                    panel_thick + extra
                ],
                anchor = FRONT + DOWN + LEFT
            );

            move([-2 * panel_belt, -2 * panel_belt, -extra / 2])
            rect_tube(
                size=[
                    dim[0] + 4 * panel_belt,
                    dim[1] + 4 * panel_belt
                ],
                h = panel_thick + extra,
                wall = 2 * panel_belt,
                anchor = FRONT + DOWN + LEFT
            );
        }
    }
}

// panel with slot for ESP32-S3-Touch-LCD-1.28
module case_panel_with_lcd(dim, solid = false, cap = true) {
    $fn = 50;
    screen_diam = 36.5;
    collar_size = 5;
    collar_thick = 0.5;
    pocket_diam = 39;
    pocket_wall = 1.5;
    pocket_depth = 8.2;
    pocket_usb_cutout = 4;
    cable_mount_size = 5;
    cable_mount_thick = 2;
    cutout_diam = screen_diam + collar_size - eps;

    // base panel + cutout
    difference() {
        zflip(z = panel_thick / 2)
        case_panel(dim = dim, solid = solid);

        move([
            dim[0] / 2,
            dim[1] / 2,
            -extra / 2
        ])
        cyl(d = cutout_diam, h = panel_thick + extra, anchor = BOTTOM);
    }

    if ($preview) {
        lcd_color()
        move([
            dim[0] / 2,
            dim[1] / 2,
            -extra / 2
        ])
        cyl(d = screen_diam, h = collar_thick + extra, anchor = BOTTOM);
    }

    panel_color()
    move([
        dim[0] / 2,
        dim[1] / 2,
        0,
    ]) {
        // collar
        difference() {
            cyl(d = screen_diam + collar_size, h = collar_thick, anchor = BOTTOM);

            down(extra / 2)
            cyl(d = screen_diam, h = collar_thick + extra, anchor = BOTTOM);
        }

        // pocket
        if (cap) {
            move([0, 0, collar_thick - eps])
            difference() {
                cyl(d = pocket_diam + pocket_wall * 2, h = pocket_depth, anchor = BOTTOM);

                down(extra / 2)
                cyl(d = pocket_diam, h = pocket_depth + extra, anchor = BOTTOM);

                // coutout for installation
                move([-(pocket_diam + pocket_wall * 2) / 2 - extra / 2, -extra / 2, eps])
                cuboid(
                    [
                        pocket_diam + pocket_wall * 2 + extra,
                        (pocket_diam + pocket_wall * 2) / 2 + extra,
                        pocket_depth
                    ],
                    anchor = FRONT + DOWN + LEFT
                );

                // cutout for usb
                move([
                    -(pocket_diam + pocket_wall) / 2 - extra / 2,
                    pocket_usb_cutout - (pocket_diam + pocket_wall) - extra / 2,
                    eps
                ])
                cuboid(
                    [
                        pocket_diam + pocket_wall + extra,
                        (pocket_diam + pocket_wall) / 2 + extra,
                        pocket_depth
                    ],
                    anchor = FRONT + DOWN + LEFT
                );
            }

            move([
                0,
                0,
                pocket_depth+collar_thick,
            ])
            cyl(d = pocket_diam + pocket_wall*2, h = pocket_wall, anchor = BOTTOM);

            // cable mounting point
            up(
                (cable_mount_size + cable_mount_thick * 2) / 2
                    + pocket_depth + pocket_wall
                    - cable_mount_thick + collar_thick
            )
            xrot(90)
            difference() {
                rect_tube(
                    h = cable_mount_thick,
                    size = [cable_mount_size + cable_mount_thick*2, cable_mount_size + cable_mount_thick*2],
                    isize = [cable_mount_size, cable_mount_size]
                );

                move([
                    -(cable_mount_size + cable_mount_thick*2 + extra) / 2,
                    -cable_mount_thick-(cable_mount_size + cable_mount_thick*2) - extra,
                    -extra/2,
                ])
                cuboid(
                    [
                        cable_mount_size + cable_mount_thick*2 + extra,
                        cable_mount_size + cable_mount_thick*2,
                        cable_mount_thick + extra
                    ],
                    anchor = FRONT + DOWN + LEFT
                );
            }
        }
    }
}

// top panel
module case_panel_top() {
    move_preview(case_top_panel_offset)
    case_panel(case_top_panel_dim, chamfer = case_top_panel_chamfer, solid = in_list("top", panel_solids));
}

// bottom panel
module case_panel_bottom() {
    move_preview(case_bottom_panel_offset)
    rot(case_bottom_panel_rotation)
    case_panel(case_bottom_panel_dim, solid = in_list("bottom", panel_solids));
}

// left panel
module case_panel_left() {
    move_preview(case_left_panel_offset)
    rot_preview(case_left_panel_rotation)
    case_panel(case_side_panel_dim, solid = in_list("left", panel_solids));
}

// right panel
module case_panel_right() {
    move_preview(case_right_panel_offset)
    rot_preview(case_right_panel_rotation)
    case_panel(case_side_panel_dim, solid = in_list("right", panel_solids));
}

// back panel
module case_panel_back() {
    move_preview(case_back_panel_offset)
    rot_preview(case_back_panel_rotation)
    case_panel(dim = case_front_panel_dim, cutout = panel_back_cutout, solid = in_list("back", panel_solids));
}

// front panel
module case_panel_front() {
    move_preview(case_front_panel_offset)
    rot_preview(case_front_panel_rotation) {
        if (panel_front_with_lcd) {
            case_panel_with_lcd(case_front_panel_dim, solid = in_list("front", panel_solids));
        } else {
            case_panel(case_front_panel_dim, solid = in_list("right", panel_solids));
        }
    }
}
