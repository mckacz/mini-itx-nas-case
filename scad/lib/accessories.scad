// accessory frame mount
module frame_mounts() {
    for(side = side_vectors) {
        move([
            -frame_offset[0],
            -frame_offset[1],
            -extra
        ])
        move([
            (1 - side[0]) * 1.2 * pillar_width + side[0] * (case_dim[0] - 1.2 * pillar_width),
            (1 - side[1]) * 1.2 * pillar_width + side[1] * (case_dim[1] - 1.2 * pillar_width),
            0
        ])
        cyl(d = hdd35_frame_mount_hole_diam, h = hdd35_frame_thick + 2 * extra, anchor = BOTTOM);
    }
}

// accessory frame
module frame(thick, width) {
    x_dim = frame_dim * sqrt(2) * 0.95;

    difference() {
        move((frame_dim - x_dim) / 2)
        zrot(45, cp = x_dim / 2)
        union() {
            move([
                0,
                (x_dim[1] - width) / 2,
                0
            ])
            cuboid(
                [
                    x_dim[0],
                    width,
                    thick,
                ],
                chamfer = width / 4,
                edges = "Z",
                anchor = FRONT + DOWN + LEFT
            );

            right((x_dim[0] - width) / 2)
            cuboid(
                [
                    width,
                    x_dim[1],
                    thick,
                ],
                chamfer = width/4,
                edges = "Z",
                anchor = FRONT + DOWN + LEFT
            );
        }

        frame_mounts();
    }
}

// 3.5" HDD frame
module hdd35_frame(color = []) {
    hdd_length = 147;
    hdd_width = 101.6;
    hdd_height = 17.8;

    x_hole_offset = 40;
    x_hole_distance = 76;
    y_hole_offset = 3.175;
    y_hole_distance = 94.5;
    hole_diam = 3.5;

    base_dim = [
        hdd_length,
        hdd_width + hdd35_frame_width,
        hdd35_frame_thick,
    ];

    frame_cutout = [
        base_dim[0] - 2 * eps,
        base_dim[1] - 2 * eps,
        hdd35_frame_thick + 2 * extra,
    ];

    accessory_color()
    union() {
        difference() {
            frame(hdd35_frame_thick, hdd35_frame_width);

            move([
                (frame_dim[0] - frame_cutout[0]) / 2 + hdd35_offset[0],
                (frame_dim[1] - frame_cutout[1]) / 2 + hdd35_offset[1],
                -extra,
            ])
            cuboid(frame_cutout, anchor = FRONT + DOWN + LEFT);
        }

        move([
            (frame_dim[0] - base_dim[0]) / 2 + hdd35_offset[0],
            (frame_dim[1] - base_dim[1]) / 2 + hdd35_offset[1],
            0,
        ])
        difference() {
             rect_tube(
                size = [base_dim[0], base_dim[1]],
                h = base_dim[2],
                wall = hdd35_frame_width,
                anchor = FRONT + DOWN + LEFT
            );

            for (side = side_vectors) {
                move([
                    hdd35_frame_width / 2 + x_hole_offset + side[0] * x_hole_distance - hdd35_frame_width/2,
                    hdd35_frame_width / 2 + y_hole_offset + side[1] * y_hole_distance,
                    -extra,
                ])
                union() {
                    cyl(d = hole_diam, h = hdd35_frame_thick + 2 * extra, anchor = BOTTOM);
                    cyl(
                        d = hdd35_frame_mount_hole_outer_diam,
                        h = hdd35_frame_mount_hole_depth + extra,
                        anchor = BOTTOM
                    );
                }
            }
        }
    }

    if ($preview) {
        accessory_color(0.5)
        move([
            (frame_dim[0] - base_dim[0]) / 2 + hdd35_offset[0],
            (frame_dim[1] - base_dim[1]) / 2 + hdd35_offset[1] + hdd35_frame_width / 2,
            hdd35_frame_thick,
        ])
        cuboid([hdd_length, hdd_width, hdd_height], anchor = FRONT + DOWN + LEFT);
    }
}
