-- Do not change this script, api is declared here for vscode information be available

engine = {}

function engine.to_string(table, tab)
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
			value = engine.to_string(v, tab .. "  ")
		end

		content = content .. "  " .. tab .. k .. " : " .. value .. ",\n"
    end

    return content .. tab .. "}"
end

function engine.log(value)
    if(value == nil) then
		__log__("nil")
		return
	end

	__log__(engine.to_string(value))
end

function engine.warning(value)
	if(value == nil) then
		__log__("nil")
		return
	end

	__warning__(engine.to_string(value))
end

function engine.error(value)
	if(value == nil) then
		__log__("nil")
		return
	end

	__error__(engine.to_string(value))
end

function engine.data(go, script)
	if(go == nil or script == nil) then
		return nil
	end

	if(_G[script] ~= nil) then
		return _G[script][go]	
	end

	return nil
end

function engine.current()
	return engine.data(_go_.current(), _script_.current())
end

engine.go = {}
engine.script = {}
engine.cam2d = {}
engine.cam3d = {}
engine.math = {}
engine.command = {}
engine.dir = {}
engine.draw2d = {}
engine.draw3d = {}
engine.framebuffer = {}
engine.generator = {}
engine.img = {}
engine.input = {}
engine.shader = {}
engine.texture = {}
engine.time = {}
engine.vertex = {}
engine.window = {}
engine.audio = {}
engine.font = {}
engine.object = {}
engine.renderer = {}

function engine.go.current()
	return _go_.current()
end

function engine.go.create(table)
	return _go_.create(table)
end

function engine.go.destroy(id)
	return _go_.destroy(id)	
end

function engine.go.create_copy(goId, newFatherId)
	return _go_.create_copy(goId, newFatherId)
end

function engine.go.get(id)
	return _go_.get(id)
end

function engine.go.set_name(goId, name)
	return _go_.set_name(goId, name)
end

function engine.go.set_active(goId, active)
	return _go_.set_active(goId, active)
end

function engine.go.change_father(goId, fatherId)
	return _go_.change_father(goId, fatherId)
end

function engine.go.change_index(goId, displacement)
	return _go_.change_index(goId, displacement)
end

function engine.go.load_scripts(goId)
	return _go_.load_scripts(goId)
end

function engine.go.set_persist_go(val)
	return _go_.set_persist_go(val)
end

function engine.go.set_persist_external_go(goId, val)
	return _go_.set_persist_external_go(goId, val)
end

function engine.go.inspect_go(goId)
	return _go_.inspect_go(goId)
end

function engine.go.get_inspected_go()
	return _go_.get_inspected_go()
end

function engine.go.find_all(goName)
    return _go_.find_all(goName)
end

function engine.script.current()
	return _script_.current()
end

function engine.script.get(goId, scriptName)
	return _script_.get(goId, scriptName)
end

function engine.script.add(goId, scriptName)
	return _script_.add(goId, scriptName)
end

function engine.script.find_all(scriptName)
	return _script_.find_all(scriptName)
end

function engine.script.set_active(goId, scriptName, val)
	return _script_.set_active(goId, scriptName, val)
end

function engine.script.destroy(goId, scriptName, remove)
	return _script_.destroy(goId, scriptName, remove)
end

function engine.script.change_index(goId, scriptName, index)
	return _script_.change_index(goId, scriptName, index)
end
 
function engine.script.displace_index(goId, scriptName, displacement)
	return _script_.displace_index(goId, scriptName, displacement)
end

function engine.script.set_persist_script(val)
	_script_.set_persist_script(val)
end

function engine.script.set_persist_script_data(dataname, val)
	_script_.set_persist_script_data(dataname, val)
end

function engine.script.set_show_script_data(dataname, val)
	_script_.set_show_script_data(dataname, val)
end

function engine.script.set_persist_ext_script(goId, scriptName, val)
	_script_.set_persist_ext_script(goId, scriptName, val)
end

function engine.script.set_persist_ext_script_data(goId, scriptName, dataName, val)
	_script_.set_persist_ext_script_data(goId, scriptName, dataName, val)
end

function engine.script.set_show_ext_script_data(goId, scriptName, dataName, val)
	_script_.set_show_ext_script_data(goId, scriptName, dataName, val)
end

function engine.cam2d.create(object)
	return _cam2d_.create(object)
end

function engine.cam2d.destroy(id)
	return _cam2d_.destroy(id)
end

function engine.cam2d.get(id)
	return _cam2d_.get(id)
