-- example of drawing primitives in 2D space
function draw_primitives.update()
    engine.draw2d.circle({
        position = { x = 300, y = 300 },
        size = { x = 100, y = 100 },
        color = { x = 1, y = 0, z = 0, w = 1 },
        filled = true,
    })

    engine.draw2d.rect({
        position = { x = 600, y = 600 },
        size = { x = 100, y = 100 },
        color = { x = 0, y = 1, z = 0, w = 1 },
        filled = true,
    })

    engine.draw2d.line({
        position_start  = { x = 300, y = 300 },
        position_end  = { x = 600, y = 600 },
        color = { x = 0, y = 0, z = 1, w = 1 },
    })

    engine.draw2d.circle({
        position = { x = 900, y = 300 },
        size = { x = 100, y = 100 },
        color = { x = 1, y = 0, z = 0, w = 1 },
        filled = false,
    })

    engine.draw2d.rect({
        position = { x = 1000, y = 600 },
        size = { x = 100, y = 100 },
        color = { x = 0, y = 1, z = 0, w = 1 },
        rotation = 0,
        filled = false,
    })

    engine.draw2d.line({
        position_start  = { x = 900, y = 300 },
        position_end  = { x = 1000, y = 600 },
        color = { x = 1, y = 1, z = 0, w = 1 },
    })

    engine.draw2d.point({
        position   = { x = 700, y = 700 },
        color = { x = 1, y = 1, z = 0, w = 1 },
    })

    engine.draw2d.triangle({
        position1 = { x = 1500, y = 600 },
        position2 = { x = 1500, y = 900 },
        position3 = { x = 1800, y = 600 },
        color = { x = 0, y = 1, z = 1, w = 1 },
        filled = false,
    })

    engine.draw2d.triangle({
        position1 = { x = 1500, y = 600 },
        position2 = { x = 1500, y = 300 },
        position3 = { x = 1200, y = 600 },
        color = { x = 0, y = 1, z = 1, w = 1 },
        filled = true,
    })
end
