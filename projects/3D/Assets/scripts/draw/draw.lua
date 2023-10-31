function draw.start()
    local this =  current()

    this.x = 10
    this.y = 0
    this.z = 0
end

function draw.update()
    local this = current()
   
    draw3d.cube({
        position = { x = this.x, y = this.y, z = this.z },
        size = { x = 10, y = 10, z = 10 },
        color = { x = 1, y = 0, z = 0, w = 1 },
        filled = true
    })
end