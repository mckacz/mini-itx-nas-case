// arrange accessories
module accessories() {
    if ($children > len(pillar_shelves)) {
        echo("======================================> Selected more accessories than shelves");
        echo("======================================> Update 'pillar_shelves' in your config");
    }

    if (len(pillar_shelves) > 0) {
        for (i = [0:len(pillar_shelves) - 1]) {
            if (i >= $children) {
                echo("======================================> No accessory selected for shelf", i);
                echo("======================================> Add it to the 'accessory' section in the main file");
            } else {
                move(frame_offset + [0, 0, pillar_shelves[i]])
                children(i);
            }
        }
    }
}

// apply zflip in render mode only
module zflip_render(z) {
    if ($preview) {
        children();
    } else {
        zflip(z = z)
        children();
    }
}

// apply move in preview mode only
module move_preview(p) {
    if ($preview) {
        move(p)
        children();
    } else {
        children();
    }
}

// apply rot in preview mode only
module rot_preview(v) {
    if ($preview) {
        rot(v)
        children();
    } else {
        children();
    }
}
