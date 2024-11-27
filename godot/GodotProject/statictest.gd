extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	print(RTSNavigation.test_static(1,3));
	var result : Array[int] = RTSNavigation.usher([Vector2(0,0)],[Vector2(0,0)])
	print(result)

func _process(delta: float) -> void:
	pass
