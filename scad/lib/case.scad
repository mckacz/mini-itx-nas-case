// case bottom plate
module case_bottom() {
    case_color()
    difference() {
        union() {
            case_bottom_base_plate();
            case_bottom_belt();
            case_bottom_pillar_base();
            case_mb_mounts();
        }

        // sockets for pillar joints
        case_bottom_pillar_sockets();

        // panel cutout
        case_bottom_panel_cutout();

        // motherboard cutout
        move(case_mb_offset)
        mb_bp_cutout();
    }

    if (fan) {
        translate([0, 0, wall-eps])
        fan_mounts();
    }
}

// base plate of case bottom
module case_bottom_base_plate() {
    difference() {
        union() {
            // base plate
            rect_tube(
                size = case_dim,
                h = wall,
                wall = bp_hex_belt,
                anchor = FRONT + DOWN + LEFT
            );

            // panel cutout
            rect_tube(
                size = case_dim,
                h = wall - panel_slot_wall,
                wall = bp_hex_belt + 2 * panel_slot_depth + 2 * panel_extra,
                anchor = FRONT + DOWN + LEFT
            );
        }

        // chamfers
        for (side = side_vectors) {
            move([
                side[0] * case_dim[0],
                side[1] * case_dim[1],
                -wall / 2
            ])
            chamfer_edge_mask(
                l = wall * 2,
                chamfer = chamfer,
                anchor = BOTTOM
            );
        }
    }
}

// bases for pillars
module case_bottom_pillar_base() {
    move([0, 0, -eps])
    for (side = side_vectors) {
        move([
            side[0] * case_dim[0],
            side[1] * case_dim[1],
            0,
        ])
        zrot(side[2])
        union() {
            case_pillar_base(height = z_belt);

            move([0, 0, z_belt - eps])
            case_pillar_joint_male();
        }
    }
}

// sockets for pillars
module case_bottom_pillar_sockets() {
    down(eps)
    for (side = side_vectors) {
        move([
            side[0] * case_dim[0],
            side[1] * case_dim[1],
            0,
        ])
        zrot(side[2])
        case_pillar_joint_socket(z_belt, bp_socket_diam, bp_socket_depth);
    }
}

// belt of case bottom
module case_bottom_belt() {
    down(eps)
    difference() {
        // base belt
        rect_tube(
            size = case_dim,
            h = z_belt,
            wall = z_belt_thick,
            anchor = FRONT + DOWN + LEFT,
            chamfer = chamfer
        );

        // cutouts for panels
        cutout_size = case_dim - [
            2 * panel_slot_wall + 2 * panel_extra,
            2 * panel_slot_wall + 2 * panel_extra
        ];

        move([
            panel_slot_wall + panel_extra,
            panel_slot_wall + panel_extra,
            z_belt - panel_slot_depth + eps,
        ])
        rect_tube(
            size = cutout_size,
            h = panel_slot_depth + panel_extra,
            wall = panel_thick + panel_extra,
            anchor = FRONT + DOWN + LEFT,
            chamfer = chamfer
        );
    }
}

// cutout for bottom panel
module case_bottom_panel_cutout() {
    cutout_dim = [
        case_dim[0] -2*bp_hex_belt,
        case_dim[1] -2*bp_hex_belt,
        z_belt
    ];

    move([
        (case_dim[0] - cutout_dim[0]) / 2 + mb_offset[0],
        (case_dim[1] - cutout_dim[1]) / 2 + mb_offset[0],
        panel_slot_wall,
    ])
    cuboid(cutout_dim, anchor=BOTTOM+LEFT+FRONT);
}

// motherboard mounts
module case_mb_mounts() {
    move(case_mb_offset_2d + [0, 0, wall - eps])
        for (hole = mb_holes) {
            move(hole)
            case_mb_mount();
        }
}

// single motherboard mount
module case_mb_mount() {
    difference() {
        cyl(h = mb_mount_height, d = mb_mount_outer_diam, anchor = BOTTOM);

        down(extra/2)
        cyl(h = mb_mount_height + extra, d = mb_mount_inner_diam, anchor = BOTTOM);
    }

