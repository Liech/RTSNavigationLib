class_name FormationPreviewUnit extends Node2D

var type : UnitType

func _ready() -> void:
	$Circle.modulate = type.color
	$Emoji.text = type.emoji
	scale = Vector2(1,1)*type.size