end

function engine.cam2d.get_matrix(id)
	return _cam2d_.get_matrix(id)
end

function engine.cam2d.update(id, info)
	return _cam2d_.update(id, info)
end

function engine.cam2d.set_current(id)
	return _cam2d_.set_current(id)
end

function engine.cam2d.get_current()
	return _cam2d_.get_current()
end

function engine.cam3d.create(object)
	return _cam3d_.create(object)
end

function engine.cam3d.destroy(id)
	return _cam3d_.destroy(id)
end

function engine.cam3d.update(id, object)
	return _cam3d_.update(id, object)
end

function engine.cam3d.get(id)
	return _cam3d_.get(id)
end

function engine.cam3d.translate(id, object)
	return _cam3d_.translate(id, object)
end

function engine.cam3d.translate_abs(id, object)
	return _cam3d_.translate_abs(id, object)
end

function engine.cam3d.rotate(id, object)
	return _cam3d_.rotate(id, object)
end

function engine.cam3d.get_view_matrix(id)
	return _cam3d_.get_view_matrix(id)
end

function engine.cam3d.get_projection_matrix(id)
	return _cam3d_.get_projection_matrix(id)
end

function engine.cam3d.set_current(id)
	return _cam3d_.set_current(id)
end

function engine.cam3d.get_current()
	return _cam3d_.get_current()
end

function engine.draw2d.rect(object)
	return _draw2d_.rect(object)
end

function engine.draw2d.circle(object)
	return _draw2d_.circle(object)
end

function engine.draw2d.triangle(object)
	return _draw2d_.triangle(object)
end

function engine.draw2d.line(object)
	return _draw2d_.line(object)
end

function engine.draw2d.point(object)
	return _draw2d_.point(object)
end

function engine.draw2d.texture(object)
	return _draw2d_.texture(object)
end

function engine.draw2d.frame(id)
	return _draw2d_.frame(id)
end

function engine.draw3d.cube(object)
	return _draw3d_.cube(object)
end

function engine.draw3d.sphere(object)
	return _draw3d_.sphere(object)
end

function engine.draw3d.point(object)
	return _draw3d_.point(object)
end

function engine.draw3d.line(object)
	return _draw3d_.line(object)
end

function engine.draw3d.rect(object)
	return _draw3d_.rect(object)
end

function engine.draw3d.triangle(object)
	return _draw3d_.triangle(object)
end

function engine.draw3d.circle(object)
	return _draw3d_.circle(object)
end

function engine.dir.read_file(file_name) 
	return _dir_.read_file(file_name) 
end

function engine.dir.create_file(file_name, content) 
	return _dir_.create_file(file_name, content) 
end

function engine.dir.create_folder(folder_name) 
	return _dir_.create_folder(folder_name) 
end

function engine.dir.move(from, to) 
	return _dir_.move(from, to) 
end

function engine.dir.copy(from, to) 
	return _dir_.copy(from, to) 
end

function engine.dir.delete(path) 
	return _dir_.delete(path) 
end

function engine.dir.is_file(path) 
	return _dir_.is_file(path) 
end

function engine.dir.is_dir(path) 
	return _dir_.is_dir(path) 
end

function engine.dir.exists(path) 
	return _dir_.exists(path) 
end

function engine.dir.get_current_path() 
	return _dir_.get_current_path() 
end

function engine.dir.get_base_path() 
	return _dir_.get_base_path() 
end

function engine.dir.get_assets_path() 
	return _dir_.get_assets_path() 
end

function engine.dir.get_logs_path() 
	return _dir_.get_logs_path() 
end

function engine.dir.list_dir(path) 
	return _dir_.list_dir(path) 
end

function engine.dir.reduce_path_by(path) 
	return _dir_.reduce_path_by(path) 
end

function engine.dir.get_file_name_ext(path) 
	return _dir_.get_file_name_ext(path) 
end

function engine.dir.get_path_or_file_name(path) 
	return _dir_.get_path_or_file_name(path) 
end

function engine.dir.get_file_name_no_ext(path) 
	return _dir_.get_file_name_no_ext(path) 
end

function engine.dir.exec(command) 
	return _dir_.exec(command) 
end

function engine.input.get_key(key) 
	return _input_.get_key(key) 
end

function engine.input.get_mod(key) 
	return _input_.get_mod(key) 
end

function engine.input.get_mouse_pos() 
	return _input_.get_mouse_pos() 
end

