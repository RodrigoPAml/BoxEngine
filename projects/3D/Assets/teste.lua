teste = {}

function teste.start()
    local path = dir.get_assets_path() .. '/models/untitled.obj'

    local id = importer.open(path)

    log(importer.get_obj_info(id))
    log(importer.get_meshes(id))
end

function teste.update()
end

function teste.destroy()
end
