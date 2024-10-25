// fan mounts
module fan_mounts(color) {
    zrot(
        fan_on_left ? 180 : 0,
        cp = [
            case_dim[0] / 2,
            case_dim[1] / 2,
            0
        ]
    )
    right((case_dim[0] - fan_size) / 2)
    union() {
        // mounts itself
        case_color()
        union() {
            back(fan_mount_y_offset)
            fan_mount();

            right(fan_hole_distance + fan_mount_size[0])
            back(fan_mount_y_offset)
            xflip()
            fan_mount();
        }

        // fan for preview
        if ($preview) {
            move([
                fan_mount_size[0] - fan_mount_size[0]/2 - fan_hole_offset,
                fan_mount_head_offset,
                fan_mount_size[2] - fan_mount_size[0]/2 - fan_hole_offset,
            ])
            fan_color()
            difference() {
                union() {
                    difference() {
                        cuboid(
                            [fan_size, fan_thick, fan_size],
                            rounding = 3,
                            edges = "X",
                            anchor = FRONT + DOWN + LEFT
                        );

                        move([
                            -extra / 2,
                            fan_collar_thick,
                            -extra / 2,
                        ])
                        cuboid(
                            [
                                fan_size + extra,
                                fan_thick - 2 * fan_collar_thick,
                                fan_size + extra
                            ],
                            rounding = 3,
                            edges = "X",
                            anchor = FRONT + DOWN + LEFT
                        );
                    }

                    move([
                        fan_size / 2,
                        0,
                        fan_size / 2,
                    ])
                    xrot(-90)
                    cyl(d = fan_size, h = fan_thick, anchor = BOTTOM);
                }

                union() {
                    for (hole = fan_hole_offsets) {
                        move(hole)
                        fwd(extra / 2)
                        xrot(-90)
                        cyl(d = fan_hole_diam, h = fan_thick + extra, anchor = BOTTOM);
                    }
                }
            }
        }
    }
}

// single fan mount
module fan_mount() {
    difference() {
        union() {
            // base
            cuboid(
                fan_mount_size,
                chamfer = fan_mount_size[0] / 3 * 2,
                edges = "Y",
                except = [BOTTOM, LEFT],
                anchor = FRONT + DOWN + LEFT
            );

            // head
            move([
                0,
                fan_mount_head_offset - (fan_head_thick - fan_mount_size[1]) / 2,
                fan_mount_size[2] - fan_mount_size[0],
            ])
            cuboid(
                [fan_mount_size[0], fan_head_thick, fan_mount_size[0]],
                chamfer = fan_mount_size[0] / 3 * 2,
                edges = "Y",
                except = [BOTTOM, LEFT],
                anchor = FRONT + DOWN + LEFT
            );

            // round edge between base and head
            move([
                fan_mount_size[0] / 2,
                fan_mount_size[1],
                fan_mount_size[2] - fan_mount_size[0] + eps,
            ])
            yrot(90)
            rounding_edge_mask(l = fan_mount_size[0], r = fan_head_thick - fan_mount_size[1]);
        }

        // screw hole
        move([
            (fan_mount_size[0]) / 2,
            fan_mount_size[1] / 2 + fan_thick / 2,
            fan_mount_size[2] - fan_mount_size[0] / 2,
        ])
        xrot(90)
        cyl(d = fan_hole_diam, h = fan_thick + extra, anchor = BOTTOM);
    }

}
