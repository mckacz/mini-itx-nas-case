// case pillars
module case_pillars() {
    if ($preview) {
        case_color()
        for (side = side_vectors) {
            move([
                side[0] * case_dim[0],
                side[1] * case_dim[1],
                z_belt,
            ])
            zrot(side[2])
            case_pillar();
        }
    } else {
        rot([90, -45, 0])
        case_pillar();
    }
}

// single pillar
module case_pillar() {
    difference() {
        union() {
            case_pillar_base(pillar_height);

            for (shelf = pillar_shelves) {
                case_pillar_shelf(shelf);
            }
        }

        // slot for inserts
        move([pillar_width / 2, pillar_width / 2, 0])
        down(extra / 2)
        cyl(d = pillar_hole_diam, h = pillar_height + extra, anchor = BOTTOM);

        // bottom joint
        move([0, 0, -eps])
        case_pillar_joint_female();

        // top joint
        move([0, 0, pillar_height+eps])
        zflip()
        case_pillar_joint_female();

        // slots for side panels
        case_pillar_side_panel_slots(pillar_height);
    }
}

// base shape of pillar including chamfer and panel slots
module case_pillar_base(height) {
    difference() {
        cuboid(
            [pillar_width, pillar_width, height],
            anchor = FRONT + DOWN + LEFT,
            rounding = pillar_width / 2,
            edges = [BACK + RIGHT]
        );

        // chamfer
        down(extra / 2)
        chamfer_edge_mask(l = height + extra, chamfer = chamfer, anchor = BOTTOM);

         // slots for side panels
        case_pillar_side_panel_slots(height);
    }
}

// side panel slots for pillar
module case_pillar_side_panel_slots(height) {
    move([
        pillar_width - panel_slot_depth - panel_extra + eps,
        panel_slot_wall + panel_extra,
        -extra / 2,
    ])
    cuboid(
        [
            panel_slot_depth + panel_extra,
            panel_thick + panel_extra,
            height + extra,
        ],
        anchor = FRONT + DOWN + LEFT
    );

    move([
        panel_slot_wall + panel_extra,
        pillar_width - panel_slot_depth - panel_extra + eps,
        -extra / 2,
    ])
    cuboid(
        [
            panel_thick+panel_extra,
            panel_slot_depth+panel_extra,
            height + extra,
        ],
        anchor = FRONT + DOWN + LEFT
    );
}

// case pillar shelf
module case_pillar_shelf(shelf_z) {
    difference() {
        move([
            pillar_width / 4,
            pillar_width / 4,
            shelf_z,
        ])
        zrot(45)
        union() {
            prismoid(
                size1 = [pillar_width * 2, pillar_width],
                size2 = [pillar_width * 2, pillar_width],
                rounding = pillar_width / 2,
                h = pillar_thick,
                anchor = DOWN + LEFT
            );

            move([0, 0, -pillar_support_thick + eps])
                prismoid(
                    size1 = [pillar_width, pillar_width],
                    size2 = [pillar_width * 2, pillar_width],
                    shift = [pillar_width / 2, 0],
                    rounding = pillar_width / 2,
                    h = pillar_support_thick,
                    anchor = DOWN + LEFT
                );
        }

        move([
            1.2 * pillar_width,
            1.2 * pillar_width,
            shelf_z + eps
        ])
        cyl(
            d = pillar_shelf_hole_diam,
            h = pillar_shelf_hole_depth + extra,
            anchor = DOWN
        );
    }
}

// pillar joint - male side
module case_pillar_joint_male() {
    move([pillar_width / 5 * 3, pillar_width / 5, 0])
    cyl(d = pillar_joint_diam, h = pillar_joint_height, anchor = BOTTOM);

    move([pillar_width / 5, pillar_width / 5 * 3, 0])
    cyl(d = pillar_joint_diam, h = pillar_joint_height, anchor = BOTTOM);
}

// pillar joint - female side
module case_pillar_joint_female() {
    move([pillar_width / 5 * 3, pillar_width / 5, 0])
    cyl(d = pillar_joint_diam + pillar_joint_extra, h = pillar_joint_height + extra, anchor = BOTTOM);

    move([pillar_width / 5, pillar_width / 5 * 3, 0])
    cyl(d = pillar_joint_diam + pillar_joint_extra, h = pillar_joint_height + extra, anchor = BOTTOM);
}

// pillar joint - socket
module case_pillar_joint_socket(insert_height, socket_diam, socket_height) {
    move([pillar_width / 2, pillar_width / 2, -eps])
    union() {
        // socket
        cyl(d = socket_diam, h = socket_height, anchor = BOTTOM);

        // slot for inserts
        cyl(d = pillar_hole_diam, h = pillar_height + extra, anchor = BOTTOM);
    }
}
