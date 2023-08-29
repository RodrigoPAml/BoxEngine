-- Do not change this script, api is declared here for vscode information be available

function to_string(table, tab)
	if tab == nil then 
		tab = ""
	end

	if(table == nil) then
		return "nil"
	end

	local ttype = type(table)

	if ttype ~= "table" then 
		if ttype == "string" then
			return table
		elseif ttype == "number" then 
			return tostring(table)
		elseif ttype == "function" then
			return "function"
		elseif ttype == "boolean" then
			if table == true then 
				return "true"
			else 
				return "false"
			end
		end
	end

	local content = "{\n"

	for k, v in pairs(table) do
		local value = "unknow"
		local t = type(v)

		if t == "string" then
			value = v
		elseif t == "number" then 
			value = tostring(v)
		elseif t == "function" then
			value = "function"
		elseif t == "boolean" then
			if v == true then 
				value =  "true"
			else 
				value = "false"
			end
		elseif t == "table" then 
			value = to_string(v, tab .. "  ")
		end

		content = content .. "  " .. tab .. k .. " : " .. value .. ",\n"
    end

    return content .. tab .. "}"
end

function log(value)
    if(value == nil) then
		__log__("nil")
		return
	end

	__log__(to_string(value))
end

function warning(value)
	if(value == nil) then
		__log__("nil")
		return
	end

	__warning__(to_string(value))
end

function error(value)
	if(value == nil) then
		__log__("nil")
		return
	end

	__error__(to_string(value))
end

go = {}
script = {}
cam2d = {}
cam3d = {}
command = {}
dir = {}
draw2d = {}
draw3d = {}
framebuffer = {}
img = {}
input = {}
shader = {}
texture = {}
time = {}
vertex = {}
utils = {}
window = {}
audio = {}

function go.current()
	return _go_.current()
end

function go.create(table)
	return _go_.create(table)
end

function go.destroy(id)
	return _go_.destroy(id)	
end

function go.get(id)
	return _go_.get(id)
end

function go.update(table)
	return _go_.update(table)
end

function go.change_father(goId, fatherId)
	return _go_.change_father(goId, fatherId)
end

function go.change_index(goId, displacement)
	return _go_.change_index(goId, displacement)
end

function script.get(goId, scriptName)
	return _script_.get(goId, scriptName)
end

function script.add(goId, scriptName)
	return _script_.add(goId, scriptName)
end

function script.remove(goId, scriptName)
	return _script_.remove(goId, scriptName)
end

function script.change_index(goId, scriptName, displacement)
	return _script_.change_index(goId, scriptName, displacement)
end

function cam2d.create(object)
	return _cam2d_.create(object)
end

function cam2d.destroy(id)
	return _cam2d_.destroy(id)
end

function cam2d.get(id)
	return _cam2d_.get(id)
end

function cam2d.get_matrix(id)
	return _cam2d_.get_matrix(id)
end

function cam2d.update(id, info)
	return _cam2d_.update(id, info)
end

function cam2d.set_current(id)
	return _cam2d_.set_current(id)
end

function cam3d.create(object)
	return _cam3d_.create(object)
end

function cam3d.destroy(id)
	return _cam3d_.destroy(id)
end

function cam3d.update(id, object)
	return _cam3d_.update(id, object)
end

function cam3d.get(id, object)
	return _cam3d_.get(id, object)
end

function cam3d.translate(id, object)
	return _cam3d_.translate(id, object)
end

function cam3d.translate_abs(id, object)
	return _cam3d_.translate_abs(id, object)
end

function cam3d.rotate(id, object)
	return _cam3d_.rotate(id, object)
end

function cam3d.get_view_matrix(id)
	return _cam3d_.get_view_matrix(id)
end

function cam3d.get_projection_matrix(id)
	return _cam3d_.get_projection_matrix(id)
end

function cam3d.set_current(id)
	return _cam3d_.set_current(id)
