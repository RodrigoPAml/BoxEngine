-- test of triangle clipping for another project
function triangle_clip.start()
    local this = engine.current()

    this.triangle11 = { x = 100, y = 300, z = 80, w = 1 }
    this.triangle12 = { x = 100, y = 300, z = 300, w = 0 }
    this.triangle13 = { x = 300, y = 300, z = 300, w = 0.5 }
end

function triangle_clip.clip(v1, v2, min_z)
    local t = (min_z - v1.z) / (v2.z - v1.z)
    local new = {
        x = v1.x + t * (v2.x - v1.x),
        y = v1.y + t * (v2.y - v1.y),
        z = min_z,
    }

    new.w = v1.w + t * (v2.w - v1.w)

    return new
end

function triangle_clip.clip_triangle(min_z, v1, v2, v3)
    local vertices = { v1, v2, v3 }
    local inside = {}
    local outside = {}

    for _, v in ipairs(vertices) do
        if v.z > min_z then
            table.insert(inside, v)
        else
            table.insert(outside, v)
        end
    end

    if #inside == 3 then
        return { inside }
    elseif #inside == 0 then
        return {}
    elseif #inside == 1 then
        local new_vertices = {
            inside[1],
            triangle_clip.clip(inside[1], outside[1], min_z),
            triangle_clip.clip(inside[1], outside[2], min_z)
        }
        return { new_vertices }
    elseif #inside == 2 then
        local new_vertices = {
            inside[1],
            inside[2],
            triangle_clip.clip(inside[1], outside[1], min_z)
        }
        local new_vertices2 = {
            inside[2],
            triangle_clip.clip(inside[1], outside[1], min_z),
            triangle_clip.clip(inside[2], outside[1], min_z)
        }
        return { new_vertices, new_vertices2 }
    end
end

function triangle_clip.update()
    local this = engine.current()

    if engine.input.get_key(engine.enums.keyboard_key["1"]) == engine.enums.input_action.press then
        this.triangle11.x = engine.input.get_cam_mouse_pos().x
        this.triangle11.z = engine.input.get_cam_mouse_pos().y
    end

    if engine.input.get_key(engine.enums.keyboard_key["2"]) == engine.enums.input_action.press then
        this.triangle12.x = engine.input.get_cam_mouse_pos().x
        this.triangle12.z = engine.input.get_cam_mouse_pos().y
    end

    if engine.input.get_key(engine.enums.keyboard_key["3"]) == engine.enums.input_action.press then
        this.triangle13.x = engine.input.get_cam_mouse_pos().x
        this.triangle13.z = engine.input.get_cam_mouse_pos().y
    end

    engine.draw2d.line({
        position_start = { x = 0, y = this.min_z },
        position_end = { x = 1920, y = this.min_z },
        color = { x = 1, y = 0, z = 0, w = 1 },
    })

    if this.show_original then
        engine.draw2d.circle({
            position = { x = this.triangle11.x, y = this.triangle11.z },
            size = { x = 20, y = 20 },
            color = { x = this.triangle11.w, y = this.triangle11.w, z = this.triangle11.w, w = 1 },
        })

        engine.draw2d.circle({
            position = { x = this.triangle12.x, y = this.triangle12.z },
            size = { x = 20, y = 20 },
            color = { x = this.triangle12.w, y = this.triangle12.w, z = this.triangle12.w, w = 1 },
        })

        engine.draw2d.circle({
            position = { x = this.triangle13.x, y = this.triangle13.z },
            size = { x = 20, y = 20 },
            color = { x = this.triangle13.w, y = this.triangle13.w, z = this.triangle13.w, w = 1 },
        })

        engine.draw2d.triangle({
            position1 = { x = this.triangle11.x, y = this.triangle11.z },
            position2 = { x = this.triangle12.x, y = this.triangle12.z },
            position3 = { x = this.triangle13.x, y = this.triangle13.z },
            color = { x = 0, y = 1, z = 0, w = 1 },
            filled = false,
        })
    end

    local triangles = triangle_clip.clip_triangle(
        this.min_z,
        { x = this.triangle11.x, y = this.triangle11.y, z = this.triangle11.z, w = this.triangle11.w },
        { x = this.triangle12.x, y = this.triangle12.y, z = this.triangle12.z, w = this.triangle12.w },
        { x = this.triangle13.x, y = this.triangle13.y, z = this.triangle13.z, w = this.triangle13.w }
    )

    if this.show_new then
        for _, tri in ipairs(triangles) do
            engine.draw2d.circle({
                position = { x = tri[1].x, y = tri[1].z },
                size = { x = 20, y = 20 },
                color = { x = tri[1].w, y = tri[1].w, z = tri[1].w, w = 1 },
            })

            engine.draw2d.circle({
                position = { x = tri[2].x, y = tri[2].z },
                size = { x = 20, y = 20 },
                color = { x = tri[2].w, y = tri[2].w, z = tri[2].w, w = 1 },
            })

            engine.draw2d.circle({
                position = { x = tri[3].x, y = tri[3].z },
                size = { x = 20, y = 20 },
                color = { x = tri[3].w, y = tri[3].w, z = tri[3].w, w = 1 },
            })

            engine.draw2d.triangle({
                position1 = { x = tri[1].x, y = tri[1].z },
                position2 = { x = tri[2].x, y = tri[2].z },
                position3 = { x = tri[3].x, y = tri[3].z },
                color = { x = 1, y = 1, z = 1, w = 1 },
                filled = false,
            })
        end
    end
end
