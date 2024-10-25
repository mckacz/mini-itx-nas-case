// motherboard
module mb() {
    move(case_mb_offset)
    union() {
        mb_color()
        difference() {
            // motherboard
            cuboid(mb_dim, anchor = FRONT + DOWN + LEFT);

            // mounting holes
            for (hole = mb_holes)
                move(hole)
                down(extra/2)
                cyl(d = mb_hole_d, h = mb_dim[2] + extra, anchor = BOTTOM);
        }

        // backplate
        mb_backplate_color()
        move(mb_bp_off)
        left(mb_flange_off)
        union() {
            cuboid(
                [
                    mb_bp_ko + mb_flange_off,
                    mb_bp_dim[0],
                    mb_bp_dim[1]
                ],
                anchor = FRONT + DOWN + LEFT
            );

            move([-mb_flange_off, -mb_flange, -mb_flange])
            cuboid(
                [
                    mb_flange,
                    mb_bp_dim[0] + mb_flange * 2,
                    mb_bp_dim[1]  + mb_flange * 2
                ],
                anchor = FRONT + DOWN + LEFT
            );
        }
    }
}

// motherboard backplate cutout
module mb_bp_cutout() {
    cuboid(mb_dim + [0, 0, mb_ko], anchor = FRONT + DOWN + LEFT);

    move(mb_bp_off)
    left(mb_flange_off)
    union() {
        move([mb_flange_wall-mb_flange_off, -mb_flange, -mb_flange])
        cuboid(
            [
                2 * mb_flange+mb_bp_ko + mb_flange_off,
                mb_bp_dim[0] + mb_flange * 2,
                mb_bp_dim[1] + mb_flange * 2
            ],
            anchor = FRONT + DOWN + LEFT
        );
    }
}
