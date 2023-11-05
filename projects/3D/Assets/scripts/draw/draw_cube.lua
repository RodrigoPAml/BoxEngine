function draw_cube.update()
    draw3d.cube({
        position = { x = 10, y = 0, z = 0 },
        size = { x = 10, y = 10, z = 10 },
        color = { x = 1, y = 0, z = 0, w = 1 },
        filled = true
    })
end