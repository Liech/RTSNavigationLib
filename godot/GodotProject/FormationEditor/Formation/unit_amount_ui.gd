extends MarginContainer

var ui_element := preload("res://FormationEditor/Formation/unit_type_element.tscn")

@onready var list : VBoxContainer = $M/VBoxContainer/Scroll/UnitTypeAmounts

func _ready() -> void:
	FormationEditor.unit_types_changed.connect(update_unit_types)
	update_unit_types()
	
func update_unit_types() -> void:
	for x in list.get_children():
		list.remove_child(x)
		x.queue_free()
	var counter := 0
	for x in FormationEditor.unit_types:
		var element := ui_element.instantiate()
		element.index = counter
		counter += 1
		list.add_child(element)
