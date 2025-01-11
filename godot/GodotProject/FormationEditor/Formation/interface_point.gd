class_name interface_point extends Button




func _on_pressed() -> void:
	print("Pressed")


func _on_mouse_entered() -> void:
	modulate = Color.BLACK


func _on_mouse_exited() -> void:
	modulate = Color.WHITE
