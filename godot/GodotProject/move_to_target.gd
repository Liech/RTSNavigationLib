extends Sprite2D

var target : Node2D = null;
var speed : float = 0.1;

func _process(delta: float) -> void:
	if target:
		position += (target.position-position).normalized() * speed

func set_target(target_ : Node2D) -> void:
	target = target_;
