extends Node

@export var start_unit_types : Array[UnitType]
@export var start_categories : Array[String]

func _ready() -> void:
	FormationEditor.categories = start_categories
	FormationEditor.unitTypes = start_unit_types
	FormationEditor.unit_types_changed.emit()
	FormationEditor.categories_changed.emit()