function engine.input.get_cam_mouse_pos() 
	return _input_.get_cam_mouse_pos() 
end

function engine.input.get_mouse_variation() 
	return _input_.get_mouse_variation() 
end

function engine.input.get_mouse_button(key) 
	return _input_.get_mouse_button(key) 
end

function engine.img.open(path)
	return _img_.open(path)
end

function engine.command.enable_vsync() 
	return _command_.enable_vsync() 
end

function engine.command.disable_vsync() 
	return _command_.disable_vsync() 
end

function engine.command.enable_depth_testing() 
	return _command_.enable_depth_testing() 
end

function engine.command.disable_depth_testing() 
	return _command_.disable_depth_testing() 
end

function engine.command.set_depth_testing_mode(mode) 
	return _command_.set_depth_testing_mode(mode) 
end

function engine.command.enable_culling_face() 
	return _command_.enable_culling_face() 
end

function engine.command.disable_culling_face() 
	return _command_.disable_culling_face() 
end

function engine.command.set_culling_face_mode(mode) 
	return _command_.set_culling_face_mode(mode) 
end

function engine.command.set_primitive_line_size(size) 
	return _command_.set_primitive_line_size(size) 
end

function engine.command.set_primitive_point_size(size) 
	return _command_.set_primitive_point_size(size) 
end

function engine.command.set_polygon_draw_mode(mode) 
	return _command_.set_polygon_draw_mode(mode) 
end

function engine.command.enable_blending() 
	return _command_.enable_blending() 
end

function engine.command.disable_blending() 
	return _command_.disable_blending() 
end

function engine.shader.create(table)
	return _shader_.create(table)
end

function engine.shader.create_raw(table)
	return _shader_.create_raw(table)
end

function engine.shader.destroy(id)
	return _shader_.destroy(id)
end

function engine.shader.activate(id)
	return _shader_.activate(id)
end

function engine.shader.set_bool(id, name, value)
	return _shader_.set_bool(id, name, value)
end

function engine.shader.set_int(id, name, value)
	return _shader_.set_int(id, name, value)
end

function engine.shader.set_float(id, name, value)
	return _shader_.set_float(id, name, value)
end

function engine.shader.set_xy(id, name, x, y)
	return _shader_.set_xy(id, name, x, y)
end

function engine.shader.set_xyz(id, name, x, y, z)
	return _shader_.set_xyz(id, name, x, y, z)
end

function engine.shader.set_xyzw(id, name, x, y, z, w)
	return _shader_.set_xyzw(id, name, x, y, z, w)
end

function engine.shader.set_vec2(id, name, value)
	return _shader_.set_vec2(id, name, value)
end

function engine.shader.set_vec3(id, name, value)
	return _shader_.set_vec3(id, name, value)
end

function engine.shader.set_vec4(id, name, value)
	return _shader_.set_vec4(id, name, value)
end

function engine.shader.set_mat2(id, name, mat2)
	return _shader_.set_mat2(id, name, mat2)
end

function engine.shader.set_mat3(id, name, mat3)
	return _shader_.set_mat3(id, name, mat3)
end

function engine.shader.set_mat4(id, name, mat4)
	return _shader_.set_mat4(id, name, mat4)
end

function engine.shader.unactive_all() 
	return _shader_.unactive_all()
end

function engine.texture.create_empty(table)
	return _texture_.create_empty(table)
end

function engine.texture.create_multi_sampled(table)
	return _texture_.create_multi_sampled(table)
end

function engine.texture.create(table)
	return _texture_.create(table)
end

function engine.texture.get_info(id)
	return _texture_.get_info(id)
end

function engine.texture.destroy(id)
	return _texture_.destroy(id)
end

function engine.texture.active(id, slot)
	return _texture_.active(id, slot)
end

function engine.texture.disabletextureunit(slot)
	return _texture_.disabletextureunit(slot)
end

function engine.framebuffer.create(table)
	return _framebuffer_.create(table)
end

function engine.framebuffer.destroy(id)
	return _framebuffer_.destroy(id)
end

function engine.framebuffer.active(id)
	return _framebuffer_.active(id)
end

function engine.framebuffer.get_attachments_size(id)
	return _framebuffer_.get_attachments_size(id)
end

function engine.framebuffer.get_attachment(id, index)
	return _framebuffer_.get_attachment(id, index)
end

function engine.framebuffer.clear(color)
	return _framebuffer_.clear(color)
end

function engine.framebuffer.set_clear_modes(modes)
	return _framebuffer_.set_clear_modes(modes)
