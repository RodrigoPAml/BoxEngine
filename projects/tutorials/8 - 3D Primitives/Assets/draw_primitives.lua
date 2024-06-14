-- example of drawing primitives in 3D space
function draw_primitives.update()
    engine.draw3d.circle({
        position = { x = 0, y = 0, z = 10 },
        size = { x = 5, y = 5, z = 5 },
        color = { x = 1, y = 0, z = 0, w = 1 },
        filled = true
    })

    engine.draw3d.circle({
        position = { x = 0, y = 0, z = -10 },
        size = { x = 5, y = 5, z = 5 },
        color = { x = 0, y = 1, z = 0, w = 1 },
        filled = false
    })

    engine.draw3d.rect({
        position = { x = 0, y = 10, z = 0 },
        size = { x = 5, y = 5, z = 5 },
        color = { x = 1, y = 1, z = 0, w = 1 },
        filled = true
    })

    engine.draw3d.rect({
        position = { x = 0, y = -10, z = 0 },
        size = { x = 5, y = 5, z = 5 },
        color = { x = 0, y = 0, z = 1, w = 1 },
        filled = false
    })

    engine.draw3d.line({
        position_start = { x = 0, y = -10, z = 0 },
        position_end = { x = 0, y = 10, z = 0 },
        color = { x = 1, y = 1, z = 1, w = 1 },
    })

    engine.draw3d.cube({
        position = { x = 10, y = 0, z = 0 },
        size = { x = 5, y = 5, z = 5 },
        color = { x = 0, y = 1, z = 1, w = 1 },
        filled = true
    })

    engine.draw3d.cube({
        position = { x = -10, y = 0, z = 0 },
        size = { x = 5, y = 5, z = 5 },
        color = { x = 1, y = 0, z = 1, w = 1 },
        filled = false
    })

    engine.draw3d.sphere({
        position = { x = 20, y = 0, z = 0 },
        size = { x = 5, y = 5, z = 5 },
        color = { x = 0.5, y = 1, z = 1, w = 1 },
        filled = true
    })

    engine.draw3d.sphere({
        position = { x = -20, y = 0, z = 0 },
        size = { x = 5, y = 5, z = 5 },
        color = { x = 1, y = 0.5, z = 1, w = 1 },
        filled = false
    })

    engine.draw3d.point({
        position = { x = -20, y = 0, z = 0 },
        color = { x = 1, y = 1, z = 1, w = 1 },
    })

    engine.draw3d.triangle({
        position1 = { x = 0, y = 20, z = 0 },
        position2 = { x = 20, y = 0, z = 0 },
        position3 = { x = 20, y = 20, z = 0 },
        color = { x = 0.5, y = 1, z = 0, w = 1 },
        filled = true
    })
end
