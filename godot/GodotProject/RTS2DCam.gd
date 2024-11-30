extends Camera2D

@export var move_speed : float = 800
@export var zoom_speed : float = 0.1

func _process(delta : float) -> void:
	var x : float = Input.get_axis("ui_left", "ui_right")
	var y : float = Input.get_axis("ui_down", "ui_up")
	global_position += (Vector2.RIGHT * x + Vector2.UP * y) * delta * move_speed * (1.0/zoom.length())
	
	if (Input.is_action_just_released("zoom_in")):
		zoom_on(get_global_mouse_position(),1+zoom_speed)
	if (Input.is_action_just_released("zoom_out")):
		zoom_on(get_global_mouse_position(),1-zoom_speed)

	
	print(get_global_view_rect())

func _input(event: InputEvent) -> void:
	var ev := event as InputEventMouseMotion
	if ev and Input.is_action_pressed("pan_active"):
		offset -= ev.relative * (1.0/zoom.length())
		

func get_global_view_rect() -> Rect2:
	var t := get_canvas_transform()
	var camera_rect := t.affine_inverse() * get_viewport_rect()
	return camera_rect

func zoom_on(location : Vector2, factor : float) ->void:
	var rect:=get_global_view_rect()
	offset += (rect.get_center()-location) * (1-factor)
	zoom *= factor
	