end

function engine.framebuffer.set_viewport(viewport)
	return _framebuffer_.set_viewport(viewport)
end

function engine.framebuffer.active_none()
	return _framebuffer_.active_none() 
end

function engine.vertex.create(vertexData, indexData)
	return _vertex_.create(vertexData, indexData)
end

function engine.vertex.get_info(id)
	return _vertex_.get_info(id)
end

function engine.vertex.destroy(id)
	return _vertex_.destroy(id)
end

function engine.vertex.activate(id)
	return _vertex_.activate(id)
end

function engine.vertex.draw(id, drawMode)
	return _vertex_.draw(id, drawMode)
end

function engine.vertex.modify(id, modifyData)
	return _vertex_.modify(id, modifyData)
end

function engine.generator.gen_2d_point(dataUse)
	return _generator_.gen_2d_point(dataUse)
end

function engine.generator.gen_2d_line(dataUse, filled)
	return _generator_.gen_2d_line(dataUse, filled)
end

function engine.generator.gen_2d_circle(dataUse, filled, segments)
	return _generator_.gen_2d_circle(dataUse, filled, segments)
end

function engine.generator.gen_2d_triangle(dataUse, filled)
	return _generator_.gen_2d_triangle(dataUse, filled)
end

function engine.generator.gen_3d_circle(dataUse, filled, segments)
	return _generator_.gen_3d_circle(dataUse, filled, segments)
end

function engine.generator.gen_3d_cube(dataUse, filled)
	return _generator_.gen_3d_cube(dataUse, filled)
end

function engine.generator.gen_3d_line(dataUse)
	return _generator_.gen_3d_line(dataUse)
end

function engine.generator.gen_3d_point(dataUse)
	return _generator_.gen_3d_point(dataUse)
end

function engine.generator.gen_3d_rect(dataUse, filled)
	return _generator_.gen_3d_rect(dataUse, filled)
end

function engine.generator.gen_3d_sphere(dataUse, filled, segments)
	return _generator_.gen_3d_sphere(dataUse, filled, segments)
end

function engine.generator.gen_3d_triangle(dataUse, filled)
	return _generator_.gen_3d_triangle(dataUse, filled)
end

function engine.time.get_timestamp()
	return _time_.get_timestamp()
end

function engine.time.get_datetime() 
	return _time_.get_datetime()
end

function engine.get_mode() 
	return _engine_.get_mode()
end

function engine.get_fps() 
	return _engine_.get_fps()
end

function engine.get_frametime() 
	return _engine_.get_frametime()
end

function engine.stop() 
	return _engine_.stop()
end

function engine.restart() 
	return _engine_.restart()
end

function engine.is_editor_focused()
	return _engine_.is_editor_focused()
end

function engine.window.get_window_size() 
	return _window_.get_window_size() 
end

function engine.window.get_editor_window_size()
	return _window_.get_editor_window_size()
end

function engine.window.get_window_limits() 
	return _window_.get_window_limits() 
end

function engine.audio.create_2d(path) 
	return _audio_.create_2d(path) 
end

function engine.audio.create_3d(path) 
	return _audio_.create_3d(path) 
end

function engine.audio.destroy(id) 
	return _audio_.destroy(id) 
end

function engine.audio.pause(id) 
	return _audio_.pause(id) 
end

function engine.audio.resume(id) 
	return _audio_.resume(id) 
end

function engine.audio.restart(id) 
	return _audio_.restart(id) 
end

function engine.audio.stop(id) 
	return _audio_.stop(id) 
end

function engine.audio.is_finished(id) 
	return _audio_.is_finished(id) 
end

function engine.audio.get_position(id) 
	return _audio_.get_position(id) 
end

function engine.audio.set_position(id, vec3) 
	return _audio_.set_position(id, vec3) 
end

function engine.audio.set_velocity(id, vec3) 
	return _audio_.set_velocity(id, vec3) 
end

function engine.audio.get_velocity(id) 
	return _audio_.get_velocity(id) 
end

function engine.audio.set_loop(id, bool) 
	return _audio_.set_loop(id, bool) 
end

function engine.audio.get_loop(id) 
	return _audio_.get_loop(id) 
end

function engine.audio.set_min_distance(id, number) 
	return _audio_.set_min_distance(id, number) 
end

function engine.audio.get_min_distance(id) 
	return _audio_.get_min_distance(id) 
end

