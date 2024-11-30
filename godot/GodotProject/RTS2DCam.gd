extends Camera2D


const MOVE_SPEED = 400

func _process(delta : float) -> void:
	var x : float = Input.get_axis("ui_left", "ui_right")
	var y : float = Input.get_axis("ui_down", "ui_up")
	global_position += Vector2.RIGHT * delta * MOVE_SPEED * x + Vector2.UP * delta * MOVE_SPEED * y
	
	if (Input.is_action_just_released("zoom_in")):
		zoom_on(Vector2(0,0),1.05)
	if (Input.is_action_just_released("zoom_out")):
		zoom_on(Vector2(0,0),0.95)

func zoom_on(location : Vector2, factor : float) ->void:
	zoom *= factor