    up(mb_mount_height / 2)
    zflip()
    rounding_hole_mask(d = mb_mount_outer_diam - eps, rounding = mb_mount_height / 2);
}

// single case leg
module case_leg() {
    cyl(d = leg_diam, h = leg_height, anchor = BOTTOM);
}

// case legs
module case_legs() {
    if ($preview) {
        case_color()
        for (side = side_vectors) {
            offset = leg_slot_offset + leg_diam / 2;

            move([
                side[0] * case_dim[0] - (2 * side[0] - 1) * offset,
                side[1] * case_dim[1] - (2 * side[1] - 1) * offset,
                -eps,
            ])
            zflip()
            case_leg();
        }
    } else {
        case_leg();
    }
}

// case top plate
module case_top_base() {
    difference() {
        union() {
            case_top_plate();
            case_top_belt();

            up(z_belt)
            zflip()
            case_bottom_pillar_base();
        }

        case_top_pillar_sockets();
    }
}

// case top plate
module case_top() {
    case_color()
    move_preview(case_top_offset)
    zflip_render(z_belt / 2)
    case_top_base();
}

// base plate of case top
module case_top_plate() {
    up(z_belt_thick - wall)
    difference() {
        union() {
            // base plate
            rect_tube(
                size = case_dim,
                h = wall,
                wall = tp_belt,
                anchor = FRONT + DOWN + LEFT
            );

            // cutouts for panels
            up(panel_slot_wall)
            rect_tube(
                size = case_dim,
                h = wall - panel_slot_wall,
                wall = tp_belt + 2 * panel_slot_depth + 2 * panel_extra,
                anchor = FRONT + DOWN + LEFT
            );
        }

        for (side = side_vectors) {
            move([
                side[0] * case_dim[0],
                side[1] * case_dim[1],
                -wall / 2
            ])
            chamfer_edge_mask(
                l = wall * 2,
                chamfer = chamfer,
                anchor = BOTTOM
            );
        }
    }
}

// belt of case top
module case_top_belt() {
    difference() {
        // base
        rect_tube(
            size = case_dim,
            h = z_belt,
            wall = z_belt_thick,
            anchor = FRONT + DOWN + LEFT,
            chamfer = chamfer
        );

        // panel cutouts
        cutout_size = case_dim - [
            2 * panel_slot_wall + 2 * panel_extra,
            2 * panel_slot_wall + 2 * panel_extra
        ];

        move([
            panel_slot_wall + panel_extra,
            panel_slot_wall + panel_extra,
            -eps,
        ])
        rect_tube(
            size = cutout_size,
            h = panel_slot_depth + panel_extra,
            wall = panel_thick + panel_extra,
            anchor = FRONT + DOWN + LEFT,
            chamfer = chamfer
        );

        // chamfer
        for (side = side_vectors) {
            move([
                side[0] * case_dim[0],
                side[1] * case_dim[1],
                -extra
            ])
            chamfer_edge_mask(
                l = z_belt + 2 * extra,
                chamfer = chamfer,
                anchor = BOTTOM
            );
        }
    }
}

// sockets for pillars on top
module case_top_pillar_sockets() {
    up(z_belt + eps)
        for (side = side_vectors) {
            move([
                side[0] * case_dim[0],
                side[1] * case_dim[1],
                0,
            ])
            zrot(side[2])
            zflip()
            case_pillar_joint_socket(z_belt, bp_socket_diam, bp_socket_depth);
        }
}

// single cap for screw sockets
module case_top_cap() {
    cyl(d = socket_cap_diam, h = socket_cap_thick, anchor = BOTTOM);
}

// caps for screw sockets
module case_top_caps() {
    if ($preview) {
        case_color()
        move(case_top_offset)
        up(z_belt + eps)
            for (side = side_vectors) {
                move([
                    side[0] * case_dim[0],
                    side[1] * case_dim[1],
                    0,
                ])
                zrot(side[2])
                zflip()
                move([pillar_width / 2, pillar_width / 2, -eps])
                case_top_cap();
            }
    } else {
        case_top_cap();
    }
}
