function draw_primitives.update()
    engine.draw2d.circle({
        position = { x = 100, y = 100 },
        size = { x = 100, y = 100 },
        color = { x = 1, y = 0, z = 0, w = 1 },
        rotation = 0,
        filled = false,
    })

    engine.draw2d.rect({
        position = { x = 200, y = 200 },
        size = { x = 100, y = 100 },
        color = { x = 1, y = 0, z = 0, w = 1 },
        rotation = 0,
        filled = true,
    })
end