function engine.audio.set_max_distance(id, number) 
	return _audio_.set_max_distance(id, number) 
end

function engine.audio.get_max_distance(id) 
	return _audio_.get_max_distance(id) 
end

function engine.audio.set_pan(id, number) 
	return _audio_.set_pan(id, number) 
end

function engine.audio.get_pan(id) 
	return _audio_.get_pan(id) 
end

function engine.audio.set_speed(id, number) 
	return _audio_.set_speed(id, number) 
end

function engine.audio.get_speed(id) 
	return _audio_.get_speed(id) 
end

function engine.audio.get_length(id) 
	return _audio_.get_length(id) 
end

function engine.audio.set_play_position(id, number) 
	return _audio_.set_play_position(id, number) 
end

function engine.audio.get_play_position(id) 
	return _audio_.get_play_position(id) 
end

function engine.audio.set_volume(id, number) 
	return _audio_.set_volume(id, number) 
end

function engine.audio.get_volume(id) 
	return _audio_.get_volume(id) 
end

function engine.audio.stop_all_audios() 
	return _audio_.stop_all_audios() 
end

function engine.audio.set_listener_position(vec3) 
	return _audio_.set_listener_position(vec3) 
end

function engine.font.create(path, width, height) 
	return _font_.create(path, width, height) 
end

function engine.font.destroy(id) 
	return _font_.destroy(id) 
end

function engine.font.get_position(id)
	return _font.get_position(id)
end

function engine.font.set_position(id, pos)
	return _font_.set_position(id, pos)
end

function engine.font.get_scale(id) 
	return _font_.get_scale(id) 
end

function engine.font.set_scale(id, scale)
	return _font_.set_scale(id, scale)
end

function engine.font.get_color(id) 
	return _font_.get_color(id) 
end

function engine.font.set_color(id, color) 
	return _font_.set_color(id, color) 
end

function engine.font.get_text_size(id) 
	return _font_.get_text_size(id) 
end

function engine.font.get_text(id) 
	return _font_.get_text(id) 
end

function engine.font.set_text(id, text) 
	return _font_.set_text(id, text) 
end

function engine.font.draw(id) 
	return _font_.draw(id) 	
end

function engine.math.random() 
	return _math_.random() 
end

function engine.math.make_mat4() 
	return _math_.make_mat4() 
end

function engine.math.make_identity_mat4() 
	return _math_.make_identity_mat4() 
end

function engine.math.translate(mat4, vec3) 
	return _math_.translate(mat4, vec3) 
end

function engine.math.rotate(mat4, vec3, angle) 
	return _math_.rotate(mat4, vec3, angle) 
end

function engine.math.scale(mat4, vec3) 
	return _math_.scale(mat4, vec3) 
end

function engine.math.multiply(mat4, vec4) 
	return _math_.multiply(mat4, vec4) 
end

function engine.math.mag_vec2(vec2) 
	return _math_.mag_vec2(vec2) 
end

function engine.math.normalize_vec2(vec2) 
	return _math_.normalize_vec2(vec2) 
end

function engine.math.mag_vec3(vec3) 
	return _math_.mag_vec3(vec3) 
end

function engine.math.normalize_vec3(vec3) 
	return _math_.normalize_vec3(vec3) 
end

function engine.object.open(path) 
	return _object_.open(path) 
end

function engine.object.destroy(id) 
	return _object_.destroy(id) 
end

function engine.object.get(id) 
	return _object_.get(id) 
end

function engine.object.get_meshes(id) 
	return _object_.get_meshes(id) 
end

function engine.object.get_materials(id) 
	return _object_.get_materials(id) 
end

function engine.renderer.render_obj(id) 
	return _renderer_.render_obj(id) 
end

