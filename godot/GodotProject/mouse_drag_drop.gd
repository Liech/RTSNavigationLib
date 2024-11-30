extends Area2D

var mouse_over : bool = false
var old_mouse_pos : Vector2;
var target : Node2D = null;
var speed : float = 1.1;
var draggin : bool = false

func _process(delta: float) -> void:
	var m := get_global_mouse_position()
	var pressed :=Input.is_action_pressed("mouse_click")
	if ((mouse_over or draggin) and pressed):
		global_position += m-old_mouse_pos
		draggin = true
	elif !pressed:
		draggin = false
	old_mouse_pos = m
	if target:
		position += (target.position-position).normalized() * speed
	
func _on_mouse_entered() -> void:
	mouse_over = true

func _on_mouse_exited() -> void:
	mouse_over = false

func set_target(target_ : Node2D) -> void:
	target = target_;
