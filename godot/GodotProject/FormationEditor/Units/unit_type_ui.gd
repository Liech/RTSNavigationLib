extends Node

var character_element := preload("res://FormationEditor/Units/character_ui.tscn")

@onready var list : FlowContainer = $M/UnitTypes/UnitList/Scroll/CharacterList

func _ready() -> void:
	FormationEditor.unit_types_changed.connect(unit_types_changed)
	unit_types_changed()

func unit_types_changed() -> void:
	while (list.get_child_count() < FormationEditor.unit_types.size()):
		var element := character_element.instantiate() as character_ui
		element.index = list.get_child_count()
		list.add_child(element)