-- Enums Table
engine.enums = {
   camera_movement = 
   {
        forward = "FORWARD",
        backward = "BACKWARD",
        left = "LEFT",
        right = "RIGHT",
        up = "UP",
        down = "DOWN",
    },

    keyboard_key = 
    {
        unknown = "UNKNOWN",
        space = "SPACE",
        apostrophe = "APOSTROPHE",
        comma = "COMMA",
        minus = "MINUS",
        period = "PERIOD",
        slash = "SLASH",
        semicolon = "SEMICOLON",
        equal = "EQUAL",
        ["0"] = "0",
        ["1"] = "1",
        ["2"] = "2",
        ["3"] = "3",
        ["4"] = "4",
        ["5"] = "5",
        ["6"] = "6",
        ["7"] = "7",
        ["8"] = "8",
        ["9"] = "9",
        A = "A",
        B = "B",
        C = "C",
        D = "D",
        E = "E",
        F = "F",
        G = "G",
        H = "H",
        I = "I",
        J = "J",
        K = "K",
        L = "L",
        M = "M",
        N = "N",
        O = "O",
        P = "P",
        Q = "Q",
        R = "R",
        S = "S",
        T = "T",
        U = "U",
        V = "V",
        W = "W",
        X = "X",
        Y = "Y",
        Z = "Z",
        left_bracket = "LEFT_BRACKET",
        backslash = "BACKSLASH",
        right_bracket = "RIGHT_BRACKET",
        grave_accent = "GRAVE_ACCENT",
        world_1 = "WORLD_1",
        world_2 = "WORLD_2",
        escape = "ESCAPE",
        enter = "ENTER",
        tab = "TAB",
        backspace = "BACKSPACE",
        insert = "INSERT",
        delete = "DELETE",
        right = "RIGHT",
        left = "LEFT",
        down = "DOWN",
        up = "UP",
        page_up = "PAGE_UP",
        page_down = "PAGE_DOWN",
        home = "HOME",
        ["end"] = "END",
        caps_lock = "CAPS_LOCK",
        scroll_lock = "SCROLL_LOCK",
        num_lock = "NUM_LOCK",
        print_screen = "PRINT_SCREEN",
        pause = "PAUSE",
        f1 = "F1",
        f2 = "F2",
        f3 = "F3",
        f4 = "F4",
        f5 = "F5",
        f6 = "F6",
        f7 = "F7",
        f8 = "F8",
        f9 = "F9",
        f10 = "F10",
        f11 = "F11",
        f12 = "F12",
        f13 = "F13",
        f14 = "F14",
        f15 = "F15",
        f16 = "F16",
        f17 = "F17",
        f18 = "F18",
        f19 = "F19",
        f20 = "F20",
        f21 = "F21",
        f22 = "F22",
        f23 = "F23",
        f24 = "F24",
        f25 = "F25",
        kp_0 = "KP_0",
        kp_1 = "KP_1",
        kp_2 = "KP_2",
        kp_3 = "KP_3",
        kp_4 = "KP_4",
        kp_5 = "KP_5",
        kp_6 = "KP_6",
        kp_7 = "KP_7",
        kp_8 = "KP_8",
        kp_9 = "KP_9",
        kp_decimal = "KP_DECIMAL",
        kp_divide = "KP_DIVIDE",
        kp_multiply = "KP_MULTIPLY",
        kp_subtract = "KP_SUBTRACT",
        kp_add = "KP_ADD",
        kp_enter = "KP_ENTER",
        kp_equal = "KP_EQUAL",
        left_shift = "LEFT_SHIFT",
        left_control = "LEFT_CONTROL",
        left_alt = "LEFT_ALT",
        left_super = "LEFT_SUPER",
        right_shift = "RIGHT_SHIFT",
        right_control = "RIGHT_CONTROL",
        right_alt = "RIGHT_ALT",
        right_super = "RIGHT_SUPER",
        menu = "MENU",
    },

    input_action = 
    {
        press = "PRESS",
        release = "RELEASE",
        none = "NONE",
    },

    key_modifier = 
    {
        shift = "SHIFT",
        control = "CONTROL",
        alt = "ALT",
        super = "SUPER",
        caps_lock = "CAPS_LOCK",
        num_lock = "NUM_LOCK",
        unknown = "UNKNOWN",
    },

   mouse_button = 
   {
        left = "LEFT",
        right = "RIGHT",
        middle = "MIDDLE",
        ["1"] = "1",
        ["2"] = "2",
        ["3"] = "3",
        ["4"] = "4",
        ["5"] = "5",
        ["6"] = "6",
        ["7"] = "7",
        ["8"] = "8",
    },

    data_use_key =
    {
        stream_draw = "STREAM_DRAW",
        stream_read = "STREAM_READ",
        stream_copy = "STREAM_COPY",
        static_draw = "STATIC_DRAW",
        static_read = "STATIC_READ",
        static_copy = "STATIC_COPY",
        dynamic_read = "DYNAMIC_READ",
        dynamic_copy = "DYNAMIC_COPY",
    },

    polygon_mode = 
    {
        point = "POINT",
        line = "LINE",
        fill = "FILL",
    },

    depth_testing_mode =
    {
        always = "ALWAYS",
        never = "NEVER",
        less = "LESS",
        lequal = "LEQUAL",
        greater = "GREATER",
        notequal = "NOTEQUAL",
        gequal = "GEQUAL",
    },

    culling_face_mode =
    {
        back = "BACK",
        front = "FRONT",
        both = "BOTH",
    },

    texture_internal_format = 
    {
        depth_component = "DEPTH_COMPONENT",
        depth_stencil = "DEPTH_STENCIL",
        r = "R",
        rg = "RG",
        rgb = "RGB",
        rgba = "RGBA",
        r8 = "R8",
        r8_snorm = "R8_SNORM",
        r16 = "R16",
        r16_snorm = "R16_SNORM",
        rg8 = "RG8",
        rg8_snorm = "RG8_SNORM",
        rg16 = "RG16",
        rg16_snorm = "RG16_SNORM",
        r3_g3_b2 = "R3_G3_B2",
        rgb4 = "RGB4",
        rgb5 = "RGB5",
        rgb8_snorm = "RGB8_SNORM",
        rgb10 = "RGB10",
        rgb12 = "RGB12",
        rgba2 = "RGBA2",
        rgba4 = "RGBA4",
        rgb5_a1 = "RGB5_A1",
        rgba8 = "RGBA8",
        rgba8_snorm = "RGBA8_SNORM",
        rgb10_a2 = "RGB10_A2",
        rgb10_a2ui = "RGB10_A2UI",
        rgba12 = "RGBA12",
        rgba16 = "RGBA16",
        srgb8 = "SRGB8",
        srgb8_alpha8 = "SRGB8_ALPHA8",
        r16f = "R16F",
        rg16f = "RG16F",
        rgb16f = "RGB16F",
        rgba16f = "RGBA16F",
        r32f = "R32F",
        rg32f = "RG32F",
        rgb32f = "RGB32F",
        rgba32f = "RGBA32F",
        r11f_g11f_b10f = "R11F_G11F_B10F",
        rgb9_e5 = "RGB9_E5",
        r8i = "R8I",
        r8ui = "R8UI",
        r16i = "R16I",
        r16ui = "R16UI",
        r32i = "R32I",
        r32ui = "R32UI",
        rg8i = "RG8I",
        rg8ui = "RG8UI",
        rg16i = "RG16I",
        rg16ui = "RG16UI",
        rg32i = "RG32I",
        rg32ui = "RG32UI",
        rgb8i = "RGB8I",
        rgb8ui = "RGB8UI",
        rgb16i = "RGB16I",
        rgb16ui = "RGB16UI",
        rgb32i = "RGB32I",
        rgb32ui = "RGB32UI",
        rgba8i = "RGBA8I",
        rgba8ui = "RGBA8UI",
        rgba16i = "RGBA16I",
        rgba16ui = "RGBA16UI",
        rgba32i = "RGBA32I",
        rgba32ui = "RGBA32UI",
        compressed_red = "COMPRESSED_RED",
        compressed_rg = "COMPRESSED_RG",
        compressed_rgb = "COMPRESSED_RGB",
        compressed_rgba = "COMPRESSED_RGBA",
        compressed_srgb = "COMPRESSED_SRGB",
        compressed_srgb_alpha = "COMPRESSED_SRGB_ALPHA",
        compressed_red_rgtc1 = "COMPRESSED_RED_RGTC1",
        compressed_signed_red_rgtc1 = "COMPRESSED_SIGNED_RED_RGTC1",
        compressed_rg_rgtc2 = "COMPRESSED_RG_RGTC2",
        compressed_signed_rg_rgtc2 = "COMPRESSED_SIGNED_RG_RGTC2",
    },

    texture_format =
    {
        r = "R",
        rg = "RG",
        rgb = "RGB",
        bgr = "BGR",
        rgba = "RGBA",
        bgra = "BGRA",
        red_integer = "RED_INTEGER",
        rg_integer = "RG_INTEGER",
        rgb_integer = "RGB_INTEGER",
        bgr_integer = "BGR_INTEGER",
        rgba_integer = "RGBA_INTEGER",
        bgra_integer = "BGRA_INTEGER",
        stencil_index = "STENCIL_INDEX",
        depth_component = "DEPTH_COMPONENT",
        depth_stencil = "DEPTH_STENCIL",
    },

    texture_pixel_format =
    {
        unsigned_byte = "UNSIGNED_BYTE",
        byte = "BYTE",
        unsigned_short = "UNSIGNED_SHORT",
        short = "SHORT",
        unsigned_int = "UNSIGNED_INT",
        int = "INT",
        half_float = "HALF_FLOAT",
        float = "FLOAT",
        unsigned_byte_3_3_2 = "UNSIGNED_BYTE_3_3_2",
        unsigned_byte_2_3_3_rev = "UNSIGNED_BYTE_2_3_3_REV",
        unsigned_short_5_6_5 = "UNSIGNED_SHORT_5_6_5",
        unsigned_short_5_6_5_rev = "UNSIGNED_SHORT_5_6_5_REV",
        unsigned_short_4_4_4_4 = "UNSIGNED_SHORT_4_4_4_4",
        unsigned_short_4_4_4_4_rev = "UNSIGNED_SHORT_4_4_4_4_REV",
        unsigned_short_5_5_5_1 = "UNSIGNED_SHORT_5_5_5_1",
        unsigned_short_1_5_5_5_rev = "UNSIGNED_SHORT_1_5_5_5_REV",
        unsigned_int_8_8_8_8 = "UNSIGNED_INT_8_8_8_8",
        unsigned_int_8_8_8_8_rev = "UNSIGNED_INT_8_8_8_8_REV",
        unsigned_int_10_10_10_2 = "UNSIGNED_INT_10_10_10_2",
        unsigned_int_2_10_10_10_rev = "UNSIGNED_INT_2_10_10_10_REV",
    },

    minifying_filter = 
    {
        only_nearest = "ONLY_NEAREST",
        only_linear = "ONLY_LINEAR",
        nearest_mipmap_nearest = "NEAREST_MIPMAP_NEAREST",
        linear_mipmap_nearest = "LINEAR_MIPMAP_NEAREST",
        nearest_mipmap_linear = "NEAREST_MIPMAP_LINEAR",
        linear_mipmap_linear = "LINEAR_MIPMAP_LINEAR",
    },

    magnification_filter = 
    {
        nearest = "NEAREST",
        linear = "LINEAR",
    },

    texture_wrap = 
    {
        clamp_to_edge = "CLAMP_TO_EDGE",
        clamp_to_border = "CLAMP_TO_BORDER",
        mirrored_repeat = "MIRRORED_REPEAT",
        repeated = "REPEATED",
        mirror_clamp_to_edge = "MIRROR_CLAMP_TO_EDGE",
    },

    vertex_buffer_type =
    {
        byte = "BYTE",
        ubyte = "UBYTE",
        short = "SHORT",
        ushort = "USHORT",
        int = "INT",
        uint = "UINT",
        half_float = "HALF_FLOAT",
        float = "FLOAT",
        double = "DOUBLE",
        int_2_10_10_10_rev = "INT_2_10_10_10_REV",
        uint_2_10_10_10_rev = "UINT_2_10_10_10_REV",
    },

    drawing_type =
    {
        points = "POINTS",
        lines = "LINES",
        line_loop = "LINE_LOOP",
        line_strip = "LINE_STRIP",
        triangles = "TRIANGLES",
        triangle_strip = "TRIANGLE_STRIP",
        triangle_fan = "TRIANGLE_FAN",
        line_adjacency = "LINE_ADJACENCY",
        line_strip_adjacency = "LINE_STRIP_ADJACENCY",
        triangles_adjacency = "TRIANGLES_ADJACENCY",
        triangle_strip_adjacency = "TRIANGLE_STRIP_ADJACENCY",
    },

    render_buffer_attachment_type =
    {
        dont_use = "DONT_USE",
        depth_attachment = "DEPTH_ATTACHMENT",
        stencil_attachment = "STENCIL_ATTACHMENT",
        depth_stencil_attachment = "DEPTH_STENCIL_ATTACHMENT",
    },

    render_buffer_format =
    {
        depth_component16 = "DEPTH_COMPONENT16",
        depth_component24 = "DEPTH_COMPONENT24",
        depth_component32f = "DEPTH_COMPONENT32F",
        depth24_stencil8 = "DEPTH24_STENCIL8",
        depth32f_stencil8 = "DEPTH32F_STENCIL8",
        stencil_index8 = "STENCIL_INDEX8",
    },

    project_mode =
    {
        play = "PLAY",
        editor = "EDITOR",
    },

    script_state_enum =
    {
       	to_load = "TO_LOAD", 
		to_start = "TO_START", 
		updating = "UPDATING", 
		to_destroy = "TO_DESTROY",
		destroyed = "DESTROYED"
    },
}