end

function draw2d.rect(object)
	return _draw2d_.rect(object)
end

function draw2d.circle(object)
	return _draw2d_.circle(object)
end

function draw2d.triangle(object)
	return _draw2d_.triangle(object)
end

function draw2d.line(object)
	return _draw2d_.line(object)
end

function draw2d.point(object)
	return _draw2d_.point(object)
end

function draw2d.texture(object)
	return _draw2d_.texture(object)
end

function draw3d.cube(object)
	return _draw3d_.cube(object)
end

function draw3d.sphere(object)
	return _draw3d_.sphere(object)
end

function draw3d.point(object)
	return _draw3d_.point(object)
end

function draw3d.line(object)
	return _draw3d_.line(object)
end

function draw3d.rect(object)
	return _draw3d_.rect(object)
end

function draw3d.triangle(object)
	return _draw3d_.triangle(object)
end

function draw3d.circle(object)
	return _draw3d_.circle(object)
end

function dir.read_file(file_name)
	return _dir_.read_file(file_name)
end

function dir.create_file(file_name, content)
	return _dir_.create_file(file_name, content)
end

function dir.create_folder(folder_name)
	return _dir_.create_folder(folder_name)
end

function dir.move(from, to)
	return _dir_.move(from, to)
end

function dir.copy(from, to)
	return _dir_.copy(from, to)
end

function dir.delete(path)
	return _dir_.delete(path)
end

function dir.is_file(path)
	return _dir_.is_file(path)
end

function dir.is_dir(path)
	return _dir_.is_dir(path)
end

function dir.exists(path)
	return _dir_.exists(path)
end

function dir.list_dir(path)
	return _dir_.list_dir(path)
end

function dir.reduce_path_by(path, n)
	return _dir_.reduce_path_by(path, n)
end

function dir.get_file_name_ext(path)
	return _dir_.get_file_name_ext(path)
end

function dir.get_path_or_file_name(path)
	return _dir_.get_path_or_file_name(path)
end

function dir.get_file_name_no_ext(path)
	return _dir_.get_file_name_no_ext(path)
end

function input.get_key(key)
	return _input_.get_key(key)
end

function input.get_mod(key)
	return _input_.get_mod(key)
end

function input.get_mouse_button(key)
	return _input_.get_mouse_button(key)
end

function img.open(path)
	return _img_.open(path)
end

function command.set_depth_testing_mode(mode)
	return _command_.set_depth_testing_mode(mode)
end

function command.set_culling_face_mode(mode)
	return _command_.set_culling_face_mode(mode)
end

function command.set_primitive_line_size(size)
	return _command_.set_primitive_line_size(size)
end

function command.set_primitive_point_size(size)
	return _command_.set_primitive_point_size(size)
end

function command.set_polygon_draw_mode(mode)
	return _command_.set_polygon_draw_mode(mode)
end

function shader.create(table)
	return _shader_.create(table)
end

function shader.destroy(id)
	return _shader_.destroy(id)
end

function shader.activate(id)
	return _shader_.activate(id)
end

function shader.set_bool(id, name, value)
	return _shader_.set_bool(id, name, value)
end

function shader.set_int(id, name, value)
	return _shader_.set_int(id, name, value)
end

function shader.set_float(id, name, value)
	return _shader_.set_float(id, name, value)
end

function shader.set_xy(id, name, x, y)
	return _shader_.set_xy(id, name, x, y)
end

function shader.set_xyz(id, name, x, y, z)
	return _shader_.set_xyz(id, name, x, y, z)
end

function shader.set_xyzw(id, name, x, y, z, w)
	return _shader_.set_xyzw(id, name, x, y, z, w)
end

function shader.set_vec2(id, name, value)
	return _shader_.set_vec2(id, name, value)
end

function shader.set_vec3(id, name, value)
	return _shader_.set_vec3(id, name, value)
end

