extends Node

@export var start_unit_types : Array[UnitType]
@export var start_categories : Array[String]
@export var start_formations : Array[Formation]

@onready var unit_scene : Node = $CanvasLayer/HBoxContainer/Scenes/UnitScene
@onready var formation_scene : Node = $CanvasLayer/HBoxContainer/Scenes/Formations
@onready var formation_preview : Node = $FormationPreview

func _ready() -> void:
	FormationEditor.formations = start_formations
	FormationEditor.categories = start_categories
	FormationEditor.unit_types = start_unit_types
	FormationEditor.unit_types_changed.emit()
	FormationEditor.categories_changed.emit()
	FormationEditor.formations_changed.emit()

func _on_characters_pressed() -> void:
	unit_scene.visible = true
	formation_scene.visible = false
	formation_preview.visible = false

func _on_formations_pressed() -> void:
	unit_scene.visible = false
	formation_scene.visible = true
	formation_preview.visible = true