function shader.set_vec4(id, name, value)
	return _shader_.set_vec4(id, name, value)
end

function shader.set_mat2(id, name, mat2)
	return _shader_.set_mat2(id, name, mat2)
end

function shader.set_mat3(id, name, mat3)
	return _shader_.set_mat3(id, name, mat3)
end

function shader.set_mat4(id, name, mat4)
	return _shader_.set_mat4(id, name, mat4)
end

function texture.create_empty(table)
	return _texture_.create_empty(table)
end

function texture.create(table)
	return _texture_.create(table)
end

function texture.destroy(id)
	return _texture_.destroy(id)
end

function texture.active(id, slot)
	return _texture_.active(id, slot)
end

function texture.disabletextureunit(slot)
	return _texture_.disabletextureunit(slot)
end

function framebuffer.create(table)
	return _framebuffer_.create(table)
end

function framebuffer.destroy(id)
	return _framebuffer_.destroy(id)
end

function framebuffer.active(id)
	return _framebuffer_.active(id)
end

function framebuffer.get_attachments_size(id)
	return _framebuffer_.get_attachments_size(id)
end

function framebuffer.get_attachment(id, index)
	return _framebuffer_.get_attachment(id, index)
end

function framebuffer.set_current(id, index)
	return _framebuffer_.set_current(id, index)
end

function framebuffer.clear(color)
	return _framebuffer_.clear(color)
end

function framebuffer.set_clear_modes(modes)
	return _framebuffer_.set_clear_modes(modes)
end

function framebuffer.set_viewport(viewport)
	return _framebuffer_.set_viewport(viewport)
end

function vertex.create(vertexData, indexData)
	return _vertex_.create(vertexData, indexData)
end

function vertex.destroy(id)
	return _vertex_.destroy(id)
end

function vertex.activate(id)
	return _vertex_.activate(id)
end

function vertex.draw(id, drawMode)
	return _vertex_.draw(id, drawMode)
end

function vertex.modify(id, modifyData)
	return _vertex_.modify(id, modifyData)
end

function generator.gen_2d_point(dataUse)
	return _generator_.gen_2d_point(dataUse)
end

function generator.gen_2d_line(dataUse, filled)
	return _generator_.gen_2d_line(dataUse, filled)
end

function generator.gen_2d_circle(dataUse, filled, segments)
	return _generator_.gen_2d_circle(dataUse, filled, segments)
end

function generator.gen_2d_triangle(dataUse, filled)
	return _generator_.gen_2d_triangle(dataUse, filled)
end

function generator.gen_3d_circle(dataUse, filled, segments)
	return _generator_.gen_3d_circle(dataUse, filled, segments)
end

function generator.gen_3d_cube(dataUse, filled)
	return _generator_.gen_3d_cube(dataUse, filled)
end

function generator.gen_3d_line(dataUse)
	return _generator_.gen_3d_line(dataUse)
end

function generator.gen_3d_point(dataUse)
	return _generator_.gen_3d_point(dataUse)
end

function generator.gen_3d_rect(dataUse, filled)
	return _generator_.gen_3d_rect(dataUse, filled)
end

function generator.gen_3d_sphere(dataUse, filled, segments)
	return _generator_.gen_3d_sphere(dataUse, filled, segments)
end

function generator.gen_3d_triangle(dataUse, filled)
	return _generator_.gen_3d_triangle(dataUse, filled)
end

function time.get_timestamp()
	return _time_.get_timestamp()
end

function time.get_datetime() 
	return _time_.get_datetime()
end

function utils.get_fps() 
	return _utils_.get_fps()
end

function utils.get_frametime() 
	return _utils_.get_frametime()
end

function window.get_window_size() 
	return _window_.get_window_size() 
end

function window.get_editor_window_size()
	return _window_.get_editor_window_size()
end

function window.get_window_limits() 
	return _window_.get_window_limits() 
end
